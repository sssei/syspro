#!/bin/sh

rm -f 1.pdf

for i in {0..99}
do
    num=$(printf "%02d" $i)
    file="1.pdf.$num"
    url="http://www.pf.is.s.u-tokyo.ac.jp/syspro/static/kadai1/$file"
    wget -q $url
    cat $file >> 1.pdf
    rm $file
done     
