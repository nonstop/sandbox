#!/usr/bin/python
import httplib
import htmllib
import sys

from HTMLParser import HTMLParser
class MyHTMLParser(HTMLParser):
    __baseUrl = ''
    def setUrl(self, url):
        self.__baseUrl = self.__clearUrl(url)

    def handle_starttag(self, tag, attrs):
        if (tag == "img"):
            for attr in attrs:
                if attr[0] == "src":
                    if (attr[1].find("http://") == -1):
                        print self.__baseUrl + attr[1]
                    else:
                        print attr[1]

    def __clearUrl(self, url):
        pos = url.find('?')
        if (pos != -1):
            url =url[0:pos]
        pos = url.rfind('/')
        pos2 = url.rfind('://')
        
        if (pos == pos2 + 1):
            url = url + '/'
            return url

        return url[0:pos + 1]

def usage():
    print >> sys.stderr, "Usage: imgget.py URL"

def main(argv=None):
    if argv is None:
        argv = sys.argv
    if len(argv) != 2:
        usage()
        return 2
    url = sys.argv[1]

    h1 = httplib.HTTPConnection("10.1.9.145", 3128)
    h1.connect()
    h1.request("GET", url)
    resp = h1.getresponse()

    s = resp.read()

    p = MyHTMLParser()
    p.setUrl(url)
    p.feed(s)

    return 0

if __name__ == "__main__":
    sys.exit(main())

