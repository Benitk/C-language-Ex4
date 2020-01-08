#include <stdio.h>
#include <string.h>
#include "ex.h"

#define LINE 256

int main(int argc,char argv[]){
	char type = argv[1];
	char line[LINE];
	int line_length = 0, num_of_input = 0;
	char* p_line = line;
	char c;
	// init root
	node* root = newNode();

/*	if(!(root)){
		printf("faild to malloc");
		return 0;
	}*/

	while(1) {
		c = getchar();       // Get one character from the input
		if (c == EOF) {
			break; }
		num_of_input++;
		if(c == '\n' || c == '\t' || c == ' '){
			*(p_line + line_length++) = '\0';
			insertWord(p_line, root);
			p_line = p_line + line_length;
			line_length = 0;
		}
		// fill the array
		else
			*(p_line + line_length++) = c;
	}
	char words[num_of_input];
	printWords(type, root, words);
	freeMemory(&root);
	printf("free memory");

	return 0;
}
