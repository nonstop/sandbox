#!/usr/bin/python

import sys
import string
import re

testStrings = ['1 file1', '2\tfile2', '3\tfile 3', '2 file 4', '4 file 5']
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
        #return "%i %s" % (self.size, self.str)
        return "%s" % (self.str)

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
        return "size: %d recs: %s" % (self.size, recStr)

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

def main(args = sys.argv):
    recs = []
    maxSize = 4500000 # kb in DVD
    for str in sys.stdin:
        recs.append(Record(str[:-1]))
    resultRecs = apportion(recs, maxSize)
    for i in resultRecs:
        print(resultRecs[i])
    return 0

if __name__ == '__main__':
    sys.exit(main())


