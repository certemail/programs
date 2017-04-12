import sys
import time
import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("seconds", help="length of time")
    args = parser.parse_args()

    interval = int(args.seconds) 

    sys.stdout.write("Elapsed:")
    sys.stdout.flush()
    for i in range(1, interval+1):
        time.sleep(1)
        sys.stdout.write('\r\t  %d' % i)
        sys.stdout.flush()
    print("\n*** COMPLETE ***")
