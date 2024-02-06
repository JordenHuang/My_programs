#!/usr/bin/env python3
import sys
number_of_args = len(sys.argv)
if number_of_args != 3:
    sys.stderr.write('Usage: %s inputFile\n' % sys.argv[0])
    sys.exit(1)
try:
    fh = open(sys.argv[2], 'r')
except:
    sys.stderr.write('cannot open input file %s\n' % sys.argv[2])
    sys.exit(2)
pattern = sys.argv[1]
for line in fh.readlines():
    if line.find(pattern) >= 0:
        print(line, end='')
fh.close()
