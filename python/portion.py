#!/usr/bin/python

import sys
import string
import re

cmd='/usr/bin/du -b'

testStrings = ['1 file1', "2\tfile2", '3\tfile 3', '2 file 4']
testSize = 4

class BadRecord(Exception):
    def __init__(self, value):
        self.value = 'BadRecord: ' + value
    def __str__(self):
        return repr(self.value)

class Record(object):
    def __init__(self, str):
        m = re.match(r"([0-9]+)[ \t]+(.*)", str)
        if not m:
            raise BadRecord(str)
        self.size = int(m.group(1))
        self.str = m.group(2)
    def __str__(self):
        return "%i %s" % (self.size, self.str)

def apportion(recs, maxSize):
    pass

def main(args = sys.argv):
    recs = []
    for str in testStrings:
        recs.append(Record(str))
    maxSize = testSize
    apportion(recs, maxSize)
    return 0

if __name__ == '__main__':
    sys.exit(main())


