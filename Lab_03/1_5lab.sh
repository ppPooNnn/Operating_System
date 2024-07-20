#!/bin/bash
message="I LOVE KMITL"

for (( i = 1; i <= $1; i++))
do
	echo -e "No:$i\t$message"
done
