
#include <zephyr/init.h>
#include <zephyr/sys/printk.h>

static int my_board_init(void)
{
    printk("Board initialized\n");
    return 0;
}

/* needs to be done after GPIO driver init */
SYS_INIT(my_board_init, POST_KERNEL,
	 CONFIG_KERNEL_INIT_PRIORITY_DEVICE);