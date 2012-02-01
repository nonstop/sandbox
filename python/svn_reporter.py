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
import getopt
from subprocess import Popen
from subprocess import PIPE
from subprocess import STDOUT

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
        cmd = 'svn diff -x -wb -c%d %s | grep "^[-+]" 2>/dev/null | grep -v "\(---\|+++\).*revision" 2>/dev/null' % (commit, svnUrl)
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

class Commit(object):
    pass

class SvnLogParser(object):
    __parser = xml.parsers.expat.ParserCreate()
    __res = None
    __commits = []
    __state = ''
    __tmpVal = ''
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
            self.__res = Commit()
            self.__res.rev = attrs['revision']
            self.__res.author = ''
    def EndElementHandler(self, name):
        if name == 'logentry':
            self.__commits.append(self.__res)
            self.__res = None
        if self.__state == 'date':
            self.__res.date = datetime.datetime.strptime(self.__tmpVal[:self.__tmpVal.rfind('.')], "%Y-%m-%dT%H:%M:%S")
        if self.__state == 'author':
            self.__res.author += self.__tmpVal.strip()
        self.__state = ''
        self.__tmpVal = ''
    def CharacterDataHandler(self, data):
        if self.__state == 'date' or self.__state == 'author':
            self.__tmpVal += data.strip()

    def commits(self):
        return self.__commits

def usage():
    print"""Usage: svn_reporter.py svn_url [date_from date_to]"""

def printResults(header, resultAuthors, totalLines):
    resultAuthors.sort(lambda l, r: cmp(l.name, r.name))
    print header
    for author in resultAuthors:
        total = author.stats.total
        if total < 0:
            total = str(total)
        else:
            total = '+' + str(total)
        print('{0:>12} {1:>5}: {2:>7} {3:>7} = {4:>7}'.format(author.name, author.stats.commits,
            '+' + str(author.stats.addedLines), '-' + str(author.stats.removedLines), total))
    if totalLines:
        if totalLines > 0:
            print "total: +%d" % totalLines
        else:
            print "total: %d" % totalLines

class CommitGroup(object):
    def __init__(self):
        self.name = ''
        self.commits = []

def createCommitGroups(groupCriterium, commits):
    commits.sort(lambda l, r: cmp(l.date, r.date))
    res = []
    if not groupCriterium:
        startDate, endDate = None, None
        if len(commits) > 0:
            startDate = commits[0].date
            endDate = commits[len(commits) - 1].date
        cg = CommitGroup()
        cg.name = "{0} - {1}".format(startDate.date(), endDate.date())
        cg.commits = commits
        res.append(cg)
    else:
        if groupCriterium == 'm': # per month
            startDate, endDate = None, None
            prevMonth = None
            cg = CommitGroup()
            for c in commits:
                if not prevMonth:
                    prevMonth = c.date.month
                    startDate = c.date
                elif prevMonth != c.date.month:
                    cg.name = "{0} - {1}".format(startDate.date(), endDate.date())
                    res.append(cg)
                    cg = CommitGroup()
                    startDate = c.date
                    prevMonth = c.date.month
                cg.commits.append(c)
                endDate = c.date
            if len(cg.commits):
                cg.name = "{0} - {1}".format(startDate.date(), endDate.date())
                res.append(cg)
    return res

def groupByAuthors(commits):
    authors = {}
    for c in commits:
        if not authors.has_key(c.author):
            authors[c.author] = Author(c.author)
        authors[c.author].addCommit(int(c.rev))
    return authors

def main(argv=None):
    if argv is None:
        argv = sys.argv
    global svnUrl
    logfile, dateFrom, dateTo, group = None, None, None, None
    try:
        opts, args = getopt.getopt(argv[1:], "", ["url=", "logfile=", "from=", "to=", "group="])
    except getopt.GetoptError, err:
        print str(err)
        usage()
        return 1
    for k, v in opts:
        if k == '--url':
            svnUrl = v
        elif k == '--from':
            dateFrom = v
        elif k == '--to':
            dateTo = v
        elif k == '--logfile':
            logfile = v
        elif k == '--group':
            group = v

    cmd = 'svn log --xml'
    if dateFrom and dateTo:
        cmd += ' -r{%s}:{%s}' % (dateFrom, dateTo)
    cmd += ' %s' % svnUrl

    p = SvnLogParser()
    if not logfile:
        proc = Popen(cmd, shell=True, stdout=PIPE, close_fds=True)
        src = proc.stdout
        p.ParseFile(src)
        src.close()
    else:
        p.ParseFile(file(logfile))
    commitGroups = createCommitGroups(group, p.commits())
    for cg in commitGroups:
        totalLines = 0
        resultAuthors = []
        authors = groupByAuthors(cg.commits)
        for author in authors:
            au = authors.get(author)
            totalLines += au.processCommits()
            if au.stats.total != None:
                resultAuthors.append(au)
        printResults(cg.name, resultAuthors, totalLines)

    return 0


if __name__ == "__main__":
    sys.exit(main())

