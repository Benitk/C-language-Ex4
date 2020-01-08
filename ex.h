#ifndef __EX_H__
#define __EX_H__

struct node;
typedef struct node node;

node* newNode();
int charToIndex(const char);
void insertWord(char*, node*);
void printWordDefualt(node* , char* , int);
void printWordReverse(node*, char*, int);
void printWords(char, node*, char*);
void freeMemory(node**);

#endif /* __EX_H__ */
