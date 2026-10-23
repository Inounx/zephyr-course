#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/our_driver.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

int main(void)
{
    int i = 0;

    while (1) 
    {
        //LED ON
        our_driver_led_on(driver);
        
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);

        //LED OFF
        our_driver_led_off(driver);

        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);

        our_driver_set_value(driver, i);
        i++;
    }
    return 0;
}
