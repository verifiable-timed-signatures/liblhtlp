# libvtsbls: The VTS BLS library for verifiable timed BLS Signatures

## Build on Linux

Clone this repository first by running:
    `git clone <THIS_REPO_URL>`

First, install dependency libraries using:

    scripts/linux/install-libs.sh

Then, set up the environment. This **will store the built code in ~/builds/vtsbls/**:

    . scripts/linux/set-env.sh release

...you can also use `debug`, `relwithdebug` or `trace` as an argument for `set-env.sh`.

To build:

    make.sh

..tests, benchmarks and any other binaries are automatically added to `PATH` but can also be found in

    cd ~/builds/vtsbls/master/release/libvtsbls/bin/

(or replace `release` with `debug` or whatever you used in `set-env.sh`)