#!/usr/bin/env bash
set -e

cmake -B build \
    -DAEL_USE_PICO_SDK=true \
    -DAEL_PICO_IMPORT=false \
    -DAEL_BOARD=pico_w \
    -DAEL_TOOLCHAIN_PATH=$(dirname "$(which arm-none-eabi-gcc)") &&
    cmake --build build --parallel &&
    sudo picotool load -F build/adxl345-accel.uf2 &&
    sleep 2 &&
    sudo picotool reboot -a
