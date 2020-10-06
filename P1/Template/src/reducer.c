#include "reducer.h"

//	User-defined variables
finalKeyValueDS *ReduceListRoot = NULL;


// create a key value node
finalKeyValueDS *createFinalKeyValueNode(char *word, int count){
	finalKeyValueDS *newNode = (finalKeyValueDS *)malloc (sizeof(finalKeyValueDS));
	strcpy(newNode -> key, word);
	newNode -> value = count;
	newNode -> next = NULL;
	return newNode;
}

// insert or update an key value
finalKeyValueDS *insertNewKeyValue(finalKeyValueDS *root, char *word, int count){
	finalKeyValueDS *tempNode = root;
	if(root == NULL)
		return createFinalKeyValueNode(word, count);
	while(tempNode -> next != NULL){
		if(strcmp(tempNode -> key, word) == 0){
			tempNode -> value += count;
			return root;
		}
		tempNode = tempNode -> next;
	}
	if(strcmp(tempNode -> key, word) == 0){
		tempNode -> value += count;
	} else{
		tempNode -> next = createFinalKeyValueNode(word, count);
	}
	return root;
}

// free the DS after usage. Call this once you are done with the writing of DS into file
void freeFinalDS(finalKeyValueDS *root) {
	if(root == NULL) return;

	finalKeyValueDS *tempNode = root -> next;;
	while (tempNode != NULL){
		free(root);
		root = tempNode;
		tempNode = tempNode -> next;
	}
}

int totalCount;
// reduce function
//	Write to an intermediate data structure, a linked list
void reduce(char *key) {
    int count = 0;
    char ch;
		char firstWord[MAXKEYSZ];
    FILE *fd = fopen(key,"r");

    if(fd == NULL){
        printf("File is not found: %s",key);
				exit(1);
    }
		else {
				fscanf(fd,"%s", firstWord);	//get the first word in .txt files
				//firstWord = word in .txt file
        while((ch = fgetc(fd)) != EOF)
        {
            if(ch =='1'){
                count++;
                totalCount++;
            }
        }
				//	Add .txt file info into linked list (word, count) pairs
				ReduceListRoot = insertNewKeyValue(ReduceListRoot, firstWord, count);
    //printf("\nKey: %s First word: %s Count: %d \n", key, firstWord, count);
    }
}

// write the contents of the final intermediate structure
// to output/ReduceOut/Reduce_reducerID.txt
//	so, make a new file at the output/ReduceOut/ location
void writeFinalDS(int reducerID){
	char pathFile[100];	//string to store file path
	FILE *reduce_txt; // fd points to file output
	finalKeyValueDS *temp = ReduceListRoot;
	sprintf(pathFile, "output/ReduceOut/Reduce_%d.txt", reducerID);
	reduce_txt = fopen(pathFile,"w+");	//create a new/truncated text file to write to
	//printf("%s \n", pathFile);
	if(reduce_txt == NULL)
	{
		fprintf(stderr, "reduce.c, output file open error, errno value: %d\n", errno);
		exit(1);
	}
	while(temp != NULL)
	{
		fprintf(reduce_txt,"%s %d \n", temp->key, temp->value);
		temp = temp->next;
	}
	fclose(reduce_txt);
	//free linked list after all information has been extracted
	freeFinalDS(ReduceListRoot);
	free(temp);
}

int main(int argc, char *argv[]) {

	if(argc < 2){
		printf("Less number of arguments.\n");
		printf("./reducer reducerID");
	}

	// ###### DO NOT REMOVE ######
	// initialize
	int reducerID = strtol(argv[1], NULL, 10);


	// ###### DO NOT REMOVE ######
	// master will continuously send the word.txt files
	// alloted to the reducer
	char key[MAXKEYSZ];
	while(getInterData(key, reducerID))
		reduce(key);


		//	Debug code to test access to the linked list
		// finalKeyValueDS *temp = ReduceListRoot;
		// while(temp != NULL)
		// {
		// 	if(strcmp(temp->key,"the") == 0)
		// 	{
		// 		printf("%s \n", temp->key);
		// 		printf("%d \n", temp->value);
		// 	}
		// 	temp = temp->next;
		// }

	// You may write this logic. You can somehow store the
	// <key, value> count and write to Reduce_reducerID.txt file
	// So you may delete this function and add your logic
	writeFinalDS(reducerID);

	return 0;
}
