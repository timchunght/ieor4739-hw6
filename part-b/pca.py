import numpy as np


def import_Q_from_file(file_path):
	input_file = open(file_path, 'r')
	# first line is number of assets
	asset_size =  int(input_file.readline().split()[1])
	# create a n times n matrix
	Q = np.ndarray(shape=(asset_size, asset_size))
	for j in range(asset_size + 1):
		current_line = input_file.readline().split()
		if current_line[0] == "matrix":
			pass
		else:
			for k in range(asset):
				Q[j,k] = float(current_line[j])

	input_file.close()
	return Q

