#include "../include/library.h"

BookNode *root = NULL;
StackNode *undoStack = NULL;
Queue requestQueue = {NULL, NULL};

void pushAction(const char *action) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (!newNode) return;
    strncpy(newNode->action, action, sizeof(newNode->action));
    newNode->next = undoStack;
    undoStack = newNode;
}

void popAction() {
    if (undoStack == NULL) {
        printf("\n[Undo Stack] No actions to undo.\n");
        return;
    }
    StackNode *temp = undoStack;
    printf("\n[Undo Action] Reversing last operation: %s\n", temp->action);
    undoStack = undoStack->next;
    free(temp);
}

void enqueueRequest(int bookId, const char *studentName) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (!newNode) return;
    newNode->bookId = bookId;
    strncpy(newNode->studentName, studentName, sizeof(newNode->studentName));
    newNode->next = NULL;

    if (requestQueue.rear == NULL) {
        requestQueue.front = requestQueue.rear = newNode;
    } else {
        requestQueue.rear->next = newNode;
        requestQueue.rear = newNode;
    }
    printf("Request queued successfully for Student: %s (Book ID: %d)\n", studentName, bookId);
}

void dequeueRequest() {
    if (requestQueue.front == NULL) {
        printf("\n[Queue] No pending borrow requests.\n");
        return;
    }
    QueueNode *temp = requestQueue.front;
    printf("\n[Processing Queue] Processing request for %s (Book ID: %d)\n", temp->studentName, temp->bookId);
    requestQueue.front = requestQueue.front->next;
    if (requestQueue.front == NULL) requestQueue.rear = NULL;
    free(temp);
}

BookNode* createNode(int id, const char *title, const char *author) {
    BookNode *newNode = (BookNode *)malloc(sizeof(BookNode));
    if (!newNode) return NULL;
    newNode->id = id;
    strncpy(newNode->title, title, MAX_TITLE);
    strncpy(newNode->author, author, MAX_AUTHOR);
    newNode->isBorrowed = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BookNode* insertBook(BookNode *node, int id, const char *title, const char *author) {
    if (node == NULL) return createNode(id, title, author);
    if (id < node->id)
        node->left = insertBook(node->left, id, title, author);
    else if (id > node->id)
        node->right = insertBook(node->right, id, title, author);
    return node;
}

BookNode* searchBook(BookNode *node, int id) {
    if (node == NULL || node->id == id) return node;
    if (id < node->id) return searchBook(node->left, id);
    return searchBook(node->right, id);
}

BookNode* findMin(BookNode *node) {
    while (node && node->left != NULL) node = node->left;
    return node;
}

BookNode* deleteBook(BookNode *node, int id) {
    if (node == NULL) return node;
    if (id < node->id)
        node->left = deleteBook(node->left, id);
    else if (id > node->id)
        node->right = deleteBook(node->right, id);
    else {
        if (node->left == NULL) {
            BookNode *temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            BookNode *temp = node->left;
            free(node);
            return temp;
        }
        BookNode *temp = findMin(node->right);
        node->id = temp->id;
        strncpy(node->title, temp->title, MAX_TITLE);
        strncpy(node->author, temp->author, MAX_AUTHOR);
        node->isBorrowed = temp->isBorrowed;
        node->right = deleteBook(node->right, temp->id);
    }
    return node;
}

void displayInOrder(BookNode *node) {
    if (node != NULL) {
        displayInOrder(node->left);
        printf("| %-5d | %-30s | %-20s | %-10s |\n", 
               node->id, node->title, node->author, node->isBorrowed ? "Borrowed" : "Available");
        displayInOrder(node->right);
    }
}

int countBooks(BookNode *node) {
    if (node == NULL) return 0;
    return 1 + countBooks(node->left) + countBooks(node->right);
}

void saveToFile(BookNode *node, FILE *fp) {
    if (node == NULL) return;
    fprintf(fp, "%d,%s,%s,%d\n", node->id, node->title, node->author, node->isBorrowed);
    saveToFile(node->left, fp);
    saveToFile(node->right, fp);
}

void saveAllData() {
    FILE *fp = fopen(FILE_PATH, "w");
    if (!fp) {
        printf("Error saving data to file.\n");
        return;
    }
    saveToFile(root, fp);
    fclose(fp);
    printf("Data successfully persisted to '%s'.\n", FILE_PATH);
}

void loadFromFile() {
    FILE *fp = fopen(FILE_PATH, "r");
    if (!fp) return;
    int id, isBorrowed;
    char title[MAX_TITLE], author[MAX_AUTHOR];
    
    while (fscanf(fp, "%d,%99[^,],%99[^,],%d\n", &id, title, author, &isBorrowed) == 4) {
        root = insertBook(root, id, title, author);
        BookNode *b = searchBook(root, id);
        if (b) b->isBorrowed = isBorrowed;
    }
    fclose(fp);
}

void freeTree(BookNode *node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}