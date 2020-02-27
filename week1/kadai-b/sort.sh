#!/bin/sh
find coreutils -name \*.c -exec wc -l {} + | sort -n | awk '{print $2}' > result.txt



