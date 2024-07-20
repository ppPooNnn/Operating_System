#!bin/bash
hello(){
	echo "Hello KMITL $1"
}
helloWithParam(){
	echo "Hello $1 $2 $3"
}

hello $0
helloWithParam CS KMITL $0
