#!/bin/bash

# Define the constant word
constant_word="supercalifragilisticexpialidocious"

# Get the input word from command-line argument
input_word="$1"

# Sort both words
sorted_constant_word=$(echo "$constant_word" | grep -o . | sort | tr -d '\n')
sorted_input_word=$(echo "$input_word" | grep -o . | sort | tr -d '\n')

# Check if the input word is a subset of the constant word
if [[ "$sorted_constant_word" == *"$sorted_input_word"* ]]; then
    echo "$input_word is composed only of characters from $constant_word"
else
    echo "$input_word is not composed only of characters from $constant_word"
fi
