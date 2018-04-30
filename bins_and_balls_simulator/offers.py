#!/usr/bin/env python
import argparse
import random
import logging
import secrets 
import sys
import math

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

    first_quarter = math.ceil(NUM_OFFERS / 4)
    logging.debug("1/4: {}".format(first_quarter))


    wins = 0
    losses = 0

    for i in range(NUM_TRIALS):
        best_offer_chosen = 0

        logging.debug("\n**** TRIAL {} ****".format(i+1))

        # initialize random dollar amount of each offer (sample without replacement)
        offers = random.sample(range(1, NUM_OFFERS+1), NUM_OFFERS) 
        logging.debug(offers)

        # get the max of the first 1/4 of offers
        logging.debug(offers[:first_quarter])

        max_first_quarter = max(offers[:first_quarter])
        logging.debug("max amount in 1/4 offers: {}".format(max_first_quarter))

        # loop thru and stop after the first offer higher than the max in the first 1/4
        
        for i in range(first_quarter, NUM_OFFERS):
            logging.debug(offers[i])
            if offers[i] > max_first_quarter:
                best_offer_chosen = offers[i]
                logging.debug("FIRST HIGHEST PAST {} is {}".format(max_first_quarter, best_offer_chosen))
                break
            
        if best_offer_chosen == max(offers):
            logging.debug("FOUND HIGHEST")
            wins += 1
        else:
            logging.debug("LOSE! highest offer is: {}".format(max(offers)))
            losses += 1


    print("--------------------")
    print("average: {:.3f}".format(wins / losses))
if __name__ == '__main__':
    main()

    ## randomly select bin
    #rng = secrets.SystemRandom()
    ##random_dollar_amount = rng.randint(0, NUM_OFFERS-1)
    #random_dollar_amount = rng.randint(0, NUM_OFFERS-1)
