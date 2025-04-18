# SGI575 specific EDK2 configurations
EDK2_BUILD_RELEASE = "0"
EDK2_PLATFORM      = "Sgi575"
EDK2_PLATFORM_DSC  = "Platform/ARM/SgiPkg/Sgi575/Sgi575.dsc"
EDK2_BIN_NAME      = "BL33_AP_UEFI.fd"

COMPATIBLE_MACHINE = "sgi575"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += " file://0001-Platform-Sgi-workaround-ArmFfaLib-error.patch;patchdir=edk2-platforms"
