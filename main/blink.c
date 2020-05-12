/*

Version inicial de sensor de color, consta de un frecuanciometro para calcular
la frecuenci obtenida a partir del sensor TCS3200
TCS3200 Output  Square wave 50% Duty cycle with frequency directly
                proportional to light intensity.
full scale frequency    10 - 12 kHz, T=> 100 - 83 microseconds
dark frequency          2 - 10 Hz
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


    //uint16_t cnt = 0;


#define PeriodoMedicion pdMS_TO_TICKS(0.05) 	//Periodo de timer
						//Debe ser bajo para medir longitud de onda
#define SalidaSensor 		14
#define GPIO_INPUT_PIN_SEL 	(1ULL<<SalidaSensor)


static xQueueHandle xColor = NULL;
static void TaskColor(void *pvParameters);
static void Callback (TimerHandle_t xTimer);


void app_main(void)
{

    printf("Sensor De Color\n");
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_PIN_INTR_ENABLE;  //enable interrupt
    io_conf.mode = GPIO_MODE_INPUT;  //set as output mode
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL; //bit mask of the pin ...
    io_conf.pull_down_en = 1; //enable pull-down mode
    io_conf.pull_up_en = 0; //disable pull-up mode
    gpio_config(&io_conf);  //configure GPIO with the given settings

  /*   io_conf.intr_type = GPIO_INTR_DISABLE;  //interrupt of rising edge
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;  //bit mask of the pin 4
    io_conf.mode = GPIO_MODE_INPUT; //set as input mode#4A465F#4A465F#FFFFFF#3A3A3C#3A3A3C
    io_conf.pull_up_en = 1; //enable pull-up mode
    gpio_config(&io_conf);
 */

   TimerHandle_t xPrimerTimer;
   BaseType_t xTimerIniciado;

   xPrimerTimer = xTimerCreate("timerMedicion", PeriodoMedicion,pdTRUE,0,Callback);
//Configuración de timer,(nombre del timer, periodo, habilitamos autoreload, id=0, Función para callback

   xTimerIniciado = TimerStart( xPrimerTimer, 0 );

    while(1){

	/*Aqui hay que ver los valores que da para determinar
	el color y que lo imprima*/


      }
  //    vTaskDelay(1000 / portTICK_RATE_MS);
    }

static void Callback (TimerHandle_t xTimer)
{
TickType_t xTimeNow;

 	xTimeNow= uxTaskGetTickCount();	//Obtiene el valor de la cuenta de ticks

	ulCallCount++;
}

static void TaskColor(void *pvParameters)
{
    uint8_t etapa = 0;
    int t1=0, t2=0, T=0, F=0;

   switch(etapa){
          case 0:
		t1 = uxTaskGetTickCount();
		etapa++;
                  break;

          case 1:
		t2 = uxTaskGetTickCount();
		T= (t2-t1)/0.05;
		F= 1/T;

		xQueueSendToBack(xColor,F,portMax_DELAY);

		  break;
}
