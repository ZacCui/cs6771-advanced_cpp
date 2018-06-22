#!/bin/bash

compiler="g++ -std=c++14 -Wall -Werror -O2 -o"

num=1

for file in test{1,2,3,4,5,6,7,8m,8c,9m,9c,10,11,12,13}.cpp
do
	filename=`basename $file`
	code=`echo "$file" | sed "s/.cpp//g; s/test//g"`
	echo "testing test case test$code and testing file is $filename------------------"
	
	target=`echo "$filename" | cut -d '.' -f1`
	test_file="result$code.txt"
	echo "test compiler-------------------------------------------------------"
	command_line="$compiler $target $filename"
	$command_line
	run="./$target"
	$run>res$num
	if diff -w "res$num" "$test_file"
	then
		echo "test case test$code pass!!!!!"
	else
		echo "test case test$code fail :("
	fi
	rm $target res$num
	num=`expr $num + 1`
done