#!/bin/bash

### 1 ###

read -p "Введите то, сколько папок должно быть создано: " NUM
for (( i=1; i <= $NUM; i++ ))
do
    >$i.txt
done
