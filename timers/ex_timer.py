import sys
import time
import argparse

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("seconds", help="length of time for each rep")
    parser.add_argument("rest_time", help="time to rest")
    args = parser.parse_args()

    interval = int(args.seconds) 
    rest = int(args.rest_time)
    
    print("Starting...")
    time.sleep(7)
    print("\a\a")

    count = 1
    while True:
        for i in range(0, interval+1):
            sys.stdout.write('\r #{} Elapsed:  {}'.format(count, i))
            sys.stdout.flush()
            time.sleep(1)
        count += 1
        sys.stdout.write("\n*******DONE!**********\a\a\a\n")
        sys.stdout.flush()

        rest = int(args.rest_time)
        while rest > 0:
            time.sleep(1)
            sys.stdout.write("\a")
            sys.stdout.flush()
            rest -= 1
        time.sleep(1)

        #sys.stdout.write(chr(27) + "[2J")
        #sys.stdout.flush()

if __name__ == '__main__':
    main()
