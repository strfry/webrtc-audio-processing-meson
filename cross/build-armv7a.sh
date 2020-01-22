#!/bin/bash

# https://gitlab.kitware.com/cmake/cmake/issues/18739

ARCH="arm"
ABI="armeabi-v7a"
API_LEVEL="21"
BUILD_DIR="armv7a-build"

ANDROID_SDK_HOME="/opt/android"
ANDROID_NDK_HOME="${ANDROID_SDK_HOME}/android-ndk-r21"
TOOLCHAIN="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake"

HOST_ROOT="${ANDROID_NDK_HOME}/toolchains/llvm/prebuilt/linux-x86_64"
SYS_ROOT="${HOST_ROOT}/sysroot"
LIB_PATH="/${SYS_ROOT}/usr/lib/${ARCH}-linux-androideabi:${SYS_ROOT}/usr/lib/${ARCH}-linux-androideabi/${API_LEVEL}:${ANDROID_NDK_HOME}/platforms/android-${API_LEVEL}/arch-${ARCH}/usr/lib"
INC_PATH="${SYS_ROOT}/usr/include"

export PATH="${HOST_ROOT}/bin:${PATH}"

export CFLAGS="-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN} \
  -DANDROID_STL=c++_shared \
  -DANDROID_TOOLCHAIN=clang \
  -DANDROID_PLATFORM=android-${API_LEVEL} \
  -DANDROID_ABI=${ABI}"

echo "building..."

echo "Toolchain: ${TOOLCHAIN}"

rm -rf ${BUILD_DIR}

meson setup --errorlogs  \
  --cross-file cross/android-armhf.ini  \
  --prefix=${ANDROID_NDK_HOME} \
  --includedir=${INC_PATH} \
  --libdir=${LIB_PATH} \
  ${BUILD_DIR} .

#  --build.cmake-prefix-path=${SYS_ROOT} \

ninja -C ${BUILD_DIR}
