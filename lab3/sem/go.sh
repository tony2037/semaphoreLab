#!/bin/sh
# http://www.felix-lin.com      date: 2013/07/04
#
# script for system V semaphore example
#  

if [ ! -e /proc/sysvipc/sem ]; then
    echo "Does you kernel support System V IPC?"
    exit 1
fi

CC=gcc

$CC -o proc1 proc1.c semaphore.c
if [ $? != 0 ]; then
    echo "compile error"
    exit 1
fi
$CC -o proc2 proc2.c semaphore.c
if [ $? != 0 ]; then
    echo "compile error"
    exit 1
fi

./proc1 &
./proc2

pid=`pidof proc1`

wait $pid

