#!/usr/bin/env python

def insertion_sort(array):
    for j in range(1, len(array)):
        key = array[j] 
        print("key: " + str(key))

        # insert A[j] into sorted sequence A[1..j-1]
        i = j-1
        while ( (i >= 0) and (array[i] > key) ):
            array[i+1] = array[i]
            i = i - 1
        array[i + 1] = key


array = [3,5,7,11,13,2,9,6]
print("array BEFORE: " + str(array))
insertion_sort(array)
print("array AFTER: " + str(array))
