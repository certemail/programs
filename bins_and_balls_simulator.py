#!/usr/bin/env python
import argparse
import random
import logging
import secrets 


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("num_bins", help="number of bins")
    parser.add_argument("num_balls", help="number of balls")
    parser.add_argument("num_trials", help="number of trials")
    parser.add_argument("k_balls", help="number of bins with exactly k balls")
    parser.add_argument("--log", help="log level")
    args = parser.parse_args()

    if args.log:
        numeric_level = getattr(logging, args.log.upper(), None)
        if not isinstance(numeric_level, int):
            raise ValueError('Invalid log level: %s' % loglevel)
        logging.basicConfig(filename='log.txt', filemode='w', level=numeric_level, format='%(levelname)s: %(message)s')


    NUM_BINS = int(args.num_bins)
    NUM_BALLS = int(args.num_balls) 
    K_BALLS = int(args.k_balls)
    NUM_TRIALS = int(args.num_trials)
    
    total_tosses = 0

    # initialize bins

    for i in range(NUM_TRIALS):
        print("\n****TRIAL {} ****".format(i+1))

        # initialize all bins to have zero balls
        bins = [0 for i in range(NUM_BINS)]

        number_of_tosses_until_k_balls_in_bin = 0

        # toss balls into bins
        for i in range(NUM_BINS):
            rng = secrets.SystemRandom()
            random_bin = rng.randint(0, NUM_BINS-1)
            print("toss #{} --> goes into bin#{}".format( (i+1), (random_bin+1)))

            bins[random_bin] += 1

            print("\tbins: ", str(bins))

            # check if any bin has K balls
            if K_BALLS in bins:
                number_of_tosses_until_k_balls_in_bin = i+1
                total_tosses += i+1
                break

            print()
        print("-----------------------------")
        print("number of tosses until one of the bins has {} balls: {}".format(K_BALLS, number_of_tosses_until_k_balls_in_bin))

    print("total tosses: {}".format(total_tosses))
    print("average number of tosses: {:.3f}".format( float(total_tosses) / float(NUM_TRIALS )))
    
if __name__ == '__main__':
    main()

