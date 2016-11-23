#!/bin/sh

APMC_DEPLOY="apmc_deployment"
APMC_WORKER="apmc/worker"
APMC="apmc"

if [ -x "tmpl_rename.sh" ] ; then
    . tmpl_rename.sh
fi

. apmc.conf

if [ $# -eq "1" -a "$1" = "clean" ] ; then
    if [ -f "$APMC_DEPLOY/apmcdeploy-2.0.0.tar.gz" ] ; then
	echo "Removing $APMC_DEPLOY/apmcdeploy-2.0.0.tar.gz" >&2
	rm -f "$APMC_DEPLOY/apmcdeploy-2.0.0.tar.gz"
	echo "Deleting temporary files" >&2
	(cd "$APMC"; rm -f property.prop model.pm hosts apmcdeploy-2.0.0.tar.gz)
    fi
    (cd "$APMC"; make clean > /dev/null)
    exit
fi

# Prepares apmc_deployment
if [ ! -f "$APMC_DEPLOY/configure" ] ; then
    echo "Running autogen for deployment" >&2
    (cd "$APMC_DEPLOY"; ./autogen.sh > /dev/null)
fi

# Prepares worker
if [ ! -f "$APMC_WORKER/configure" ] ; then
    echo "Running autogen for worker" >&2
    (cd "$APMC_WORKER"; ./autogen.sh > /dev/null)
fi

# Prepares master
if [ ! -f "configure" ] ; then
    ./autogen.sh
fi

if [ ! -f "$APMC/Makefile" ] ; then
    echo "Running configure" >&2
    ./configure > /dev/null
fi

if [ ! -f "$APMC_DEPLOY/Makefile" ] ; then
    echo "Running configure for deployment" >&2
    (cd "$APMC_DEPLOY"; ./configure > /dev/null)
fi
if [ ! -f "$APMC_DEPLOY/apmcdeploy-2.0.0.tar.gz" ] ; then
    echo "Creating tarball of deployment sources" >&2
    (cd "$APMC_DEPLOY"; make dist > /dev/null)
fi
cp "$APMC_DEPLOY/apmcdeploy-2.0.0.tar.gz" "$APMC"

if [ ! -f "$APMC_WORKER/Makefile" ] ; then
    echo "Running configure for worker" >&2
    (cd "$APMC_WORKER"; ./configure > /dev/null)
fi

if [ ! -f  "$APMC/apmc-cmdline" ] ; then
    echo "Compiling apmc" >&2
    (cd "$APMC"; make > /dev/null)
fi

if [ $# -ne "6" ] ; then
    echo "Usage:"
    echo "$0 property_file model_file strategy_name path_len nbpath hosts_file" >&2
    exit 2
fi

if [ ! -f "$1" ] ; then
    echo "File $1 not found" >&2
    exit 1
fi
cp "$1" "$APMC/property.prop"

if [ ! -f "$2" ] ; then
    echo "File $2 not found" >&2
    exit 1
fi
cp "$2" "$APMC/model.pm"

if [ ! -f "$6" ] ; then
    echo "File $6 not found" >&2
    exit 1
fi
cp "$6" "$APMC/hosts_apmc"


echo "Executing apmc" >&2
(cd "$APMC"; ./apmc-cmdline property.prop model.pm "$3" "$4" "$5" "$LOGIN_NAME" "$NICE_LEVEL" "$ARITY" "$N_WORKERS")
echo "Deleting temporary files" >&2
(cd "$APMC"; rm -f property.prop model.pm hosts_apmc apmcdeploy-2.0.0.tar.gz)
