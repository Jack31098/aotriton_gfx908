// Copyright © 2023-2025 Advanced Micro Devices, Inc.
// SPDX-License-Identifier: MIT

#include <aotriton/config.h>
#include <aotriton/flash.h>
#include <aotriton/runtime.h>
#include <aotriton/util.h>
#include <flash/shim.attn_fwd.h>
#include <flash/shim.bwd_kernel_dk_dv.h>
#if !defined(AOTRITON_DISABLE_FUSED_BWD)
#include <flash/shim.bwd_kernel_fuse.h>
#endif
#include <flash/shim.bwd_kernel_dq.h>
#include <flash/shim.bwd_preprocess.h>
#include <flash/shim.bwd_preprocess_varlen.h>
#include <iostream>

namespace AOTRITON_NS::v2::flash {
using AttnFwdContext              = AOTRITON_NS::v3::flash::AttnFwdContext;
using BwdPreprocessContext        = AOTRITON_NS::v3::flash::BwdPreprocessContext;
using BwdPreprocessVarlenContext  = AOTRITON_NS::v3::flash::BwdPreprocessVarlenContext;
using BwdKernelDkDvContext        = AOTRITON_NS::v3::flash::BwdKernelDkDvContext;
#if !defined(AOTRITON_DISABLE_FUSED_BWD)
using BwdKernelFuseContext        = AOTRITON_NS::v3::flash::BwdKernelFuseContext;
#endif
using BwdKernelDqContext          = AOTRITON_NS::v3::flash::BwdKernelDqContext;

#define CHECK_FOR_KERNEL(Context) \
  do { \
    Context context; \
    auto [arch_number, mod_number] = context.get_archmod_number(gpu); \
    if (arch_number < 0) { \
      std::cerr << STRINGIFICATION(Context) << ": hipErrorNoBinaryForGpu" << std::endl; \
      return hipErrorNoBinaryForGpu; \
    } \
  } while(0)

hipError_t
check_gpu(AOTRITON_NS::Stream stream_wrap) {
  auto stream = stream_wrap.native();
  auto gpu = getGpuFromStream(stream);
  CHECK_FOR_KERNEL(AttnFwdContext);
  CHECK_FOR_KERNEL(BwdPreprocessContext);
  CHECK_FOR_KERNEL(BwdPreprocessVarlenContext);
  CHECK_FOR_KERNEL(BwdKernelDkDvContext);
#if !defined(AOTRITON_DISABLE_FUSED_BWD)
  CHECK_FOR_KERNEL(BwdKernelFuseContext);
#endif
  CHECK_FOR_KERNEL(BwdKernelDqContext);
  return hipSuccess;
}

} // AOTRITON_NS::v2::flash
