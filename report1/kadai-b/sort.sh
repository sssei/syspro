#!/bin/sh
find coreutils-8.9/ -name *.c -exec wc -l {} + | sort -n | awk '{print $2}' > result.txt
sed -i -e '$d' result.txt 




