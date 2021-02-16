#!/bin/bash

user='NEET the 3rd'
address='neet3@example.com'
myname='my_name'
myaddress='my_address'

for file in *.cpp
do
    sed -i "s/$user/$myname/" $file
    sed -i "s/$address/$myaddress/" $file
    sed -i 's/\s*$//' $file
    mv $file ${file%.*}.c
done     
	   
