#include <Arduino_FreeRTOS.h>

const TickType_t xDelay1k  pdMS_TO_TICKS(1000);

static const char *textForTask1 = "Task 1 is here LMAO YEET";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xTaskCreate(MyTask1, "Task1", 100, (void*) textForTask1, 1 , NULL);
  // pvTaskCode
  // Desc
  // usStackDepth - number of words for task thread
  // pvParameters   
  // uxPriority o - configMAX_PRIORITIES - 1
  // pxCreatedTask - optional and set to NULL
  vTaskStartScheduler();  
}

static void MyTask1(void *pvParameters) {
  char *pvString = (char *)pvParameters;
  while(1)
  {
    Serial.println(pvString);
    vTaskDelay(xDelay1k); //delay 1000ms 
    }
}

void loop() {
  // put your main code here, to run repeatedly:

}
