#!/usr/bin/env python

import os
import sys
import datetime
#from datetime import date
from time import strptime
from popen2 import Popen3

class Stat:
    commits = 0
    addedLines = 0
    removedLines = 0
    total = 0
    def __init__(self, com_, add_, rem_):
        self.commits = com_
        self.addedLines = add_
        self.removedLines = rem_
        self.total = self.addedLines - self.removedLines

class Author:
    name = ''
    __commits = []
    stats = None
    def __init__(self, name_):
        self.name = name_
        self.__commits = []
        self.stats = None
    def addCommit(self, revNo, revDate):
        self.__commits.append((revNo, revDate))
    #def stat(self):
        #return '%s: %d' % (self.__name, len(self.__commits))
    def processCommits(self, dateFrom, dateTo):
        totalRemoved, totalAdded, commits = (0, 0, 0)
        for commit, revDate in self.__commits[:-1]:
            if dateFrom == None:
                commits += 1
                (lnRem, lnAdd) = self.__processCommit(commit)
                totalRemoved += lnRem
                totalAdded += lnAdd
            elif (dateFrom < revDate) and (revDate < dateTo):
                commits += 1
                (lnRem, lnAdd) = self.__processCommit(commit)
                totalRemoved += lnRem
                totalAdded += lnAdd
        self.stats = Stat(commits, totalAdded, totalRemoved)
        return int(self.stats.total)

    def __processCommit(self, commit):
        linesRemoved, linesAdded = 0, 0
        cmd = 'svn diff -c%d | grep "^[-+][^-+]" 2>/dev/null' % commit
        proc = Popen3(cmd)
        src = proc.fromchild
        l = src.readline()
        while len(l) :                
            if l[0] == '-':
                linesRemoved += 1
            elif l[0] == '+':
                linesAdded += 1
            else:
                l = l[:-1]
                print "bad line: ", l
            sys.stdout.flush()
            l = src.readline()
        src.close()
        return (linesRemoved, linesAdded)

class LineStat:
    revNo = 0
    author = ""
    revDate = None
    def __init__(self, ln):
        words = ln.split(' | ')
        self.revNo = int(words[0][1:])
        self.author = words[1]
        self.revDate = getDate(words[2].split()[0])
    def __str__(self):
        return '%s: %d - %s' % (self.author, self.revNo, self.revDate)

def appendStat(authors, stat):
    if not authors.has_key(stat.author):
        authors[stat.author] = Author(stat.author)
    authors.get(stat.author).addCommit(stat.revNo, stat.revDate)

def xmlPrinter(author, stats):
    str = '<author name="%s"><commits>%d</commits><added>%d</added><removed>%d</removed><total>%d</total></author>'
    print str % (author, stats.commits, stats.addedLines, stats.removedLines, stats.total)

def consolePrinter(author, stats):
    total = stats.total
    if total < 0:
        total = str(total)
    else:
        total = '+' + str(total)
    print '%s\t%d\t+%d\t-%d\t%s' % (author, stats.commits, stats.addedLines, stats.removedLines, total)

def getDate(dateStr):
    return datetime.date(*strptime(dateStr, "%Y-%m-%d")[0:3])

def main(argv=None):
    if argv is None:
        argv = sys.argv

    dateFrom, dateTo = None, None
    if len(argv) == 3:
        dateFrom = getDate(sys.argv[1])
        dateTo = getDate(sys.argv[2])

    cmd = 'svn log | grep "^r[0-9].*|" 2>/dev/null'
    authors = {}

    cmd = 'cat /home/nonstop/tmp/svn.log | grep "^r[0-9].*|" 2>/dev/null'
    proc = Popen3(cmd)
    src = proc.fromchild
    l = src.readline()
    while len(l) :
        stat = LineStat(l)
        appendStat(authors, stat)
        sys.stdout.flush()
        l = src.readline()
    src.close()

    #for author in authors:
        #print authors.get(author).stat()
    
    totalLines = 0
    for author in authors:
        au = authors.get(author)
        totalLines += au.processCommits(dateFrom, dateTo)
        if au.stats.total:
            #xmlPrinter(au.name, au.stats)
            consolePrinter(au.name, au.stats)

    if totalLines:
        if totalLines > 0:
            print "total: +%d" % totalLines
        else:
            print "total: %d" % totalLines

    return 0

if __name__ == "__main__":
    sys.exit(main())

