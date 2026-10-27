#include "zephyr/drivers/our_driver.h"
#include <zephyr/shell/shell.h>
#include <stdlib.h>

static int cmd_our_driver_led_on_handler(const struct shell * sh, int argc, char** argv)
{
    const struct device* dev = shell_device_get_binding(argv[1]);
    if(!dev)
    {
        shell_error(sh, "Unknown device %s", argv[1]);
        return -EFAULT;
    }

    int ret = our_driver_led_on(dev);
    if(ret != 0)
    {
        shell_error(sh, "Led on error: %d", ret);
        return -EFAULT;
    }

    return 0;
}

static int cmd_our_driver_led_off_handler(const struct shell * sh, int argc, char** argv)
{
    const struct device* dev = shell_device_get_binding(argv[1]);
    if(!dev)
    {
        shell_error(sh, "Unknown device %s", argv[1]);
        return -EFAULT;
    }

    int ret = our_driver_led_off(dev);
    if(ret != 0)
    {
        shell_error(sh, "Led off error: %d", ret);
        return -EFAULT;
    }

    return 0;
}

static int cmd_our_driver_set_handler(const struct shell * sh, int argc, char** argv)
{
    const struct device* dev = shell_device_get_binding(argv[1]);
    if(!dev)
    {
        shell_error(sh, "Unknown device %s", argv[1]);
        return -EFAULT;
    }

    int val = strtol(argv[2], NULL, 10);
    if(val < 1 || val > 100)
    {
        shell_error(sh, "Invalid value, or invalid arg format: %s", argv[2]);
        return -EINVAL;
    }

    int ret = our_driver_set_value(dev, val);
    if(ret != 0)
    {
        shell_error(sh, "Set value error: %d", ret);
        return -EFAULT;
    }

    return 0;
}

static int cmd_our_driver_info_handler(const struct shell * sh, int argc, char** argv)
{
    const struct device* dev = shell_device_get_binding(argv[1]);
    if(!dev)
    {
        shell_error(sh, "Unknown device %s", argv[1]);
        return -EFAULT;
    }

    shell_info(sh, "Device name: %s", dev->name);
    shell_info(sh, "Device ready: %d", (dev->state->initialized && dev->state->init_res >= 0));

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmd, 
    SHELL_CMD_ARG(led_on, NULL, "calls custom api led on. Usage: led_on <dev>", cmd_our_driver_led_on_handler, 2, 0),
    SHELL_CMD_ARG(led_off, NULL, "calls custom api led off. Usage: led_off <dev>", cmd_our_driver_led_off_handler, 2, 0),
    SHELL_CMD_ARG(set, NULL, "Set value between 1 and 100. Usage: set <dev> <val>", cmd_our_driver_set_handler, 3, 0),
    SHELL_CMD_ARG(info, NULL, "prints the device name and ready state. Usage: info <dev>", cmd_our_driver_info_handler, 2, 0),
    SHELL_SUBCMD_SET_END,
);

SHELL_CMD_REGISTER(sensor, &our_driver_subcmd, "our driver shell", NULL);