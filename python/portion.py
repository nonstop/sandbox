#!/usr/bin/python

import sys
import string
import re

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
        if string.find(self.str, ' ') == -1:
            return "%s" % (self.str)
        else:
            return "\"%s\"" % (self.str)

def record_compare(lv, rv):
    if lv.size < rv.size:
        return 1
    elif lv.size == rv.size:
        return 0
    else:
        return -1

class RecordStorage(object):
    def __init__(self):
        self.size = 0
        self.records = []
    def __str__(self):
        recStr = ''
        for rec in self.records:
            recStr += " " + str(rec)
        return "size: %d recs:\n%s" % (self.size, recStr[1:])

def apportion(records, maxSize):
    records.sort(record_compare)
    n = 0
    resultRecs = {}
    for rec in records:
        noMoreSpace = True
        for i in range(n):
            if resultRecs[i].size + rec.size <= maxSize:
                resultRecs[i].size += rec.size
                resultRecs[i].records.append(rec)
                noMoreSpace = False
                break
        if noMoreSpace == True:
            resultRecs[n] = RecordStorage()
            resultRecs[n].size += rec.size
            resultRecs[n].records.append(rec)
            n += 1
    return resultRecs

def usage():
    print("portion.py size < file")

def main(argv = sys.argv):
    recs = []
    if len(argv) != 2:
        usage()
        return 1
    maxSize = int(argv[1])
    for str in sys.stdin:
        recs.append(Record(str[:-1]))
    resultRecs = apportion(recs, maxSize)
    for i in resultRecs:
        print("\t%d %s" % (i, resultRecs[i]))
    return 0

if __name__ == '__main__':
    sys.exit(main())


