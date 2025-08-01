FILESEXTRAPATHS:prepend:corstone1000 := "${THISDIR}/corstone1000:"

COMPATIBLE_MACHINE:corstone1000 = "corstone1000"
SRC_URI:append:corstone1000  = " \
    file://0001-Add-stub-capsule-update-service-components.patch \
    file://0002-Fix-in-AEAD-for-psa-arch-test-254.patch \
    file://0003-FMP-Support-in-Corstone1000.patch \
    file://0004-Fix-psa-api-crypto-test-no-243.patch \
    file://0005-plat-corstone1000-Use-the-stateless-platform-service.patch \
    file://0006-plat-corstone1000-Initialize-capsule-update-provider.patch \
    file://0007-plat-corstone1000-add-client_id-for-FMP-service.patch \
    file://0008-Remove-Werror-flag.patch \
    file://0009-Remove-PLATFORM_HAS_ATTEST_PK-define-from-IAT-test.patch \
    file://0010-Make-RSS-and-MHU-sizes-compile-time-definitions-user.patch \
    file://0011-Align-PSA-Crypto-with-TF-Mv2.1.patch \
    file://0012-Revert-Make-variable-index-usage-robust-with-redunda.patch \
    file://0013-Revert-Load-and-store-UEFI-variable-index-in-chunks.patch \
    file://0014-Revert-Make-constraints-of-NV-UEFI-variables-persist.patch \
    file://0015-se-proxy-protobuf-change.patch \
    file://0021-Align-PSA-Crypto-structs-with-TF-Mv2.1.1.patch \
    file://0016-Add-the-com-buffer-address-and-page-count.patch \
    "
# The patches above introduce errors with GCC 14.1, silence them for now
CFLAGS:append:corstone1000 = " -Wno-int-conversion -Wno-implicit-function-declaration"

COMPATIBLE_MACHINE:fvp-base = "fvp-base"
TS_PLATFORM:fvp-base = "arm/fvp/fvp_base_revc-2xaemv8a"
