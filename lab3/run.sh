touch ./cache

./proc2 &
./proc1

pid=`pidof proc1`

wait $pid
