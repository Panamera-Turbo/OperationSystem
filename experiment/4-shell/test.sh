clear
# echo "Hello, world!"
echo "Please input the name of the file"
read filename
ls -l $filename

size=$(ls -l $filename | cut -d " " -f 5)
# echo $size
unchanged_count=0
changed_count=0
# t=0

for((i=1;i<10;i++))
do
    new_size=$(ls -l $filename | cut -d " " -f 5)

    if [ $new_size == $size ]
    then
        unchanged_count+=1
        echo "file not changed"
    else
        changed_count+=1
        size=new_size
        echo "file "$filename" size changed"·
    fi

    if [ $changed_count -ge 2 ]
    then    
        echo "检测的文件已累计改变了两次大小"
        exit
    fi

    sleep 5s
    
done
echo "已连续检测了十次还未改变大小"