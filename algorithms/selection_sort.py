#!/usr/bin/env python

def index_of_minimum(array, start_index):
    print("getting index of minimum, starting at index: " + str(start_index))
    min_value = array[start_index];
    min_index = start_index;

    curr_index = min_index + 1;

    for i in range(curr_index, len(array)):
        print("comparing: " + str(array[i]) + ":" + str(array[min_index]))
        if array[i] < array[min_index]:
            min_index = i;
            min_value = array[min_index]
    return min_index;

array = [18, 6, 66, 44, 9, 22, 14];
print("ARRAY:" + str(array))

index = index_of_minimum(array, 2);

print("the index of the minimum value of the subarray starting at index 2 is: " + str(index))

