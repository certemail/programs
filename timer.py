import sys
import time
import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("seconds", help="length of time")
    args = parser.parse_args()

    interval = int(args.seconds) 

    for i in range(0, interval+1):
        sys.stdout.write('\rElapsed:  %d' % i)
        sys.stdout.flush()
        time.sleep(1)
    print("\n*** COMPLETE ***")
