#! /home/oskja067/.pyenv/shims/python3

import sys
import subprocess
import itertools


def get_unordered():
    seeds = ["1337", "4711", "42", "3571290", "1984"]
    n_messages = ["0", "5", "10"]
    for seed in seeds:
        for n in n_messages:
            test_config = ["./unordered.out", seed, n, "0"]
            yield test_config


def get_unordered_sleep():
    seeds = ["1337", "4711", "42", "3571290", "1984"]
    n_messages = ["0", "5", "10"]
    sleeps = ["0", "500", "1000", "1500", "2000",
              "2500", "3000", "3500", "4000", "4500", "5000"]
    for seed in seeds:
        for n in n_messages:
            for sleep in sleeps:
                test_config = ["./unordered_sleep.out", seed, n, sleep]
                yield test_config


def get_expectmsg():
    seeds = ["1337", "4711", "42", "3571290", "1984"]
    for seed in seeds:
        test_config = ["./expect_msg.out", seed, "0", "0"]
        yield test_config


def get_expectmsg_sleep():
    seeds = ["1337", "4711", "42", "3571290", "1984"]
    sleeps = ["0", "500", "1000", "1500", "2000",
              "2500", "3000", "3500", "4000", "4500", "5000"]
    for seed in seeds:
        for sleep in sleeps:
            test_config = ["./expect_msg_sleep.out", seed, "0", sleep]
            yield test_config


def main():
    col_width = 21
    labels = ["Test", "seed", "n_messages", "test_sleep"]
    print("[=========]", "Gathering initialized.")
    print("[  Start  ]", "".join(num.rjust(col_width) for num in labels))

    for args in get_expectmsg():
        print("[ Running ]", "".join(num.rjust(col_width) for num in args))
        filename = "data/ex_" + "_".join(num for num in args[1:]) + ".data"
        with open(filename, 'wb') as f:
            cp = subprocess.run(args, stdout=subprocess.PIPE)
            f.write(cp.stdout)

    for args in get_unordered():
        print("[ Running ]", "".join(num.rjust(col_width) for num in args))
        filename = "data/un_" + "_".join(num for num in args[1:]) + ".data"
        with open(filename, 'wb') as f:
            cp = subprocess.run(args, stdout=subprocess.PIPE)
            f.write(cp.stdout)

    for args in get_expectmsg_sleep():
        print("[ Running ]", "".join(num.rjust(col_width) for num in args))
        filename = "data/exsl_" + "_".join(num for num in args[1:]) + ".data"
        with open(filename, 'wb') as f:
            cp = subprocess.run(args, stdout=subprocess.PIPE)
            f.write(cp.stdout)

    for args in get_unordered_sleep():
        print("[ Running ]", "".join(num.rjust(col_width) for num in args))
        filename = "data/unsl_" + "_".join(num for num in args[1:]) + ".data"
        with open(filename, 'wb') as f:
            cp = subprocess.run(args, stdout=subprocess.PIPE)
            f.write(cp.stdout)


if __name__ == '__main__':
    main()
