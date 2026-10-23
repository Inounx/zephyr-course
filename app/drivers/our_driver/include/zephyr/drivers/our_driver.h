
#ifndef OUR_DRIVER_H
#define OUR_DRIVER_H

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*our_driver_cmd)(const struct device *dev);
typedef int (*our_driver_cmd_param)(const struct device* dev, int val);

__subsystem struct our_driver_api 
{
    our_driver_cmd led_on;
    our_driver_cmd led_off;
    our_driver_cmd_param set_value;
};

__syscall int our_driver_led_on(const struct device* dev);
static inline int z_impl_our_driver_led_on(const struct device* dev)
{
	const struct our_driver_api* api = (const struct our_driver_api*)dev->api;
	__ASSERT(api->led_on, "led_on function not defined!");
	return api->led_on(dev);
}

__syscall int our_driver_led_off(const struct device* dev);
static inline int z_impl_our_driver_led_off(const struct device* dev)
{
	const struct our_driver_api* api = (const struct our_driver_api*)dev->api;
	__ASSERT(api->led_off, "led_off function not defined!");
	return api->led_off(dev);
}

__syscall int our_driver_set_value(const struct device* dev, int val);
static inline int z_impl_our_driver_set_value(const struct device* dev, int val)
{
	const struct our_driver_api* api = (const struct our_driver_api*)dev->api;
	__ASSERT(api->set_value, "set_value function not defined!");
	return api->set_value(dev, val);
}

#include <syscalls/our_driver.h>

#ifdef __cplusplus
}
#endif

#endif //OUR_DRIVER_H
