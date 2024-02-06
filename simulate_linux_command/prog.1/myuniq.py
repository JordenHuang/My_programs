#!/usr/bin/env python3
import sys
number_of_args = len(sys.argv)
if number_of_args != 2:
    sys.stderr.write('Usage: %s inputFile\n' % sys.argv[0])
    sys.exit(1)
try:
    fh = open(sys.argv[1], 'r')
except:
    sys.stderr.write('cannot open input file %s\n' % sys.argv[1])
    sys.exit(2)
previous_line =''  #initialize
for line in fh.readlines():
    if line != previous_line: #filter
        print(line, end='')
    previous_line = line #update previous
fh.close()
