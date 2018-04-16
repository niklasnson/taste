#! /home/oskja067/.pyenv/shims/python3

from sys import argv

def main(filename):
    freq = {}
    total = 0
    with open(filename, 'r') as f:
        for line in f:
            if line[0] == '[':
                which = line.split('.')[1][:-1]
                if which in freq.keys():
                    freq[which] += 1
                else:
                    freq[which] = 1
                total += 1

    length = max(len(entry) for entry in freq.keys())
    for entry in freq.items():
        print("{}:\t{}\t({}%)".format(entry[0].rjust(length), entry[1], (entry[1]/total)*100))
    print("Total: {}".format(total))

if __name__ == '__main__':
    if len(argv) > 1:
        main(argv[1])
    else:
        print("usage: {} filename".format(argv[0]), file=sys.stderr)