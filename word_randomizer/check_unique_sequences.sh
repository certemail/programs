#!/bin/bash

echo "Checking solutions for possible duplicate sequences..."
md5sum $(find Solutions -type f -name "*.csv") | awk '{print $1}' | sort | uniq -D
