#!/bin/bash
set -e

scriptdir=$(cd $(dirname $0); pwd -P)
sourcedir=$(cd $scriptdir/../..; pwd -P)
. $scriptdir/shlibs/check-env.sh
. $scriptdir/shlibs/os.sh

$scriptdir/submodule-update.sh

builddir=$LHTLP_BUILD_DIR
mkdir -p "$builddir"
cd "$builddir"

cmake $LHTLP_CMAKE_ARGS $@ "$sourcedir"
