cmd_mediatek/custom/out/wiko/kernel/dct/pmic_drv.o := arm-linux-androideabi-gcc -Wp,-MD,mediatek/custom/out/wiko/kernel/dct/.pmic_drv.o.d  -nostdinc -isystem /home/android/workspace/8513user/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/../lib/gcc/arm-linux-androideabi/4.6.x-google/include -I/home/android/workspace/alps/kernel/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/android/workspace/alps/kernel/include/linux/kconfig.h  -I../mediatek/platform/mt6582/kernel/core/include/ -I../mediatek/kernel/include/ -I../mediatek/custom/wiko/common/ -I../mediatek/platform/mt6582/kernel/drivers/dispsys -I../mediatek/platform/mt6582/kernel/drivers/uart/ -I../mediatek/platform/mt6582/kernel/drivers/video -I../mediatek/custom/out/wiko/kernel/rtc/ -I../mediatek/custom/out/wiko/kernel/flashlight/ -I../mediatek/custom/out/wiko/kernel/headset/ -I../mediatek/custom/out/wiko/kernel/battery/ -I../mediatek/custom/out/wiko/kernel/leds/ -I../mediatek/custom/out/wiko/kernel/accelerometer/ -I../mediatek/custom/out/wiko/kernel/alsps/ -I../mediatek/custom/out/wiko/kernel/core/ -I../mediatek/custom/out/wiko/kernel/imgsensor/ -I../mediatek/custom/out/wiko/kernel/dct/ -I../mediatek/custom/out/wiko/kernel/kpd/ -I../mediatek/custom/out/wiko/kernel/camera/ -I../mediatek/custom/out/wiko/kernel/vibrator/ -I../mediatek/custom/out/wiko/kernel/magnetometer/ -I../mediatek/custom/out/wiko/kernel/hdmi/inc/ -I../mediatek/custom/out/wiko/kernel/gyroscope/inc/ -I../mediatek/custom/out/wiko/kernel/flashlight/inc/ -I../mediatek/custom/out/wiko/kernel/lens/inc/ -I../mediatek/custom/out/wiko/kernel/lens/ -I../mediatek/custom/out/wiko/kernel/headset/inc/ -I../mediatek/custom/out/wiko/kernel/barometer/inc/ -I../mediatek/custom/out/wiko/kernel/cam_cal/inc/ -I../mediatek/custom/out/wiko/kernel/cam_cal/ -I../mediatek/custom/out/wiko/kernel/leds/inc/ -I../mediatek/custom/out/wiko/kernel/touchpanel/ -I../mediatek/custom/out/wiko/kernel/lcm/ -I../mediatek/custom/out/wiko/kernel/lcm/inc/ -I../mediatek/custom/out/wiko/kernel/accelerometer/inc/ -I../mediatek/custom/out/wiko/kernel/ssw/inc/ -I../mediatek/custom/out/wiko/kernel/ssw/ -I../mediatek/custom/out/wiko/kernel/alsps/inc/ -I../mediatek/custom/out/wiko/kernel/sound/inc/ -I../mediatek/custom/out/wiko/kernel/sound/ -I../mediatek/custom/out/wiko/kernel/imgsensor/inc/ -I../mediatek/custom/out/wiko/kernel/jogball/inc/ -I../mediatek/custom/out/wiko/kernel/ccci/ -I../mediatek/custom/out/wiko/kernel/./ -I../mediatek/custom/out/wiko/kernel/eeprom/inc/ -I../mediatek/custom/out/wiko/kernel/eeprom/ -I../mediatek/custom/out/wiko/kernel/magnetometer/inc/ -I../mediatek/custom/out/wiko/hal/lens/ -I../mediatek/custom/out/wiko/hal/audioflinger/ -I../mediatek/custom/out/wiko/hal/sensors/ -I../mediatek/custom/out/wiko/hal/imgsensor/ -I../mediatek/custom/out/wiko/hal/camera/ -I../mediatek/custom/out/wiko/hal/aal/ -I../mediatek/custom/out/wiko/hal/inc/ -I../mediatek/custom/out/wiko/hal/camera/inc/ -I../mediatek/custom/out/wiko/hal/flashlight/ -I../mediatek/custom/out/wiko/hal/ant/ -I../mediatek/custom/out/wiko/hal/matv/ -I../mediatek/custom/out/wiko/hal/cam_cal/ -I../mediatek/custom/out/wiko/hal/bluetooth/ -I../mediatek/custom/out/wiko/hal/vt/ -I../mediatek/custom/out/wiko/hal/fmradio/ -I../mediatek/custom/out/wiko/hal/combo/ -I../mediatek/custom/out/wiko/hal/eeprom/ -I../mediatek/custom/out/wiko/common -D__KERNEL__ -mlittle-endian -Imediatek/platform/mt6582/kernel/core/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -fno-pic -marm -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -DWIKO_STS_NVRAM -DCUSTOM_WIKO_VERSION -DPROJECT_S8513 -DMTK_BT_PROFILE_AVRCP -DMTK_GPS_SUPPORT -DMTK_FM_SUPPORT -DMTK_USES_HD_VIDEO -DMTK_AUDIO_ADPCM_SUPPORT -DMTK_GEMINI_SMART_3G_SWITCH -DMTK_BT_PROFILE_MANAGER -DMTK_FM_RECORDING_SUPPORT -DMTK_NFC_SE_NUM -DMTK_IPV6_SUPPORT -DMTK_BT_PROFILE_PBAP -DMTK_BT_PROFILE_PAN -DMTK_BT_PROFILE_A2DP -DMTK_BT_PROFILE_HFP -DMTK_HDR_SUPPORT -DHAVE_AACENCODE_FEATURE -DMTK_WIFI_HOTSPOT_SUPPORT -DMTK_COMBO_SUPPORT -DMTK_BT_PROFILE_OPP -DMTK_FLIGHT_MODE_POWER_OFF_MD -DMTK_MULTI_STORAGE_SUPPORT -DMTK_WFD_SUPPORT -DMTK_ENABLE_VIDEO_EDITOR -DMTK_EAP_SIM_AKA -DMTK_AUDIO_RAW_SUPPORT -DMTK_WAPI_SUPPORT -DMTK_FD_SUPPORT -DHAVE_ADPCMENCODE_FEATURE -DMTK_WFD_VIDEO_FORMAT -DMTK_FACEBEAUTY_SUPPORT -DMTK_HANDSFREE_DMNR_SUPPORT -DMTK_YAML_SCATTER_FILE_SUPPORT -DMTK_CAMERA_BSP_SUPPORT -DMTK_DVFS_DISABLE_LOW_VOLTAGE_SUPPORT -DMTK_HIGH_QUALITY_THUMBNAIL -DMTK_FM_RX_SUPPORT -DMTK_ENABLE_MD1 -DHAVE_XLOG_FEATURE -DMTK_VOICE_UNLOCK_SUPPORT -DMTK_MATV_ANALOG_SUPPORT -DMTK_AUTORAMA_SUPPORT -DCUSTOM_KERNEL_ACCELEROMETER -DMTK_BT_SUPPORT -DMTK_VT3G324M_SUPPORT -DMTK_KERNEL_POWER_OFF_CHARGING -DCUSTOM_KERNEL_MAGNETOMETER -DMTK_BT_PROFILE_HIDH -DMTK_ION_SUPPORT -DMTK_PRODUCT_INFO_SUPPORT -DMTK_WLAN_SUPPORT -DMTK_PQ_SUPPORT -DMTK_TETHERINGIPV6_SUPPORT -DMTK_UART_USB_SWITCH -DMTK_IPOH_SUPPORT -DMTK_USES_VR_DYNAMIC_QUALITY_MECHANISM -DMTK_PLATFORM_OPTIMIZE -DMTK_SW_BTCVSD -DMTK_BT_PROFILE_SPP -DMTK_BT_30_SUPPORT -DMTK_BQ24158_SUPPORT -DMTK_LCEEFT_SUPPORT -DMTK_BT_21_SUPPORT -DMTK_DHCPV6C_WIFI -DHAVE_AWBENCODE_FEATURE -DMTK_WEB_NOTIFICATION_SUPPORT -DMTK_MD_SHUT_DOWN_NT -DMTK_SPH_EHN_CTRL_SUPPORT -DMTK_WB_SPEECH_SUPPORT -DCUSTOM_KERNEL_ALSPS -DMTK_SENSOR_SUPPORT -DMTK_M4U_SUPPORT -DMTK_EMMC_SUPPORT -DMTK_2SDCARD_SWAP -DTINNO_FEATURE_ONEKEY_LOCK -DTINNO_FEATURE_DRIVE_PROFILE -DTINNO_FEATURE_WIFI_HOTSPOT_AUTOPOP -DTINNO_PROJECT_NAME -DMT6582 -DFM50AF -DSENSORDRIVE -DDUMMY_LENS -DSENSORDRIVE -DHD720 -DHX8394A_DSI_VDO -DOTM1283A_HD720_DSI_VDO -DIMX111_MIPI_RAW -DMTK_CONSYS_MT6582 -DMT6620 -DCONSTANT_FLASHLIGHT -DOV5648_MIPI_RAW -DDUMMY_LENS -DMTK_AUDIO_BLOUD_CUSTOMPARAMETER_V4 -DIMX111_MIPI_RAW -DOV5648_MIPI_RAW -DFM_DIGITAL_INPUT -DCONSYS_6582 -DMTK_GPS_MT6582 -DFM50AF -DFM_DIGITAL_OUTPUT -DMT6627_FM -DMTK_SIM1_SOCKET_TYPE=\"1\" -DMTK_TOUCH_PHYSICAL_ROTATION_RELATIVE_TO_LCM=\"0\" -DMTK_LCM_PHYSICAL_ROTATION=\"0\" -DMTK_NEON_SUPPORT=\"yes\" -DCUSTOM_KERNEL_SSW=\"ssw_single\" -DMTK_SHARE_MODEM_SUPPORT=\"2\" -DLCM_HEIGHT=\"1280\" -DMTK_SHARE_MODEM_CURRENT=\"2\" -DLCM_WIDTH=\"720\" -DMTK_SIM2_SOCKET_TYPE=\"1\" -Wframe-larger-than=1400 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(pmic_drv)"  -D"KBUILD_MODNAME=KBUILD_STR(pmic_drv)" -c -o mediatek/custom/out/wiko/kernel/dct/pmic_drv.o mediatek/custom/out/wiko/kernel/dct/pmic_drv.c

source_mediatek/custom/out/wiko/kernel/dct/pmic_drv.o := mediatek/custom/out/wiko/kernel/dct/pmic_drv.c

deps_mediatek/custom/out/wiko/kernel/dct/pmic_drv.o := \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/android/workspace/alps/kernel/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  arch/arm/include/generated/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /home/android/workspace/alps/kernel/arch/arm/include/asm/posix_types.h \
  include/asm-generic/posix_types.h \
  ../mediatek/platform/mt6582/kernel/core/include/mach/mt_typedefs.h \
  include/linux/bug.h \
    $(wildcard include/config/generic/bug.h) \
  /home/android/workspace/alps/kernel/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/debug/bugverbose.h) \
    $(wildcard include/config/arm/lpae.h) \
  include/linux/linkage.h \
  /home/android/workspace/alps/kernel/arch/arm/include/asm/linkage.h \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/smp.h) \
  ../mediatek/platform/mt6582/kernel/core/include/mach/mt_pm_ldo.h \

mediatek/custom/out/wiko/kernel/dct/pmic_drv.o: $(deps_mediatek/custom/out/wiko/kernel/dct/pmic_drv.o)

$(deps_mediatek/custom/out/wiko/kernel/dct/pmic_drv.o):
