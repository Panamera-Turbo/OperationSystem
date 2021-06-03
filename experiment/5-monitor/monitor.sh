if [ $# -ge 2]
then 
    echo "Usage: usr_monitor  username"
fi

if [ $# -eq 0]
then
    echo "input one username!"
fi


target_name=$1


name_list=$(who | cut -d" " -f 1)
echo $name  #这里有错，要求是打印name_list

while [ 1 ]
do
    for $target_name in ${name_list[*]}
    do  
        echo $target_name"logged in"
        exit
    done

    echo "waiting user"$target_name"..."
    sleep 5s
done