#!/bin/bash

### 3 ###

for i in *.txt; do
    if [[ $i != *"4"* ]]; then
	rm -fv $i
    fi
done
