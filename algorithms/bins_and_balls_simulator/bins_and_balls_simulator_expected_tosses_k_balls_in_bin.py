#!/usr/bin/env python
import argparse
import random
import logging
import secrets 
import sys

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("num_bins", help="number of bins")
    parser.add_argument("num_trials", help="number of trials")
    parser.add_argument("k_balls", help="number of bins with exactly k balls")
    parser.add_argument("--log", help="log level")
    args = parser.parse_args()

    if args.log:
        numeric_level = getattr(logging, args.log.upper(), None)
        if not isinstance(numeric_level, int):
            raise ValueError('Invalid log level: %s' % loglevel)
        logging.basicConfig(level=numeric_level, \
                            format='%(levelname)s: %(message)s', \
                            stream=sys.stdout)
                            #filename='log.txt', filemode='w'

    NUM_BINS = int(args.num_bins)
    K_BALLS = int(args.k_balls)
    NUM_TRIALS = int(args.num_trials)
    
    print("number bins:   {}".format(NUM_BINS))
    print("k balls:       {}".format(K_BALLS))
    print("running {:,} trials ...".format(NUM_TRIALS))

    total_tosses = 0

    for i in range(NUM_TRIALS):
        logging.debug("\n**** TRIAL {} ****".format(i+1))

        # initialize all bins to have zero balls
        bins = [0 for i in range(NUM_BINS)]

        tosses = 0

        # begin tossing...
        while True:

            # ball is up in the air...
            tosses += 1

            # randomly select bin
            rng = secrets.SystemRandom()
            random_bin = rng.randint(0, NUM_BINS-1)
            logging.debug("toss #{} --> goes into bin {}". \
                                  format( (tosses), (random_bin+1)))

            # add ball to random bin
            bins[random_bin] += 1

            logging.debug("\t  bins: {}".format(bins))

            if K_BALLS in bins:
                number_of_tosses_until_k_balls_in_bin = tosses 
                total_tosses += tosses 
                break

    print("----------------------------")
    print("total tosses until a bin has {} balls: {}". \
                        format(K_BALLS, total_tosses))

    print("average number of tosses until a bin has {} balls: {:.4f}". \
                        format( K_BALLS, (float(total_tosses) / float(NUM_TRIALS ))))
    
if __name__ == '__main__':
    main()

