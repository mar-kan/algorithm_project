import os
import struct


def createOutputFile(filename, rows, columns, vectors):  # creates output file for a dataset in dir 'A_outputFiles'
    os.chdir('../A_outputFiles')
    output_file = open(filename, "w+b")

    output_file.write((23).to_bytes(4, byteorder='big'))  # writes magic number
    output_file.write(len(vectors).to_bytes(4, byteorder='big'))  # writes number of images
    output_file.write(rows.to_bytes(4, byteorder='big'))  # writes number of rows
    output_file.write(columns.to_bytes(4, byteorder='big'))  # writes number of columns

    # writes vectors
    for vector in vectors:
        for num in vector:
            output_file.write(bytes(num))

    output_file.close()
