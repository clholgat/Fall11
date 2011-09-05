

import sys
from collections import deque


def convert(infile, outfile, obj):
	outfile = open(outfile, 'w+')
	infile = open(infile, 'r')
	
	for line in infile.readlines():
		line = line.strip(' \n').split(" ")
		line = deque(line)
		outfile.write("int %sLen = %d;\n" % (obj, len(line)/3))
		outfile.write("float %s[][3] = {" % obj )
		while len(line) > 0:
			outfile.write("{%s, %s, %s}," % (line.popleft(), line.popleft(), line.popleft()))
	outfile.write("};\n")



if __name__ == "__main__":
	convert(sys.argv[1], sys.argv[2], sys.argv[3])
