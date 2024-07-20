#!/bin/bash
echo -n "Enter your age: "
read age

if [ $age -ge 1 ] && [ $age -lt 21 ];
then
	echo "be child !!!"
elif [ $age -ge 21 ] && [ $age -lt 46 ];
then
	echo "be teenage !!!"
elif [ $age -ge 46 ] && [ $age -lt 61 ];
then
	echo "be adult !!!"
elif [ $age -ge 61 ] && [ $age -lt 71 ];
then
	echo "be middle age !!!"
elif [ $age -ge 71 ] && [ $age -lt 80 ];
then
	echo "be elderly !!!"
else
	echo "be old age"
fi
