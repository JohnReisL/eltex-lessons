#!/bin/bash

### 2 ###

./1.sh
NUM=20
for (( i=1; i <= $NUM; i++ ))
do
echo "$i.txt" > $i.txt
done

