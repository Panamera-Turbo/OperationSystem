#!/bin/bash
if [ $# -ge 2 ]
then 
    echo "Usage: usr_monitor  username"
    exit
fi

if [ $# -eq 0 ]
then
    echo "input one username!"
    exit
fi

target_name=$1
echo "target user: "$target_name
echo ""
name_list=$(who | cut -d" " -f 1)
echo $name_list
echo ""
while [ 1 ]
do
    for target_name in ${name_list[*]}
    do  
        echo $target_name" logged in"
        exit
    done

    echo "waiting user "$target_name"..."
    sleep 1s
done