import argparse
import sys
from MaskBuilder import toBinaryArray

def readFileBytes(filename):
	f = open(filename, "rb")
	characters = []
	try:
		byte = f.read(1)
		while byte != "":
			characters.append(ord(byte))
			byte = f.read(1)
	finally:
		f.close()
	return characters

def toInteger(bits):
	number = 0
	base = 1
	for b in reversed(bits):
		number += base if b == 1 else 0
		base *= 2
	return number

if __name__ == "__main__":

	parser = argparse.ArgumentParser()
	parser.add_argument("-s", "--size-bits", help="The number of bits used for specifying the mask size. 10 by default. It must match the value used for encoding the mask file.", default=10, type=int)
	parser.add_argument("mask", help="The path of the mask file to print. The file has to have been generated with the MaskBuilder.py tool.")

	args = parser.parse_args()
	maskFile = args.mask
	bitsForSize = args.size_bits

	mask = readFileBytes(maskFile)

	imageWidth = toInteger(mask[0:bitsForSize])
	imageHeight = toInteger(mask[bitsForSize:bitsForSize+bitsForSize])
	print("Image size is {},{}").format(imageWidth, imageHeight)

	dataOffset = bitsForSize+bitsForSize

	data = []
	for x in xrange(dataOffset, len(mask)):
		byte = mask[x]
		bits = toBinaryArray(byte, 8)
		for i in reversed(bits):
			data.append(i)
	n = 0
	for i in xrange(0, imageWidth):
		s = ""
		for j in xrange(0, imageHeight):
			s += "-" if data[n] == 0 else "*"
			n += 1
		print s