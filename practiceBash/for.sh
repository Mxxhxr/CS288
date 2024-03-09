#!/bin/bash
# INPUT_STRING="hello"

# while [ "$INPUT_STRING" != "bye" ]
# do
#     echo "Please type something. (bye to quit)"
#     read INPUT_STRING
#     echo "You said: $INPUT_STRING"
# done


# while :
# do
#     echo "Please type something (^C to quit)"
#     read input
#     echo "You typed: $input"
# done

# while read input
# do
#     case $input in
#         hello)          echo English ;;
#         howdy)          echo American ;;
#         gday)           echo Australian ;;
#         bonjour)        echo French ;;
#         "guten tag")    echo German ;;
#         *)              echo Unknown Language: "$input"
#                 ;;
#     esac
# done < input.txt

# mkdir CS{301,490,350}
# x=-0
# if [ "$x" -lt "0" ]
# then 
#     echo "X is less than zero"
#     else
#         echo "x is greater than "
# fi

# X=0
# [ $X -ne 0 ] && echo "X isn't zero" || echo "X is zero"
# echo "Please talk to me ..."
# while :
# do
#   read INPUT_STRING
#   case $INPUT_STRING in
# 	hello)
# 		echo "Hello yourself!"
# 		;;
# 	bye)
# 		echo "See you again!"
# 		break
# 		;;
# 	*)
# 		echo "Sorry, I don't understand"
# 		;;
#   esac
# done
# echo 
# echo "That's all folks!"

# echo "I was called with $# parameters"
# echo "My name is "$0"
# echo "My first parameter is $1"
# echo "My second parameter is $2"
# echo "All parameters are "$@"

add_a_user()
{
  USER=$1
  PASSWORD=$2
  shift; shift;
  # Having shifted twice, the rest is now comments ...
  COMMENTS=$@
  echo "Adding user $USER ..."
  echo useradd -c "$COMMENTS" $USER
  echo passwd $USER $PASSWORD
  echo "Added user $USER ($COMMENTS) with pass $PASSWORD"
}

###
# Main body of script starts here
###
echo "Start of script..."
add_a_user bob letmein Bob Holness the presenter
add_a_user fred badpassword Fred Durst the singer
add_a_user bilko worsepassword Sgt. Bilko the role model
echo "End of script..."