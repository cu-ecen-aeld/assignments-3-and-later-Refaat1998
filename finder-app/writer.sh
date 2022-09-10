#!/bin/bash
# use predefined variables to access passed arguments
#echo arguments to the shell
set -e

echo $1 $2 $3 ' -> echo $1 $2 $3'

# We can also store arguments from bash command line in special array
args=("$@")
#echo arguments to the shell
writefile=${args[0]}
writestr=${args[1]}
echo $writefile $writestr ${args[2]} ' -> args=("$@"); echo ${args[0]} ${args[1]} ${args[2]}'

if [ "$#" -lt 2 ] 
then
	echo "You must insert two arguments"
	exit 1
else
	echo "inserted two arguments successfully"
	if echo "$writestr" > "$writefile"; then
		echo "file created successfully"
		exit 0
		
	else 
		echo "file couldn't be created"
		exit 1
	fi

fi
