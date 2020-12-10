#include "main.h"

void Delay(){
	for(volatile int i=0;i<2000000;i++);

}

int main(void)
{
	Board_GPIO_Init();

	GpioWrite(LED1, true);
	GpioWrite(LED3, true);

	bool flag = 0;
	while (1)
	{
		//Delay();
		GpioWrite(LED1, false);
		//Delay();
		GpioWrite(LED1, true);

		if(GpioRead(TEC_1)) {
			flag =!flag;
		}
		GpioWrite(LED2, flag);

	}
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/
