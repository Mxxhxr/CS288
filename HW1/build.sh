#!/bin/bash

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

if [ "$SUFFIXES" != ".c" -a -n "$SUFFIXES" ]
then
    sfx=("$SUFFIXES")
else
    sfx=(".c")
fi

#Iterate through each suffix
for sufx in ${sfx[@]}
do
    #Iterate through each file that contains a suffix in sfx[]
    for file in $(find -name "*$sufx")
    do
        #strip the file extension to be used in compile command using basename unix command
        noExtension=$(basename "$file" "$sufx")

        #check for verbose in here, not effecient but we only want to emit the command that compiles
        #compile command using the correct compiler, flags, output filename, filename

        #also, set -x would print a '+' before emitting the compiler. Dr.itani's example doesnt have a '+' before
        #so instead, im echo-ing it out
        if [ -n "$VERBOSE" ]
        then
            "$compiler" ${flags[@]} -o "$noExtension" "$file"
            result=$?
            if [ $result -eq 0 ]
            then
                echo "$compiler" ${flags[@]} -o "$noExtension" "$file"
            else
                exit 1
            fi
        else
            "$compiler" ${flags[@]} -o "$noExtension" "$file"
        fi
        
    done
done