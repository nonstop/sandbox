#!/usr/bin/python

import sys
import pstats


p = pstats.Stats(sys.argv[1])
p.strip_dirs().sort_stats('cum').print_stats()
