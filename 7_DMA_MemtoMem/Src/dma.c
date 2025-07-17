#include "dma.h"

#define DMA2EN 			(1U<<22)
#define DMA_SCR_EN		(1U<<0)
#define DMA_SCR_MINC 	(1U<<10)
#define DMA_SCR_PINC 	(1U<<9)
#define DMA_SCR_TCIE	(1U<<4)
#define DMA_SCR_TEIE	(1U<<2)
#define DMA_SFCR_DMDIS	(1U<<2)

void dma2_mem2mem_config(void)
{
	/*Enable clock access to the DMA module*/
	RCC ->AHB1ENR |= DMA2EN;

	/*Disable DMA stream*/
	DMA2_Stream0 -> CR = 0;

	/*Wait until stream is disabled*/
	while((DMA2_Stream0->CR & DMA_SCR_EN)){}

	/*Configure DMA parameters*/

	/*Set MEIZE(Memory data size) to half-word*/
	DMA2_Stream0 ->CR |= (1U<<13);
	DMA2_Stream0 ->CR &=~(1U<<14);

	/*Set PSIZE(Peripheral data size) to half-word*/
	DMA2_Stream0 ->CR |= (1U<<11);
	DMA2_Stream0 ->CR &=~(1U<<12);

	/*Enable memory address increment*/
	DMA2_Stream0 ->CR |= DMA_SCR_MINC;

	/*Enable Peripheral address increment*/
	DMA2_Stream0 ->CR |= DMA_SCR_PINC;

	/*Select Mem-to-Mem transfer*/
	DMA2_Stream0 ->CR &=~(1U<<6);
	DMA2_Stream0 ->CR |= (1U<<7);

	/*Disable direct mode*/
	DMA2_Stream0 ->FCR |= DMA_SFCR_DMDIS;

	/*Set DMA FIFI threshold*/
	DMA2_Stream0 ->FCR |= (1U<<0);
	DMA2_Stream0 ->FCR |= (1U<<1);

	/*Enable DMA interrupt in NVIC*/
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}


void dma_transfer_start(uint32_t scr_buff, uint32_t dest_buff, uint32_t len){

	/*Set peripheral address*/
	DMA2_Stream0 ->PAR = scr_buff;

	/*Set memory address*/
	DMA2_Stream0 ->M0AR= dest_buff;

	/*set transfer Length*/
	DMA2_Stream0 ->NDTR = len;

	/*Enable dma stream*/
	DMA2_Stream0 ->CR |= DMA_SCR_EN;
}
