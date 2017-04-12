#!/bin/bash

NUM_WORDS=$1

if [[ $# != 1 ]]; then
    echo Usage: $0 "<num_dummy_words>"
    exit 1
fi

for ((i=1; i<=${NUM_WORDS}; i++)); do
    echo "Word${i}" >> dummy_words_${NUM_WORDS}.csv
done
