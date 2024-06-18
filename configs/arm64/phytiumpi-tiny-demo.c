/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for Phytium E2000Q
 * Copyright (c) 2022-2024 ZCShou
 *
 * Authors:
 *  ZCShou <72115@163.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.
 * See the COPYING file in the top-level directory.
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_cell_desc cell;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[3];
	struct jailhouse_irqchip irqchips[1];
} __attribute__((packed)) config = {
	.cell = {
		.signature = JAILHOUSE_CELL_DESC_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.architecture = JAILHOUSE_ARM64,
		.name = "phytiumpi-tiny-demo",
		.flags = JAILHOUSE_CELL_PASSIVE_COMMREG | JAILHOUSE_CELL_VIRTUAL_CONSOLE_PERMITTED,

		.cpu_set_size = sizeof(config.cpus),
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		.num_irqchips = ARRAY_SIZE(config.irqchips),

		.console = {
			.address = 0x2800d000,
			.type    = JAILHOUSE_CON_TYPE_PL011,
			.flags   = JAILHOUSE_CON_ACCESS_MMIO | JAILHOUSE_CON_REGDIST_4,
		},
	},

	.cpus = {
		0b1000,
	},

	.mem_regions = {
		/* UART 1 */ {
			.phys_start = 0x2800d000,
			.virt_start = 0x2800d000,
			.size		= 0x1000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO | JAILHOUSE_MEM_ROOTSHARED,
		},

		/* RAM */ {
			.phys_start = 0xb1000000,
			.virt_start = 0x0,
			.size		= 0x00100000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE,
		},

		/* communication region */ {
			.virt_start = 0x80000000,
			.size		= 0x00001000,
			.flags		= JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_COMM_REGION,
		},
	},

	.irqchips = {
		/* GIC */
		{
			.address = 0x30800000,
			.pin_base = 32,
			.pin_bitmap = {
				0x1 << (36 - 32) /* SPI 36 pcie_inta */
			},
		},
	},
};

