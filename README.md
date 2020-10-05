CSCI4061 Fall 2020
Project 1 - Group 41
Group members:
  Minh Bui    bui00011
  John Kimlinger
  Andrew Trudeau

Project details as mentioned in Section Deliverables.

• The purpose of your program:
  The goal of the project is to implement a simple mapreduce operation on a text file. The mapreduce program could process an input text file to output information on the different words in the file and how many occurrences each of those words have.  

• How to compile the program
  First, we would have to go the Template folder of the project, using something like: $ cd [project_folder_path]/Template
  Then, we run the makefile to handle the necessary compilations: $ make
  This will produce all the executables needed for running the program.
  To run the program, we simply call on the master phase executable using the format:
  $ ./mapreduce #mappers #reducers inputFile
    The number of mappers should be greater than or equal to the number of reducers
    The inputFile argument should be the path of the input file relative to the makefile location (by default the makefile should be in the project Template folder)

• What exactly your program does
  There are four phases of the program: mapreduce(or master phase), map phase, shuffle phase, and reduce phase. Overall, the program takes in an input text file and outputs the number of occurrences of each word in the file. The text file would first be divided into chunks of data for processing in the map phase. The map phase parses the chunks of data and stores the different (case sensitive) words in a 2-level linked list, keeping check of both the words and their number of occurrences. This information is then written to intermediary .txt files for each words, an act whose completion comes with the freeing of the 2-level linked list in memory. The shuffle phase will partition these .txt files between different reducers. The reducer phase will read the files and compute the number of occurrences for each word.   

• Any assumptions outside this document

• Contribution by each member of the team
  Minh Bui: completed most of the mapper.c implementation and the handling of mapper processes in mapreduce 
