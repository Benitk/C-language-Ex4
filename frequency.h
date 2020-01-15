#ifndef __FREQUENCY__H__
#define __FREQUENCY__H__

//declare struct
struct node;
typedef struct node node;


//declare functions
node* newNode();
int charToIndex(const char);
void insertWord(char*, node*);
void printWordDefualt(node* , char* , int);
void printWordReverse(node*, char*, int);
void printWords(char, node*, char*);
void freeMemory(node**);

#endif /* __FREQUENCY__H__ */
