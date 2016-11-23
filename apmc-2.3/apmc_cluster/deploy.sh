#!/bin/sh

echo -n "Stopping apmcds "

for i in `cat $OAR_NODEFILE`; do
	ssh $i killall -TERM apmcd &
done

for i in `cat $OAR_NODEFILE`; do
	wait
done

echo done

if [ "x$1" == "xstop" ]; then
	exit 0
fi

echo -n "launching apmcds "

for i in `cat $OAR_NODEFILE`; do
	ssh $i "/home/orsay/therault/APMC/apmc-trunk-1.Dec.06/apmc_cluster/run_apmcd" &
done

for i in `cat $OAR_NODEFILE`; do
	wait
done

echo done

i=0
max=`wc -l $OAR_NODEFILE | awk '{print $1}'`

function id()
{
	i=$1
	if [ $((i+1)) -gt $max ]; then
		return
	fi
	head -n $((i+1)) $OAR_NODEFILE | tail -n 1
}

while [ $i -lt $max ]; do
	l=`id $((2*i+1))`
	r=`id $((2*(i+1)))`
	m=`id $i`
	if [ -n "$l" ]; then
		/home/orsay/therault/APMC/apmc-trunk-1.Dec.06/apmc_cluster/connect $m $l
	fi
	if [ -n "$r" ]; then
		/home/orsay/therault/APMC/apmc-trunk-1.Dec.06/apmc_cluster/connect $m $r
	fi
	i=$((i+1))
done

