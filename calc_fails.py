from pprint import pprint as pp
from sys import argv

def main(filename):
    freq = {'exsl':0,'unsl':0,'ex':0,'un':0}
    with open(filename, 'r') as f:
        skip_first = True
        for line in f:
            if skip_first:
                skip_first = False
                continue
            l = line.split()
            freq[l[0]] += 1 if l[4] == '1' else 0

    pp(freq)

if __name__ == '__main__':
    if len(argv) < 1:
        print("usage: {} filename".format(argv[0]), file=sys.stderr)
    main(argv[1])
