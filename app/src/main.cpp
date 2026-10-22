#include "zephyr/drivers/sensor.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

int main(void)
{
    struct sensor_value val;
    while (1) 
    {
        //LED ON
        sensor_sample_fetch(driver);
        
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);

        //LED OFF
        sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);

        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
