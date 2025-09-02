
cmake -S /home/jack/code/aotriton -B /home/jack/code/aotriton/cpptune_build  -G Ninja \
	-DCMAKE_INSTALL_PREFIX=./install_dir \
	-DCMAKE_BUILD_TYPE=Release \
	-DAOTRITON_BUILD_FOR_TUNING=ON \
	-DAOTRITON_NAME_SUFFIX=test0 \
	-DAOTRITON_TARGET_ARCH=gfx908 \
	-DAOTRITON_OVERRIDE_TARGET_GPUS=gfx908_mod0 \
	-DPython3_EXECUTABLE=/usr/bin/python3.12 \
	-DVENV_DIR=/home/jack/code/aotriton/venv \
	-DPython3_INCLUDE_DIR=/usr/include/python3.12 \
        -DPython3_LIBRARY=/usr/lib/x86_64-linux-gnu/libpython3.12.so
