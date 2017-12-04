#!/usr/bin/env python

import sys
import math

SENTINEL = math.inf

def merge(A, p, q, r):
    sys.stdout.write("[merge]: entering merge()...\n")
    sys.stdout.flush()
    sys.stdout.write("[merge]: p, q, r --> " + str(p) + ", " + str(q) + ", " + str(r) + "\n")
    sys.stdout.flush()

    low_half = []
    low_half.extend( A[p : q+1] )

    high_half = []
    high_half.extend(A[q+1 : r+1 ] )

    sys.stdout.write("[merge]: low_half  --> " + str(low_half) + "\n")
    sys.stdout.flush()
    sys.stdout.write("[merge]: high_half --> " + str(high_half) + "\n")
    sys.stdout.flush()

    # add sentinel value (infinity)
    low_half.append(SENTINEL)
    high_half.append(SENTINEL)

    i = 0
    j = 0

    for k in range(p, r+1):
        if low_half[i] <= high_half[j]:
            A[k] = low_half[i]
            i += 1
        else:
            A[k] = high_half[j]
            j += 1

    sys.stdout.write("[merge]: complete -->  " + str(A) + "\n")
    sys.stdout.flush()


def merge_sort(array, p, r):
    sys.stdout.write("[merge_sort]: entering merge_sort()...\n")
    sys.stdout.flush()
    sys.stdout.write("[merge_sort]: arr --> " + str(array) + "\n")
    sys.stdout.flush()
    sys.stdout.write("[merge_sort]: p --> " + str(p) + "\n")
    sys.stdout.flush()
    sys.stdout.write("[merge_sort]: r --> " + str(r) + "\n")
    sys.stdout.flush()

    if ( p < r):
        q = math.floor( ( p + r ) / 2 )
        sys.stdout.write("[merge_sort]: q --> " + str(q) + "\n")
        sys.stdout.flush()

        merge_sort( array, p, q )   # left subarray
        merge_sort( array, q+1, r ) # right subarray

        merge( array, p, q, r )

arr = [3, 7, 12, 14, 2, 6, 9, 11]
print(arr)
print("---------------------")

merge_sort( arr, 0, len(arr)-1 )
print("---------------------")
print(arr)

#p = 0
#r = len(arr)-1
#q = math.floor((p+r)/2)
#merge(arr, p, q, r)


