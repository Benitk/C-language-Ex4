#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "ex.h"
#define NUM_LETTERS 26

typedef struct node{
	char letter;
	long unsigned int count;
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

		TrieNode->hasChildren = false;
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

	// new pointer to current
	node *p_curr = current;

	// char isn't letter
	if(*word < 65 || (*word > 90 && *word < 97) || *word > 122)
		insertWord(word+1,p_curr);

	// change Capital to lower
	*word = tolower(*word);
	// getting index
	int index = charToIndex(*word);

	if(strlen(word) == 1){
		// ignore bad chars in the word
		if(p_curr->children[index] == NULL){
			// malloc new memory
			p_curr->children[index] = newNode();
			// define paramters
			p_curr->children[index]->letter = *word;
			p_curr->children[index]->count++;
			p_curr->children[index]->endWord = true;
			p_curr->children[index]->hasChildren = false;
		}
		else{
			p_curr->children[index]->count++;
			p_curr->children[index]->endWord = true;
		}
	}
	// word length >= 2
	else{
		if(p_curr->children[index] == NULL){
			p_curr->children[index] = newNode();
			p_curr->children[index]->letter = *word;
			p_curr->children[index]->endWord = false;
			p_curr->children[index]->hasChildren = true;
			insertWord(word+1,p_curr->children[index]);
		}
		else{
			p_curr->children[index]->hasChildren = true;
			insertWord(word+1,p_curr->children[index]);
		}
	}
}

// Print all words in Trie
void printWordDefualt(node* current, char* wordArray, int index)
{
	if(current == NULL)
		return;

	if(current->endWord){

		// add space
		*(wordArray + index++) = '\t';
		// number of appearance
		*(wordArray + index++) = current->count + '0';
		// add finish of string
		*(wordArray + index++) = '\0';

		printf("%s\n", wordArray);

		wordArray = wordArray + index;
	}
	for(int i=0; i<NUM_LETTERS; i++){
		if(current->children[i] != NULL){
			wordArray[index] = current->children[i]->letter;
			printWordDefualt(current->children[i], wordArray, index+1);
		}
	}
}

void printWordReverse(node* current, char* wordArray, int index){
	if(current == NULL)
		return;

	if(current->endWord){

		// add space
		*(wordArray + index++) = '\t';
		// number of appearance
		*(wordArray + index++) = current->count + '0';
		// add finish of string
		*(wordArray + index++) = '\0';

		printf("%s\n", wordArray);

		wordArray = wordArray + index;
	}

	for(int i=(NUM_LETTERS-1); i>=0; i--){
		if(current->children[i] != NULL){
			wordArray[index] = current->children[i]->letter;
			printWordReverse(current->children[i], wordArray, index+1);
		}
	}
}

void printWords(char type, node *current, char *word){
	unsigned int word_index = 0;
	if(type == 'r'){
		printWordReverse(current, word, word_index);
	}
	else{
		printWordDefualt(current, word, word_index);
	}
}


void freeMemory(node** current){
	if(*current == NULL)
		return;

	if((*current)->hasChildren){
		for(int i=0; i<NUM_LETTERS; i++){
			if((*current)->children[i] != NULL)
				freeMemory(&((*current)->children[i]));
		}
	}
	free(*current);
	*current = NULL;
}


/*int main(){
	char word[6][4] = {"aaa","bbb","abc", "bac","abc"};
	node* root = newNode();

	for(int i =0 ; i < 6; i++){
		insertWord(word[i], root);
	}

	char words[256];
	printWords('o',root, words);
	freeMemory(&root);
	printf("free memory");

	return 0;
}*/


/*void swap(int a, int b){
	int temp = a;
	a = b;
	b = temp;
}*/

