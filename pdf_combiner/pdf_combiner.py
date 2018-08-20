#!/usr/bin/env python

# Automate the Boring Stuff, Al Sweigart

import os
import PyPDF2

OUTPUT_PDF = 'OUTPUT.pdf'

def main():
    # remove previous output
    if os.path.exists(OUTPUT_PDF):
        print("Deleting {}".format(OUTPUT_PDF))
        os.remove(OUTPUT_PDF)

    pdffiles = []
    for filename in os.listdir('.'):
        if filename.endswith('.pdf'):
            pdffiles.append(filename)

    if len(pdffiles) == 0:
        print("No PDF files in current directory")
        exit(1)

    pdffiles.sort(key = str.lower)
    
    pdfWriter = PyPDF2.PdfFileWriter()

    # loop through all pdf files
    for filename in pdffiles:
        print("processing: {}".format(filename))
        pdfFileObj = open(filename, 'rb')
        pdfReader = PyPDF2.PdfFileReader(pdfFileObj)

        # loop thru all pages (except first) and add them
        for pageNum in range(0, pdfReader.numPages):
            pageObj = pdfReader.getPage(pageNum)
            pdfWriter.addPage(pageObj)

    # save resulting PDF to a file
    pdfOutput = open(OUTPUT_PDF, 'wb')
    pdfWriter.write(pdfOutput)
    pdfOutput.close()
    

if __name__ == '__main__':
    main()
