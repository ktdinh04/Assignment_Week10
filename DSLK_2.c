#include<stdio.h>
#include<stdlib.h>
#define MAX_LENGTH 1000

// Thiết kế thông tin file lưu trữ
struct File {
    char name[MAX_LENGTH];
    char type[MAX_LENGTH];
    int size;
    char date[MAX_LENGTH];
    struct File* next;
};

// Thiết kế một danh sách lưu trữ mô tả một folder để lưu trữ thông tin file
struct Folder {
    struct File* head;
};

// Hàm sao chép chuỗi
void string_copy(char* dest, const char* src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0'; // Thêm ký tự kết thúc chuỗi
}

// Hàm tạo một file mới
struct File* create_file(char* name, char* type, int size, char* date) {
    struct File* new_file = (struct File*)malloc(sizeof(struct File));
    string_copy(new_file->name, name);
    string_copy(new_file->type, type);
    new_file->size = size;
    string_copy(new_file->date, date);
    new_file->next = NULL;
    return new_file;
}

// Thêm file vào folder
void add_file(struct Folder* folder, struct File* file) {
    file->next = folder->head;
    folder->head = file;
}

// Sắp xếp file trong thư mục theo thứ tự tăng dần về dung lượng
void sort_files(struct Folder* folder) {
    if (!folder->head) return;
    struct File* current;
    struct File* index;
    struct File temp;

    for (current = folder->head; current != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (current->size > index->size) {
                // Hoán đổi nội dung của hai file
                temp = *current;
                *current = *index;
                *index = temp;

                // Khôi phục liên kết do hoán đổi con trỏ
                struct File* temp_next = current->next;
                current->next = index->next;
                index->next = temp_next;
            }
        }
    }
}

// Hàm so sánh ngày (format: YYYY-MM-DD)
int compare_date(const char* date1, const char* date2) {
    return strcmp(date1, date2); // Hàm so sánh chuỗi tiêu chuẩn, trả về giá trị âm nếu date1 < date2
}

// Xóa file có dung lượng bé nhất và ngày lưu lâu nhất
void delete_min_size_file(struct Folder* folder) {
    if (!folder->head) return;

    struct File* current = folder->head;
    struct File* min_file = folder->head;
    struct File* prev = NULL;
    struct File* min_prev = NULL;

    while (current != NULL) {
        // Kiểm tra nếu dung lượng nhỏ hơn hoặc (dung lượng bằng và ngày lưu lâu hơn)
        if (current->size < min_file->size || 
           (current->size == min_file->size && compare_date(current->date, min_file->date) < 0)) {
            min_file = current;
            min_prev = prev;
        }
        prev = current;
        current = current->next;
    }

    // Xóa file tìm được
    if (min_file == folder->head) {
        folder->head = folder->head->next;
    } else {
        min_prev->next = min_file->next;
    }

    free(min_file);
}


// In ra các file trong folder
void print_files(struct Folder* folder) {
    struct File* current = folder->head;
    int index = 0;
    while (current != NULL) {
        printf("%d: %s %s %d %s\n", index, current->name, current->type, current->size, current->date);
        current = current->next;
        index++;
    }
}

int main() {
    // Tạo folder
    struct Folder folder;
    folder.head = NULL;
    // Tạo các file
    struct File* file1 = create_file("file1", "txt", 100, "2021-01-01");
    struct File* file2 = create_file("file2", "txt", 200, "2021-01-01");
    struct File* file3 = create_file("file3", "txt", 50, "2021-01-01");
    struct File* file4 = create_file("file4", "txt", 150, "2021-01-04");
    struct File* file5 = create_file("file5", "txt", 100, "2021-01-05");
    struct File* file6 = create_file("file6", "txt", 100, "2021-01-06");
    struct File* file7 = create_file("file7", "txt", 100, "2021-01-07");
    struct File* file8 = create_file("file8", "txt", 100, "2021-01-01");
    struct File* file9 = create_file("file9", "txt", 100, "2021-01-09");
    struct File* file10 = create_file("file10", "txt", 100, "2021-01-10");

    // Thêm file vào folder
    add_file(&folder, file1);
    add_file(&folder, file2);
    add_file(&folder, file3);
    add_file(&folder, file4);
    add_file(&folder, file5);
    add_file(&folder, file6);
    add_file(&folder, file7);
    add_file(&folder, file8);
    add_file(&folder, file9);
    add_file(&folder, file10);




    // In ra các file trong folder
    printf("Danh sach file:\n");
    print_files(&folder);

    // Sắp xếp file trong thư mục
    sort_files(&folder);
    printf("Danh sach file sau khi sap xep:\n");
    print_files(&folder);
    // Xóa file có dung lượng bé nhất
    delete_min_size_file(&folder);
    // Kiểm tra lại danh sách file sau khi xóa
    printf("Danh sach file sau khi xoa:\n");
    print_files(&folder);

    return 0;
}
    