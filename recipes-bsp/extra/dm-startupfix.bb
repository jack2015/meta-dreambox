require conf/license/license-gplv2.inc

SRC_URI = "file://startup_fix.sh"

INITSCRIPT_NAME = "startup_fix"
INITSCRIPT_PARAMS = "start 03 S ."

inherit update-rc.d

do_compile() {
}

do_install() {
	install -d ${D}${INIT_D_DIR}/
	install -m 0755 ${WORKDIR}/startup_fix.sh ${D}${INIT_D_DIR}/startup_fix
}
