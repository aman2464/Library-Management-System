#include "include/library.h"

int main() {
    loadFromFile();
    int choice, id;
    char title[MAX_TITLE], author[MAX_AUTHOR], student[100];
    char actionBuf[100];

    while (1) {
        printf("\n=======================================================\n");
        printf("       LIBRARY MANAGEMENT SYSTEM (Capstone)           \n");
        printf("=======================================================\n");
        printf("1. Add New Book Record (BST Insert)\n");
        printf("2. Search Book by ID (BST Search)\n");
        printf("3. Display All Books (In-Order Traversal)\n");
        printf("4. Delete Book Record (BST Delete)\n");
        printf("5. Add Borrow Request to Queue (FIFO)\n");
        printf("6. Process Next Borrow Request\n");
        printf("7. Undo Last Dynamic Action (Stack)\n");
        printf("8. Generate System Report Summary\n");
        printf("9. Save & Exit\n");
        printf("Select an option (1-9): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Terminating program safely.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter Book ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Title: ");
                fgets(title, MAX_TITLE, stdin);
                title[strcspn(title, "\n")] = 0;
                printf("Enter Author: ");
                fgets(author, MAX_AUTHOR, stdin);
                author[strcspn(author, "\n")] = 0;
                
                root = insertBook(root, id, title, author);
                snprintf(actionBuf, sizeof(actionBuf), "Added Book ID %d", id);
                pushAction(actionBuf);
                printf("Book successfully inserted!\n");
                break;

            case 2:
                printf("Enter Book ID to Search: ");
                scanf("%d", &id);
                BookNode *found = searchBook(root, id);
                if (found) {
                    printf("\n--- Book Details Found ---\n");
                    printf("ID: %d\nTitle: %s\nAuthor: %s\nStatus: %s\n",
                           found->id, found->title, found->author, found->isBorrowed ? "Borrowed" : "Available");
                } else {
                    printf("\nBook with ID %d not found.\n", id);
                }
                break;

            case 3:
                printf("\n-------------------------------------------------------------------\n");
                printf("| %-5s | %-30s | %-20s | %-10s |\n", "ID", "Title", "Author", "Status");
                printf("-------------------------------------------------------------------\n");
                displayInOrder(root);
                printf("-------------------------------------------------------------------\n");
                break;

            case 4:
                printf("Enter Book ID to Delete: ");
                scanf("%d", &id);
                root = deleteBook(root, id);
                snprintf(actionBuf, sizeof(actionBuf), "Deleted Book ID %d", id);
                pushAction(actionBuf);
                printf("Record processed for deletion.\n");
                break;

            case 5:
                printf("Enter Book ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Student Name: ");
                fgets(student, sizeof(student), stdin);
                student[strcspn(student, "\n")] = 0;
                enqueueRequest(id, student);
                break;

            case 6:
                dequeueRequest();
                break;

            case 7:
                popAction();
                break;

            case 8:
                printf("\n================ SYSTEM SUMMARY REPORT ================\n");
                printf("Total Books Managed: %d\n", countBooks(root));
                printf("Queue Status: %s\n", requestQueue.front ? "Active Requests Pending" : "Empty");
                printf("=======================================================\n");
                break;

            case 9:
                saveAllData();
                freeTree(root);
                printf("Exiting system safely.\n");
                return 0;

            default:
                printf("Invalid selection. Try again.\n");
        }
    }
    return 0;
}