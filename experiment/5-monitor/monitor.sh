echo "Usage:sh ./monitor.sh [username]"

if [ $# -ge 2]
then 
    echo "only one user"
fi

if [ $# -eq 0]
then
    echo "input one username!"
fi

target_name=$1


name_list=$(who | cut -d" " -f 1)
echo $name

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