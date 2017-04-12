#!/usr/bin/python3.4

import os
import shutil
import argparse

if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("executable_filename", help="binary file to be modified")
    parser.add_argument("start_offset", help="starting file offset as hex (e.g. 05ee)")
    parser.add_argument("end_offset", help="end of file offset as hex (e.g., 05ff)")
    args = parser.parse_args()

    exe_file = args.executable_filename
    if not os.path.exists(exe_file):
        print(f + "does not exist...exiting")
        exit(1)

    encrypted_filename = exe_file + "_encrypted"

    # delete encrypted file if already exists
    if os.path.exists(encrypted_filename):
        print("deleting: ", encrypted_filename)
        os.remove(encrypted_filename)

    # copy and rename new file with encrypted_filename
    shutil.copy(exe_file, encrypted_filename) 


    # decode file offset hex strings as integers
    s_offset = int.from_bytes(bytes.fromhex(args.start_offset), byteorder='big')
    e_offset = int.from_bytes(bytes.fromhex(args.end_offset), byteorder='big')
    num_bytes_to_change = e_offset - s_offset

    print("file offset start: ", hex(s_offset))
    print("file offset end:   ", hex(e_offset))
    print("number of bytes to overwrite: ", num_bytes_to_change)
    print()
	
    with open(encrypted_filename, 'rb+') as f:

        # seek to offset in file
        print("seeking to start position...")
        f.seek(s_offset)

        print("file pointer at: " + str(hex(f.tell())))

        # get bytes to be encrypted
        b_arr = bytearray(f.read(num_bytes_to_change))
        
        print("-----------")
        print("bytes to be encrypted: ")
        print(b_arr)
        print("-----------")

        xor_key = 0xCC
        for i in range(len(b_arr)):
            b_arr[i] ^= xor_key

        print("bytes after encryption:")
        print(b_arr) 
        print("-----------")
        print("file pointer at: " + str(hex(f.tell())))

        # reset file pointer
        print("reseting file back to start: ", str(hex(s_offset)))
        f.seek(s_offset)

        print()
        print("writing encrypted bytes back to disk...") 
        f.write(b_arr)
        f.flush()




