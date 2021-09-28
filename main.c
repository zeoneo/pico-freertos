
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"

void makeBlink(int times, int delayMs)
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    for (int i = 0; i < times; i++)
    {
        gpio_put(LED_PIN, 1);
        sleep_ms(delayMs);
        gpio_put(LED_PIN, 0);
        sleep_ms(delayMs);
    }
    gpio_put(LED_PIN, 0);
}
void runOnCore0()
{
    while (1)
    {
        makeBlink(3, 500);
        vTaskDelay(3000);
    }
}

void runOnCore1()
{
    while (1)
    {
        makeBlink(10, 1000);
        vTaskDelay(5000);
    }
}

int main()
{
    stdio_init_all();
    printf("Start LED blink\n");
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);
    // makeBlink(2, 100);
    xTaskCreate(runOnCore0, "LED_Task 0", 256, NULL, 1, NULL);
    // makeBlink(4, 200);
    xTaskCreate(runOnCore1, "LED_Task 1", 256, NULL, 1, NULL);
    // makeBlink(8, 400);

    // gpio_put(LED_PIN, 0);
    vTaskStartScheduler();

    while (true)
        ;
}