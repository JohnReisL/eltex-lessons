#!/bin/bash

### 2 пункт из задач ###


STR=$(ps | grep 'sleep' |  awk '{print $1}')

first=$(echo $STR | awk '{print $1}')
second=$(echo $STR | awk '{print $2}')
thierd=$(echo $STR | awk '{print $3}')

echo $first $second $thierd | xargs -r kill -9
