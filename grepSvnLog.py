#!/bin/env python

import sys
import string
import getopt
import xml.parsers.expat

class Result(object):
    def a(): pass

class SvnLogParser(object):
    __parser = xml.parsers.expat.ParserCreate()
    __res = None
    __state = ''
    __filter = ''
    def __init__(self, filter):
        self.__parser.StartElementHandler = self.StartElementHandler
        self.__parser.EndElementHandler = self.EndElementHandler
        self.__parser.CharacterDataHandler = self.CharacterDataHandler
        self.__filter = filter
    def ParseFile(self, file):
        self.__parser.ParseFile(file)
    def Parse(self, str):
        self.__parser.Parse(str)
    def StartElementHandler(self, name, attrs):
        self.__state = name
        if self.__state == 'logentry':
            self.__res = Result()
            self.__res.rev = attrs['revision']
            self.__res.msg = ''
            self.__res.author = ''
    def EndElementHandler(self, name):
#        if name == 'logentry':
        if name == 'logentry' and self.__res.author == self.__filter:
#            print '[1;33m', self.__res.rev, '[1;32m', self.__res.msg, '[0m'
            print self.__res.rev, self.__res.msg
            self.__res = None
        self.__state = ''
    def CharacterDataHandler(self, data):
        if self.__state == 'author':
            self.__res.author += data.strip()
        elif self.__state == 'msg':
            self.__res.msg += data.strip()

def usage():
    print """usage:
    """

def main(argv):
    if len(argv) != 3:
        usage()
        return 0
    query = argv[2]

    p = SvnLogParser(query)
    p.ParseFile(file(argv[1]))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))

