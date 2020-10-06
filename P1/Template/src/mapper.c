#include "mapper.h"


//	User-defined variables
	char listVal = '1';	//constant value of "1" to add to 2 level linked list
	// Had to put '1' in SINGLE QUOTE to work
	char *listValpt = &listVal;
	struct intermediateDS* LinkedListRoot = NULL;


// combined value list corresponding to a word <1,1,1,1....>
valueList *createNewValueListNode(char *value){
	valueList *newNode = (valueList *)malloc (sizeof(valueList));
	strcpy(newNode -> value, value);
	newNode -> next = NULL;
	return newNode;
}

// insert new count to value list
valueList *insertNewValueToList(valueList *root, char *count){
	valueList *tempNode = root;
	if(root == NULL)
		return createNewValueListNode(count);
	while(tempNode -> next != NULL)
		tempNode = tempNode -> next;
	tempNode -> next = createNewValueListNode(count);
	return root;
}

// free value list
void freeValueList(valueList *root) {
	if(root == NULL) return;

	valueList *tempNode = root -> next;;
	while (tempNode != NULL){
		free(root);
		root = tempNode;
		tempNode = tempNode -> next;
	}
}

// create <word, value list>
intermediateDS *createNewInterDSNode(char *word, char *count){
	intermediateDS *newNode = (intermediateDS *)malloc (sizeof(intermediateDS));
	strcpy(newNode -> key, word);
	newNode -> value = NULL;
	newNode -> value = insertNewValueToList(newNode -> value, count);
	newNode -> next = NULL;
	return newNode;
}

// insert or update a <word, value> to intermediate DS
intermediateDS *insertPairToInterDS(intermediateDS *root, char *word, char *count){
	intermediateDS *tempNode = root;
	if(root == NULL)
		return createNewInterDSNode(word, count);
	//traversing down the 1st level of list
	while(tempNode -> next != NULL) {
		if(strcmp(tempNode -> key, word) == 0){
			tempNode -> value = insertNewValueToList(tempNode -> value, count);
			return root;
		}
		tempNode = tempNode -> next;

	}
	//have reached last case without a match
	if(strcmp(tempNode -> key, word) == 0){
		tempNode -> value = insertNewValueToList(tempNode -> value, count);
	} else {
		tempNode -> next = createNewInterDSNode(word, count);
	}
	return root;
}

// free the DS after usage. Call this once you are done with the writing of DS into file
void freeInterDS(intermediateDS *root) {
	if(root == NULL) return;

	intermediateDS *tempNode = root -> next;
	while (tempNode != NULL){
		freeValueList(root -> value);
		free(root);
		root = tempNode;
		tempNode = tempNode -> next;
	}
}

// emit the <key, value> into intermediate DS
// so, write into the imtermediate DS?
void emit(char *key, char *value) {	//key is word, value is "1"
	LinkedListRoot = insertPairToInterDS(LinkedListRoot, key, value);
}

// map function
void map(char *chunkData){
	int count = 0;	//debug var to print number of words in chunkData
	int i = 0;


	char *buffer;
	//Issue: chunkData is not parsing in last word (at EOF)
	while((buffer = getWord(chunkData, &i)) != NULL)
	{
		//write the word to the intermediateDS
		//the word should propagate into the 2-level linked list with the help of the helper functions
		emit(buffer, listValpt);
		count++;
	}



	//printf("\n ID: %s \t Word Count %d \n", chunkData, count); //Debug statement
	// you can use getWord to retrieve words from the
	// chunkData one by one. Example usage in utils.h
}

// write intermediate data to separate word.txt files
// Each file will have only one line : word 1 1 1 1 1 ...
void writeIntermediateDS(void) {
	//Outerloop: loop through the keys in the intermediateDS, for each key, start a new file if it does not already exist, and start writing to it
	//Inner loop: loop through the intermediateDS->valueList and output the value stored in the inner linked list to the opened file
	//Only Outerloop: call the free functions to free interDS and all its valueLists
	//After the 2-level linked list has been exhausted, all elements/nodes should have been freed
	intermediateDS *temp = LinkedListRoot;
	valueList *tempValNode = temp->value;


	while(temp != NULL)
	{
		FILE *newtxt;
		char fNameStr[100]; //temporate string/char array to store file name
		strcpy(fNameStr, mapOutDir);
		strncat(fNameStr, "/", 2);
		strncat(fNameStr, temp->key, 100);
		strncat(fNameStr, ".txt", 7);	//concatenate the .txt suffix
		//If appropriate .txt file exist, write to it; else make a new one
		newtxt = fopen(fNameStr,"a+");
		if(newtxt == NULL)
		{
			fprintf(stderr, "mapper.c, file open error, errno value: %d\n", errno);
			exit(1);
		}
		fprintf(newtxt,"%s ", temp->key);
		while(tempValNode != NULL)
		{
				//print in succession the 1's from valueList
				fprintf(newtxt, "%c ", *tempValNode->value);
				tempValNode = tempValNode->next;
		}
		fclose(newtxt);
		temp = temp->next;
		tempValNode = temp->value;
	}
	freeInterDS(LinkedListRoot);
	free(tempValNode);
	free(temp);
}

int main(int argc, char *argv[]) {

	if (argc < 2) {
		printf("Less number of arguments.\n");
		printf("./mapper mapperID\n");
		exit(0);
	}
	// ###### DO NOT REMOVE ######
	mapperID = strtol(argv[1], NULL, 10);

	// ###### DO NOT REMOVE ######
	// create folder specifically for this mapper in output/MapOut
	// mapOutDir has the path to the folder where the outputs of
	// this mapper should be stored
	mapOutDir = createMapDir(mapperID);
	//Debug: show that that mapOutDir stores the necessary file path to the output folder Map_mapperID
	//printf("mapOutDir %s \n", mapOutDir);

	// ###### DO NOT REMOVE ######
	while(1) {
		// create an array of chunkSize=1024B and intialize all
		// elements with '\0'
		char chunkData[chunkSize + 1]; // +1 for '\0'
		memset(chunkData, '\0', chunkSize + 1);

		char *retChunk = getChunkData(mapperID);
		if(retChunk == NULL) {

			// 	Debug loop to print out the keys of the 1st level linked list
			//	Used here to see what the final linked list, 1st level looks like
			//intermediateDS *temp = LinkedListRoot;
			// while(temp != NULL)
			// {
			// 	printf("Node keys: %s \n", temp->key);
			// 	temp = temp->next;
			// }

			//Debug loop to step into a valueList of an intermediateDS node
			// temp = LinkedListRoot;
			// valueList *tempValNode = temp->value;
			// while(tempValNode != NULL)
			// {
			// 	printf("First node list value: %c \n", *tempValNode->value);
			// 	tempValNode = tempValNode->next;
			// }
			break;
		}

		strcpy(chunkData, retChunk);
		free(retChunk);

		//map is called as many times as there are chunks of data
		map(chunkData);
	}

	// ###### DO NOT REMOVE ######
	writeIntermediateDS();

	return 0;
}
