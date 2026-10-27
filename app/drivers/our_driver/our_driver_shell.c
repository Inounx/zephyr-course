#include "zephyr/drivers/sensor.h"
#include <zephyr/shell/shell.h>

static int cmd_our_driver_fetch_handler(const struct shell * sh, int argc, char** argv)
{
    const struct device* dev = shell_device_get_binding(argv[1]);
    if(!dev)
    {
        shell_error(sh, "Unknown device %s", argv[1]);
        return -EFAULT;
    }

    int ret = sensor_sample_fetch(dev);
    if(ret != 0)
    {
        shell_error(sh, "Sample fetch error: %d", ret);
        return -EFAULT;
    }

    return 0;
}

static int cmd_our_driver_channel_get_handler(const struct shell * sh, int argc, char** argv)
{
    const struct device* dev = shell_device_get_binding(argv[1]);
    if(!dev)
    {
        shell_error(sh, "Unknown device %s", argv[1]);
        return -EFAULT;
    }

    struct sensor_value val;
    int ret = sensor_channel_get(dev, SENSOR_CHAN_ACCEL_X, &val);
    if(ret != 0)
    {
        shell_error(sh, "Channel get error: %d", ret);
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
    SHELL_CMD_ARG(fetch, NULL, "calls sensor_sample_fetch()", cmd_our_driver_fetch_handler, 2, 0),
    SHELL_CMD_ARG(read, NULL, "calls sensor_channel_get() and prints the result", cmd_our_driver_channel_get_handler, 2, 0),
    SHELL_CMD_ARG(info, NULL, "prints the device name and ready state", cmd_our_driver_info_handler, 2, 0),
    SHELL_SUBCMD_SET_END,
);

SHELL_CMD_REGISTER(sensor, &our_driver_subcmd, "our driver shell", NULL);