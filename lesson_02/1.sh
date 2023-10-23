#!/bin/bash

### 1 ###

NUM=20
ALLNUM=''
for (( i=1; i <= $NUM; i++ ))
do
ALLNUM+=$i" "
>$i.txt
done


