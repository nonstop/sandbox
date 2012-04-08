#!/usr/bin/python


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
