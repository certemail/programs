#!/usr/bin/env python

import argparse
import os
import glob
import fileinput

WARNING_MSG='*****************************************\n \
WARNING! THIS WILL MODIFY FILES IN PLACE!\n \
PROCEED WITH CAUTION...\n \
*****************************************'

def number_by_file_extension(root_dir, file_ext):
    for filename in glob.iglob(root_dir + '/**/*' + file_ext, recursive=True):
        print("adding line numbers to: ", filename)

        with fileinput.input(inplace=True, files=(filename)) as f:
            for i, line in enumerate(f):
                print(str(i+1) + " " + line.rstrip())

def main():
    parser = argparse.ArgumentParser(description=WARNING_MSG)
    parser.add_argument("base_dir", help="root directory of source files to add linenumbers")
    parser.add_argument("file_ext", help="file extension of files to modify e.g., .c, .java, etc")
    args = parser.parse_args()

    base_dir = args.base_dir
    file_ext = args.file_ext

    print(WARNING_MSG)
    answer = input("Adding line numbers to all {} files in {} Continue? [y|n]: " \
                                                                .format(file_ext, base_dir))
    if answer.lower() != 'y':
        print("Exiting...")
        exit(1)

    print()
    number_by_file_extension(base_dir, file_ext)

if __name__ == '__main__':
    main()
