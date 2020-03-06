#!/bin/bash
user='NEET the 3rd'
address='neet3@example.com'
myname='myname'
my_address='my_address'
for file in *.cpp
do
    sed -i 's/myname/NEET/' $file
    sed -i 's/$user/$myname/'  $file
    sed -i 's/${address}/${my_address}/' $file
    # sed -i 's/\s*$//' $file
    # mv $file ${file%.*}.cc
done     
	   
