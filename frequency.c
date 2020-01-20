#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "frequency.h"
#define NUM_LETTERS 26

//create new struct node that represent node in Trie
// parameter count - count number of words appearance
typedef struct node{
	char letter;
	unsigned long int count;
	struct node* children[NUM_LETTERS];
	bool endWord;
	bool hasChildren;
}node;


/**
 * new trie node
 * Initial memory allocation
 */
node* newNode(){

	node* TrieNode = NULL;

	TrieNode = (struct node*)malloc(sizeof(struct node));

	if(TrieNode){

		TrieNode->hasChildren = true;
		TrieNode->count = 0;

		for (int i = 0; i < NUM_LETTERS; i++)
			TrieNode->children[i] = NULL;
	}

	return TrieNode;
}

/**
 * convert char to index
 */
int charToIndex(const char letter){
	// change char to int
	int letter_int = (int)letter;
	//getting index
	return letter_int - 97;
}

/**
 * insert word recrusive
 */
void insertWord(char *word, node *current){
	// empty word
	if(strlen(word) == 0 || current == NULL)
		return;


	// change Capital to lower
	*word = tolower(*word);
	// getting index
	int index = charToIndex(*word);

	if(strlen(word) == 1){

		if(current->children[index] == NULL){
			// allocate new memory to node
			current->children[index] = newNode();
			// define parameters
			current->children[index]->letter = *word;
			current->children[index]->count++;
			current->children[index]->endWord = true;
			current->children[index]->hasChildren = false;
		}
		else{
			current->children[index]->count++;
			current->children[index]->endWord = true;
		}
	}
	// word length >= 2
	else{
		if(current->children[index] == NULL){
			current->children[index] = newNode();
			current->children[index]->letter = *word;
			current->children[index]->endWord = false;
			current->children[index]->hasChildren = true;
			insertWord(word+1,current->children[index]);
		}
		else{
			current->children[index]->hasChildren = true;
			insertWord(word+1,current->children[index]);
		}
	}

}
//print the words in Alphabet order with the number of appearance of each word
//Recursively

void printWordDefualt(node* current, char* wordArray, int index)
{
	if(current == NULL)
		return;

	if(current->endWord){

		// add finish of string
		*(wordArray + index++) = '\0';

		printf("%s\t", wordArray);

		// print number of appearance
		printf("%lu\n", current->count);

		wordArray = wordArray + index;
	}
	for(int i=0; i<NUM_LETTERS; i++){
		if(current->children[i] != NULL){
			wordArray[index] = current->children[i]->letter;
			printWordDefualt(current->children[i], wordArray, index+1);
		}
	}
}


//print the words in reverse Alphabet order with the number of appearance of each word
//Recursively

void printWordReverse(node* current, char* wordArray, int index){
	if(current == NULL)
		return;

	if(current->endWord){

		// add finish of string
		*(wordArray + index++) = '\0';

		printf("%s\t", wordArray);

		// print number of appearance
		printf("%lu\n", current->count);

		wordArray = wordArray + index;
	}

	for(int i=(NUM_LETTERS-1); i>=0; i--){
		if(current->children[i] != NULL){
			wordArray[index] = current->children[i]->letter;
			printWordReverse(current->children[i], wordArray, index+1);
		}
	}
}

/**
 * function that direct the arguments to the correct print (default or reverse)
 * by checking type
 */
void printWords(char type, node *current, char *word){
	unsigned int word_index = 0;
	if(type == 'r'){
		printWordReverse(current, word, word_index);
	}
	else{
		printWordDefualt(current, word, word_index);
	}

}



// free memory recursive
// childs first then parent
void freeMemory(node** current){
	if(*current == NULL)
		return;

	if((*current)->hasChildren){
		for(int i=0; i<NUM_LETTERS; i++){
			if((*current)->children[i] != NULL){
				freeMemory(&((*current)->children[i]));
				(*current)->children[i] = NULL;
			}
		}
	}
	free(*current);
	*current = NULL;
}
