#!/bin/bash

gcc -o test test.c && strace ./test $1 && echo PASSED

