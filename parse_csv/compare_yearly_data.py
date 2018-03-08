import csv, os, argparse

COL_A = 0
COL_B = 1

def compare_student_data(input_file):
    print("Parsing", str(input_file), "...")

    column_a = []
    column_b = []

    with open(input_file, 'r') as csvfile:
        rdr = csv.reader(csvfile, dialect='excel')

        # skip header (first row)
        next(rdr)

        for row in rdr:
            if row[COL_A] != '':
                column_a.append(row[0])
            if row[COL_B] != '':
                column_b.append(row[1])

    print("Number of UIDs in column_a: ", str(len(column_a)))
    print("Number of UIDs in column_b: ", str(len(column_b)))
    print("column_a: ", str(column_a)) 
    print("column_b: ", str(column_b)) 
    print()

    # convert to set to remove any duplicates within each column
    print("Removing any duplicates within each column...")
    column_a = set(column_a)
    column_b = set(column_b)
    print()

    uids_in_a_but_not_in_b = column_a - column_b 
    #print("UIDs in column A but NOT in column B: " +str(uids_in_a_but_not_in_b))
    print("UIDs in column A but NOT in column B: ")

    uids_in_col_a_sorted = sorted(list(uids_in_a_but_not_in_b))
    for i, uid in enumerate(uids_in_a_but_not_in_b):
        print(i+1,")",uid)

def main():
    parser = argparse.ArgumentParser(description="compare student data")
    parser.add_argument("input_csv", help="input CSV file containing student data")
    args = parser.parse_args()
    infile = args.input_csv

    if not os.path.exists(infile):
        print(infile + " does not exist. Exiting...")
        exit(1)
    
    compare_student_data(infile)

if __name__ == '__main__':
    main()
