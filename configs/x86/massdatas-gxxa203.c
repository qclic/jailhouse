/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for Massdatas-Gxxa203 machine with 12th Gen Intel(R) 
 * Core(TM) i5-1240P and 62G RAM
 *
 * Copyright (c) ZCShou, 2024
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 * Created with 'jailhouse config create massdatas-gxxa203.c' and adjusted
 * by ZCShou <72115@163.com>.
 *
 * NOTE: This config expects the following to be appended to your kernel cmdline
 *       "memmap=0x5200000$0x100000000"
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_system header;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[51];
	struct jailhouse_irqchip irqchips[1];
	struct jailhouse_pio pio_regions[15];
	struct jailhouse_pci_device pci_devices[25];
	struct jailhouse_pci_capability pci_caps[81];
} __attribute__((packed)) config = {
	.header = {
		.signature = JAILHOUSE_SYSTEM_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.flags = JAILHOUSE_SYS_VIRTUAL_DEBUG_CONSOLE,
		.hypervisor_memory = {
			.phys_start = 0x100000000,
			.size = 0x600000,
		},
		.debug_console = {
			.address = 0x3f8,
			.type = JAILHOUSE_CON_TYPE_8250,
			.flags = JAILHOUSE_CON_ACCESS_PIO |
				 JAILHOUSE_CON_REGDIST_1,
		},
		.platform_info = {
			.pci_mmconfig_base = 0xc0000000,
			.pci_mmconfig_end_bus = 0xff,
			.iommu_units = {
				{
					.type = JAILHOUSE_IOMMU_INTEL,
					.base = 0xfed90000,
					.size = 0x1000,
				},
				{
					.type = JAILHOUSE_IOMMU_INTEL,
					.base = 0xfed91000,
					.size = 0x1000,
				},
			},
			.x86 = {
				.pm_timer_address = 0x1808,
				.vtd_interrupt_limit = 256,
			},
		},
		.root_cell = {
			.name = "RootCell",
			.cpu_set_size = sizeof(config.cpus),
			.num_memory_regions = ARRAY_SIZE(config.mem_regions),
			.num_irqchips = ARRAY_SIZE(config.irqchips),
			.num_pio_regions = ARRAY_SIZE(config.pio_regions),
			.num_pci_devices = ARRAY_SIZE(config.pci_devices),
			.num_pci_caps = ARRAY_SIZE(config.pci_caps),
		},
	},

	.cpus = {
		0x000000000000ffff,
	},

	.mem_regions = {
		/* MemRegion: 00000000-0009dfff : System RAM */
		{
			.phys_start = 0x0,
			.virt_start = 0x0,
			.size = 0x9e000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 0009f000-0009ffff : System RAM */
		{
			.phys_start = 0x9f000,
			.virt_start = 0x9f000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 000a0000-000bffff : PCI Bus 0000:00 */
		{
			.phys_start = 0xa0000,
			.virt_start = 0xa0000,
			.size = 0x20000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 000f0000-000fffff : System ROM */
		{
			.phys_start = 0xf0000,
			.virt_start = 0xf0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 00100000-1c1bafff : System RAM */
		{
			.phys_start = 0x100000,
			.virt_start = 0x100000,
			.size = 0x1c0bb000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 1c3fc000-214d1fff : System RAM */
		{
			.phys_start = 0x1c3fc000,
			.virt_start = 0x1c3fc000,
			.size = 0x50d6000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 214d3000-24917fff : System RAM */
		{
			.phys_start = 0x214d3000,
			.virt_start = 0x214d3000,
			.size = 0x3445000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 27a18000-27b1bfff : ACPI Tables */
		{
			.phys_start = 0x27a18000,
			.virt_start = 0x27a18000,
			.size = 0x104000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 27b1c000-27fa4fff : ACPI Non-volatile Storage */
		{
			.phys_start = 0x27b1c000,
			.virt_start = 0x27b1c000,
			.size = 0x489000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 28fff000-28ffffff : System RAM */
		{
			.phys_start = 0x28fff000,
			.virt_start = 0x28fff000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 4f800000-4f800fff : r8169 */
		{
			.phys_start = 0x4f800000,
			.virt_start = 0x4f800000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4f900000-4f900fff : r8169 */
		{
			.phys_start = 0x4f900000,
			.virt_start = 0x4f900000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4fa00000-4fafffff : 0000:01:00.0 */
		{
			.phys_start = 0x4fa00000,
			.virt_start = 0x4fa00000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4fb01000-4fb03fff : 0000:01:00.0 */
		{
			.phys_start = 0x4fb01000,
			.virt_start = 0x4fb01000,
			.size = 0x3000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4fc00000-4fc0ffff : 0000:02:00.0 */
		{
			.phys_start = 0x4fc00000,
			.virt_start = 0x4fc00000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4fc11000-4fc13fff : 0000:02:00.0 */
		{
			.phys_start = 0x4fc11000,
			.virt_start = 0x4fc11000,
			.size = 0x3000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4fd00000-4fd01fff : ahci */
		{
			.phys_start = 0x4fd00000,
			.virt_start = 0x4fd00000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4fd02000-4fd027ff : ahci */
		{
			.phys_start = 0x4fd02000,
			.virt_start = 0x4fd02000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4fd03000-4fd030ff : ahci */
		{
			.phys_start = 0x4fd03000,
			.virt_start = 0x4fd03000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4fd04000-4fd04fff : 0000:00:1f.5 */
		{
			.phys_start = 0x4fd04000,
			.virt_start = 0x4fd04000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fd690000-fd69ffff : INTC1055:00 */
		{
			.phys_start = 0xfd690000,
			.virt_start = 0xfd690000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fd6a0000-fd6affff : INTC1055:00 */
		{
			.phys_start = 0xfd6a0000,
			.virt_start = 0xfd6a0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fd6d0000-fd6dffff : INTC1055:00 */
		{
			.phys_start = 0xfd6d0000,
			.virt_start = 0xfd6d0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fd6e0000-fd6effff : INTC1055:00 */
		{
			.phys_start = 0xfd6e0000,
			.virt_start = 0xfd6e0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed00000-fed003ff : PNP0103:00 */
		{
			.phys_start = 0xfed00000,
			.virt_start = 0xfed00000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed20000-fed7ffff : pnp 00:09 */
		{
			.phys_start = 0xfed20000,
			.virt_start = 0xfed20000,
			.size = 0x60000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: feda0000-feda0fff : pnp 00:09 */
		{
			.phys_start = 0xfeda0000,
			.virt_start = 0xfeda0000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: feda1000-feda1fff : pnp 00:09 */
		{
			.phys_start = 0xfeda1000,
			.virt_start = 0xfeda1000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fedc0000-fedc7fff : pnp 00:09 */
		{
			.phys_start = 0xfedc0000,
			.virt_start = 0xfedc0000,
			.size = 0x8000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 100000000-1005fffff : Jailhouse hypervisor */
		{
			.phys_start = 0x100000000,
			.virt_start = 0x100000000,
			.size = 0x600000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 105200000-10b3ffffff : System RAM */
		{
			.phys_start = 0x105200000,
			.virt_start = 0x105200000,
			.size = 0xfaee00000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 4000000000-40002fffff : efifb */
		{
			.phys_start = 0x4000000000,
			.virt_start = 0x4000000000,
			.size = 0x300000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4010000000-4016ffffff : 0000:00:02.0 */
		{
			.phys_start = 0x4010000000,
			.virt_start = 0x4010000000,
			.size = 0x7000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4017000000-4017000fff : 0000:00:15.0 */
		{
			.phys_start = 0x4017000000,
			.virt_start = 0x4017000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4017001000-4017001fff : 0000:00:15.1 */
		{
			.phys_start = 0x4017001000,
			.virt_start = 0x4017001000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4017002000-4017002fff : 0000:00:1e.0 */
		{
			.phys_start = 0x4017002000,
			.virt_start = 0x4017002000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4017003000-4017003fff : 0000:00:1e.3 */
		{
			.phys_start = 0x4017003000,
			.virt_start = 0x4017003000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 4020000000-40ffffffff : 0000:00:02.0 */
		{
			.phys_start = 0x4020000000,
			.virt_start = 0x4020000000,
			.size = 0xe0000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 6000001000-6000003fff : 0000:06:00.0 */
		{
			.phys_start = 0x6000001000,
			.virt_start = 0x6000001000,
			.size = 0x3000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 6000101000-6000103fff : 0000:05:00.0 */
		{
			.phys_start = 0x6000101000,
			.virt_start = 0x6000101000,
			.size = 0x3000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 6001000000-6001ffffff : 0000:00:02.0 */
		{
			.phys_start = 0x6001000000,
			.virt_start = 0x6001000000,
			.size = 0x1000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 6002000000-60020fffff : ICH HD audio */
		{
			.phys_start = 0x6002000000,
			.virt_start = 0x6002000000,
			.size = 0x100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 6002100000-600210ffff : xhci-hcd */
		{
			.phys_start = 0x6002100000,
			.virt_start = 0x6002100000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 6002110000-6002117fff : 0000:00:0a.0 */
		{
			.phys_start = 0x6002110000,
			.virt_start = 0x6002110000,
			.size = 0x8000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 6002120000-6002123fff : ICH HD audio */
		{
			.phys_start = 0x6002120000,
			.virt_start = 0x6002120000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 6002124000-6002127fff : 0000:00:14.2 */
		{
			.phys_start = 0x6002124000,
			.virt_start = 0x6002124000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 6002128000-60021280ff : 0000:00:1f.4 */
		{
			.phys_start = 0x6002128000,
			.virt_start = 0x6002128000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 600212b000-600212bfff : 0000:00:16.0 */
		{
			.phys_start = 0x600212b000,
			.virt_start = 0x600212b000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 600212e000-600212efff : 0000:00:14.2 */
		{
			.phys_start = 0x600212e000,
			.virt_start = 0x600212e000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 2f000000-4f7fffff : ACPI DMAR RMRR */
		/* PCI device: 00:02.0 */
		{
			.phys_start = 0x2f000000,
			.virt_start = 0x2f000000,
			.size = 0x20800000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 100600000-1051fffff : JAILHOUSE Inmate Memory */
		{
			.phys_start = 0x100600000,
			.virt_start = 0x100600000,
			.size = 0x4c00000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
	},

	.irqchips = {
		/* IOAPIC 2, GSI base 0 */
		{
			.address = 0xfec00000,
			.id = 0x100f7,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
	},

	.pio_regions = {
		/* Port I/O: 0000-001f : dma1 */
		/* PIO_RANGE(0x0, 0x20), */
		/* Port I/O: 0020-0021 : pic1 */
		/* PIO_RANGE(0x20, 0x2), */
		/* Port I/O: 0040-0043 : timer0 */
		PIO_RANGE(0x40, 0x4),
		/* Port I/O: 0050-0053 : timer1 */
		/* PIO_RANGE(0x50, 0x4), */
		/* Port I/O: 0060-0060 : keyboard */
		PIO_RANGE(0x60, 0x1),
		/* Port I/O: 0064-0064 : keyboard */
		PIO_RANGE(0x64, 0x1),
		/* Port I/O: 0070-0071 : rtc0 */
		PIO_RANGE(0x70, 0x2),
		/* Port I/O: 0080-008f : dma page reg */
		/* PIO_RANGE(0x80, 0x10), */
		/* Port I/O: 00a0-00a1 : pic2 */
		/* PIO_RANGE(0xa0, 0x2), */
		/* Port I/O: 00c0-00df : dma2 */
		/* PIO_RANGE(0xc0, 0x20), */
		/* Port I/O: 00f0-00ff : fpu */
		/* PIO_RANGE(0xf0, 0x10), */
		/* Port I/O: 02e0-02e7 : serial */
		/* PIO_RANGE(0x2e0, 0x8), */
		/* Port I/O: 02e8-02ef : serial */
		/* PIO_RANGE(0x2e8, 0x8), */
		/* Port I/O: 02f0-02f7 : serial */
		/* PIO_RANGE(0x2f0, 0x8), */
		/* Port I/O: 02f8-02ff : serial */
		PIO_RANGE(0x2f8, 0x8),
		/* Port I/O: 03e8-03ef : serial */
		/* PIO_RANGE(0x3e8, 0x8), */
		/* Port I/O: 03f8-03ff : serial */
		PIO_RANGE(0x3f8, 0x8),
		/* Port I/O: 0680-069f : pnp 00:07 */
		/* PIO_RANGE(0x680, 0x20), */
		/* Port I/O: 0a00-0a2f : pnp 00:00 */
		/* PIO_RANGE(0xa00, 0x30), */
		/* Port I/O: 0a30-0a3f : pnp 00:00 */
		/* PIO_RANGE(0xa30, 0x10), */
		/* Port I/O: 0a40-0a4f : pnp 00:00 */
		/* PIO_RANGE(0xa40, 0x10), */
		/* Port I/O: 3000-30ff : 0000:06:00.0 */
		PIO_RANGE(0x3000, 0x100),
		/* Port I/O: 4000-40ff : 0000:05:00.0 */
		PIO_RANGE(0x4000, 0x100),
		/* Port I/O: 5000-50ff : 0000:02:00.0 */
		PIO_RANGE(0x5000, 0x100),
		/* Port I/O: 6000-603f : 0000:00:02.0 */
		PIO_RANGE(0x6000, 0x40),
		/* Port I/O: 6060-607f : 0000:00:17.0 */
		PIO_RANGE(0x6060, 0x20),
		/* Port I/O: 6080-6083 : 0000:00:17.0 */
		PIO_RANGE(0x6080, 0x4),
		/* Port I/O: 6090-6097 : 0000:00:17.0 */
		PIO_RANGE(0x6090, 0x8),
		/* Port I/O: efa0-efbf : 0000:00:1f.4 */
		PIO_RANGE(0xefa0, 0x20),
		/* Port I/O: 0x1804 : tiny-demo */
		PIO_RANGE(0x1804, 0x2),
	},

	.pci_devices = {
		/* PCIDevice: 00:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x0,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 1,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:02.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 0,
			.domain = 0x0,
			.bdf = 0x10,
			.bar_mask = {
				0xff000000, 0xffffffff, 0xf0000000,
				0xffffffff, 0xffffffc0, 0x00000000,
			},
			.caps_start = 1,
			.num_caps = 8,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.msi_maskable = 1,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:0a.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x50,
			.bar_mask = {
				0xffff8000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 9,
			.num_caps = 5,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:14.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xa0,
			.bar_mask = {
				0xffff0000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 14,
			.num_caps = 4,
			.num_msi_vectors = 8,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:14.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xa2,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0xfffff000,
				0xffffffff, 0x00000000, 0x00000000,
			},
			.caps_start = 18,
			.num_caps = 1,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:15.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xa8,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 19,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:15.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xa9,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 19,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:16.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xb0,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 21,
			.num_caps = 3,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:17.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xb8,
			.bar_mask = {
				0xffffe000, 0xffffff00, 0xfffffff8,
				0xfffffffc, 0xffffffe0, 0xfffff800,
			},
			.caps_start = 24,
			.num_caps = 3,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1c.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xe0,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 27,
			.num_caps = 8,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1c.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xe5,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 27,
			.num_caps = 8,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1c.7 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xe7,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 27,
			.num_caps = 8,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1e.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xf0,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 19,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1e.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xf3,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 19,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xf8,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xfb,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0xfff00000, 0xffffffff,
			},
			.caps_start = 35,
			.num_caps = 3,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xfc,
			.bar_mask = {
				0xffffff00, 0xffffffff, 0x00000000,
				0x00000000, 0xffffffe0, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.5 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xfd,
			.bar_mask = {
				0xfffff000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 01:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x100,
			.bar_mask = {
				0xfff00000, 0x00000000, 0x00000000,
				0xffffc000, 0x00000000, 0x00000000,
			},
			.caps_start = 38,
			.num_caps = 9,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 1,
			.num_msix_vectors = 5,
			.msix_region_size = 0x1000,
			.msix_address = 0x4fb00000,
		},
		/* PCIDevice: 02:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x200,
			.bar_mask = {
				0xffffff00, 0x00000000, 0xffff0000,
				0xffffffff, 0xffffc000, 0xffffffff,
			},
			.caps_start = 47,
			.num_caps = 12,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 1,
			.num_msix_vectors = 32,
			.msix_region_size = 0x1000,
			.msix_address = 0x4fc10000,
		},
		/* PCIDevice: 03:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x300,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 59,
			.num_caps = 7,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 04:03.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x418,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 66,
			.num_caps = 6,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 04:07.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x438,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 66,
			.num_caps = 6,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 05:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x500,
			.bar_mask = {
				0xffffff00, 0x00000000, 0xfffff000,
				0xffffffff, 0xffffc000, 0xffffffff,
			},
			.caps_start = 72,
			.num_caps = 9,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 4,
			.msix_region_size = 0x1000,
			.msix_address = 0x6000100000,
		},
		/* PCIDevice: 06:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x600,
			.bar_mask = {
				0xffffff00, 0x00000000, 0xfffff000,
				0xffffffff, 0xffffc000, 0xffffffff,
			},
			.caps_start = 72,
			.num_caps = 9,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 4,
			.msix_region_size = 0x1000,
			.msix_address = 0x6000000000,
		},
	},

	.pci_caps = {
		/* PCIDevice: 00:00.0 */
		{
			.id = PCI_CAP_ID_VNDR,
			.start = 0xe0,
			.len = 0x2,
			.flags = 0,
		},
		/* PCIDevice: 00:02.0 */
		{
			.id = PCI_CAP_ID_VNDR,
			.start = 0x40,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x70,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0xac,
			.len = 0x14,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0xd0,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_EXT_CAP_ID_PASID | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x8,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ATS | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x200,
			.len = 0x4,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_PRI | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x300,
			.len = 0x4,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_SRIOV | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x320,
			.len = 0x40,
			.flags = 0,
		},
		/* PCIDevice: 00:0a.0 */
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x70,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0xd0,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x23 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x4,
			.flags = 0,
		},
		{
			.id = 0x23 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x110,
			.len = 0x4,
			.flags = 0,
		},
		{
			.id = 0x23 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x120,
			.len = 0x4,
			.flags = 0,
		},
		/* PCIDevice: 00:14.0 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x70,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x80,
			.len = 0xe,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_VNDR,
			.start = 0x90,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_VNDR,
			.start = 0xb0,
			.len = 0x2,
			.flags = 0,
		},
		/* PCIDevice: 00:14.2 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x80,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* PCIDevice: 00:15.0 */
		/* PCIDevice: 00:15.1 */
		/* PCIDevice: 00:1e.0 */
		/* PCIDevice: 00:1e.3 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x80,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_VNDR,
			.start = 0x90,
			.len = 0x2,
			.flags = 0,
		},
		/* PCIDevice: 00:16.0 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x50,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x8c,
			.len = 0xe,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_VNDR,
			.start = 0xa4,
			.len = 0x2,
			.flags = 0,
		},
		/* PCIDevice: 00:17.0 */
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x80,
			.len = 0xa,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x70,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_SATA,
			.start = 0xa8,
			.len = 0x2,
			.flags = 0,
		},
		/* PCIDevice: 00:1c.0 */
		/* PCIDevice: 00:1c.5 */
		/* PCIDevice: 00:1c.7 */
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x40,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x80,
			.len = 0xa,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_SSVID,
			.start = 0x90,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0xa0,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x0 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x4,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ACS | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x220,
			.len = 0x8,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_PTM | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x150,
			.len = 0xc,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_SECPCI | JAILHOUSE_PCI_EXT_CAP,
			.start = 0xa30,
			.len = 0x10,
			.flags = 0,
		},
		/* PCIDevice: 00:1f.3 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x50,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_VNDR,
			.start = 0x80,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x60,
			.len = 0xe,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* PCIDevice: 01:00.0 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x40,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x50,
			.len = 0x18,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSIX,
			.start = 0x70,
			.len = 0xc,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0xa0,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x40,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_DSN | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x140,
			.len = 0xc,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_LTR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x1c0,
			.len = 0x8,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_PTM | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x1f0,
			.len = 0xc,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_L1SS | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x1e0,
			.len = 0x4,
			.flags = 0,
		},
		/* PCIDevice: 02:00.0 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x40,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x50,
			.len = 0x18,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x70,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_MSIX,
			.start = 0xb0,
			.len = 0xc,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_VPD,
			.start = 0xd0,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x40,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VC | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x148,
			.len = 0x10,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_DSN | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x168,
			.len = 0xc,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_TPH | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x178,
			.len = 0x4,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_LTR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x204,
			.len = 0x8,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_L1SS | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x20c,
			.len = 0x4,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x21c,
			.len = 0x104,
			.flags = 0,
		},
		/* PCIDevice: 03:00.0 */
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x50,
			.len = 0xe,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x78,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x80,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_SSVID,
			.start = 0xc0,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VC | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x10,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x200,
			.len = 0x40,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x300,
			.len = 0xc04,
			.flags = 0,
		},
		/* PCIDevice: 04:03.0 */
		/* PCIDevice: 04:07.0 */
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x50,
			.len = 0xe,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x78,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x80,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_SSVID,
			.start = 0xc0,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VC | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x10,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x200,
			.len = 0x40,
			.flags = 0,
		},
		/* PCIDevice: 05:00.0 */
		/* PCIDevice: 06:00.0 */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x40,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x50,
			.len = 0xe,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x70,
			.len = 0x3c,
			.flags = 0,
		},
		{
			.id = PCI_CAP_ID_MSIX,
			.start = 0xb0,
			.len = 0xc,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_VPD,
			.start = 0xd0,
			.len = 0x2,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x40,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VC | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x140,
			.len = 0x10,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_DSN | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x160,
			.len = 0xc,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_LTR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x170,
			.len = 0x8,
			.flags = 0,
		},
	},
};
