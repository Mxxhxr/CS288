# !/bin/bash
# The first line tells unix that the file is to be executed by /bin/sh

echo "What is your name"
read USERNAME
echo "Hello $USERNAME, I will make you a file called ${USERNAME}.txt"
touch "${USERNAME}.txt"
touch "${USERNAME}.t"
touch "${USERNAME}.tt"
touch "${USERNAME}.x"
touch "${USERNAME}.xt"
touch "${USERNAME}.xtt"
touch "${USERNAME}.ct"
touch "${USERNAME}.xet"
echo "File ${USERNAME}.txt created!"
