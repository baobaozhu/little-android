#
# Product-specific compile-time definitions.
#

# The generic product target doesn't have any hardware-specific pieces.
TARGET_NO_BOOTLOADER := true

TARGET_ARCH := x86
TARGET_CPU_ABI := x86
#TARGET_ARCH_VARIANT := x86-atom
TARGET_PRELINK_MODULE := false
TARGET_BOARD_PLATFORM := android-x86
#TARGET_INITRD_SCRIPTS := device/generic/x86/android-x86_info

# Some framework code requires this to enable BT
BOARD_HAVE_BLUETOOTH := false

# customize the malloced address to be 16-byte aligned
BOARD_MALLOC_ALIGNMENT := 16

# Enable dex-preoptimization to speed up the first boot sequence
# of an SDK AVD. Note that this operation only works on Linux for now
ifeq ($(HOST_OS),linux)
WITH_DEXPREOPT := true
endif

TARGET_USERIMAGES_USE_EXT4 := true
TARGET_BOOTIMAGE_USE_EXT2 := true
TARGET_USERIMAGES_SPARSE_EXT_DISABLED := true
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 104857600

# the following variables could be overridden
TARGET_NO_KERNEL ?= false
TARGET_NO_RECOVERY ?= true
TARGET_PROVIDES_INIT_RC ?= true
TARGET_CPU_SMP ?= true

TARGET_USE_DISKINSTALLER ?= false

BOARD_USES_GENERIC_AUDIO ?= false
BOARD_USES_ALSA_AUDIO ?= false
BUILD_WITH_ALSA_UTILS ?= false
BOARD_HAS_GPS_HARDWARE ?= false

BUILD_EMULATOR ?= false
BUILD_STANDALONE_EMULATOR ?= false
BUILD_EMULATOR_QEMUD ?= false
BUILD_EMULATOR_OPENGL ?= false
BUILD_EMULATOR_QEMU_PROPS ?= false
BUILD_EMULATOR_CAMERA_HAL ?= false
BUILD_EMULATOR_GPS_MODULE ?= false
BUILD_EMULATOR_LIGHTS_MODULE ?= false
BUILD_EMULATOR_SENSORS_MODULE ?= false

BOARD_USE_LIBVA_INTEL_DRIVER := true
BOARD_USE_LIBVA := true
BOARD_USE_LIBMIX := true
BOARD_USES_WRS_OMXIL_CORE := true
USE_INTEL_OMX_COMPONENTS := true

USE_OPENGL_RENDERER ?= true
NUM_FRAMEBUFFER_SURFACE_BUFFERS ?= 3

USE_CAMERA_STUB ?= false

# This enables the wpa wireless driver
BOARD_WPA_SUPPLICANT_DRIVER ?= NL80211
BOARD_WPA_SUPPLICANT_PRIVATE_LIB ?= private_lib_driver_cmd
WPA_SUPPLICANT_VERSION ?= VER_0_8_X
WIFI_DRIVER_MODULE_PATH ?= auto

#BOARD_GPU_DRIVERS ?= i915 i965 ilo r300g r600g nouveau vmwgfx
BOARD_GPU_DRIVERS ?= i915 i965 swrast r300g r600g
ifneq ($(strip $(BOARD_GPU_DRIVERS)),)
TARGET_HARDWARE_3D := true
BOARD_EGL_CFG ?= device/generic/x86/gpu/egl_mesa.cfg
endif

BOARD_KERNEL_CMDLINE := root=/dev/ram0 androidboot.hardware=$(TARGET_PRODUCT) video=-16 console=ttyS0

SUPERUSER_EMBEDDED := true
SUPERUSER_PACKAGE_PREFIX := com.android.settings.cyanogenmod.superuser

TARGET_PREBUILT_KERNEL := prebuilts/kernel/$(TARGET_ARCH)/kernel