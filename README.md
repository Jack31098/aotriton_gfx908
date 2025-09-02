# AOTriton MI100 Flash Attention Support

## Project Overview

This project enables PyTorch Scaled Dot-Product Attention (SDPA) Flash Attention support for AMD MI100 GPUs, specifically targeting head dimensions of 32 and 64. It validates the correctness of both forward and backward passes for these configurations.

**Based on AMD's Official AOTriton**: This project is derived from and builds upon [AMD's official AOTriton repository](https://github.com/ROCm/aotriton). All core functionality and architecture credit goes to the original AMD development team.

## Project Goals

- Enable Flash Attention support for AMD MI100 GPUs
- Validate forward and backward pass correctness for head_dim = 32 and 64
- Optimize Flash Attention kernels specifically for MI100 architecture
- Integrate optimized kernels into PyTorch's SDPA implementation

## Implementation Steps

### 1. Minimal AOTriton Compilation
Build a minimal version of AOTriton to establish the basic compilation pipeline and dependencies.

### 2. PyTorch Integration with AOTriton
Compile PyTorch with AOTriton linking to enable the Flash Attention backend integration.

### 3. Flash Attention Kernel Tuning for MI100
Use cpptune to optimize Flash Attention kernels specifically for MI100 architecture characteristics.

### 4. Complete AOTriton Build with MI100 Tuning Data
Perform a full AOTriton compilation incorporating the MI100-specific tuning parameters.

### 5. PyTorch Dependency Replacement
Replace PyTorch's AOTriton dependency linking to point to the optimized MI100-specific build.

## Build Instructions

```bash
pip install -r requirements.txt
mkdir build
cd build
export PKG_CONFIG_PATH="${PKG_CONFIG_PATH}:${CONDA_PREFIX}/lib/pkgconfig"
cmake .. -DCMAKE_INSTALL_PREFIX=./install_dir -DCMAKE_BUILD_TYPE=Release -DAOTRITON_GPU_BUILD_TIMEOUT=0 -G Ninja
# Use ccmake to tweak options
ninja install/strip  # Use `ninja install` to keep symbols
```

The library and the header file can be found under `build/install_dir` afterwards.
You may ignore the `export PKG_CONFIG_PATH` part if you're not building with conda.

Note: do not run `ninja` separately, due to the limit of the current build
system, `ninja install` will run the whole build process unconditionally.

### Prerequisites

* `python >= 3.10`
* `gcc >= 8` or `clang >= 10`
  - For Designated initializers, but only gcc >= 9 is tested.
  - The binary delivery is compiled with gcc13
* `cmake >= 3.26`
  - Only `cmake >= 3.30` is tested
* `ninja`
  - Only `ninja >= 1.11` is tested
* `liblzma`
  - Common names are `liblzma-dev` or `xz-devel`.

## Kernel Generation

The kernel definition for generation is done in
[rules.py](https://github.com/ROCm/aotriton/blob/main/python/rules.py). Edits
to this file are needed for each new kernel, but it is extensible and generic.

Include files can be added in
[this](https://github.com/ROCm/aotriton/tree/main/include/aotriton) directory.

The final build output is an archive object file any new project may link
against.

The archive file and header files are installed in the path specified by
`CMAKE_INSTALL_PREFIX`.

## Kernel Support

Currently the first kernel supported is FlashAttention as based on the
[algorithm from Tri Dao](https://github.com/Dao-AILab/flash-attention).

This project extends support specifically for AMD MI100 GPUs with optimized kernels.

## Acknowledgments

This project is built upon [AMD's official AOTriton repository](https://github.com/ROCm/aotriton). We acknowledge and thank the AMD ROCm team for their foundational work on AOTriton and Flash Attention kernel implementation.
