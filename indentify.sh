#!/bin/bash

indent -orig -bad -bap -bs -cli2 -di1 -nbc -nut *.c
indent -orig -bad -bap -bs -cli2 -di1 -nbc -nut *.h
indent -orig -bad -bap -bs -cli2 -di1 -nbc -nut tests/*.c
indent -orig -bad -bap -bs -cli2 -di1 -nbc -nut examples/*.c
