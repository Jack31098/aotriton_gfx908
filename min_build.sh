cmake -S /home/jack/code/aotriton -B /home/jack/code/aotriton/min_build  -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=/home/jack/code/aotriton/min_install \
  -DPython3_EXECUTABLE=/usr/bin/python3.12 \
  -DVENV_DIR=/home/jack/code/aotriton/venv \
  -DPython3_INCLUDE_DIR=/usr/include/python3.12 \
  -DPython3_LIBRARY=/usr/lib/x86_64-linux-gnu/libpython3.12.so \
  -DAOTRITON_ENABLE_SUFFIX=ON \
  -DAOTRITON_DISABLE_FUSED_BWD=OFF \
  -DAOTRITON_TARGET_ARCH=gfx908

# 编译和安wq装
ninja -C min_build -j24
ninja -C min_build install
