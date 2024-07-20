#!/bin/bash
message1="I AM COM-SCI"
message2="I LOVE KMITL"

count=0
while [ $count -lt 1000 ]
do
	if [ $((count % 2)) -eq 0 ]
	then
		echo -e "No.$((count + 1))\t${message1}"
	else
		echo -e "No.$((count + 1))\t${message2}"
	fi
	count=$((count+1))
done
