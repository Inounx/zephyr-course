#include "zephyr/drivers/our_driver.h"
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define LED_NODE DT_ALIAS(app_led)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

struct our_driver_data
{
	int value;
};

static int impl_our_driver_led_off(const struct device* dev)
{
	LOG_INF("LED OFF");
    return gpio_pin_set_dt(&led, 0);
}

static int impl_our_driver_led_on(const struct device *dev)
{
	LOG_INF("LED ON");
	return gpio_pin_set_dt(&led, 1);
}

static int impl_our_driver_set_value(const struct device* dev, int val)
{
	__ASSERT(dev->data, "Device data is null!");
	struct our_driver_data* data = (struct our_driver_data*)dev->data;
	data->value = val;
	LOG_INF("Our driver set new value: %d", data->value);
	return 0;
}

static struct our_driver_api our_driver_api = 
{
    .led_on = &impl_our_driver_led_on,
	.led_off = &impl_our_driver_led_off,
	.set_value = &impl_our_driver_set_value
};

//Init function
static int init(const struct device* dev)
{
	if (!gpio_is_ready_dt(&led)) 
		return -1;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE) < 0) 
		return -1;

	__ASSERT(dev->data, "Device data is null!");
	struct our_driver_data* data = (struct our_driver_data*)dev->data;
	data->value = 0;

	LOG_INF("Device initialized!");
	return 0;
}	


#define DEV_INST(inst) \
	static struct our_driver_data data_##inst; \
	DEVICE_DT_INST_DEFINE(inst, init, NULL, &data_##inst, NULL, POST_KERNEL, 80, &our_driver_api); \

DT_INST_FOREACH_STATUS_OKAY(DEV_INST);