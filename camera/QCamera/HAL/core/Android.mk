OLD_LOCAL_PATH := $(LOCAL_PATH)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

DLOPEN_LIBMMCAMERA:=0

LOCAL_CFLAGS:= -DDLOPEN_LIBMMCAMERA=$(DLOPEN_LIBMMCAMERA)

ifeq ($(strip $(TARGET_USES_ION)),true)
        LOCAL_CFLAGS += -DUSE_ION
endif

LOCAL_CFLAGS += -DCAMERA_ION_HEAP_ID=ION_CP_MM_HEAP_ID # 8660=SMI, Rest=EBI
LOCAL_CFLAGS += -DCAMERA_ZSL_ION_HEAP_ID=ION_CP_MM_HEAP_ID

LOCAL_CFLAGS+= -DHW_ENCODE
LOCAL_CFLAGS+= -DUSE_NEON_CONVERSION

ifeq ($(call is-board-platform,msm8974),true)
        LOCAL_CFLAGS += -DCAMERA_GRALLOC_HEAP_ID=GRALLOC_USAGE_PRIVATE_MM_HEAP
        LOCAL_CFLAGS += -DCAMERA_GRALLOC_FALLBACK_HEAP_ID=GRALLOC_USAGE_PRIVATE_IOMMU_HEAP
        LOCAL_CFLAGS += -DCAMERA_ION_FALLBACK_HEAP_ID=ION_IOMMU_HEAP_ID
        LOCAL_CFLAGS += -DCAMERA_ZSL_ION_FALLBACK_HEAP_ID=ION_IOMMU_HEAP_ID
        LOCAL_CFLAGS += -DCAMERA_GRALLOC_CACHING_ID=0
        LOCAL_CFLAGS += -DNUM_RECORDING_BUFFERS=9
else ifeq ($(call is-board-platform,msm8960),true)
        LOCAL_CFLAGS += -DCAMERA_GRALLOC_HEAP_ID=GRALLOC_USAGE_PRIVATE_MM_HEAP
        LOCAL_CFLAGS += -DCAMERA_GRALLOC_FALLBACK_HEAP_ID=GRALLOC_USAGE_PRIVATE_IOMMU_HEAP
        LOCAL_CFLAGS += -DCAMERA_ION_FALLBACK_HEAP_ID=ION_IOMMU_HEAP_ID
        LOCAL_CFLAGS += -DCAMERA_ZSL_ION_FALLBACK_HEAP_ID=ION_IOMMU_HEAP_ID
        LOCAL_CFLAGS += -DCAMERA_GRALLOC_CACHING_ID=0
        LOCAL_CFLAGS += -DNUM_RECORDING_BUFFERS=5
else ifeq ($(call is-chipset-prefix-in-board-platform,msm8660),true)
        LOCAL_CFLAGS += -DCAMERA_GRALLOC_HEAP_ID=GRALLOC_USAGE_PRIVATE_CAMERA_HEAP
        LOCAL_CFLAGS += -DCAMERA_GRALLOC_FALLBACK_HEAP_ID=GRALLOC_USAGE_PRIVATE_IOMMU_HEAP # Don't Care
        LOCAL_CFLAGS += -DCAMERA_ION_FALLBACK_HEAP_ID=ION_IOMMU_HEAP_ID # EBI
        LOCAL_CFLAGS += -DCAMERA_ZSL_ION_FALLBACK_HEAP_ID=ION_IOMMU_HEAP_ID
        LOCAL_CFLAGS += -DCAMERA_GRALLOC_CACHING_ID=0
        LOCAL_CFLAGS += -DNUM_RECORDING_BUFFERS=5
else
        LOCAL_CFLAGS += -DCAMERA_GRALLOC_HEAP_ID=GRALLOC_USAGE_PRIVATE_CAMERA_HEAP
        LOCAL_CFLAGS += -DCAMERA_GRALLOC_FALLBACK_HEAP_ID=GRALLOC_USAGE_PRIVATE_CAMERA_HEAP # Don't Care
        LOCAL_CFLAGS += -DCAMERA_GRALLOC_CACHING_ID=GRALLOC_USAGE_PRIVATE_UNCACHED #uncached
        LOCAL_CFLAGS += -DCAMERA_ION_FALLBACK_HEAP_ID=ION_CAMERA_HEAP_ID
        LOCAL_CFLAGS += -DCAMERA_ZSL_ION_FALLBACK_HEAP_ID=ION_CAMERA_HEAP_ID
        LOCAL_CFLAGS += -DNUM_RECORDING_BUFFERS=5
endif

LOCAL_HAL_FILES := \
        src/QCameraHAL.cpp \
        src/QCameraHWI_Parm.cpp \
        src/QCameraHWI.cpp \
        src/QCameraHWI_Preview.cpp \
        src/QCameraHWI_Record.cpp \
        src/QCameraHWI_Still.cpp \
        src/QCameraHWI_Rdi.cpp \
        src/QCameraHWI_Mem.cpp \
        src/QCameraParameters.cpp\
        src/QCameraStream.cpp\
        ../usbcamcore/src/QualcommUsbCamera.cpp\
        ../usbcamcore/src/QCameraMjpegDecode.cpp\
        ../usbcamcore/src/QCameraUsbParm.cpp

LOCAL_HAL_WRAPPER_FILES := ../wrapper/QualcommCamera.cpp

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../wrapper \
        $(LOCAL_PATH)/inc \
        $(LOCAL_PATH)/../usbcamcore/inc\
        $(LOCAL_PATH)/../../stack/mm-camera-interface/inc \
        $(LOCAL_PATH)/../../stack/mm-jpeg-interface/inc \
        $(LOCAL_PATH)/../../../ \
        $(TARGET_OUT_INTERMEDIATES)/include/mm-camera-interface \
#       $(TARGET_OUT_INTERMEDIATES)/include/mm-jpeg-interface\

# may need remove this includes
LOCAL_C_INCLUDES += $(TARGET_OUT_HEADERS)/mm-camera
#LOCAL_C_INCLUDES += $(TARGET_OUT_HEADERS)/mm-still
LOCAL_C_INCLUDES += $(TARGET_OUT_HEADERS)/mm-still/jpeg
#end

LOCAL_C_INCLUDES += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_C_INCLUDES += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include/media
LOCAL_ADDITIONAL_DEPENDENCIES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr

LOCAL_C_INCLUDES += hardware/qcom/display/libgralloc \
        hardware/qcom/display/libgenlock \
        hardware/qcom/media/libstagefrighthw

# if debug service layer and up , use stub camera!
LOCAL_C_INCLUDES += \
        frameworks/base/services/camera/libcameraservice

LOCAL_SRC_FILES := \
        $(LOCAL_HAL_WRAPPER_FILES) \
        $(LOCAL_HAL_FILES)

LOCAL_SHARED_LIBRARIES := libutils libui libcamera_client liblog libcutils libmmjpeg
LOCAL_SHARED_LIBRARIES += libmmcamera_interface
LOCAL_SHARED_LIBRARIES += libgenlock libbinder libmmjpeg_interface libhardware

LOCAL_CFLAGS += -include bionic/libc/kernel/common/linux/socket.h

LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_MODULE:= camera.$(TARGET_BOARD_PLATFORM)
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

LOCAL_PATH := $(OLD_LOCAL_PATH)
