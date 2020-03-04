#!/bin/bash
user='NEET the 3rd'
address='neet3@example.com'
myname='myname'
my_address='my_address'
for file in *.cpp
do
    # sed -i 's/_${user}/${address}_${myname}/${my_address}_/g' $file
    sed -i 's/\s*$//' $file
    # mv $file ${file%.*}.cc
done     
	   
