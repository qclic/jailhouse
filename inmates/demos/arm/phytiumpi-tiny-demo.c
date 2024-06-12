/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) 2022-2024 ZCShou
 *
 * Authors:
 *  ZCShou <72115@163.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <inmate.h>

void inmate_main(void)
{
	/*
	 * The cell config can set up a mapping to access UARTx instead of UART0
	 */
	for (int i = 0; i < 10; i++)
	{
		printk("%d. Hello Phytiumpi from phytiumpi-tiny-demo!\n", i);
		delay_us(1000000);
	}
	
	/* lr should be 0, so a return will go back to the reset vector */
}
