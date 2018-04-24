#! /home/oskja067/.pyenv/shims/python3

import sys
import subprocess
import itertools


def get_args(iterations):
    # 18432
    seeds = ["1337"]  # , "1989", "42", "420", "2018", "1804"]
    n_messages = ["100"]  # , "1000", "1000000"]
    sleeps = ["0", "50", "500", "1000"]
    for seed in seeds:
        for n in n_messages:
            for perm in list(itertools.product(sleeps, repeat=5)):
                test_config = ["./test_solutions.out", seed, n]
                test_config += perm
                test_config += ["--gtest_repeat={}".format(iterations)]
                yield test_config


def main(iterations):
    col_width = 12
    labels = ["seed", "n_messages", "sleep_one", "sleep_uno1",
              "sleep_uno2", "sleep_uno3", "sleep_uno4"]
    print("[=========]", "Gathering for", iterations, "iterations.")
    print("[  Start  ]", "".join(num.rjust(col_width) for num in labels))

    n = 0
    for args in get_args(iterations):
        print("[ Running ]", "".join(num.rjust(col_width)
                                     for num in args[1:-1]))
        n += 1
        filename = "data/gather_" + \
            "_".join(num for num in args[1:-1]) + ".out"
        with open(filename, 'wb') as f:
            cp = subprocess.run(args, stdout=subprocess.PIPE)
            f.write(cp.stdout)

        print("[  Done   ]", "{}/{}".format(n, 1024), n/1024 * 100, '%')


if __name__ == '__main__':
    iterations = 0
    if len(sys.argv) > 1:
        try:
            iterations = int(sys.argv[1])
        except:
            print("usage: {} <num_iterations, integer>".format(
                sys.argv[0]), file=sys.stderr)
        main(iterations)
    else:
        print("usage: {} <num_iterations, integer>".format(
            sys.argv[0]), file=sys.stderr)