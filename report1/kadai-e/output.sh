#!/bin/bash

strace /bin/cat /proc/meminfo > cat.txt
strace /bin/cat /proc/meminfo 2> strace.txt
strace /bin/cat /proc/meminfo &> all.txt
