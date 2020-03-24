#!/bin/bash

gcc -o test test.c && strace ./test && echo PASSED

