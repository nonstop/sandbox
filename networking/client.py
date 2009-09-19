#!/usr/bin/python

import socket
import sys


def main(argv):
    if len(argv) != 4:
        print """usage: client host port msgFile"""
        return 1
    srvHost = argv[1]
    srvPort = int(argv[2])
    msg = file(argv[3]).read()

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect((srvHost, srvPort))
    while (1):
        #print('bytes send: %d' % s.send(msg))
        #print('answer: %s' % s.recv(1024))
        s.send(msg)
        s.recv(1024)


if __name__ == '__main__':
    sys.exit(main(sys.argv))

