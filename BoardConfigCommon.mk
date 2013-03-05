# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#
# This file sets variables that control the way modules are built
# thorughout the system. It should not be used to conditionally
# disable makefiles (the proper mechanism to control what gets
# included in a build is to use PRODUCT_PACKAGES in a product
# definition file).
#

# WARNING: This line must come *before* including the proprietary
# variant, so that it gets overwritten by the parent (which goes
# against the traditional rules of inheritance).

# Include path
TARGET_SPECIFIC_HEADER_PATH := device/htc/msm8960-common/include

BOARD_VENDOR := htc

# Bootloader
TARGET_NO_BOOTLOADER 			:= true

# Camera
TARGET_PROVIDES_CAMERA_HAL 		:= true

# Kernel
TARGET_KERNEL_SOURCE := kernel/htc/msm8960

# Platform
TARGET_BOARD_PLATFORM := msm8960
TARGET_BOARD_PLATFORM_GPU := qcom-adreno320
TARGET_BOOTLOADER_BOARD_NAME := DLX
TARGET_BOOTLOADER_NAME := dlx

# Architecture
TARGET_GLOBAL_CFLAGS += -mfpu=neon -mfloat-abi=softfp
TARGET_GLOBAL_CPPFLAGS += -mfpu=neon -mfloat-abi=softfp
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_CPU_SMP := true
TARGET_ARCH := arm
TARGET_ARCH_VARIANT := armv7-a-neon
ARCH_ARM_HAVE_TLS_REGISTER := true
TARGET_CPU_SMP := true
TARGET_USE_KRAIT_BIONIC_OPTIMIZATION := true

# Flags
COMMON_GLOBAL_CFLAGS += -DQCOM_HARDWARE

# Preload bootanimation
TARGET_BOOTANIMATION_PRELOAD		:= true

# QCOM hardware
BOARD_USES_QCOM_HARDWARE			:= true

# Audio   
BOARD_USES_ALSA_AUDIO 				:= true
BOARD_HAVE_HTC_AUDIO	 			:= true

# Bluetooth
BOARD_HAVE_BLUETOOTH 				:= true
BOARD_HAVE_BLUETOOTH_BCM			:= true
TARGET_NEEDS_BLUETOOTH_INIT_DELAY	:= true

# FM radio
BOARD_HAVE_QCOM_FM := true
COMMON_GLOBAL_CFLAGS += -DQCOM_FM_ENABLED

# QCOM GPS
BOARD_USES_QCOM_GPS := true

# Graphics
COMMON_GLOBAL_CFLAGS += -DQCOM_NO_SECURE_PLAYBACK
BUILD_EMULATOR_OPENGL := false
TARGET_NO_HW_VSYNC := true
TARGET_USES_C2D_COMPOSITION := true
BOARD_EGL_CFG := device/htc/msm8960-common/configs/egl.cfg
BOARD_EGL_NEEDS_LEGACY_FB := true
USE_OPENGL_RENDERER := true
TARGET_USES_ION := true
TARGET_USES_OVERLAY := true
TARGET_USES_SF_BYPASS := true

# Wifi
DX2_BUILD_WIFI						:= true
WPA_SUPPLICANT_VERSION				:= VER_0_8_X
BOARD_WLAN_DEVICE_REV 				:= bcm4334
BOARD_HOSTAPD_DRIVER				:= NL80211
WIFI_DRIVER_FW_PATH_AP 				:= "/system/etc/firmware/fw_bcm4334_apsta.bin"
WIFI_DRIVER_FW_PATH_STA 			:= "/system/etc/firmware/fw_bcm4334.bin"
WIFI_DRIVER_FW_PATH_P2P 			:= "/system/etc/firmware/fw_bcm4334_p2p.bin"
WIFI_DRIVER_MODULE_NAME 			:= "bcmdhd"
WIFI_DRIVER_MODULE_PATH 			:= "/system/lib/modules/bcmdhd.ko"
WIFI_DRIVER_FW_PATH_PARAM   		:= "/sys/module/bcmdhd/parameters/firmware_path"
WIFI_DRIVER_MODULE_ARG 				:= "firmware_path=/system/etc/firmware/bcmdhd.bin nvram_path=/etc/calibration"
WIFI_BAND		 					:= 802_11_ABG

# Webkit
ENABLE_WEBGL := true 
TARGET_FORCE_CPU_UPLOAD := true
