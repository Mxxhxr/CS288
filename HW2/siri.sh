#!/bin/bash

inputWord="$1"

#false by default
inWord=1

#check if any character is not in supercali...
inputNotInWord=$(echo $1 | egrep '[^supercalifragilisticexpialidocious]+')

#if the length of inputNotInWord = 0, then we know every word in the input exists in supercali...
#so set inWord to true
if [ -z $inputNotInWord ]
then
    inWord=0
else
    # a letter in the input doesnt exist in supercali.. so just echo 0 and end program
    echo 0
    exit
fi

declare -A superCali
wordInSuperCali=0
loopRepeated=0

superCali["i"]=7
superCali["c"]=3
superCali["a"]=3
superCali["s"]=3
superCali["l"]=3
superCali["u"]=2
superCali["p"]=2
superCali["e"]=2
superCali["r"]=2
superCali["o"]=2
superCali["f"]=1
superCali["g"]=1
superCali["t"]=1
superCali["x"]=1
superCali["d"]=1


# didn't know you can do a for loop like this!
#loop through each letter while i is less than the length of the inputWord
#have to assign letter to a slice of the input string (in this case just 1 letter at a time)
for ((i=0; i < ${#inputWord}; i++))
do
    letter=${inputWord:i:1}
    var=$(echo $letter | egrep '[supercalifragilisticexpialidocious]')

    if [ -n "${superCali[$letter]}" -a "${superCali[$letter]}" -gt 0 ]
    then
        ((superCali[$letter]--))
    else
        break
    fi

    ((loopRepeated++))

    if (( i == ${#inputWord}-1 ))
    then
        (( wordInSuperCali++ ))
        i=-1
    fi
done

echo $wordInSuperCali