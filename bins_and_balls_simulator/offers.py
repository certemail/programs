#!/usr/bin/env python
import argparse
import random
import logging
import secrets 
import sys

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("num_offers", help="number of offers")
    parser.add_argument("num_trials", help="number of trials")
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

    NUM_OFFERS = int(args.num_offers)
    NUM_TRIALS = int(args.num_trials)
    
    print("number offers:   {}".format(NUM_OFFERS))
    print("running {:,} trials ...".format(NUM_TRIALS))

    for i in range(NUM_TRIALS):
        logging.debug("\n**** TRIAL {} ****".format(i+1))

        # sample without replacement
        offers = random.sample(range(1, NUM_OFFERS+1), NUM_OFFERS) 
        print(offers)

        for i in range(NUM_OFFERS):

            j = i 
            ## randomly select bin
            #rng = secrets.SystemRandom()
            ##random_dollar_amount = rng.randint(0, NUM_OFFERS-1)
            #random_dollar_amount = rng.randint(0, NUM_OFFERS-1)

            ## add ball to random bin
            #offers[i] = random_dollar_amount

        #print("-----------------------------")
        #print("\t  offer: {}".format(offers))
    
    
if __name__ == '__main__':
    main()

