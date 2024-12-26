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
	struct jailhouse_system header;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[4];
	struct jailhouse_irqchip irqchips[2];
} __attribute__((packed)) config = {
	.header = {
		.signature = JAILHOUSE_SYSTEM_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.architecture = JAILHOUSE_ARM64,
		.flags = JAILHOUSE_SYS_VIRTUAL_DEBUG_CONSOLE,
		.hypervisor_memory = {
			.phys_start = 0x40000000,
			.size       = 0x01000000,
		},
		.debug_console = {
			.address = 0xfe201000,
			.size = 0x1000,
			.type = JAILHOUSE_CON_TYPE_PL011,
			.flags = JAILHOUSE_CON_ACCESS_MMIO | JAILHOUSE_CON_REGDIST_4,
		},
		.platform_info = {
			.pci_mmconfig_base = 0xff900000,
			.pci_mmconfig_end_bus = 0,
			.pci_is_virtual = 1,
			.pci_domain = 1,
			.arm = {
				.gic_version = 2,
				.gicd_base = 0xff841000,
				.gicc_base = 0xff842000,
				.gich_base = 0xff844000,
				.gicv_base = 0xff846000,
				.maintenance_irq = 25,
			},
		},
		.root_cell = {
			.name = "RaspberryPi4",
			.cpu_set_size = sizeof(config.cpus),
			.num_memory_regions = ARRAY_SIZE(config.mem_regions),
			.num_irqchips = ARRAY_SIZE(config.irqchips),
			.vpci_irq_base = 182 - 32,
		},
	},

	.cpus = {
		0b1111,
	},

	.mem_regions = {
		/* RAM for the ARM + VC */
		{
 			.phys_start = 0x0,
 			.virt_start = 0x0,
			.size = 0x40000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_EXECUTE,
		},
		/* RAM (for the ARM) */
		{
			.phys_start = 0x40000000,
			.virt_start = 0x40000000,
			.size = 0xbd500000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_EXECUTE,
		},
		/* MMIO 1 (permissive) */
		{
			.phys_start = 0xfd500000,
			.virt_start = 0xfd500000,
			.size = 0x1b00000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
		/* MMIO 1 （PCIe） */
		{
			.phys_start = 0x600000000,
			.virt_start = 0x600000000,
			.size = 0x4000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO,
		},
	},

	.irqchips = {
		/* GIC */
		{
			.address = 0xff841000,
			.pin_base = 32,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
		/* GIC */
		{
			.address = 0xff841000,
			.pin_base = 160,
			.pin_bitmap = {
				0xffffffff, 0xffffffff
			},
		},
	},
};
