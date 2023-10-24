#!/bin/bash

### 5 ###

read -p "Введите то, сколько папок должно быть создано: " FOLDERS

for (( i=1; i <= $FOLDERS; i++ ))
do
    if ! [ -f "i.txt" ]; then
	echo "$i.txt" > $i.txt
    fi
done

for (( i=1; i <= $FOLDERS; i++ ))
do
    if [ -d "$i" ]; then
	rm -r $i
    fi
    
    WAY='./'
    for (( j=1; j <= i; j++ ))
    do
    mkdir $WAY$i
    WAY+=$i/
    done
    ln -rs $i.txt $WAY$i.txt
done

