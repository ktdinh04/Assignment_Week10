#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc Gỗ
typedef struct Wood {
    char type[20];
    int size;
    int age;
    struct Wood* next;
} Wood;

// Định nghĩa stack cho từng loại gỗ
typedef struct WoodStack {
    char type[20];
    Wood* top;
} WoodStack;

// Hàm tự viết để sao chép chuỗi
void string_copy(char* dest, const char* src) {
    while ((*dest++ = *src++)); // Sao chép từng ký tự, bao gồm cả ký tự null
}

// Hàm khởi tạo stack gỗ
WoodStack* createStack(const char* type) {
    WoodStack* stack = (WoodStack*)malloc(sizeof(WoodStack));
    string_copy(stack->type, type);
    stack->top = NULL;
    return stack;
}

// Hàm thêm gỗ vào stack
void push(WoodStack* stack, int size, int age) {
    Wood* newWood = (Wood*)malloc(sizeof(Wood));
    string_copy(newWood->type, stack->type);
    newWood->size = size;
    newWood->age = age;
    newWood->next = stack->top;
    stack->top = newWood;
}

// Hàm lấy gỗ ra khỏi stack
Wood* pop(WoodStack* stack) {
    if (stack->top == NULL) {
        printf("Trong!\n");
        return NULL;
    }
    Wood* topWood = stack->top;
    stack->top = stack->top->next;
    return topWood;
}

// Hàm đếm số lượng gỗ có cùng tuổi
int countSameAge(WoodStack* stack, int age) {
    int count = 0;
    Wood* current = stack->top;
    while (current != NULL) {
        if (current->age == age) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// Hàm hiển thị các thanh gỗ trong stack
void displayStack(WoodStack* stack) {
    printf("Loai go %s:\n", stack->type);
    Wood* current = stack->top;
    while (current != NULL) {
        printf("  Do dai: %d, Tuoi: %d\n", current->size, current->age);
        current = current->next;
    }
    printf("\n");
}


int main() {
    // Tạo stack cho từng loại gỗ
    WoodStack* GoKeo = createStack("Go_Keo");
    WoodStack* GoNghien = createStack("Go_Nghien");

    // Thêm gỗ vào kho
    push(GoKeo, 5, 10);
    push(GoKeo, 3, 15);
    push(GoNghien, 4, 8);
    push(GoKeo, 3, 10);

    // Hiển thị kho
    printf("Go trong kho:\n");
    displayStack(GoKeo);
    displayStack(GoNghien);

    // Đếm số lượng gỗ cùng tuổi
    printf("So go co so tuoi la 10 la: %d\n", countSameAge(GoKeo, 10));

    // Lấy gỗ ra khỏi kho
    Wood* removedWood = pop(GoKeo);
    if (removedWood) {
        printf("So loai go: Type: %s, Size: %d, Age: %d\n", removedWood->type, removedWood->size, removedWood->age);
        free(removedWood);
    }

    // Hiển thị kho sau khi lấy gỗ
    printf("\nSo go sau khi lay go la:\n");
    displayStack(GoKeo);
    displayStack(GoNghien);

    // Giải phóng bộ nhớ
    free(GoKeo);
    free(GoNghien);

    return 0;
}
