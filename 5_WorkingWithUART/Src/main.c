#include "stm32f4xx.h"
#include <string.h>
#include <stdio.h>
#include "uart.h"


int main()
{

	uart2_tx_int();

	while(1){
		printf("Hello from func \n\r");
	}
}
