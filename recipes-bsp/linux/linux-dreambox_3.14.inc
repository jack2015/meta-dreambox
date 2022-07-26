require linux_3.14.inc

do_configure:prepend() {
        sed -e "/^SUBLEVEL = /d" -i ${S}/Makefile
}

KERNEL_ENABLE_CGROUPS = "1"

# By default, kernel.bbclass modifies package names to allow multiple kernels
# to be installed in parallel. We revert this change and rprovide the versioned
# package names instead, to allow only one kernel to be installed.
PKG:${KERNEL_PACKAGE_NAME} = "${KERNEL_PACKAGE_NAME}"
PKG:${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-base"
PKG:${KERNEL_PACKAGE_NAME}-image = "${KERNEL_PACKAGE_NAME}-image"
PKG:${KERNEL_PACKAGE_NAME}-image-zimage = "${KERNEL_PACKAGE_NAME}-image"
RPROVIDES:${KERNEL_PACKAGE_NAME} = "${KERNEL_PACKAGE_NAME}-${LINUX_VERSION}"
RPROVIDES:${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-${KERNEL_VERSION}"
RPROVIDES:${KERNEL_PACKAGE_NAME}-image = "${KERNEL_PACKAGE_NAME}-image-${KERNEL_VERSION}"
#RPROVIDES:${KERNEL_PACKAGE_NAME}-image-zimage = "${KERNEL_PACKAGE_NAME}-image"
RDEPENDS:${KERNEL_PACKAGE_NAME}-image = "${KERNEL_PACKAGE_NAME}-devicetree flash-scripts"


pkg_postinst:${KERNEL_PACKAGE_NAME}-image () {
#!/bin/sh
if [ -z "$D" ]; then
    flash-kernel /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}-${LINUX_VERSION}
fi
}
