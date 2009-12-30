#!/bin/env python
# this script generates report of commit activity at selected SVN url
# and date-period (optional).
# output format is:
# SVN url
# <user>  <commits>  <rows added>  <rows deleted>  <total rows>
# ...
# <total rows for all users>
# Fields are separated with TABs <\t>
#


import os
import sys
import datetime
import xml.parsers.expat
from subprocess import Popen
from subprocess import PIPE
from subprocess import STDOUT

authors = {}
svnUrl = None

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
    def addCommit(self, revNo):
        #print(self.name, revNo)
        self.__commits.append((revNo))
    def processCommits(self):
        totalRemoved, totalAdded, commits = (0, 0, 0)
        for commit in self.__commits:
            (lnRem, lnAdd) = self.__processCommit(commit)
            totalRemoved += lnRem
            totalAdded += lnAdd
            commits += 1
        self.stats = Stat(commits, totalAdded, totalRemoved)
        return int(self.stats.total)

    def __processCommit(self, commit):
        linesRemoved, linesAdded = 0, 0
        #cmd = 'svn diff -c%d | grep "^[-+][^-+]" 2>/dev/null' % commit
        cmd = 'svn diff -x -wb -c%d %s | grep "^[-+][^-+]" 2>/dev/null' % (commit, svnUrl)
        proc = Popen(cmd, shell=True, stdout=PIPE, close_fds=True)
        src = proc.stdout
        l = src.readline()
        while len(l):
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

class Result(object):
    pass

class SvnLogParser(object):
    __parser = xml.parsers.expat.ParserCreate()
    __res = None
    __state = ''
    def __init__(self):
        self.__parser.StartElementHandler = self.StartElementHandler
        self.__parser.EndElementHandler = self.EndElementHandler
        self.__parser.CharacterDataHandler = self.CharacterDataHandler
    def ParseFile(self, file):
        self.__parser.ParseFile(file)
    def Parse(self, str):
        self.__parser.Parse(str)
    def StartElementHandler(self, name, attrs):
        self.__state = name
        if self.__state == 'logentry':
            self.__res = Result()
            self.__res.rev = attrs['revision']
            self.__res.author = ''
    def EndElementHandler(self, name):
        if name == 'logentry':
            global authors
            if not authors.has_key(self.__res.author):
                authors[self.__res.author] = Author(self.__res.author)
            authors[self.__res.author].addCommit(int(self.__res.rev))
            self.__res = None
        self.__state = ''
    def CharacterDataHandler(self, data):
        if self.__state == 'author':
            self.__res.author += data.strip()
def getDate(dateStr):
    return datetime.date(*strptime(dateStr, "%Y-%m-%d")[0:3])

def usage():
    print"""Usage: svn_reporter.py svn_url [date_from date_to]"""

def consolePrinter(author, stats):
    total = stats.total
    if total < 0:
        total = str(total)
    else:
        total = '+' + str(total)
    print('{0:>12} {1:>5}: {2:>7} {3:>7} = {4:>7}'.format(author, stats.commits, '+' + str(stats.addedLines), '-' + str(stats.removedLines), total))

def main(argv=None):
    if argv is None:
        argv = sys.argv
    global svnUrl
    dateFrom, dateTo = None, None
    if len(argv) == 2:
        svnUrl = argv[1]
    elif len(argv) == 4:
        svnUrl = argv[1]
        dateFrom = sys.argv[2]
        dateTo = sys.argv[3]
    else:
        usage()
        return 1

    cmd = 'svn log --xml'
    if dateFrom and dateTo:
        cmd += ' -r{%s}:{%s}' % (dateFrom, dateTo)
    cmd += ' %s' % svnUrl

    p = SvnLogParser()
    #print(cmd)
    proc = Popen(cmd, shell=True, stdout=PIPE, close_fds=True)
    src = proc.stdout
    p.ParseFile(src)
    src.close()

#    p.ParseFile(file('a.xml'))
    totalLines = 0
    global authors
    resultAuthors = []
    for author in authors:
        #print(author)
        au = authors.get(author)
        totalLines += au.processCommits()
        if au.stats.total != None:
            resultAuthors.append(au)

    resultAuthors.sort(lambda l, r: cmp(l.name, r.name))
    for author in resultAuthors:
        consolePrinter(author.name, author.stats)
    if totalLines:
        if totalLines > 0:
            print "total: +%d" % totalLines
        else:
            print "total: %d" % totalLines

    return 0


if __name__ == "__main__":
    sys.exit(main())

