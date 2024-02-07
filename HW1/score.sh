#!/bin/bash

#5 command line arguments (ints between 1-6)
dice=($1 $2 $3 $4 $5)

numOne=0
numTwo=0
numThree=0
numFour=0
numFive=0
numSix=0

for die in ${dice[@]}
do
    if [ $die -eq 1 ]
    then
        ((numOne=numOne+1))
    elif [ $die -eq 2 ]
    then
        ((numTwo=numTwo+1))
    elif [ $die -eq 3 ]
    then
        ((numThree=numThree+1))
    elif [ $die -eq 4 ]
    then
        ((numFour=numFour+1))
    elif [ $die -eq 5 ]
    then
        ((numFive=numFive+1))
    elif [ $die -eq 6 ]
    then
        ((numSix=numSix+1))
    fi
done

#for full house i dont wanna make a giant if stmnt
#also added variables that help with the checks
twoSame=0
threeSame=0
amntOdd=0
odds=0

for i in $numOne $numTwo $numThree $numFour $numFive $numSix; do
    if [ "$i" -eq 3 ]; then
        ((threeSame++))
    elif [ "$i" -eq 2 ]; then
        ((twoSame++))
    elif (("$i" % 2 == 1)); then
        ((odds++));
    fi
done

#three of a kind
for each in ${dice[@]}
do
    if ((each % 2 == 1));
    then
        ((amntOdd=amntOdd+1))
    fi
done

#if statements for dice
if [ "${dice[0]}" -eq "${dice[1]}" -a "${dice[1]}" -eq "${dice[2]}" -a "${dice[2]}" -eq "${dice[3]}" -a "${dice[3]}" -eq "${dice[4]}" ]
then
    echo "Five of a kind"

elif [ "$numOne" -eq 4 -o "$numTwo" -eq 4 -o "$numThree" -eq 4 -o "$numFour" -eq 4 -o "$numFive" -eq 4 -o "$numSix" -eq 4 ]
then
    echo "Four of a kind"

elif [ "$numOne" -eq 1 -a "$numTwo" -eq 1 -a "$numThree" -eq 1 -a "$numFour" -eq 1 -a "$numFive" -eq 1 ]
then
    echo "Straight"
elif [ "$numTwo" -eq 1 -a "$numThree" -eq 1 -a "$numFour" -eq 1 -a "$numFive" -eq 1 -a "$numSix" -eq 1 ]
then
    echo "Straight"
elif [ "$threeSame" -eq 1 -a "$twoSame" -eq 1 ]
then
    echo "Full house"

elif [ "$threeSame" -eq 1 ] && [ $odds -eq 2 ]
then
    echo "Three of a kind"

elif [ $twoSame -eq 2 -a $odds -eq 1 ]
then
    echo "Two pair"

elif [ $twoSame -ge 1 -a $amntOdd -ge 3 ]
then
    echo "One pair"
else
    echo "Bust"
fi