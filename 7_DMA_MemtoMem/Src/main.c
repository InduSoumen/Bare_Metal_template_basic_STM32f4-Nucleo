#include "stm32f4xx.h"
#include <string.h>
#include <stdio.h>
#include "dma.h"
#include "uart.h"
#define buff_siz	5

uint16_t sesnordara_arr[buff_siz]={13564,15742,16473,14645,16425};
uint16_t temp_data_arr[buff_siz];

volatile uint8_t g_transfer_cmplt;

int main()
{
	uart2_tx_int();

	dma2_mem2mem_config();
	dma_transfer_start((uint32_t)sesnordara_arr, (uint32_t)temp_data_arr, (uint32_t)buff_siz);

	/*wait till transfer colplete*/
	while(!g_transfer_cmplt){}

	for(int i=0; i<buff_siz;i++){
		printf("Temp buff[%d]: %d \r\n",i,temp_data_arr[i]);
	}
	while(1){
	}
}

void DMA1_Stream0_IRQHandler(void){
	/*Check if transfer complete interrupt occurred*/
	if((DMA2->LISR)& LISR_TCIF0){

		g_transfer_cmplt = 0;

		/*Clear flag*/
		DMA2->LIFCR |= LIFCR_CTCIF0;
	}

	/*Check if transfer error occurred*/
	if((DMA2->LISR)& LISR_TEIF0){
		/*Execute something*/
		/*Clear flag*/
		DMA2->LIFCR |= LIFCR_CTEIF0;
	}
}
