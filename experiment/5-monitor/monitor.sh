#!/bin/bash
if [ $# -ge 2 ]
then 
    echo "Usage: bash monitor.sh  username"
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
echo "name list: "
for rc in ${name_list[*]}
do
    echo $rc
done

echo ""

while [ 1 ]
do
    for rc in ${name_list[*]}
    do  
        if [ $rc = $target_name ]
        then
            echo $target_name" logged in"
            exit
        fi
    done

    echo "waiting user "$target_name"..."
    name_list=$(who | cut -d" " -f 1)
    sleep 1s
done