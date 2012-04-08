#!/usr/bin/python

import sys, string, random, subprocess, shlex

# generate test cases, then run all available and display results in table
# string
# k
# |  C  |  C++  |  Go  | Python | Haskell | Erlang |
# |------------------------------------------------|
# |  ok |  fail |  ok  |        |         |        |
# |  3s |   5s  |  8s  |        |         |        |


def testGenerator():
    for i in range(0, 2): #10
        s = ""
        k = 0
        for j in range(1, random.randint(1, 20)): #1024
            v = random.randint(1, 3) > 2
            if v:
                k = k + 1
                s = s + '1'
            else:
                s = s + '0'
        if k > 0:
            ks = []
            for j in range(0, 3): # 3
                v = random.randint(1, k)
                if not v in ks:
                    ks.append(v)
                    yield (str(v), s)

programs = [('C', 'search_c'),
        ('C++', 'search_cc'),
        ('Go', 'search_go'),
        ('Scheme', '/usr/bin/guile -e main -s search.scm')]

def main(argv = sys.argv):
    s = ''
    for p in programs:
        s = s + '%10s' % (p[0])
    print s
    for tc in testGenerator():
        results = {}
        print tc[0], tc[1]
        s =  ''
        for p in programs:
            args = shlex.split(p[1])
            args.append(tc[0])
            args.append(tc[1])
            sp = subprocess.Popen(args, stdout=subprocess.PIPE)
            sp.wait()
            if sp.returncode != 0:
                s = s + '%10s' % 'fail'
            else:
                res = sp.stdout.read()[:-1]
                results[res] = p[0]
                s = s + '%10s' % (res)
        if len(results) != 1:
            print '[1;31m' + s + '[0m'
        else:
            print s

    return 0

if __name__ == '__main__':
    sys.exit(main())
