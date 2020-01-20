#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "frequency.h"
#define INITIAL_CAPACITY 256
#define RESIZE 50


int main(int argc,char *argv[]){
	unsigned long int num_of_input = 0;
	unsigned long int capacity = INITIAL_CAPACITY;
	unsigned long int word_length = 0;

	char c, type;

	if(argc > 1){
		type = *argv[1];
	}

	// Initialize array
	char* temp_arr = NULL;
	char* arr = NULL;
	arr = malloc(capacity * sizeof(char));
	// Initialize root of the trie
	node* root = NULL;
	root = newNode();
	if(!root || !arr){
		printf("Failed to allocate memory");
		exit(1);
	}
	char* p_arr = arr;


	// reading input - letter by letter searching for end of line/tab or space
	// then insert that word to the trie
	while(1) {
		c = getchar();
		if (c == EOF) {
			break; }
		num_of_input++;

		//char isn't letter
		if(c < 65 || (c > 90 && c < 97) || c > 122){
			*(p_arr + word_length++) = '\0';
			insertWord(p_arr, root);
			p_arr = p_arr + word_length;
			word_length = 0;
		}
		else
			*(p_arr + word_length++) = c;

		//  realloc
		if(num_of_input == capacity){
			arr = realloc(arr, capacity + RESIZE);
			if(!arr){
				printf("Failed to allocate memory");
				exit(1);
			}
			p_arr = arr + (num_of_input-word_length);
			capacity+=RESIZE;
		}
	}
	free(arr);
	arr = NULL;
	// prints all word in the right type (default or reverse)
	char words[num_of_input];
	char *p = words;
	printWords(type, root, p);
	freeMemory(&root);

	return 0;
}
