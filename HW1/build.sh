#!/bin/bash

# check for suffix

#if length of STRING 'VERBOSE' is not zero (verbose is set)
if [ -n "$VERBOSE" ]
then
    set -x
fi

#if CC is not gcc and not empty, set compiler to CC, else CC is default (gcc)
if [ "$CC" != "gcc" -a -n "$CC" ]
then
    compiler=$CC
else
    compiler="gcc"
fi

#if CFLAGS is not the default and CFLAGS is not empty set it to that. else set compilerto default
if [ "$CFLAGS" != "-Wall -Werror" -a -n "$CFLAGS" ]
then
    flags=("$CFLAGS")
else
    flags=(-Wall -Werror)
fi


# find files with default extension .c
files=$(find ./*.c)

for file in $files
do
    # remove extension using basename unix command. (will use this to set the name when we compile)
    noExtension=$(basename "$file" .c)
    #compile the files with default SUFFIXES, CC, and CFLAGS
    "$compiler" ${flags[@]} -o "$noExtension" "$file"
done



#suffixes
#verbose. ask tmrw, dont get response then im gonna manually printf it out.
#also check for compulation command fail.