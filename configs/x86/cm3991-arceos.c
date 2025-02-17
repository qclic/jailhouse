/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * ArceOS configuration for demo inmates, 1 CPU, 64 MB RAM, serial ports
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
	struct jailhouse_memory mem_regions[4];
	struct jailhouse_cache cache_regions[1];
	struct jailhouse_irqchip irqchips[1];
	struct jailhouse_pio pio_regions[3];
} __attribute__((packed)) config = {
	.cell = {
		.signature = JAILHOUSE_CELL_DESC_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.architecture = JAILHOUSE_X86,
		.name = "cm3991-arceos",
		.flags = JAILHOUSE_CELL_PASSIVE_COMMREG |
			JAILHOUSE_CELL_TEST_DEVICE |
			JAILHOUSE_CELL_VIRTUAL_CONSOLE_PERMITTED,

		.cpu_set_size = sizeof(config.cpus),
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		.num_cache_regions = ARRAY_SIZE(config.cache_regions),
		.num_irqchips =  ARRAY_SIZE(config.irqchips),
		.num_pio_regions = ARRAY_SIZE(config.pio_regions),
		.num_pci_devices = 0,

		.console = {
			.type = JAILHOUSE_CON_TYPE_8250,
			.flags = JAILHOUSE_CON_ACCESS_PIO,
			.address = 0x3f8,
		},
	},

	.cpus = {
		0b1000,	/* use cpu3. used by bit */
	},

	.mem_regions = {
		{	/* RAM for arceos-loader */
			.phys_start = 0x100600000,
			.virt_start = 0,
			.size = 0x00100000,		/* 1M */
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE | JAILHOUSE_MEM_DMA,
		},
		{	/* communication region for arceos-loader and arceos */
			.phys_start = 0x100700000,
			.virt_start = 0x00200000,
			.size = 0x00100000,		/* 1M */
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_COMM_REGION,
		},
		{	/* RAM for arceos */
			.phys_start = 0x100800000,
			.virt_start = 0x300000,
			.size = 0x4000000,		/* 74M */
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE | JAILHOUSE_MEM_DMA,
		},
		{	/* communication region for hypervisor and the current cell */
			.virt_start = 0x00100000,
			.size = 0x00001000,		/* 4K */
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

	.irqchips = {
		/* IOAPIC */ {
			.address = 0xfec00000,
			.id = 0x100f7,
			.pin_bitmap = {
				(1 << 3) | (1 << 4),
			},
		},
	},

	.pio_regions = {
		PIO_RANGE(0x2f8, 8), /* serial 2 */
		PIO_RANGE(0x3f8, 8), /* serial 1 */
		PIO_RANGE(0xe010, 8), /* OXPCIe952 serial2 */
	},
};
