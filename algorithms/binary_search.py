#!/usr/bin/env python

def binary_search(arr, target_value):
    print("searching for target value: ", str(target_value)) 

    min = 0
    max = len(arr) - 1

    i = 1
    while (max >= min):
        guess = (min + max) // 2

        print("guess: " + str(i) + ": " +  str(guess))
        i += 1

        if (arr[guess] == target_value):
            return guess

        elif (arr[guess] < target_value):
            min = guess + 1

        else:
            max = guess - 1

    return -1


arr = [2,3,5,7,11,17,19,23,29,59,67,73,83,97]
print("array: " + str(arr))
print("length of array: " + str(len(arr)))

result = binary_search(arr, 102)
print("\nfound result at index: ", str(result))
