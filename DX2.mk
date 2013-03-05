ifeq ($(DX2_WIFI_BUILD),true)
	BUILD_WLAN := true
	ifeq ($DX2_WIFI_TYPE,wext)	
		WPA_SUPPLICANT_VERSION				:= VER_0_8_X
		BOARD_WPA_DRIVER					:= WEXT
		BOARD_HOSTAPD_DRIVER				:= WEXT
		WIFI_DRIVER_FW_PATH_AP 				:= "/system/etc/firmware/fw_bcm4334_apsta.bin"
		WIFI_DRIVER_FW_PATH_STA 			:= "/system/etc/firmware/fw_bcm4334.bin"
		WIFI_DRIVER_FW_PATH_P2P 			:= "/system/etc/firmware/fw_bcm4334_p2p.bin"
		WIFI_DRIVER_MODULE_NAME 			:= "dhd"
		WIFI_DRIVER_MODULE_PATH 			:= "/system/lib/modules/dhd.ko"
		WIFI_DRIVER_FW_PATH_PARAM   		:= "/sys/module/dhd/parameters/firmware_path"
		WIFI_DRIVER_MODULE_ARG 				:= "firmware_path=/system/etc/firmware/bcmdhd.bin nvram_path=/etc/calibration"
		WIFI_BAND		 					:= 802_11_ABG
	endif
	ifeq ($DX2_WIFI_TYPE,bcm4334)	
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
	endif
ifneq ($(DX2_WIFI_BUILD),true)
	PRODUCT_COPY_FILES += \
	device/htc/msm8960-common/dx2_modules/bluetooth-power.ko:/system/lib/modules/bluetooth-power.ko \
    device/htc/msm8960-common/dx2_modules/bcmdhd.ko:/system/lib/modules/bcmdhd.ko
endif
