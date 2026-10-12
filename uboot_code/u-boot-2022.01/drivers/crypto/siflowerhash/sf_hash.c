/*
 * Siflower Hareware Hash.
 */

#include <common.h>
#include <cpu_func.h>
#include <log.h>
#include <malloc.h>
#include <memalign.h>
#include <hw_sha.h>
#include <asm/cache.h>
#include <linux/errno.h>
#include <asm/io.h>
#include "secure_boot.h"

struct sha256_state {
	u64 count;
	u8 buf[64];
	u32 flag;
};

static inline u32 arm_readl(unsigned long addr)
{
	return (u32)readl(addr);
}

static inline void arm_writel(u32 value, unsigned long addr)
{
	writel(value, addr);
}

/* HW SHA256*/
static int sf_sha256_init(struct sha256_state **ctxp)
{

	struct sha256_state * hash_state;
	hash_state = malloc(sizeof(struct sha256_state));
	if (!hash_state)
		return -ENOMEM;

	arm_writel(0x1, SHA_CTRL_REG_ADDR);
	hash_state->count = 0;
	hash_state->flag = 0;

	*ctxp = hash_state;
	return 0;
}

static int sf_sha256_update(struct sha256_state *sctx, const u8 *data, __u32 len)
{
	unsigned int partial, done, i;
	const u8 *src;

	partial = sctx->count & 0x3f;
	sctx->count += len;
	done = 0;
	src = data;

	if ((partial + len) > 63) {
		if (partial) {
			done = -partial;
			memcpy(sctx->buf + partial, data, done + 64);
			src = sctx->buf;
		}

		do {
			const __be32 *_src = (const __be32 *)src;

			for (i = 0; i < 16; i++)
				arm_writel(__builtin_bswap32(_src[i]), PKT_SHA(i));

			arm_writel(sctx->flag ? 0xb : 0x7, SHA_CTRL_REG_ADDR);

			i = 0;
			while (!(arm_readl(SHA_STATUS_ADDR) & 0x1)) {
				if (i > 1000000)
					return -EIO;

				i++;
			}
			done += 64;
			src = data + done;
		} while (done + 63 < len);

		partial = 0;
	}
	memcpy(sctx->buf + partial, src, len - done);
	return 0;
}

static int sf_sha256_final(struct sha256_state *sctx, u8 *out)
{
	__be32 *dst = (__be32 *)out;
	__be64 bits;
	unsigned int index, pad_len;
	int i, ret;
	static const u8 padding[64] = {0x80};

	/* Save number of bits */
	bits = __builtin_bswap64(sctx->count << 3);

	/* Pad out to 56 mod 64. */
	index = sctx->count & 0x3f;
	pad_len = (index < 56) ? (56 - index) : ((64+56) - index);
	sctx->flag = 0;
	ret = sf_sha256_update(sctx, padding, pad_len);
	if (ret)
		return ret;

	/* Append length (before padding) */
	sctx->flag = 1;
	ret = sf_sha256_update(sctx, (const u8 *)&bits, sizeof(bits));
	if (ret)
		return ret;
	i = 0;
	while (!(arm_readl(SHA_STATUS_ADDR) & 0x3)) {
		if (i > 1000000)
			return -EIO;

		i++;
	}
	/* Store state in digest */
	for (i = 0; i < 8; i++)
		dst[i] = __builtin_bswap32(arm_readl(SHA_RESULT(i)));

	if(sctx != NULL)
		free(sctx);

	return 0;
}

static int sf_sha256(const u8 *data, size_t len, u8 *out)
{
	struct sha256_state *sctx;
	int ret;

	ret = sf_sha256_init(&sctx);
	if (ret){
		return ret;
	}

	ret = sf_sha256_update(sctx, data, len);
	if (ret){
		return ret;
	}

	return sf_sha256_final(sctx, out);
}

void hw_sha256(const unsigned char *pbuf, unsigned int buf_len,
			unsigned char *pout, unsigned int chunk_size)
{
	if (sf_sha256(pbuf, buf_len, pout))
		printf("sf was not setup properly or it is faulty\n");
}

int hw_sha_init(struct hash_algo *algo, void **ctxp)
{
	return sf_sha256_init((struct sha256_state **)ctxp);
}

int hw_sha_update(struct hash_algo *algo, void *ctx, const void *buf,
			    unsigned int size, int is_last)
{
	return sf_sha256_update(ctx, buf, size);
}

int hw_sha_finish(struct hash_algo *algo, void *ctx, void *dest_buf,
		     int size)
{
	return sf_sha256_final(ctx, dest_buf);
}