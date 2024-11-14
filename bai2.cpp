#include <iostream>
#include <cstring>

using namespace std;

// Cấu trúc của một node trong danh sách liên kết
struct Node {
    char word[50];
    int count;
    Node* next;
};

// Hàm tạo một node mới
Node* createNode(const char* word) {
    Node* newNode = new Node;
    strcpy(newNode->word, word);
    newNode->count = 1;
    newNode->next = nullptr;
    return newNode;
}

// Hàm thêm từ vào danh sách liên kết (tăng đếm nếu từ đã tồn tại)
void addWord(Node*& head, const char* word) {
    Node* temp = head;
    while (temp != nullptr) {
        if (strcmp(temp->word, word) == 0) {
            temp->count++;
            return;
        }
        temp = temp->next;
    }
    Node* newNode = createNode(word);
    newNode->next = head;
    head = newNode;
}

// Hàm tìm các từ xuất hiện nhiều nhất
void findMostFrequentWords(Node* head) {
    Node* temp = head;
    int maxCount = 0;

    // Tìm số lần xuất hiện lớn nhất
    while (temp != nullptr) {
        if (temp->count > maxCount) {
            maxCount = temp->count;
        }
        temp = temp->next;
    }

    // Liệt kê các từ có số lần xuất hiện bằng maxCount
    cout << "Cac tu xuat hien nhieu nhat (" << maxCount << " lan): ";
    temp = head;
    while (temp != nullptr) {
        if (temp->count == maxCount) {
            cout << temp->word << " ";
        }
        temp = temp->next;
    }
    cout << endl;
}

// Hàm kiểm tra từ láy và loại bỏ nếu tồn tại
void removeReduplication(Node* head) {
    Node* temp = head;
    while (temp != nullptr && temp->next != nullptr) {
        if (strcmp(temp->word, temp->next->word) == 0) {
            Node* redundant = temp->next;
            temp->next = temp->next->next;
            delete redundant;
        } else {
            temp = temp->next;
        }
    }
}

// Hàm đếm số từ vựng xuất hiện trong câu
int countWords(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Hàm giải phóng bộ nhớ của danh sách
void freeList(Node* head) {
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

// Hàm tách từ trong câu
void splitWords(Node*& head, char* sentence) {
    char* word = strtok(sentence, " \n");
    while (word != nullptr) {
        addWord(head, word);
        word = strtok(nullptr, " \n");
    }
}

// Hàm chính
int main() {
    Node* head = nullptr;
    char sentence[256];
    
    cout << "Nhap cau cua ban: ";
    cin.getline(sentence, 256);
    
    // Tách câu thành các từ và thêm vào danh sách liên kết
    splitWords(head, sentence);
    
    // Đếm số từ vựng trước khi xóa từ láy
    int totalWordsBeforeRemoving = countWords(head);
    cout << "Tong so tu vung trong cau la: " << totalWordsBeforeRemoving << endl;
    
    // Xác định các từ xuất hiện nhiều nhất
    findMostFrequentWords(head);

    // Loại bỏ từ láy
    removeReduplication(head);

    // Giải phóng bộ nhớ
    freeList(head);

    return 0;
}
