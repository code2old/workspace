#! /bin/bash

largest=70
while :; do 
    mem=$(ps -p `pidof mgc` -o %mem | tail -1)
    imem=$(printf %.0f $mem)
    if [ $imem -gt $largest ]; then
        largest=$imem
        echo `date`, $largest >> /tmp/largest_mem.log
    fi
    sleep 10
done