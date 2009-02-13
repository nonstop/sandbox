#!/bin/bash

VAR="qwe"
VAR2=$VAR

echo "start"

if [ "$VAR" != "$VAR2" ]
then
    echo $VAR" != "$VAR2
else
    echo $VAR" == "$VAR2
fi

echo "finish"

echo
echo "Internal Variables"
echo

if [ ! -n "$1" ]
then
  echo "Usage: `basename $0` argument1 argument2 etc."
  exit $E_BADARGS
fi  
echo "Listing args with \"\$*\":"
index=1          # Initialize count.
for arg in "$*"  # Doesn't work properly if "$*" isn't quoted.
do
  echo "Arg #$index = $arg"
  let "index+=1"
done             # $* sees all arguments as single word. 

index=1          # Reset count.
                 # What happens if you forget to do this?

echo "Listing args with \"\$@\":"
for arg in "$@"
do
  echo "Arg #$index = $arg"
  let "index+=1"
done             # $@ sees arguments as separate words. 
echo "Arg list seen as separate words."

echo
echo "Manipulating Strings"
echo

stringZ=abcABC123ABCabc

# String Length
echo ${#stringZ}                 # 15
echo `expr length $stringZ`      # 15
echo `expr "$stringZ" : '.*'`    # 15

# Length of Matching Substring at Beginning of String
echo `expr match "$stringZ" 'abc[A-Z]*.2'`   # 8
echo `expr "$stringZ" : 'abc[A-Z]*.2'`       # 8
# Numerical position in $string of first character in $substring that matches.
echo `expr index "$stringZ" 1c`              # 3
# Substring Extraction
echo ${stringZ:0}                            # abcABC123ABCabc
echo ${stringZ:1}                            # bcABC123ABCabc
echo ${stringZ:7}                            # 23ABCabc
echo ${stringZ:7:3}                          # 23A
# Extracts $length characters from $string starting at $position.
echo `expr substr $stringZ 1 2`              # ab
echo `expr substr $stringZ 4 3`              # ABC
# Extracts $substring  at beginning of $string, where $substring is a regular expression.
echo `expr match "$stringZ" '\(.[b-c]*[A-Z]..[0-9]\)'`   # abcABC1
echo `expr "$stringZ" : '\(.[b-c]*[A-Z]..[0-9]\)'`       # abcABC1
echo `expr "$stringZ" : '\(.......\)'`                   # abcABC1


warningStr="file:line warning text : "
echo $warningStr `expr "$warningStr" : '.*\(warning\)'`

if [ `expr "$warningStr" : '.*\(warning\)'` ]
then
    warningStr=$RED$warningStr
fi
RED='\e[1;31m'
echo $RED
echo $warningStr

echo -e "\e[1;31m$warningStr\e[0m"

index=1          # Initialize count.
for arg in "$@"  # Doesn't work properly if "$*" isn't quoted.
do
    if [ `expr "$arg" : '.*\(warning\)'` ]
    then
        echo -e "\e[1;31m$arg\e[0m"
    else
        echo $arg
    fi

    let "index+=1"
done             # $* sees all arguments as single word. 

echo "cycle"
read
while [ "$REPLY" ]
do
    if [ `expr "$REPLY" : '.*\(warning\)'` ]
    then
        echo -e "\e[1;31m$REPLY\e[0m"
    else
        echo $REPLY
    fi
    read
done

# renaming
for FILE in *.mp3 ; do 
    NEWFILE=`echo $FILE | sed 's/ /_/g'`; 
    echo "$FILE will be renamed as $NEWFILE"; 
done


