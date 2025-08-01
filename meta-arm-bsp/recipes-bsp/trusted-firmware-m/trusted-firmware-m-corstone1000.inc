# Corstone1000 machines specific TFM support

COMPATIBLE_MACHINE = "(corstone1000)"

TFM_PLATFORM = "arm/corstone1000"

TFM_DEBUG = "1"

## Default is the MPS3 board
TFM_PLATFORM_IS_FVP ?= "FALSE"
EXTRA_OECMAKE += "-DPLATFORM_IS_FVP=${TFM_PLATFORM_IS_FVP}"
EXTRA_OECMAKE += "-DCC312_LEGACY_DRIVER_API_ENABLED=OFF"
EXTRA_OECMAKE:append:corstone1000-fvp = " -DENABLE_MULTICORE=${@bb.utils.contains('MACHINE_FEATURES', 'corstone1000_fvp_smp', 'TRUE', 'FALSE', d)}"
EXTRA_OECMAKE:append:corstone1000-mps3 = " -DPLATFORM_PSA_ADAC_SECURE_DEBUG=${@bb.utils.contains('MACHINE_FEATURES', 'secure-debug', 'ON', 'OFF', d)}"
EXTRA_OECMAKE:append:corstone1000-mps3 = " -DPLATFORM_PSA_ADAC_SOURCE_PATH=${S}/../tfm-psa-adac -DPLATFORM_PSA_ADAC_BUILD_PATH=${B}/tfm-psa-adac-build"

SRC_URI += " \
            file://0001-arm-trusted-firmware-m-disable-address-warnings-into.patch \
           "

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI:append:corstone1000 = " \
    file://0001-Platform-Corstone1000-Align-capsule-UEFI-structs.patch \
    file://0002-Platform-Corstone1000-Fix-NV-counter-writing.patch \
    file://0003-Platform-Corstone1000-Enable-firewall-in-FVP.patch \
    file://0004-Platform-CS1000-Increase-ITS-max-asset-size.patch \
    file://0005-Platform-CS1000-Increase-RSE_COMMS-buffer-size.patch \
    file://0006-Platform-CS1000-Increase-buffers-for-EFI-vars.patch \
    file://0007-Plaform-Corstone1000-Switch-to-metadata-v2.patch \
    file://0008-Platform-CS1000-Increase-flash-PS-area-size.patch \
    file://0009-corstone1000-Remove-reset-after-capsule-update.patch \
    file://0010-platform-CS1000-Add-multicore-support-for-FVP.patch \
    file://0011-Platform-CS1000-Fix-Bank-offsets.patch \
    file://0012-Platform-CS1000-Increase-BL2-partition-size.patch \
    file://0013-CC312-ADAC-Add-PSA_WANT_ALG_SHA_256-definition.patch \
    file://0014-Platform-CS1000-Add-crypto-configs-for-ADAC.patch \
    file://0015-Platform-CS1000-Fix-platform-name-in-logs.patch \
    file://0017-Platform-CS1000-Remove-unused-BL1-files.patch \
    file://0018-Platform-CS1000-Remove-duplicated-metadata-write.patch \
    file://0019-Platform-CS1000-Fix-compiler-switch-in-BL1.patch \
    file://0020-Platform-CS1000-Validate-both-metadata-replicas.patch \
    file://0021-platform-corstone1000-add-unique-guid-for-mps3.patch \
    file://0022-CC312-alignment-of-cc312-differences.patch \
    file://0023-Platform-CS1000-Remove-duplicate-configuration-parameters.patch \
    "

FILESEXTRAPATHS:prepend:corstone1000-mps3 := "${THISDIR}/files/corstone1000/psa-adac:"
SRC_URI:append:corstone1000-mps3 = " \
    file://0001-PSA-revert-header-versions.patch;patchdir=../tfm-psa-adac \
    file://0002-ADAC-Link-psa_interface-instead-of-tfm_sprt.patch;patchdir=../tfm-psa-adac \
    file://0003-Fix-psa_key_handle_t-initialization.patch;patchdir=../tfm-psa-adac \
    "

do_install() {
  install -D -p -m 0644 ${B}/bin/tfm_s_signed.bin ${D}/firmware/tfm_s_signed.bin
  install -D -p -m 0644 ${B}/bin/bl2_signed.bin ${D}/firmware/bl2_signed.bin
  install -D -p -m 0644 ${B}/bin/bl1_1.bin ${D}/firmware/bl1_1.bin
  install -D -p -m 0644 ${B}/bin/bl1_provisioning_bundle.bin ${D}/firmware/bl1_provisioning_bundle.bin
}

create_bl1_image(){
    dd conv=notrunc bs=1 if=${D}/firmware/bl1_1.bin of=${D}/firmware/bl1.bin seek=0
    dd conv=notrunc bs=1 if=${D}/firmware/bl1_provisioning_bundle.bin of=${D}/firmware/bl1.bin seek=40960
}
do_install[postfuncs] += "create_bl1_image"
