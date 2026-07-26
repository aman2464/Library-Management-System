#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_AUTHOR 100
#define FILE_PATH "sample-data/library_data.txt"

typedef struct BookNode {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int isBorrowed;
    struct BookNode *left;
    struct BookNode *right;
} BookNode;

typedef struct StackNode {
    char action[100];
    struct StackNode *next;
} StackNode;

typedef struct QueueNode {
    int bookId;
    char studentName[100];
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

extern BookNode *root;
extern StackNode *undoStack;
extern Queue requestQueue;

void pushAction(const char *action);
void popAction();

void enqueueRequest(int bookId, const char *studentName);
void dequeueRequest();

BookNode* createNode(int id, const char *title, const char *author);
BookNode* insertBook(BookNode *node, int id, const char *title, const char *author);
BookNode* searchBook(BookNode *node, int id);
BookNode* findMin(BookNode *node);
BookNode* deleteBook(BookNode *node, int id);
void displayInOrder(BookNode *node);
int countBooks(BookNode *node);

void saveToFile(BookNode *node, FILE *fp);
void saveAllData();
void loadFromFile();
void freeTree(BookNode *node);

#endif