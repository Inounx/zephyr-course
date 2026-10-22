#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define LED_NODE DT_ALIAS(app_led)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

static int our_driver_channel_get(const struct device* dev,
				              enum sensor_channel chan,
				              struct sensor_value* val)
{
	LOG_INF("LED OFF");
    return gpio_pin_set_dt(&led, 0);
}

static int our_driver_sample_fetch(const struct device *dev, enum sensor_channel chan)
{
	LOG_INF("LED ON");
	return gpio_pin_set_dt(&led, 1);
}

static DEVICE_API(sensor, our_driver_api) = 
{
    .channel_get = &our_driver_channel_get,
    //sensor_attr_set_t attr_set;
	//sensor_attr_get_t attr_get;
	//sensor_trigger_set_t trigger_set;
	.sample_fetch = &our_driver_sample_fetch
	//sensor_channel_get_t channel_get;
	//sensor_get_decoder_t get_decoder;
	//sensor_submit_t submit;
};

//Init function
static int init(const struct device* dev)
{
	if (!gpio_is_ready_dt(&led)) 
		return -1;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE) < 0) 
		return -1;

	LOG_INF("Device initialized!");
	return 0;
}	

#define DEV_INST(inst) DEVICE_DT_INST_DEFINE(inst, init, NULL, NULL, NULL, POST_KERNEL, 80, &our_driver_api);

DT_INST_FOREACH_STATUS_OKAY(DEV_INST);