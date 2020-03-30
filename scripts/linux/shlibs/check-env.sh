#!/bin/bash

if [ -z "$LHTLP_HAS_ENV_SET" ]; then
    echo "ERROR: You must call 'source set-env.sh <build-type>' first"
    exit 1
fi