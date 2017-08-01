/*
 * GM20B MMU
 *
 * Copyright (c) 2014-2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#include "gk20a/gk20a.h"

#include "mm_gm20b.h"

#include <nvgpu/hw/gm20b/hw_gmmu_gm20b.h>
#include <nvgpu/hw/gm20b/hw_ram_gm20b.h>

void gm20b_mm_set_big_page_size(struct gk20a *g,
				struct nvgpu_mem *mem, int size)
{
	u32 val;

	gk20a_dbg_fn("");

	gk20a_dbg_info("big page size %d\n", size);
	val = nvgpu_mem_rd32(g, mem, ram_in_big_page_size_w());
	val &= ~ram_in_big_page_size_m();

	if (size == SZ_64K)
		val |= ram_in_big_page_size_64kb_f();
	else
		val |= ram_in_big_page_size_128kb_f();

	nvgpu_mem_wr32(g, mem, ram_in_big_page_size_w(), val);
	gk20a_dbg_fn("done");
}

u32 gm20b_mm_get_big_page_sizes(void)
{
	return SZ_64K | SZ_128K;
}

u32 gm20b_mm_get_default_big_page_size(void)
{
	return SZ_128K;
}

bool gm20b_mm_support_sparse(struct gk20a *g)
{
	return true;
}

bool gm20b_mm_is_bar1_supported(struct gk20a *g)
{
	return true;
}

u64 gm20b_gpu_phys_addr(struct gk20a *g,
			struct nvgpu_gmmu_attrs *attrs, u64 phys)
{
	return phys;
}
