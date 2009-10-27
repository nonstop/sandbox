#!/bin/sh

set -e

HOST=a3fc
CLIENTS=10
HANDLERS=1
CLIENTS_PORT=9999
HANDLERS_PORT=9998

if [ "$1" == "start" ]; then
    rm -f log
    ./dispatcher $CLIENTS_PORT $HANDLERS_PORT &
    for ((i=0; i<$CLIENTS; i=i+1)); do
        python client.py $HOST $CLIENTS_PORT "Hi" &
    done
elif [ "$1" == "stop" ]; then
    python client.py $HOST $CLIENTS_PORT "STOP"
else
    echo "usage: $0 start|stop"
    exit 1
fi


