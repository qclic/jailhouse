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

#define MULTIBOOT_MAGIC     0x2BADB002
#define MULTIBOOT_INFO      0x200000
#define KERNEL_ENTRY        0x300000

void inmate_main(void)
{
	printk("arceos-loader: entry: %p, parm: %p\n", (void*)KERNEL_ENTRY, (void*)MULTIBOOT_INFO);

    map_range((void*)KERNEL_ENTRY, 0x4000000, MAP_CACHED);

    asm (
        "cli\n\t"
        "cld\n\t"
        "mov $0x0000, %%rsp\n\t"   // temporary stack
        "mov %0, %%rax\n\t"     // multiboot magic
        "mov %1, %%rbx\n\t"     // multiboot information
        "mov %2, %%rcx\n\t"     // kernel entry
        "jmp *%%rcx\n\t"
        : 
        : "i"(MULTIBOOT_MAGIC), "i"(MULTIBOOT_INFO), "i"(KERNEL_ENTRY)
        : "%rax", "%rbx", "%rcx"
    );

	printk("arceos-loader: SHOULD NOT come here.\n");
}
