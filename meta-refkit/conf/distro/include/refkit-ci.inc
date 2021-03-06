#
# jenkins CI configuration:
# This file applied via conf/auto.conf for every build
# happening in IoT Reference OS Kit Project CI
#

#
# Static section
# Items that are always present in any CI build:
#

# Generate summary statistics
INHERIT += "buildstats-summary"

# Enable CVE and other security checks.
INHERIT += "isafw"

# Most of the images are expected to contain GPLv3
# components. Therefore we only enable the license check for those
# which must not have them (whitelisting), instead of excluding images
# from the check (blacklisting).
ISAFW_LA_PLUGIN_IMAGE_WHITELIST = "refkit-image-minimal refkit-initramfs"

# refkit-image-minimal is only getting built below as proof that an IoT Reference OS Kit root
# filesystem is possible without depending on GPLv3 components. The actual
# image files are not needed for that.
IMAGE_FSTYPES_pn-refkit-image-minimal = ""
REFKIT_VM_IMAGE_TYPES_pn-refkit-image-minimal = ""
 
# Test data generation:
INHERIT += "test-iot"
TEST_EXPORT_DIR = "iottest"
TEST_TARGET = "simpleremote"

# SDK defaults:
SDKMACHINE ?= "x86_64"

# HOSTTOOLS setup:
HOSTTOOLS_remove = "hostname ip vi"

# Generate source mirror tarballs:
BB_GENERATE_MIRROR_TARBALLS = "1"

# Configure images in "development mode".
require conf/distro/include/refkit-development.inc

# Enable flatpak application support.
require conf/distro/include/flatpak-applications.inc

REFKIT_VM_IMAGE_TYPES = "wic.xz wic.zip wic.bmap wic.xz.sha256sum"

#
# pre/post-build oe-selftests started by CI builder, whitespace-separated.
#
REFKIT_CI_PREBUILD_SELFTESTS="iotsstatetests.SStateTests.test_sstate_samesigs"
REFKIT_CI_POSTBUILD_SELFTESTS=""
#
# Automated build targets
# Those targets should be space separated list of items,
# which must contain only alphanumeric symbols,'-' and '_'.
# Any other symbols would be skipped in parser.
#
# Following targets would be used to perform default build task:
REFKIT_CI_BUILD_TARGETS="refkit-image-minimal refkit-image-common refkit-image-computervision refkit-image-gateway"
# Following targets would be executed with do_populate_sdk task
REFKIT_CI_SDK_TARGETS=""
# Following targets would be executed with do_populate_sdk_ext task.
# Uses the fully-populated image to ensure that the eSDK is as complete
# as possible.
REFKIT_CI_ESDK_TARGETS=""
# We'll automatically enable flatpak runtime/SDK support for the
# following targets if flatpak support is enabled (by commenting out
# the corresponding require above.
REFKIT_CI_FLATPAK_RUNTIME_TARGETS = " \
  ${@bb.utils.contains('DISTRO_FEATURES', 'flatpak', \
     'refkit-image-minimal', '', d)} \
"
REFKIT_CI_FLATPAK_SDK_TARGETS = " \
  ${@bb.utils.contains('DISTRO_FEATURES', 'flatpak', \
     'refkit-image-minimal', '', d)} \
"
# Following targets would be executed with do_test_iot_export task
REFKIT_CI_TEST_EXPORT_TARGETS="refkit-image-common refkit-image-computervision refkit-image-gateway"
# Execute automatic tests for following images with corresponding
# test suite and test files.
# Space separated list of tuples, each should in format:
# <image_name>,<testsuite_name>,<testfiles_name>,$MACHINE
REFKIT_CI_TEST_RUNS=" \
  refkit-image-common,iot-testsuite.tar.gz,iot-testfiles.${MACHINE}.tar.gz,${MACHINE} \
  refkit-image-computervision,iot-testsuite.tar.gz,iot-testfiles.${MACHINE}.tar.gz,${MACHINE} \
  refkit-image-gateway,iot-testsuite.tar.gz,iot-testfiles.${MACHINE}.tar.gz,${MACHINE} \
"

# Dont use disk space monitor in CI builds, to avoid frequent
# space checks on (possibly remote, like NFS) volumes.
BB_DISKMON_DIRS = ""

#
# Dymamic section.
# Values are applied dynamically based on runtime config or builder host
# parameters.
# Present here as reference only.
#

# Explicit machine declaration by build job:
# MACHINE = "$TARGET_MACHINE"

# Shared download directory between builders:
# DL_DIR = "/srv/bb-cache/iot-ref-kit/sources"

# Limit CPU utilization, based on amount of slots/CPU cores
# on builder hosts:
# BB_NUMBER_PARSE_THREADS = "X"
# BB_NUMBER_THREADS = "X"
# PARALLEL_MAKE = "-j X"

# Local optimizations on SSTATE directories, shared between builder hosts:
# SSTATE_MIRRORS ?= "file://.* http://$IP/bb-cache/iot-ref-kit/sstate/PATH"
# SSTATE_DIR ?= "/var/tmp/sstate-$slot"

# Local directory, where builder puts local copy of buildhistory
# BUILDHISTORY_DIR ?="$WORKSPACE/buildhistory"

# PRserv host dynamically allocated by master:
# PRSERV_HOST = "$IP:$PORT"

# Enabled for master release builds:
# INHERIT += "archiver"
# ARCHIVER_MODE[src] = "original"
# ARCHIVER_MODE[diff] = "1"
# ARCHIVER_MODE[recipe] = "1"
