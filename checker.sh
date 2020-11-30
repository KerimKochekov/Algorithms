#!/bin/bash

for ((i=1;i<=100;i++))
do
	./e.exe > in
	./c.exe < in > out
	./c_slow.exe < in > ans
	if diff out ans
	then
		echo $i OK
	else
		echo $i WA
		exit
	fi
done
