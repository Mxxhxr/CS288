#!/bin/bash

#search current directory for files that match any of the suffixes
#in the enviornment variable 'SUFFIXES' (default SUFFIXES = ".c")


#if there is not 3, then we know 
if [$1]

SUFFIXES=".c"

variable=$(find ./*${SUFFIXES})

echo $variable

