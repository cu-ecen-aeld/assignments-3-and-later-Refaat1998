#!/bin/bash
# use predefined variables to access passed arguments
#echo arguments to the shell
set -e

echo $1 $2 $3 ' -> echo $1 $2 $3'

# We can also store arguments from bash command line in special array
args=("$@")
#echo arguments to the shell
filesdir=${args[0]}
searchstr=${args[1]}
echo $filesdir $searchstr ${args[2]} ' -> args=("$@"); echo ${args[0]} ${args[1]} ${args[2]}'

if [ "$#" -lt 2 ] 
then
	echo "You must insert two arguments"
	exit 1
else
	echo "inserted two arguments successfully"
	if [ -d "$filesdir" ]; then
		x="$(grep -rnw "$filesdir" -e "$searchstr" | wc -l)"
		y="$(grep -rnw "$filesdir" -e "$searchstr" | wc -w)"
		echo "The number of files are $x and the number of matching lines are $y"
		
		exit 0  
	else 
		echo "Directory doesn't exist"
		exit 1
	fi 
fi



#use $@ to print out all arguments at once
echo $@ ' -> echo $@'
# use $# variable to print out
# number of arguments passed to the bash script
echo Number of arguments passed: $# ' -> echo Number of arguments passed: $#' 
