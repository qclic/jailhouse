/*
 * Jailhouse arceos loader
 *
 * Copyright (C) ZCShou
 *
 * Authors:
 *  ZCShou <72115@163.com.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <inmate.h>

void inmate_main(void)
{
	void (*entry)(int, void *);
    void *parm;

	entry = (void*)0x100800000;
	parm = (void*)0x100700000;
	printk("arceos-loader: entry: %p, dtb: %p\n", entry, parm);

	entry(0, parm);
}
