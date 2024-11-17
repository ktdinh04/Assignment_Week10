#include <stdio.h>
#include <stdlib.h>

// Tạo danh sách liên kết
struct Node {
    int data;
    struct Node* next;
};

// Hàm thêm node ở đầu danh sách
struct Node* insertNode(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return head;
    }
    newNode->data = data;
    newNode->next = head;
    return newNode;
}

// Hàm thêm node ở cuối danh sách
struct Node* insertLast(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return head;
    }
    newNode->data = data;
    newNode->next = NULL;
    if (head == NULL) return newNode;
    struct Node* last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
    return head;
}

// Xóa node ở đầu danh sách
struct Node* deleteFirst(struct Node* head) {
    if (head == NULL) return NULL;
    struct Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

// Xóa node ở cuối danh sách
struct Node* deleteLast(struct Node* head) {
    if (head == NULL) return NULL;
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    struct Node* second_last = head;
    while (second_last->next->next != NULL) {
        second_last = second_last->next;
    }
    free(second_last->next);
    second_last->next = NULL;
    return head;
}

// Xóa node cho trước
struct Node* deleteNode(struct Node* head, int key) {
    if (head == NULL) return head;
    if (head->data == key) {
        return deleteFirst(head);
    }
    struct Node* current = head;
    while (current->next != NULL && current->next->data != key) {
        current = current->next;
    }
    if (current->next == NULL) {
        printf("Key %d not found in the list\n", key);
        return head;
    }
    struct Node* temp = current->next;
    current->next = current->next->next;
    free(temp);
    return head;
}

// Hàm in danh sách
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Giải phóng danh sách
void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Hàm main ví dụ
int main() {
    struct Node* head = NULL;

    // Tạo các node
    head = insertNode(head, 7);
    head = insertNode(head, 1);
    head = insertNode(head, 3);
    head = insertNode(head, 2);
    head = insertNode(head, 8);
    head = insertNode(head, 5);
    head = insertLast(head, 10);
    head = insertLast(head, 6);

    printf("Danh sach ban dau: ");
    printList(head);

    head = deleteFirst(head);
    printf("Sau khi xoa dau: ");
    printList(head);

    head = deleteLast(head);
    printf("Sau khi xoa cuoi: ");
    printList(head);

    head = deleteNode(head, 3);
    printf("Sau khi xoa gia tri 3: ");
    printList(head);

    // Giải phóng bộ nhớ
    freeList(head);
    return 0;
}
