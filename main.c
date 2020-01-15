#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "frequency.h"
#define LINE 256

int main(int argc,char *argv[]){
	char line[LINE], c, type;
	if(argc > 1){
		type = *argv[1];
	}
	int line_length = 0, num_of_input = 0;

	char* p_line = line;

	// Initialize root of the trie
	node* root = NULL;
	root = newNode();
	if(!root){
		printf("Failed to allocate memory");
		exit(0);
	}



	// reading input - letter by letter searchin for end of line/tab or space
	// then insert that word to the trie
	while(1) {
		c = getchar();
		if (c == EOF) {
			break; }
		num_of_input++;
		//char isn't letter
		if(c < 65 || (c > 90 && c < 97) || c > 122){
			*(p_line + line_length++) = '\0';
			insertWord(p_line, root);
			p_line = p_line + line_length;
			line_length = 0;
		}
		else
			*(p_line + line_length++) = c;
	}
	// prints all word in the right type (default or reverse)
	char words[num_of_input];
	char *p = words;
	printWords(type, root, p);
	freeMemory(&root);

	return 0;
}
