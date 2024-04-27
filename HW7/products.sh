#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Invalid file amount"
    exit 1
fi






fname=$1
mkdir -p "downloaded_files"
count1=100
while IFS= read -r url || [ -n "$url" ]; do
    wget -P "downloaded_files" "$url" #download html
    filename=$(basename "$url") #get basename
    new_filename="file$count1.html" #generate new filename
    mv "downloaded_files/$filename" "downloaded_files/$new_filename" #rename html file
    java -jar tagsoup-1.2.1.jar --files "downloaded_files/$new_filename" #download xhtml
    xhtml_file="downloaded_files/$(basename "$new_filename" .html).xhtml"
    new_xhtml_file="file$count1.xhtml" #generate new filename
    mv "$xhtml_file" "downloaded_files/$new_xhtml_file" #rename xhtml file
    python3 parser.py "downloaded_files/$new_xhtml_file"
    ((count1++))
    sleep 2
done < "$fname"

fname=$2
count2=200
while IFS= read -r url || [ -n "$url" ]; do
    wget -P "downloaded_files" "$url" #download html
    filename=$(basename "$url") #get basename
    new_filename="file$count2.html" #generate new filename
    mv "downloaded_files/$filename" "downloaded_files/$new_filename" #rename html file
    java -jar tagsoup-1.2.1.jar --files "downloaded_files/$new_filename" #download xhtml
    xhtml_file="downloaded_files/$(basename "$new_filename" .html).xhtml"
    new_xhtml_file="file$count2.xhtml" #generate new filename
    mv "$xhtml_file" "downloaded_files/$new_xhtml_file" #rename xhtml file
    python3 parser.py "downloaded_files/$new_xhtml_file"
    ((count2++))
    sleep 2
done < "$fname"


rm -rf "downloaded_files"
