#!/bin/sh

set -e

i="0"
while [ $i -lt 30 ]
do
    ./udpclient&
    i=$[$i+1]
done


