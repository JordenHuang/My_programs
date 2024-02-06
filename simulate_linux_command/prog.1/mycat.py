#!/usr/bin/env python3
import sys
number_of_args = len(sys.argv)
if number_of_args < 2:
    sys.stderr.write('Usage: %s inputFile\n' % sys.argv[0])
    sys.exit(1)
for file_name in sys.argv[1:]:
    try:
        fh = open(file_name, 'r')
    except:
        sys.stderr.write('cannot open input file %s\n' % file_name)
        sys.exit(2)
    for line in fh.readlines():
        print(line, end='')
    fh.close()
