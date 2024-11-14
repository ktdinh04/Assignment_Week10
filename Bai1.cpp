#include <iostream>
#include <string>

struct FileNode {
    std::string file_name;    // Tên file
    long file_size;           // Kích thước file (tính bằng byte)
    std::string created_date; // Ngày tạo file (định dạng: YYYY-MM-DD)
    FileNode* next;           // Con trỏ đến file tiếp theo trong danh sách

    FileNode(std::string name, long size, std::string date)
        : file_name(name), file_size(size), created_date(date), next(nullptr) {}
};

struct FileLinkedList {
    FileNode* head;

    FileLinkedList() : head(nullptr) {}

    // Hàm thêm file vào danh sách theo thứ tự thời gian
    void insertFile(std::string name, long size, std::string date) {
        FileNode* newNode = new FileNode(name, size, date);

        if (!head || head->created_date > date) {
            newNode->next = head;
            head = newNode;
        } else {
            FileNode* current = head;
            while (current->next && current->next->created_date < date) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Hàm tính tổng kích thước của tất cả các file trong thư mục
    long calculateTotalSize() {
        long totalSize = 0;
        FileNode* current = head;
        while (current) {
            totalSize += current->file_size;
            current = current->next;
        }
        return totalSize;
    }

    // Hàm xóa file có kích thước nhỏ nhất trong danh sách
    void removeSmallestFile() {
        if (!head) return;

        FileNode* current = head;
        FileNode* smallest = head;
        FileNode* prev = nullptr;
        FileNode* prev_smallest = nullptr;

        while (current) {
            if (current->file_size < smallest->file_size) {
                smallest = current;
                prev_smallest = prev;
            }
            prev = current;
            current = current->next;
        }

        if (smallest == head) {
            head = head->next;
        } else {
            prev_smallest->next = smallest->next;
        }
        delete smallest;
    }

    // Hàm in danh sách file
    void printFiles() {
        FileNode* current = head;
        while (current) {
            std::cout << "File: " << current->file_name
                      << ", Size: " << current->file_size
                      << ", Created Date: " << current->created_date << "\n";
            current = current->next;
        }
    }
};

// Hàm copy file vào thư mục
void copyFileToDocument(FileLinkedList& document, std::string name, long size, std::string date) {
    document.insertFile(name, size, date);
}

// Hàm sao lưu vào USB 32GB, loại bỏ các file nhỏ nhất nếu cần
const long long USB_CAPACITY = 32LL * 1024LL * 1024LL * 1024LL; // 32GB tính bằng byte


void backupFilesToUSB(FileLinkedList& document) {
    while (document.calculateTotalSize() > USB_CAPACITY) {
        document.removeSmallestFile();
    }
}

// Chương trình chính để kiểm tra các chức năng
int main() {
    FileLinkedList document;

    // Thêm file mẫu
    document.insertFile("file1.txt", 2000, "2023-01-01");
    document.insertFile("file2.txt", 500, "2023-01-02");
    document.insertFile("file3.txt", 30000, "2023-02-01");

    // Copy một file mới vào thư mục
    copyFileToDocument(document, "file4.txt", 1000, "2023-01-15");

    // In danh sách file sau khi copy
    std::cout << "Files in Document folder:\n";
    document.printFiles();

    // Tính tổng kích thước các file
    long totalSize = document.calculateTotalSize();
    std::cout << "\nTotal Size of Files: " << totalSize << " bytes\n";

    // Sao lưu vào USB 32GB (loại bỏ các file nếu cần)
    backupFilesToUSB(document);

    // In danh sách file sau khi sao lưu
    std::cout << "\nFiles after backup operation:\n";
    document.printFiles();

    return 0;
}
