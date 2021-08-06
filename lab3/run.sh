./proc1 &
./proc2

pid=`pidof proc1`

wait $pid
