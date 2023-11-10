#!/bin/bash

### 3 пункт из задач ###

ps | grep 'file.sh' |  awk '{print $1}' | xargs -r kill -9
