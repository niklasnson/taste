#! /home/oskja067/.pyenv/shims/python3

from sys import argv
import os
import re


def main(folder):
    with open("data/data.txt", 'a') as f:
        f.write("Test Seed Messages Sleep Passed Time(ms)\n")
        for filename in os.listdir(folder):
            if filename == 'data.txt':
                continue
            print("Processing", filename)

            f.write(" ".join(part for part in filename[:-5].split(
                '_')) + ' ' + find_failed(folder + '/' + filename) +
                ' ' + find_time(folder + '/' + filename) + '\n')


def find_failed(filename):
    with open(filename, 'r') as f:
        for line in f:
            if "FAILED" in line:
                return "0"
    return "1"


def find_time(filename):
    with open(filename, 'r') as f:
        for line in f:
            m = re.search('\((\d+)\sms\)', line)
            if m:
                return m.group(1)
    return "NaN"


if __name__ == '__main__':
    if len(argv) > 1:
        main(argv[1])
    else:
        print("usage: {} folder".format(argv[0]), file=sys.stderr)
