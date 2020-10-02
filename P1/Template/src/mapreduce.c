#include "mapreduce.h"

int main(int argc, char *argv[]) {
	
	if(argc < 4) {
		printf("Less number of arguments.\n");
		printf("./mapreduce #mappers #reducers inputFile\n");
		exit(0);
	}

	// ###### DO NOT REMOVE ######
	int nMappers 	= strtol(argv[1], NULL, 10);
	int nReducers 	= strtol(argv[2], NULL, 10);
	char *inputFile = argv[3];

	// ###### DO NOT REMOVE ######
	bookeepingCode();

	// ###### DO NOT REMOVE ######
	pid_t pid = fork();
	if(pid == 0){
		//send chunks of data to the mappers in RR fashion
		sendChunkData(inputFile, nMappers);
		exit(0);
	}
	sleep(1);


	// To do
	// spawn mappers processes and run 'mapper' executable using exec
	
	// To do
	// wait for all children to complete execution
    

	// ###### DO NOT REMOVE ######
    // shuffle sends the word.txt files generated by mapper 
    // to reducer based on a hash function
	pid = fork();
	if(pid == 0){
		shuffle(nMappers, nReducers);
		exit(0);
	}
	sleep(1);


	// To do
	// spawn reducer processes and run 'reducer' executable using exec

	// To do
	// wait for all children to complete execution

	return 0;
}