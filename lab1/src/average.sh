#!/bin/sh

s=0
b=10
arr=($(cat ./numbers.txt))
echo $arr
for (( i=-1; i >= -150; i-- ))
do
s+=${arr: -1}
let "arr = $arr / $b"
echo $arr
done
