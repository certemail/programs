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
    parser.add_argument("--log", help="log level")
    args = parser.parse_args()

    if args.log:
        numeric_level = getattr(logging, args.log.upper(), None)
        if not isinstance(numeric_level, int):
            raise ValueError('Invalid log level: %s' % loglevel)
        logging.basicConfig(filename='log.txt', \
                            filemode='w', \
                            level=numeric_level, \
                            format='%(levelname)s: %(message)s')

    NUM_BINS = int(args.num_bins)
    NUM_BALLS = int(args.num_balls) 
    NUM_TRIALS = int(args.num_trials)
    
    print("number bins:   {}".format(NUM_BINS))
    print("number balls:  {}".format(NUM_BALLS))
    print("running {:,} trials ...".format(NUM_TRIALS))

    total_bins_empty = 0

    for i in range(NUM_TRIALS):
        logging.debug("\n**** TRIAL {} ****".format(i+1))

        # initialize all bins to have zero balls
        bins = [0 for i in range(NUM_BINS)]

        # begin tossing...
        for tosses in range(NUM_BALLS):

            # randomly select bin
            rng = secrets.SystemRandom()
            random_bin = rng.randint(0, NUM_BINS-1)
            logging.debug("toss #{} --> goes into bin {}".format( (tosses+1), (random_bin+1)))

            # add ball to random bin
            bins[random_bin] += 1

            logging.debug("\t  bins: {}".format(bins))

        total_bins_empty += bins.count(0)
        logging.debug("-----------------------------")
        logging.debug("number of empty bins: {}".format(bins.count(0)))
    
    print("----------------------------------------")
    print("total empty bins: {}".format(total_bins_empty))
    print("average number of empty bins: {:.5f}".format( float(total_bins_empty) / float(NUM_TRIALS)))
    
if __name__ == '__main__':
    main()

