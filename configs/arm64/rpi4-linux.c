/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for Raspberry Pi 4 (quad-core Cortex-A72, 1GB, 2GB, 4GB or 8GB RAM)
 * Copyright (c) 2022-2024 ZCShou
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
	struct jailhouse_memory mem_regions[5];
	struct jailhouse_irqchip irqchips[2];
} __attribute__((packed)) config = {
	.cell = {
		.signature = JAILHOUSE_CELL_DESC_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.architecture = JAILHOUSE_ARM64,
		.name = "rpi4-linux",
		.flags = JAILHOUSE_CELL_PASSIVE_COMMREG,
		.cpu_set_size = sizeof(config.cpus),
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		.num_irqchips = ARRAY_SIZE(config.irqchips),
		.vpci_irq_base = 185-32,
		.console = {
			.address = 0xfe201000,
			.type = JAILHOUSE_CON_TYPE_PL011,
			.flags = JAILHOUSE_CON_ACCESS_MMIO | JAILHOUSE_CON_REGDIST_4,
		},
	},

	.cpus = {
		0b1100,
	},

	.mem_regions = {
		/* UART */
		{
			.phys_start = 0xfe201000,
			.virt_start = 0xfe201000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO | JAILHOUSE_MEM_IO_8 | JAILHOUSE_MEM_IO_32 | JAILHOUSE_MEM_ROOTSHARED,
		},
		/* RAM for linux-loader */
		{
			.phys_start = 0x41000000,
			.virt_start = 0,
			.size = 0x00800000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE,
		},
		/* RAM for dtb（unused） */
		{
			.phys_start = 0x41800000,
			.virt_start = 0x41800000,
			.size = 0x00800000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE,
		},
		/* RAM for linux */
		{
			.phys_start = 0x42000000,
			.virt_start = 0x42000000,
			.size = 0x2e000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE | JAILHOUSE_MEM_DMA,
		},
		/* communication region for hypervisor and the current cell */
		{
			.virt_start = 0x80000000,
			.size = 0x00001000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_COMM_REGION,
		},
	},

	.irqchips = {
		/* GIC */ {
			.address = 0xff841000,
			.pin_base = 32,
			.pin_bitmap = {
				0,
				0,
				1 << (125 - 96),
				0,
			},
		},
		/* GIC */ {
			.address = 0xff841000,
			.pin_base = 160,
			.pin_bitmap = {
				(1 << (185 - 160)) | (1 << (186 - 160)),
				0,
				0,
				0
			},
		},
	},
};
