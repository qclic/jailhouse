/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Minimal configuration for cm3991-tiny-cell inmates, 
 * 1 CPU, 1 MB RAM, serial ports
 *
 * Copyright (c) ZCShou, 2024
 *
 * Authors:
 *  ZCShou <72115@163.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_cell_desc cell;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[2];
	struct jailhouse_cache cache_regions[1];
	struct jailhouse_pio pio_regions[3];
} __attribute__((packed)) config = {
	.cell = {
		.signature = JAILHOUSE_CELL_DESC_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.architecture = JAILHOUSE_X86,
		.name = "cm3991-tiny-cell",
		.flags = JAILHOUSE_CELL_PASSIVE_COMMREG |
			JAILHOUSE_CELL_TEST_DEVICE |
			JAILHOUSE_CELL_VIRTUAL_CONSOLE_PERMITTED,

		.cpu_set_size = sizeof(config.cpus),
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		.num_cache_regions = ARRAY_SIZE(config.cache_regions),
		.num_irqchips = 0,
		.num_pio_regions = ARRAY_SIZE(config.pio_regions),
		.num_pci_devices = 0,

		.console = {
			.type = JAILHOUSE_CON_TYPE_8250,
			.flags = JAILHOUSE_CON_ACCESS_PIO,
			.address = 0x3f8,
		},
	},

	.cpus = {
		0b0100,	/* use cpu2. used by bit */
	},

	.mem_regions = {
		/* RAM */ {
			.phys_start = 0x100600000,
			.virt_start = 0,
			.size = 0x00100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE,
		},
		/* communication region */ {
			.virt_start = 0x00100000,
			.size = 0x00001000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_COMM_REGION,
		},
	},

	.cache_regions = {
		{
			.start = 2,
			.size = 1,
			.type = JAILHOUSE_CACHE_L3,
		},
	},

	.pio_regions = {
		PIO_RANGE(0x2f8, 8), /* serial 2 */
		PIO_RANGE(0x3f8, 8), /* serial 1 */
		PIO_RANGE(0xe010, 8), /* OXPCIe952 serial2 */
	},
};
