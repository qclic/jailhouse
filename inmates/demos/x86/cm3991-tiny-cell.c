/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) ZCShou, 2024
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
	unsigned long long start, now;
	int n;

	printk("Hello from cm3991-tiny-cell!\n");

	start = pm_timer_read();
	for (n = 0; n < 10; n++) {
		do {
			now = pm_timer_read();
			cpu_relax();
		} while (now - start < 1000000000ULL);
		start += 1000000000ULL;
		printk("PM Timer: %11llu\n", now);
	}
}
