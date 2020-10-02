#ifndef REDUCER_H
#define REDUCER_H

#include "utils.h"

#define MAXKEYSZ 50

// ###### DO NOT REMOVE ######
typedef struct finalKeyValueDS {
	char key[MAXKEYSZ];
	int value;
	struct finalKeyValueDS *next;
} finalKeyValueDS;

// ###### DO NOT REMOVE ######
finalKeyValueDS *createFinalKeyValueNode(char *value, int count);
finalKeyValueDS *insertNewKeyValue(finalKeyValueDS *root, char *word, int count);
void freeFinalDS(finalKeyValueDS *root);

// ###### DO NOT REMOVE ######
void writeFinalDS(int reducerID);
void reduce(char *key);

#endif