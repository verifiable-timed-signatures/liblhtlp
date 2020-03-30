#!/bin/bash
set -e

scriptdir=$(cd $(dirname $0); pwd -P)
sourcedir=$(cd $scriptdir/../..; pwd -P)
. $scriptdir/shlibs/check-env.sh
. $scriptdir/shlibs/os.sh

builddir=$VTSBLS_BUILD_DIR

(
    cd $sourcedir;
    git submodule init;
    git submodule update;
)