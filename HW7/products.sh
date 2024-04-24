#!/bin/bash

# if [ $# -ne 2 ]
# then
#     echo "Invalid file amount"
#     exit 1
# fi


# download_files() {
#     fname=$1
#     mkdir -p "downloaded_files"
#     while IFS= read -r url; do
#         wget -P "downloaded_files" "$url" #download html
#         filename=$(basename "$url") #get basename
#         java -jar tagsoup-1.2.1.jar --files "downloaded_files/$filename" #download xhtml
#         xhtml_file="downloaded_files/$(basename "$url" .html).xhtml"
#         # python3 parser.py "$xhtml_file"
#         # rm "downloaded_files/$filename" #delete html file
#         # rm "downloaded_files/$xhtml_file" #delete xhtml file
#     done < "$fname"
#     # rm -r "downloaded_files" #delete the now empty folder
# }

# download_files "$1"
# # download_files "$2"

# download_files() {
#     fname=$1
#     mkdir -p "downloaded_files"
#     count=0
#     while IFS= read -r url; do
#         wget -P "downloaded_files" "$url" #download html
#         filename=$(basename "$url") #get basename
#         new_filename="file$((++count)).html" #generate new filename
#         mv "downloaded_files/$filename" "downloaded_files/$new_filename" #rename html file
#         java -jar tagsoup-1.2.1.jar --files "downloaded_files/$new_filename" #download xhtml
#         xhtml_file="downloaded_files/$(basename "$new_filename" .html).xhtml"
#         new_xhtml_file="file$((++count)).xhtml" #generate new filename
#         mv "$xhtml_file" "downloaded_files/$new_xhtml_file" #rename xhtml file
#         # python3 parser.py "downloaded_files/$new_xhtml_file"
#     done < "$fname"
# }


# download_files "$1"
# # download_files "$2"



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
    # python3 parser.py "downloaded_files/$new_xhtml_file"
    ((count1++))
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
    # python3 parser.py "downloaded_files/$new_xhtml_file"
    ((count2++))
done < "$fname"


