#include <stdio.h>
#include <stdlib.h>
#include "ex.h"

#define LINE 256

int main(int argc,char *argv[]){
	char line[LINE], c, type;
	if(argc > 1){
		type = *argv[1];
	}
	int line_length = 0, num_of_input = 0;
	char* p_line = line;
	// init root
	node* root = NULL;
	root = newNode();

	while(1) {
		c = getchar();
		if (c == EOF) {
			break; }
		num_of_input++;
		if(c == '\n' || c == '\t' || c == ' '){
			*(p_line + line_length++) = '\0';
			insertWord(p_line, root);
			p_line = p_line + line_length;
			line_length = 0;
		}
		else
			*(p_line + line_length++) = c;
	}
	char words[num_of_input];
	char *p = words;
	printWords(type, root, p);
	freeMemory(&root);

	return 0;
}
