#!/usr/bin/env python

import math

def merge(A, p, q, r):
    print("[merge] p, q, r: " + str(p) + ", " + str(q) + ", " + str(r))
    k = p
    i = 0
    j = 0

    low_half  = A[:q]
    high_half = A[q:]
    print("[merge] low_half: "+ str(low_half))
    print("[merge] high_half "+ str(high_half))

    while  i < len(low_half) and j < len(high_half):
        if low_half[i] < high_half[j]:
            A[k] = low_half[i]
            i += 1
        else:
            A[k] = high_half[j]
            j +=1

        k += 1

    # either low_half or high_half has been fully copied into A
    while i < len(low_half):
        A[k] = low_half[i]
        i += 1
        k += 1

    while j < len(high_half):
        A[k] = high_half[j]
        j += 1
        k += 1

def merge_sort(array, p, r):
    print("[merge_sort] arr: " + str(array))
    print("[merge_sort] p: " + str(p))
    print("[merge_sort] r: " + str(r))

    if ( p < r):
        q = math.floor( ( p + r ) / 2 )
        print("[merge_sort] q: " + str(q))

        merge_sort( array, p, q )   # left subarray
        merge_sort( array, q+1, r ) # right subarray

        merge( array, p, q, r )

arr = [3, 7, 12, 14, 2, 6, 9, 11]
print(arr)

#p = 0
#r = len(arr)
#q = math.floor((p+r)/2)
#merge(arr, p, q, r)

merge_sort( arr, 0, len(arr)-1 )
print("arr: " + str(arr))

