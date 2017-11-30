#!/usr/bin/env python

def swap(array, first_index, second_index):
    temp = array[first_index]
    array[first_index] = array[second_index]
    array[second_index] = temp

def index_of_minimum(array, start_index):
    print("getting index of minimum, starting at index: " + str(start_index))
    min_index = start_index;

    for curr_index in range(min_index+1, len(array)):
        print("comparison #" + str(curr_index) + ": " + str(array[curr_index]) + ":" + str(array[min_index]))
        if array[curr_index] < array[min_index]:
            min_index = curr_index;
    return min_index;

def selection_sort(array):
    for i in range(len(array)):
        idx_min = index_of_minimum(array, i)
        swap(array, i, idx_min)

array = [18, 6, 66, 44, 9, 22, 14];
print("ARRAY:" + str(array))
print("-----unsorted--------")

selection_sort(array)
print("-----sorted--------")
print("ARRAY:" + str(array))



