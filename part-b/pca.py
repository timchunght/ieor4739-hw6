import numpy as np
import time

def import_Q_from_file(file_path):
	input_file = open(file_path, 'r')
	# first line is number of assets
	asset_size =  int(input_file.readline().split()[1])
	# create a n times n matrix
	Q = np.ndarray(shape=(asset_size, asset_size))

	input_file.readline()
	for j in range(asset_size):
		current_line = input_file.readline().split()
		while len(current_line) == 0 or current_line[1] == "matrix":
			current_line = input_file.readline()	
			current_line = current_line.split()
		print current_line
		for k in range(asset_size):
			Q[j,k] = float(current_line[j])

	input_file.close()
	return Q


import_Q_from_file("/Users/timothychung/Documents/workspace/IEOR/hw4/part-a/rpower/data/russell-1000-Q.dat")