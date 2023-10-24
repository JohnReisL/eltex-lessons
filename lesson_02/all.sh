#!/bin/bash


### 1 ###

NUM=20
for (( i=1; i <= $NUM; i++ ))
do
>$i.txt
done


### 2 ###

for (( i=1; i <= $NUM; i++ ))
do
echo "$i.txt" > $i.txt
done


### 3 ###

for (( i=1; i <= $NUM; i++ ))
do
    if [[ $i.txt != *"4"* ]]; then
	rm -fv $i.txt
    fi
done


### 4 ###

echo -e "Одна ошибка\nИ ты ощибся\n" > 14.txt


### 5 ###

FOLDERS=3

for (( i=1; i <= $FOLDERS; i++ ))
do
echo "$i.txt" > $i.txt
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

