ls -t > temp
declare -a array
readarray array < temp
i=0
count=0
while (( i < ${#array[*]} )); do
    if [ ${array[i]} -ot file ]; then
        (( count++ ));
    fi
    ((i++));
done
echo $count