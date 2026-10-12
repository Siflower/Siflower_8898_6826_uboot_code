#include "lif_reg.h"
#include "lif_common.h"

char rcv_pkt1[ENH_RCV_BUFSIZE] = {0};
char rcv_pkt2[ENH_RCV_BUFSIZE] = {0};
char rcv_pkt3[ENH_RCV_BUFSIZE] = {0};
char rcv_pkt4[ENH_RCV_BUFSIZE] = {0};
extern struct XG_macContext g_xgmac_context;
extern struct XG_macContext g_gmac_context;
extern char TEST_PKT_ICMP[74];
uint32_t lif_get_dut(uint32_t register_addr)
{
	return CSR_REG_READ((uintptr_t)register_addr);
}

int32_t dma_read_interrupt_src(void)
{
#ifdef XG_DMA
    return CSR_REG_READ(REG_XGMAC_DMA_CH0_Status);
#else
	return CSR_REG_READ(REG_DWCXG_DMA_Status);
#endif
}

int32_t dma_wait_tx_irq_timeout(struct XG_macContext *gmacdev,int32_t timeout_us)
{
	int32_t wait_time_us = 0;
	int32_t dma_status_reg = dma_read_interrupt_src();
    printf("dma tx status=0x%x",dma_status_reg);
	while(!(dma_status_reg & DmaIntTxCompleted))
	{
		if(wait_time_us > timeout_us)
		{
			return -1;
		}
		mydl(1);
		wait_time_us += 100;
        dma_status_reg = dma_read_interrupt_src();
	}
    printf("dma tx status=0x%x",dma_status_reg);
#ifdef XG_DMA
    CSR_REG_WRITE(REG_XGMAC_DMA_CH0_Status,DmaIntTxCompleted);
    xgmac_get_tx_qptr(gmacdev,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
#else
	CSR_REG_WRITE(REG_DWCXG_DMA_Status,DmaIntTxCompleted);
    gmac_get_tx_qptr(gmacdev,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
#endif

	return 0;
}

int32_t dma_wait_rx_irq_timeout(uint32_t timeout_us)
{
	int wait_time_us = 0;
	uint32_t dma_status_reg = dma_read_interrupt_src();
   // printf("%s,%d:dma rx status=0x%x",__FUNCTION__,__LINE__,dma_status_reg);
	while(!(dma_status_reg & DmaIntRxCompleted))
	{
		if(wait_time_us > timeout_us)
		{
			return -1;
		}
		wait_time_us += 1;
        dma_status_reg = dma_read_interrupt_src();
	}
    printf("dma rx status=0x%x",dma_status_reg);
    CSR_REG_WRITE(REG_XGMAC_DMA_CH0_Status,DmaIntRxCompleted);
	return 0;

}

void mydl(unsigned int tm)
{
	unsigned int i = tm;
	for (; i != 0;) {
		asm volatile("");
		i--;
	}
}


void dma_disable_interrupt_all(void)
{
	CSR_REG_WRITE(REG_DWCXG_DMA_Interrupt, DmaIntDisable);
	return;
}

void dma_enable_interrupt(uint32_t interrupts)
{
	CSR_REG_WRITE(REG_DWCXG_DMA_Interrupt, interrupts);
	return;
}

#ifdef XG_DMA
void xgmac_dma_init(struct XG_macContext *gmacdev)
{
	xgmac_dma_reset();
	// set burst len
   	reg_set_bits(REG_XGMAC_DMA_BusMode,/*XG_DmaAAL |XG_DmaUNDEF |XG_DmaEAME*/ 1<<3 );
	// disable descriptor prefetch
	reg_set_bits(XGMAC_DMA_ADDR_BASE + 0x3044, 3<<30 ); // for rx
	reg_set_bits(XGMAC_DMA_ADDR_BASE + 0x3040, 3<<30 ); // for tx


    dma_setup_tx_desc_queue(gmacdev,gmacdev->TRANSMIT_DESC_SIZE,gmacdev->BUFFER_DESC_MODE);
	dma_setup_rx_desc_queue(gmacdev,gmacdev->RECEIVE_DESC_SIZE,gmacdev->BUFFER_DESC_MODE);

    xgmac_dma_set_tx_desc_ring_length((gmacdev->TRANSMIT_DESC_SIZE)*2 - 1);
    xgmac_dma_set_rx_desc_ring_length((gmacdev->RECEIVE_DESC_SIZE) - 1);
    xgmac_dma_init_tx_desc_base(gmacdev->TxDescDma);
    xgmac_dma_init_rx_desc_base(gmacdev->RxDescDma);
    xgmac_dma_init_tx_tail_desc_base(gmacdev->Last_TxDescDma+sizeof(XGMAC_DmaTXDesc));
    xgmac_dma_init_rx_tail_desc_base(gmacdev->Last_RxDescDma+sizeof(XGMAC_DmaRXDesc));
    xgmac_dma_enable_interrupt(XG_DmaTIE | XG_DmaTXSE | XG_DmaRSE | XG_DmaTBUE | XG_DmaRBUE | XG_DmaRSE | XG_DmaDDDE | XG_DmaFBEE | XG_DmaCDEE | XG_DmaAIE | XG_DmaNIE);

	xgmac_dma_set_brust_length(XG_DmaBurstLength32);
  //  xgmac_dma_set_desc_skip(XG_DmaDescriptorSkip2);
    xgmac_dma_set_rx_buffer_size(0x3ff);

    //	printf("%s,%d,REG_XGMAC_DMA_CH0_RX_Control=0x%x,value=0x%x",__FUNCTION__,__LINE__,REG_XGMAC_DMA_CH0_RX_Control,CSR_REG_READ(REG_XGMAC_DMA_CH0_RX_Control));
}

void xgmac_dma_set_rx_buffer_size(uint32_t size)
{
	uint32_t i = 0;
	for(i = 0; i < XGMAC_DMA_CH_NUM ; i++)
	{
		reg_set_bits(REG_XGMAC_DMA_CH0_RX_Control,size<<4);

	}
}

void xgmac_dma_reset(void)
{
	reg_set_bits(REG_XGMAC_DMA_Mode, DmaResetOn);

	while(TRUE)
	{
		if(0 == (CSR_REG_READ(REG_XGMAC_DMA_Mode) &  DmaResetOn) )
		{
			break;
		}
	}

}

void xgmac_dma_set_brust_length(uint32_t brustlength)
{
	uint32_t i = 0;
	for(i = 0; i < XGMAC_DMA_CH_NUM ; i++)
	{
		reg_set_bits(REG_XGMAC_DMA_CH0_TX_Control + i*0x80, brustlength);
   	    reg_set_bits(REG_XGMAC_DMA_CH0_RX_Control + i*0x80, brustlength);
	}
}

void xgmac_dma_set_desc_skip(uint32_t skip)
{
	uint32_t i = 0;
	for(i = 0; i < XGMAC_DMA_CH_NUM ; i++)
	{
		reg_set_bits(REG_XGMAC_DMA_CH0_Control, skip);
	}
}

void xgmac_dma_set_tx_desc_ring_length(uint32_t length)
{
	uint32_t i = 0;
	for(i = 0 ; i < XGMAC_DMA_CH_NUM ; i++)
	{
		CSR_REG_WRITE(REG_XGMAC_DMA_CH0_TX_Control2+i*0x80,length);
	}
//    printf("%s,%d,REG_XGMAC_DMA_CH0_TX_Control2=0x%x,value=0x%x",__FUNCTION__,__LINE__,REG_XGMAC_DMA_CH0_TX_Control2,CSR_REG_READ(REG_XGMAC_DMA_CH0_TX_Control2));

}

void xgmac_dma_set_rx_desc_ring_length(uint32_t length)
{
	uint32_t i = 0;
	for(i = 0 ; i < XGMAC_DMA_CH_NUM ; i++)
	{
		CSR_REG_WRITE(REG_XGMAC_DMA_CH0_RX_Control2+i*0x80,length);
	}
 //   printf("%s,%d,REG_XGMAC_DMA_CH0_RX_Control2=0x%x,value=0x%x",__FUNCTION__,__LINE__,REG_XGMAC_DMA_CH0_RX_Control2,CSR_REG_READ(REG_XGMAC_DMA_CH0_RX_Control2));
}

void xgmac_dma_init_tx_desc_base(uint32_t tx_dma_base)
{
	uint32_t i = 0;
	for(i = 0 ; i < XGMAC_DMA_CH_NUM ; i++)
	{
		reg_set_bits(REG_XGMAC_DMA_TxBaseAddr+i*0x80,tx_dma_base);
	}
//	printf("%s,%d,REG_XGMAC_DMA_TxBaseAddr=0x%x,value=0x%x",__FUNCTION__,__LINE__,REG_XGMAC_DMA_TxBaseAddr,CSR_REG_READ(REG_XGMAC_DMA_TxBaseAddr));
}

void xgmac_dma_init_rx_desc_base(uint32_t rx_dma_base)
{
	uint32_t i = 0;
	for(i = 0 ; i < XGMAC_DMA_CH_NUM ; i++)
	{
		reg_set_bits(REG_XGMAC_DMA_RxBaseAddr + i*0x80,rx_dma_base);
	}
 //   printf("%s,%d,REG_XGMAC_DMA_RxBaseAddr=0x%x,value=0x%x",__FUNCTION__,__LINE__,REG_XGMAC_DMA_RxBaseAddr,CSR_REG_READ(REG_XGMAC_DMA_RxBaseAddr));

}
void xgmac_dma_init_rx_tail_desc_base(uint32_t rx_tail_dma_base)
{
	uint32_t i = 0;
	for(i = 0 ; i < XGMAC_DMA_CH_NUM ; i++)
	{
		reg_set_bits(REG_XGMAC_DMA_RxTailAddr+0x80*i,rx_tail_dma_base);
	}
  //  printf("%s,%d,REG_XGMAC_DMA_RxTailAddr=0x%x,value=0x%x",__FUNCTION__,__LINE__,REG_XGMAC_DMA_RxTailAddr,CSR_REG_READ(REG_XGMAC_DMA_RxTailAddr));

}
void xgmac_dma_init_tx_tail_desc_base(uint32_t tx_tail_dma_base)
{
	uint32_t i = 0;
	for(i = 0 ; i < XGMAC_DMA_CH_NUM ; i++)
	{
		reg_set_bits(REG_XGMAC_DMA_TxTailAddr+0x80*i,tx_tail_dma_base);
	}
  //  printf("%s,%d,REG_XGMAC_DMA_TxTailAddr=0x%x,value=0x%x",__FUNCTION__,__LINE__,REG_XGMAC_DMA_TxTailAddr,CSR_REG_READ(REG_XGMAC_DMA_TxTailAddr));

}

void xgmac_dma_enable_interrupt(uint32_t interrupts)
{
	uint32_t i = 0;
	for(i = 0 ; i < XGMAC_DMA_CH_NUM ; i++)
	{
		reg_set_bits(REG_XGMAC_DMA_CH0_Interrupt_Enable + i*0x80,interrupts);
	}
//printf("%s,%d,REG_XGMAC_DMA_CH0_Interrupt_Enable=0x%x,value=0x%x",__FUNCTION__,__LINE__,REG_XGMAC_DMA_CH0_Interrupt_Enable,CSR_REG_READ(REG_XGMAC_DMA_CH0_Interrupt_Enable));
}

void xgmac_dma_enable_tx(BOOLEAN enable)
{
    reg_set_bits(REG_XGMAC_DMA_CH0_TX_Control,enable);
   // printf("%s,%d,REG_XGMAC_DMA_CH0_TX_Control=0x%x,value=0x%x",__FUNCTION__,__LINE__,REG_XGMAC_DMA_CH0_TX_Control,CSR_REG_READ(REG_XGMAC_DMA_CH0_TX_Control));
}
void xgmac_dma_disable_tx(void)
{
    reg_clear_bits(REG_XGMAC_DMA_CH0_TX_Control,1);
   // printf("%s,%d,REG_XGMAC_DMA_CH0_TX_Control=0x%x,value=0x%x",__FUNCTION__,__LINE__,REG_XGMAC_DMA_CH0_TX_Control,CSR_REG_READ(REG_XGMAC_DMA_CH0_TX_Control));
}
void xgmac_dma_enable_rx(BOOLEAN enable)
{
	reg_set_bits(REG_XGMAC_DMA_CH0_RX_Control,enable);
  //  printf("%s,%d,REG_XGMAC_DMA_CH0_RX_Control=0x%x,value=0x%x",__FUNCTION__,__LINE__,REG_XGMAC_DMA_CH0_RX_Control,CSR_REG_READ(REG_XGMAC_DMA_CH0_RX_Control));
}
void xgmac_dma_disable_rx()
{
	reg_clear_bits(REG_XGMAC_DMA_CH0_RX_Control,1);
   // printf("%s,%d,REG_XGMAC_DMA_CH0_RX_Control=0x%x,value=0x%x",__FUNCTION__,__LINE__,REG_XGMAC_DMA_CH0_RX_Control,CSR_REG_READ(REG_XGMAC_DMA_CH0_RX_Control));
}
void xgmac_dma_tx_desc_init_ring(XGMAC_DmaTXDesc *desc)
{
    desc->rdes0    = 0;
	desc->rdes1    = 0;
	desc->rdes2    = 0;
	desc->rdes3    = 0;
#ifdef XGMAC_DMA_CONTEXT_DESC
    desc->timestamp_low  = 0;
	desc->timestamp_high = 0;
	desc->tag            = 0;
	desc->control        = 0;
#endif
}
void xgmac_dma_rx_desc_init_ring(XGMAC_DmaRXDesc *desc)
{
    desc->rdes0    = 0;
	desc->rdes1    = 0;
	desc->rdes2    = 0;
	desc->rdes3    = 0;

}
int32_t xgmac_dma_is_desc_owned_by_dma(uintptr_t desc,char direct)
{
	XGMAC_DmaTXDesc *tx_desc = NULL;
    XGMAC_DmaRXDesc *rx_desc = NULL;

    if(TX_Desc == direct)
	{
		tx_desc = (XGMAC_DmaTXDesc *)desc;
	    return ((tx_desc->rdes3 & DescOwnByDma) == DescOwnByDma) ? 1:0;
	}
	else
	{
		rx_desc = (XGMAC_DmaRXDesc *)desc;
	    return ((rx_desc->rdes3 & DescOwnByDma) == DescOwnByDma) ? 1:0;
	}
}
int32_t xgmac_dma_is_desc_empty(uintptr_t desc,char direct)
{
    XGMAC_DmaTXDesc *tx_desc = NULL;
    XGMAC_DmaRXDesc *rx_desc = NULL;

	if(TX_Desc == direct)
	{
        tx_desc = (XGMAC_DmaTXDesc * )desc;
	//	printf("%s,%d,tx_desc=0x%x,rdes2=0x%x",__FUNCTION__,__LINE__,tx_desc,tx_desc->rdes2);
		return ((tx_desc->rdes2 & 0x3FFF) == 0)  ? 1 : 0;
	}
	else
	{
		rx_desc = (XGMAC_DmaRXDesc * )desc;
		return ((rx_desc->rdes3 & 0x3FFF) == 0 ) ? 1 : 0;
	}
}
int32_t xgmac_dma_is_last_tx_desc(struct XG_macContext *gmacdev,XGMAC_DmaTXDesc *desc )
{
	if(desc == gmacdev->Last_TxDesc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int32_t xgmac_dma_is_last_rx_desc(struct XG_macContext *gmacdev,XGMAC_DmaRXDesc *desc )
{
	if(desc == gmacdev->Last_RxDesc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int32_t xgmac_set_tx_qptr(struct XG_macContext *gmacdev,
		uint32_t Buffer1,
		uint32_t Length1,
		uint32_t timestamp_low,
		uint32_t timestamp_high,
		uint32_t tag,
		uint32_t control)
{
	uint32_t txnext = gmacdev->TxNext;

	XGMAC_DmaTXDesc *txdesc = gmacdev->TxNextDesc;

	if (!xgmac_dma_is_desc_empty((uintptr_t)txdesc,TX_Desc))
	{
		return -1;
	}

	(gmacdev->BusyTxDesc)++;



	txdesc->timestamp_low  = timestamp_low;
	txdesc->timestamp_high = timestamp_high;
	txdesc->tag            = tag;
	txdesc->control        = control | DescOwnByDma| (1<<30) | (1<<25);

	txdesc->rdes0 = Buffer1;
	txdesc->rdes2 |= ((1<<31) | ((Length1 << 0) & 0x3FFF) /*| ((Length2 << 16) & 0x3FFF0000)*/);
	txdesc->rdes3 |= DescTxLast|DescTxFirst| DescOwnByDma;
	//printf("txdesc=0x%x,txdesc->rdes0=0x%x,rdes1=0x%x,rdes2=0x%x,rdes3=0x%x,tpl=0x%x,tph=0x%x,control=0x%x,TxNext=%d",txdesc,txdesc->rdes0,txdesc->rdes1,txdesc->rdes2,txdesc->rdes3,txdesc->timestamp_low,txdesc->timestamp_high,txdesc->control,txnext);
	gmacdev->TxNext = xgmac_dma_is_last_tx_desc(gmacdev, txdesc) ? 0 : txnext + 1;
	gmacdev->TxNextDesc = xgmac_dma_is_last_tx_desc(gmacdev, txdesc) ? gmacdev->TxDesc : (txdesc + 1);
	return txnext;
}
int32_t xgmac_set_rx_qptr(struct XG_macContext *gmacdev,
		uint32_t Buffer1,
		uint32_t Length1)
{
	int32_t rxnext = gmacdev->RxNext;
	XGMAC_DmaRXDesc *rxdesc = gmacdev->RxNextDesc;

	if (!xgmac_dma_is_desc_empty((uintptr_t)rxdesc,RX_Desc))
	{

		return -1;
	}

	rxdesc->rdes3 |= ((Length1 << 0) & 0x3FFF);
	rxdesc->rdes0 = Buffer1;

	rxdesc->rdes3   |= DescOwnByDma| DescTxIntEnable;
    //rxdesc->control |= DescOwnByDma| (1<<30);
    //printf("rc=0x%x,rs0=0x%x,rs1=0x%x,rs2=0x%x,rs3=0x%x,RxNext=%d", rxdesc,rxdesc->rdes0,rxdesc->rdes1,rxdesc->rdes2,rxdesc->rdes3,rxnext);
	gmacdev->RxNext = xgmac_dma_is_last_rx_desc(gmacdev,rxdesc) ? 0:rxnext + 1;
	gmacdev->RxNextDesc =  xgmac_dma_is_last_rx_desc(gmacdev,rxdesc) ? gmacdev->RxDesc:(rxdesc+1);

	(gmacdev->BusyRxDesc)++;
	return rxnext;
}

int32_t xgmac_get_tx_qptr(struct XG_macContext *gmacdev,
		uint32_t *Status,
		uint32_t *Buffer1,
		uint32_t *Length1,
		uint32_t *Data1,
		uint32_t *Buffer2,
		uint32_t *Length2,
		uint32_t *Data2)
{
	uint32_t txover = gmacdev->TxBusy;
	XGMAC_DmaTXDesc *txdesc = gmacdev->TxBusyDesc;

	if (xgmac_dma_is_desc_owned_by_dma((uintptr_t)txdesc,TX_Desc))
	{
		printf("%s,%d,desc own dma",__FUNCTION__,__LINE__);
		return -1;
	}
	/*
	if (xgmac_dma_is_desc_empty((uintptr_t)txdesc,TX_Desc))
	{
		printf("%s,%d,desc length is 0",__FUNCTION__,__LINE__);
		return -1;
	}*/

	(gmacdev->BusyTxDesc)--;

/*
	if (Status != 0)
		*Status = txdesc->status;
*/
	if (Buffer1 != 0)
		*Buffer1 = txdesc->rdes0;
	if (Length1 != 0)
		*Length1 = (txdesc->rdes2 & 0x00003FFF) ;
	if (Data1 != 0)
	//	*Data1 = txdesc->data1;

	if (Buffer2 != 0)
		*Buffer2 = txdesc->rdes1;
	if (Length2 != 0)
		*Length2 = (txdesc->rdes2 & 0x3FFF0000) >> 16;
	if (Data1 != 0)
	//	*Data2 = txdesc->data2;

	gmacdev->TxBusy = xgmac_dma_is_last_tx_desc(gmacdev, txdesc) ? 0 : txover + 1;

	gmacdev->TxBusyDesc = xgmac_dma_is_last_tx_desc(gmacdev, txdesc) ? gmacdev->TxDesc  : (txdesc + 1);
	xgmac_dma_tx_desc_init_ring(txdesc);

	return txover;
}

int32_t xgmac_get_rx_qptr(struct XG_macContext *gmacdev,uint32_t *Length1, char *is_context)
{
    uint32_t rxnext = gmacdev->RxBusy;
	XGMAC_DmaRXDesc *rxdesc = gmacdev->RxBusyDesc;

	if (xgmac_dma_is_desc_owned_by_dma((uintptr_t)rxdesc,RX_Desc))
	{
		//printf("%s,%d,desc own dma,so cpu not deal the descriptor",__FUNCTION__,__LINE__);
		return -1;
	}

    if (xgmac_dma_is_desc_empty((uintptr_t)rxdesc,RX_Desc))
    {
		printf("%s,%d ,after DMA RX,RX desc packet length is 0",__FUNCTION__,__LINE__);
		return -1;
	}

	if (NULL != Length1)
	{
		*Length1 = (rxdesc->rdes3 & 0x3FFF);
	}

	if((rxdesc->rdes3 & 0x40000000) == 0x40000000 )
	{
		*is_context = 1;
	}
	else
	{
		*is_context = 0;
	}



   // printf("%s,%d,rxdesc=0x%x,rxdesc->rdes0=0x%x,rdes1=0x%x,rdes2=0x%x,rdes3=0x%x,timestamp_low=0x%x,timestamp_high=0x%x,tag=0x%x,control=0x%x,rxnext=0x%x",__FUNCTION__,__LINE__,rxdesc,rxdesc->rdes0,rxdesc->rdes1,rxdesc->rdes2,rxdesc->rdes3,rxdesc->timestamp_low,rxdesc->timestamp_high,rxdesc->tag,rxdesc->control,rxnext);

	gmacdev->RxBusy = xgmac_dma_is_last_rx_desc(gmacdev, rxdesc) ? 0 : rxnext + 1;
	gmacdev->RxBusyDesc = xgmac_dma_is_last_rx_desc(gmacdev, rxdesc) ? gmacdev->RxDesc : (rxdesc + 1);
	xgmac_dma_rx_desc_init_ring(rxdesc);
	(gmacdev->BusyRxDesc)--;

	return (rxnext);
}


#else
void gmac_dma_tx_desc_init_ring(GMAC_DmaTxDesc *desc, uint32_t last_ring_desc)
{
    desc->status   = (last_ring_desc == 1) ? TxDescEndOfRing:0;
	desc->length   = 0;
	desc->buffer1  = 0;
	desc->buffer2  = 0;
	desc->data1    = 0;
    desc->data2    = 0;
}
void gmac_dma_rx_desc_init_ring(GMAC_DmaRxDesc *desc, uint32_t last_ring_desc)
{
	desc->status = 0;
	desc->length = (last_ring_desc == 1) ? RxDescEndOfRing : 0;
	desc->buffer1 = 0;
	desc->buffer2 = 0;
	desc->data1 = 0;
	desc->data2 = 0;
}

int32_t gmac_dma_is_desc_owned_by_dma(GMAC_DmaTxDesc *desc)
{
	return ((desc->status & DescOwnByDma) == DescOwnByDma) ? 1:0;
}


int32_t gmac_dma_is_desc_empty(GMAC_DmaTxDesc *desc)
{
	return (((desc->length & DescSize1Mask) == 0) && ((desc->length  & DescSize2Mask) == 0) ) ? 1 : 0;
}

int32_t gmac_get_tx_qptr(struct XG_macContext *gmacdev,
		uint32_t *Status,
		uint32_t *Buffer1,
		uint32_t *Length1,
		uint32_t *Data1,
		uint32_t *Buffer2,
		uint32_t *Length2,
		uint32_t *Data2)
{
	uint32_t txover = gmacdev->TxBusy;
	GMAC_DmaTxDesc *txdesc = gmacdev->TxBusyDesc;

	if (gmac_dma_is_desc_owned_by_dma(txdesc))
		return -1;
	if (gmac_dma_is_desc_empty(txdesc))
		return -1;

	(gmacdev->BusyTxDesc)--; // busy tx descriptor is reduced by one as it
				 // will be handed over to Processor now

	if (Status != 0)
		*Status = txdesc->status;

	if (Buffer1 != 0)
		*Buffer1 = txdesc->buffer1;
	if (Length1 != 0)
		*Length1 = (txdesc->length & DescSize1Mask) >> DescSize1Shift;
	if (Data1 != 0)
		*Data1 = txdesc->data1;

	if (Buffer2 != 0)
		*Buffer2 = txdesc->buffer2;
	if (Length2 != 0)
		*Length2 = (txdesc->length & DescSize2Mask) >> DescSize2Shift;
	if (Data1 != 0)
		*Data2 = txdesc->data2;

	gmacdev->TxBusy = gmac_dma_is_last_tx_desc(gmacdev, txdesc) ? 0 : txover + 1;

	gmacdev->TxBusyDesc = gmac_dma_is_last_tx_desc(gmacdev, txdesc) ? gmacdev->TxDesc  : (txdesc + 1);
	gmac_dma_tx_desc_init_ring(txdesc, gmac_dma_is_last_tx_desc(gmacdev, txdesc));

	return txover;
}


uint32_t gmac_get_rx_qptr(struct XG_macContext *gmacdev,
		uint32_t *Status,
		uint32_t *Buffer1,
		uint32_t *Length1,
		uint32_t *Data1,
		uint32_t *Buffer2,
		uint32_t *Length2,
		uint32_t *Data2,
		uint32_t *Ext_Status,
		uint32_t *Time_Stamp_High,
		uint32_t *Time_Stamp_Low
		)
{
    uint32_t rxnext = gmacdev->RxBusy;
	GMAC_DmaRxDesc *rxdesc = gmacdev->RxBusyDesc;

uint32_t i = 0;

char *ptr = NULL;//only for test

	if (gmac_dma_is_desc_owned_by_dma(rxdesc))
	{
		printf("ganzl:desc own dma");
		return -1;
	}
/*	if (xgmac_is_desc_empty(rxdesc))
	{
		printf("ganzl:desc is null");

		return -1;
	}*/

	if (NULL != Status)
	{
		*Status = rxdesc->status;
printf("ganzl:rxdesc->status=0x%x",rxdesc->status );
	}
    if(NULL != Ext_Status)
	{

	}
	if(NULL != Time_Stamp_High)
	{

	}
	if(NULL != Time_Stamp_Low)
	{

	}

	if (NULL != Length1)
	{
		*Length1 = (rxdesc->length & DescSize1Mask) >> DescSize1Shift;
		printf("ganzl:length1=%d",*Length1 );
	}
	if (Buffer1 != 0)
	{
		*Buffer1 = rxdesc->buffer1;


		 printf("ganzl:rxdesc->buffer1=0x%x",rxdesc->buffer1 );
        ptr = (char *)(rxdesc->buffer1 );
	    for(i = sizeof(TEST_PKT_ICMP)-6 ; i < sizeof(TEST_PKT_ICMP)+4; i++)
		{
			printf("%x ",ptr[i]);
		}
	}
	if (Data1 != 0)
	{
		*Data1 = rxdesc->data1;
printf("ganzl:rxdesc->data1=0x%x",rxdesc->data1 );



	}

	if (Length2 != 0)
	{
		*Length2 = (rxdesc->length & DescSize2Mask) >> DescSize2Shift;
	}
	if (Buffer2 != 0)
	{
		*Buffer2 = rxdesc->buffer2;
	}
	if (Data2 != 0)
	{
		*Data2 = rxdesc->data2;
	}

	gmacdev->RxBusy = gmac_dma_is_last_rx_desc(gmacdev, rxdesc) ? 0 : rxnext + 1;

	gmacdev->RxBusyDesc = gmac_dma_is_last_rx_desc(gmacdev, rxdesc) ? gmacdev->RxDesc : (rxdesc + 1);
	gmac_dma_rx_desc_init_ring(rxdesc, gmac_dma_is_last_rx_desc(gmacdev, rxdesc));


	(gmacdev->BusyRxDesc)--;

	return (rxnext);
}

int32_t gmac_dma_is_last_rx_desc(struct XG_macContext *gmacdev,GMAC_DmaRxDesc *desc)
{
	return ((desc->length & RxDescEndOfRing) == RxDescEndOfRing) ? 1:0;

}


int32_t gmac_dma_is_last_tx_desc(struct XG_macContext *gmacdev,GMAC_DmaTxDesc *desc )
{
	return ((desc->status & TxDescEndOfRing) == TxDescEndOfRing)  ? 1:0;
}

int32_t gmac_set_tx_qptr(struct XG_macContext *gmacdev,
		uint32_t Buffer1,
		uint32_t Length1,
		uint32_t Data1,
		uint32_t Buffer2,
		uint32_t Length2,
		uint32_t Data2,
		uint32_t offload_needed,
		int32_t tx_flag)
{
	uint32_t txnext = gmacdev->TxNext;

	GMAC_DmaTxDesc *txdesc = NULL;


    txdesc	= gmacdev->TxNextDesc;

	if (!gmac_dma_is_desc_empty(txdesc))
	{
		return -1;
	}

	(gmacdev->BusyTxDesc)++;
	txdesc->length |= (((Length1 << DescSize1Shift) & DescSize1Mask) | ((Length2 << DescSize2Shift) & DescSize2Mask));

    //one TX interrupt only transmit one packet and desriptor belong to DMA
	txdesc->status |= tx_flag;

	txdesc->buffer1 = Buffer1;
	txdesc->data1 = Data1;

	txdesc->buffer2 = Buffer2;
	txdesc->data2 = Data2;

	if(offload_needed)
	{
		xgmac_tx_checksum_offload_tcponly(txdesc);
	}

	txdesc->status |= DescOwnByDma; // ENH_DESC

	gmacdev->TxNext = gmac_dma_is_last_tx_desc(gmacdev, txdesc) ? 0 : txnext + 1;
	gmacdev->TxNextDesc = gmac_dma_is_last_tx_desc(gmacdev, txdesc) ? gmacdev->TxDesc : (txdesc + 1);
	return txnext;
}

int32_t gmac_set_rx_qptr(struct XG_macContext *gmacdev,
		uint32_t Buffer1,
		uint32_t Length1,
		uint32_t Data1,
		uint32_t Buffer2,
		uint32_t Length2,
		uint32_t Data2)
{
	uint32_t rxnext = gmacdev->RxNext;
	GMAC_DmaRxDesc *rxdesc = gmacdev->RxNextDesc;



	if (!gmac_dma_is_desc_empty(rxdesc))
	{
		return -1;
	}


	rxdesc->length |= (((Length1 << DescSize1Shift) & DescSize1Mask) |((Length2 << DescSize2Shift) & DescSize2Mask));
	rxdesc->buffer1 = Buffer1;
	rxdesc->data1 = Data1;

	rxdesc->buffer2 = Buffer2;
	rxdesc->data2 = Data2;


	if ((rxnext % MODULO_INTERRUPT) != 0)
	{
		rxdesc->length |= RxDisIntCompl;
	}

	rxdesc->status = DescOwnByDma;




	gmacdev->RxNext = gmac_dma_is_last_rx_desc(gmacdev,rxdesc) ? 0:rxnext + 1;
	gmacdev->RxNextDesc =  gmac_dma_is_last_rx_desc(gmacdev,rxdesc) ? gmacdev->RxDesc:(rxdesc+1);



	(gmacdev->BusyRxDesc)++;
	return rxnext;
}



#endif





























int32_t xgmac_is_rx_desc_valid(uint32_t status)
{
	return (((status & DescError) == 0) && ((status & DescRxFirst) == DescRxFirst) && ((status & DescRxLast) == DescRxLast)) ? 1 : 0;
}

int32_t xgmac_get_rx_desc_frame_length(uint32_t status)
{
	return ((status & DescFrameLengthMask) >> DescFrameLengthShift);
}

int32_t dma_reset(void)
{
	CSR_REG_WRITE(REG_DWCXG_DMA_BusMode, DmaResetOn);

	while(TRUE)
	{
		if(0 == (CSR_REG_READ(REG_DWCXG_DMA_BusMode) &  DmaResetOn) )
		{
			break;
		}
	}

	return 0;
}


int32_t dma_control_init(uint32_t init_value)
{
	CSR_REG_WRITE(REG_DWCXG_DMA_Control, init_value);

	return 0;
}
void dma_disable_tx(void)
{
	reg_clear_bits(REG_DWCXG_DMA_Control, DmaTxStart);
}
void dma_disable_rx(void)
{
	reg_clear_bits(REG_DWCXG_DMA_Control, DmaRxStart);
}

void dma_enable_rx(void)
{
	uint32_t data;
	data = CSR_REG_READ(REG_DWCXG_DMA_Control);
 	data |= DmaRxStart;
	CSR_REG_WRITE(REG_DWCXG_DMA_Control ,data);
}

void dma_enable_tx(void)
{
	uint32_t data;
	data = CSR_REG_READ(REG_DWCXG_DMA_Control);
	data |= DmaTxStart;
	CSR_REG_WRITE(REG_DWCXG_DMA_Control ,data);
}


int32_t dma_bus_mode_init(uint32_t init_value)
{
	CSR_REG_WRITE(REG_DWCXG_DMA_BusMode, init_value);
	return 0;
}





void dma_init_tx_desc_base(int32_t tx_dma_base)
{
	CSR_REG_WRITE(REG_DWCXG_DMA_TxBaseAddr,tx_dma_base);

}




void dma_init_rx_desc_base(int32_t rx_dma_base)
{
	CSR_REG_WRITE(REG_DWCXG_DMA_RxBaseAddr,rx_dma_base);
}

void dma_resume_dma_tx(void)
{
	CSR_REG_WRITE(REG_DWCXG_DMA_TxPollDemand,0);
}

void dma_init(struct XG_macContext *gmacdev)
{
	//set SWR in DMA_Mode register
	dma_reset();

	dma_setup_tx_desc_queue(gmacdev,gmacdev->TRANSMIT_DESC_SIZE,gmacdev->BUFFER_DESC_MODE);
	dma_init_tx_desc_base(gmacdev->TxDescDma);
	dma_setup_rx_desc_queue(gmacdev,gmacdev->RECEIVE_DESC_SIZE,gmacdev->BUFFER_DESC_MODE);
	dma_init_rx_desc_base(gmacdev->RxDescDma);
    //dma_bus_mode_init(DmaBurstLength32 | DmaDescriptorSkip1 | DmaDescriptor8Words);
	dma_bus_mode_init(DmaBurstLength32 | DmaDescriptorSkip2 );
	dma_control_init(0x200000 | 0x4 |0x18);
}

int32_t reset_rx_buffer(struct XG_macContext *gmacdev)
{

	//int32_t dma_addr = virt_to_phys(rcv_pkt1);
	int32_t dma_addr = (uintptr_t)(rcv_pkt1);
#ifdef XG_DMA
  //  printf("%s,%d,dma_addr=0x%x",__FUNCTION__,__LINE__,dma_addr);
	return xgmac_set_rx_qptr(gmacdev, dma_addr, sizeof(rcv_pkt1));
#else
	return gmac_set_rx_qptr(gmacdev, dma_addr, sizeof(rcv_pkt1));
#endif
}

void *plat_alloc_consistent_dmaable_memory(uint32_t size, uint32_t *addr)
{
	void *ptr =(void *)malloc(size);
	*addr = virt_to_phys(ptr);
    return ptr;
}

int32_t dma_setup_rx_desc_queue(struct XG_macContext *gmacdev,uint32_t no_of_desc,uint32_t desc_mode)
{
	int32_t i = 0;
#ifdef XG_DMA
    XGMAC_DmaRXDesc *first_desc = NULL;
#else
	GMAC_DmaRxDesc *first_desc = NULL;
#endif

	dma_addr_t dma_addr;
	gmacdev->RxDescCount = 0;

	if (desc_mode == RINGMODE)
	{

		first_desc = plat_alloc_consistent_dmaable_memory(sizeof(XGMAC_DmaRXDesc) * no_of_desc,(uint32_t *)&dma_addr);

        dma_addr = (dma_addr_t)first_desc;//only for test

		if (first_desc == NULL)
		{
			return -ESYNOPGMACNOMEM;
		}
		gmacdev->RxDescCount = no_of_desc;
		gmacdev->RxDesc = first_desc;
		gmacdev->RxDescDma = dma_addr;

		gmacdev->Last_RxDesc = gmacdev->RxDesc + no_of_desc - 1;
		gmacdev->Last_RxDescDma = (dma_addr_t)(gmacdev->Last_RxDesc); // only for test,should be Last_RxDescDma=virt_to_phys(gmacdev->Last_RxDesc)
      //  printf("%s,%d,first_rx=0x%x,Last_RxDesc=0x%x",__FUNCTION__,__LINE__,first_desc,gmacdev->Last_RxDesc );
		for (i = 0; i < gmacdev->RxDescCount; i++)
		{
		#ifdef XG_DMA
			xgmac_dma_rx_desc_init_ring(gmacdev->RxDesc + i);

		#else
			gmac_dma_rx_desc_init_ring(gmacdev->RxDesc + i,(i == (gmacdev->RxDescCount - 1)) ? 1 : 0);
		#endif
		}
	}
	else
	{
	//chain link
	}

	gmacdev->RxNext = 0;
	gmacdev->RxBusy = 0;
	gmacdev->RxNextDesc = gmacdev->RxDesc;
	gmacdev->RxBusyDesc = gmacdev->RxDesc;

	gmacdev->BusyRxDesc = 0;

	return -ESYNOPGMACNOERR;
}


int32_t dma_setup_tx_desc_queue(struct XG_macContext *gmacdev,uint32_t no_of_desc,uint32_t desc_mode)
{
	int32_t i = 0;
#ifdef XG_DMA
	XGMAC_DmaTXDesc *first_desc = NULL;
#else
    GMAC_DmaTxDesc *first_desc = NULL;
#endif
	dma_addr_t dma_addr;
	gmacdev->TxDescCount = 0;

	if (desc_mode == RINGMODE)
	{

        first_desc = plat_alloc_consistent_dmaable_memory(sizeof(XGMAC_DmaTXDesc) * no_of_desc,(uint32_t *)&dma_addr);

        dma_addr = (dma_addr_t) first_desc;//only for test

		if (first_desc == NULL)
		{
			return -ESYNOPGMACNOMEM;
		}
		gmacdev->TxDescCount = no_of_desc;
		gmacdev->TxDesc = first_desc;
		gmacdev->TxDescDma = dma_addr;

    	gmacdev->Last_TxDesc = gmacdev->TxDesc + no_of_desc-1;
    //    printf("%s,%d,first_tx=0x%x,Last_TxDesc=0x%x",__FUNCTION__,__LINE__,first_desc,gmacdev->Last_TxDesc );
		gmacdev->Last_TxDescDma =(dma_addr_t )(gmacdev->Last_TxDesc); // only for test,should be Last_TxDescDma=virt_to_phys(gmacdev->Last_TxDesc)


		for (i = 0; i < gmacdev->TxDescCount; i++)
		{
#ifdef XG_DMA
			xgmac_dma_tx_desc_init_ring(gmacdev->TxDesc + i);
#else
            gmac_dma_tx_desc_init_ring(gmacdev->TxDesc + i,(i == (gmacdev->TxDescCount - 1)) ? 1 : 0);
#endif
		}
	}
	else
	{
	;	//chain link
	}

	gmacdev->TxNext = 0;
	gmacdev->TxBusy = 0;
	gmacdev->TxNextDesc = gmacdev->TxDesc;
	gmacdev->TxBusyDesc = gmacdev->TxDesc;

	gmacdev->BusyTxDesc = 0;

	return -ESYNOPGMACNOERR;
}


void reg_set_bits(uint32_t reg, uint32_t bits)
{
	CSR_REG_WRITE(reg, CSR_REG_READ(reg) | bits);
}

void reg_clear_bits(uint32_t reg,uint32_t bits_mask)
{
	CSR_REG_WRITE(reg,CSR_REG_READ(reg)&(~bits_mask));
}

void drop_giant_frames(void)
{
	reg_set_bits(REG_DWCXG_DMA_Control,DmaDropGiantFrames);
}

void xgmac_tx_checksum_offload_tcponly(GMAC_DmaTxDesc * desc)
{
	desc->status = ((desc->status & (~DescTxCisMask)) | DescTxCisTcpOnlyCs);
}
void xgmac_init_mtl(void)
{
    uint32_t i = 0;
	reg_set_bits(DWCXG_MTL_Operation_Mode,Mtl_ETSALG | Mtl_RAA | Mtl_FTS);
	for(i = 0 ; i < XGMAC_DMA_CH_NUM ;i++)
	{
		reg_set_bits(DWCXG_MTL_TxQ0_Operation_Mode + 0x80*i,/*Mtl_TSF | */Mtl_TTC | Mtl_TSQEN | Mtl_TSQ | Mtl_Q2TCMAP);
		reg_set_bits(DWCXG_MTL_RxQ0_Operation_Mode + 0x80*i,/*Mtl_RSF |*/ Mtl_RSQ | Mtl_RTC);
 //   printf("%s,%d,DWCXG_MTL_TxQ0_Operation_Mode=0x%x,value=0x%x",__FUNCTION__,__LINE__,DWCXG_MTL_TxQ0_Operation_Mode,CSR_REG_READ(DWCXG_MTL_TxQ0_Operation_Mode));
    }
}
void lif_dma_mtl_init(struct XG_macContext *gmacdev)
{
#ifdef XG_DMA
	xgmac_dma_init(gmacdev);
#endif
    xgmac_init_mtl();
}

int32_t dma_wait_tps_irq_timeout(struct XG_macContext *gmacdev,int32_t timeout_us)
{
	int32_t wait_time_us = 0;
	int32_t dma_status_reg = dma_read_interrupt_src();
    printf("%s,%d:dma tx status=0x%x",__FUNCTION__,__LINE__,dma_status_reg);
	while(!(dma_status_reg & DmaIntTxStopped))
	{
		if(wait_time_us > timeout_us)
		{
			return -1;
		}
		mydl(1);
		wait_time_us += 100;
        dma_status_reg = dma_read_interrupt_src();
	}
    printf("%s,%d:dma tx status=0x%x",__FUNCTION__,__LINE__,dma_status_reg);

    CSR_REG_WRITE(REG_XGMAC_DMA_CH0_Status,DmaIntTxStopped);


	return 0;
}

int pkt_check(u8 *buf1,u8 *buf2, int len)
{
	int index = 0;
    int error = 0;
	for(index = 0; index < len ; index++)
	{
		if(buf1[index] != buf2[index] ){
        	printf( "check fail: buf1[%d]=0x%x, buf2[%d]=0x%x", index, buf1[index], index, buf2[index]);
            error++;
		}
    }
    return error;
}
