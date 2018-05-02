#!/usr/bin/env python

import argparse
import random
import logging
import secrets 
import sys
import math

prog_description= \
"""
Variation of the monty hall problem. You receive n offers for some job. 
The offers arrived in your mailbox in random order must decide right away 
to accept the offer or move on to the next one. once you accept an offer, 
you are committed and cannot accept offers from those you have not yet opened. 
Implements algorithm to open the first 1/n offers, record the max, and then 
pick the first one that is greater than the max in the first 1/n.
"""

def main():
    parser = argparse.ArgumentParser(description=prog_description)
    parser.add_argument("num_offers", help="number of offers")
    parser.add_argument("fraction_to_open", help="fraction of offers to open (e.g., .25)")
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
    FRACTION_TO_OPEN = float(args.fraction_to_open)
    
    print("total number of offers:   {}".format(NUM_OFFERS))
    print("fraction to open first:   {}".format(FRACTION_TO_OPEN))
    print("running {:,} trials...".format(NUM_TRIALS))
    print("--------------------------------")

    #fraction_to_open = .25
    offers_opened = math.ceil(NUM_OFFERS * FRACTION_TO_OPEN)
    logging.debug("{} of {} offers: {} will be opened".format(FRACTION_TO_OPEN, NUM_OFFERS, offers_opened))


    wins = 0
    losses = 0

    for i in range(NUM_TRIALS):
        if i % (NUM_TRIALS / 10) == 0:
            sys.stdout.write("\r{:,} of {:,} completed".format(i, NUM_TRIALS))
            sys.stdout.flush()
        best_offer_chosen = 0

        logging.debug("\n**** TRIAL {} ****".format(i+1))

        # initialize random dollar amount of each offer (sample without replacement)
        rng = secrets.SystemRandom()
        offers = rng.sample(range(1, NUM_OFFERS+1), NUM_OFFERS)
        logging.debug("OFFERS: {}".format(offers))

        # get the max of the first 1/x of offers
        logging.debug(offers[:offers_opened])

        max_offers_opened = max(offers[:offers_opened])
        logging.debug("max amount in opened offers: {}".format(max_offers_opened))

        # loop thru and stop after the first offer higher than the max in the first 1/4
        
        for i in range(offers_opened, NUM_OFFERS):
            logging.debug(offers[i])
            if offers[i] > max_offers_opened:
                best_offer_chosen = offers[i]
                logging.debug("FIRST HIGHEST PAST {} is {}".format(max_offers_opened, best_offer_chosen))
                break
            
        if best_offer_chosen == max(offers):
            logging.debug("FOUND HIGHEST")
            wins += 1
        else:
            logging.debug("LOSE! highest offer is: {}".format(max(offers)))
            losses += 1

    sys.stdout.write("\r{:,} of {:,} completed".format(NUM_TRIALS, NUM_TRIALS))
    sys.stdout.flush()


    print()
    print("--------------------------------")
    print("total wins:   {}".format(wins))
    print("total losses: {}".format(losses))
    print("average: {:.4f}".format(wins / NUM_TRIALS))
if __name__ == '__main__':
    main()

