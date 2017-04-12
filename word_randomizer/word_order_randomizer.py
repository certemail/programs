#!/usr/local/bin/python3

import csv, random, os, shutil, time, platform, argparse
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

num_word_appearances = ""
num_output_words = ""
num_solutions = ""
input_word_list = []
output_word_list = []
output_dir = "Solutions"
os_platform = ""
notification_email = ""

def initializeInputWordList(input_file):
    """read in words to be processed from csv file"""
    with open(input_file, 'r') as csvfile:
        rdr = csv.reader(csvfile, dialect='excel')
        for word in rdr:
            input_word_list.append(word[0])
	
def initializeOutputWordList():
    """initialize output list to None"""
    output_word_list[:] = []
    for i in range(0,num_output_words):
        output_word_list.append(None)

def getFirstPosition():
    """find first available empty index"""
    for i in range(0,num_output_words):
        if output_word_list[i] == None:
            return i
		
def getNextPosition(current_position):
    """find next open index 5-9 spaces away"""
    count = 0
    while True:
        next_pos = current_position + random.randint(5,9)
        count += 1
        if count == 15:
            return -1
        if next_pos > num_output_words-1:
            continue
        if (output_word_list[next_pos] == None):
            return next_pos
    return -1

def doWordAssigments():
    """assign words to available positions"""

    for word in input_word_list:
				
        # assign first available position
        curr_pos = getFirstPosition()
        output_word_list[curr_pos] = word
		
        for x in range(num_word_appearances - 1):
			
            # assign next open position
            next_pos = getNextPosition(curr_pos)
            if next_pos == -1:
                return False
            output_word_list[next_pos] = word
            curr_pos = next_pos	
	
    # successful config	
    return True

def writeSolutionToCSV(solution, number):
    """writes solution to disk"""
    fname = "Solution" + str(number) + ".csv"
    fname = os.path.join(output_dir, fname)

    # running on Windows
    if os_platform == 'Windows': 
        with open(fname, 'w', newline='') as csvfile:
            wtr = csv.writer(csvfile, dialect='excel')
            for word in solution:
                wtr.writerow([word])
    # running on non-Windows
    else:
        with open(fname, 'w') as csvfile:
            wtr = csv.writer(csvfile, dialect='excel')
            for word in solution:
                wtr.writerow([word])

def create_output_dir():
    """create directory for output solution csv files"""
    if not os.path.exists(output_dir):
        print("The path \"" + output_dir + "\" does not exist")
        print("Creating directory \"" + output_dir + "\"")
        os.makedirs(output_dir)
    else:
        print("\"" + output_dir + "\" directory already exists. Cleaning before use...")
        shutil.rmtree(output_dir)
        os.makedirs(output_dir)

def formatSeconds(seconds, show_days=False):
    """converts seconds into hh:mm:ss"""
    min, sec  = divmod(seconds, 60)
    hrs, min  = divmod(min, 60)
    days, hrs = divmod(hrs, 24)
    if show_days:
        return ("%02d:%02d:%02d:%02d" % (days, hrs, min, sec))
    else:
        return ("%02d:%02d:%02d" % (hrs, min, sec)) 

def sendEmailNotification(output_str, all_complete=False):
    try:
        if all_complete:
            subject = "Your Word Order Randomization Program is Finished!"
            body  = "Phew! Sorry I took so long, but your " + str(num_solutions) + \
                    " solutions are ready.\nHere are your are program stats:\n\n"
            body += output_str
        else:
            subject = "Your Word Order Randomization Program Update"
            body = output_str
	
            fromaddr = "wordgeneratorcomplete2@gmail.com"
            toaddr = notification_email
            msg = MIMEMultipart()
            msg['From'] = fromaddr
            msg['To'] = toaddr
            msg['Subject'] = subject
            
            msg.attach(MIMEText(body, 'plain'))
            server = smtplib.SMTP('smtp.gmail.com', 587)
            server.ehlo()
            server.starttls()
            server.ehlo()
            server.login("wordgeneratorcomplete2", "xxxxxxxxxxxx")
            text = msg.as_string()
            server.sendmail(fromaddr, toaddr, text)
            print("Sent notification to: " + toaddr)

    except Exception as ex:
        print(ex)
        print("Email notification failed. Might be a network problem...")
    finally:
        return
			
if __name__ == '__main__':
    # process command line argument for input csv file
    parser = argparse.ArgumentParser(
                description='Word Order Randomizer',  
                epilog='Example use: ' \
                        'prompt% python3 word_order_randomizer.py input_word_list.csv 4 30 someone@gmail.com'
            )
    parser.add_argument("input_file", help="List of words to be processed (must be in CSV format)")
    parser.add_argument("num_word_appearances", help="Total number of appearances per word in solution")
    parser.add_argument("number_solutions", help="Number of solutions to be processed")
    parser.add_argument("notify_email", help="Notification email address when complete")
    args = parser.parse_args()
    infile = args.input_file
    if not os.path.exists(infile):
        print(infile + " does not exist. Exiting...")
        exit(1)
    num_word_appearances = int(args.num_word_appearances)
    num_solutions = int(args.number_solutions)
    notification_email = args.notify_email

    # initialization tasks
    border = "*" * 60
    print(border)
    print("Program started: " + time.ctime())
    time_program_started = time.time()
    os_platform = platform.system()
    print("Detected operating system: " + os_platform)
    create_output_dir()
    print("Reading in data...")

    initializeInputWordList(infile)
    print("-- Number input words: ", str(len(input_word_list)))	
    print("-- Number of appearances: ", str(num_word_appearances))
    num_output_words = num_word_appearances * len(input_word_list)	 
    print("-- Total number output words: ", str(num_output_words))

    initializeOutputWordList()
            

    print("Initialization tasks complete.")
    print(border)
            
    all_failed_attempts = []
    all_solution_times  = []
    for i in range(1, num_solutions+1):
        print("Working on Solution" + str(i) + ". Please wait, this could take awhile...")
        random.shuffle(input_word_list)
        num_failed_attempts = 0
        time_solution_started = time.time()
		
        # keep attempting until success
        while True:
            check_success = doWordAssigments()
            if check_success:
                break
            else:
                initializeOutputWordList()
                num_failed_attempts += 1
				
        time_solution_ended = time.time()
        elapsed_time = time_solution_ended - time_solution_started
        all_solution_times.append(elapsed_time)
        all_failed_attempts.append(num_failed_attempts)
        
        print("SUCCESS!!\a\a\a")
        print("Number of failed attempts: " + str(num_failed_attempts))
        print("Elapsed time (hh:mm:ss): " + formatSeconds(elapsed_time))
        print("Writing Solution" + str(i) + " to disk...")
        sendEmailNotification("Finished Solution" + str(i) )
        writeSolutionToCSV(output_word_list, i)
        print("Reinitializing...")
        print("-" * 60)
        initializeOutputWordList()
	
    # calculate program statistics
    time_program_ended      = time.time()
    elapsed_total_time 	    = time_program_ended - time_program_started
    average_solution_time   = sum(all_solution_times) /  len(all_solution_times)
    average_failed_attempts = sum(all_failed_attempts) / len(all_failed_attempts)
    
    output_str  = "Program completed: " + time.ctime() + "\n"
    output_str += "Program running time (dd:hh:mm:ss): " + formatSeconds(elapsed_total_time, show_days=True) + "\n"
    output_str += "Average time per solution (hh:mm:ss):  " + formatSeconds(average_solution_time) + "\n"
    output_str += "Average number failed attempts per solution: " + str(round(average_failed_attempts)) + "\n"
    
    print(border)
    print(output_str)
    sendEmailNotification(output_str, all_complete=True)
    print(border)
