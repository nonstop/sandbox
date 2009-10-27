#!/usr/bin/python

import socket
import sys


def main(argv):
    if len(argv) != 4:
        print """usage: client host port msg"""
        return 1
    srvHost = argv[1]
    srvPort = int(argv[2])
    msg = argv[3]

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect((srvHost, srvPort))
    s.send(msg)
    if msg == "STOP":
        return 0
    print s.recv(1024)


if __name__ == '__main__':
    sys.exit(main(sys.argv))

