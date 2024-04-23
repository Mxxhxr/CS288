#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Invalid file amount"
    exit 1
fi

link1=$1
link2=$2
current_dir=$(dirname "$0")

# Process links from ex.txt and ex2.txt
for file in "$link1" "$link2"
do
    i=1
    while IFS= read -r line
    do
        echo "Downloading $line"
        wget -P "$current_dir" -O "file${i}_${file##*_}.html" "$line"
        java -jar tagsoup-1.2.1.jar --files "file${i}_${file##*_}.html"
        ((i++))
    done < "$file"
done
