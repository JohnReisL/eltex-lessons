#!/bin/bash

COUNTER=0

>log.log

for i in {1..5}
do
    ./sleeper.sh &&
	COUNTER=$(($COUNTER + 1)) && #без понятия что не так
	echo -e "Отработало $COUNTER (цикл $i)" >> log.log &
done 

wait

sleep 3600
# А тут должно было бы нормально вывести 
# echo "Отработало $COUNTER"
