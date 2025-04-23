#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
using namespace std;

struct Product {
    int id;
    string label;
    int harga; 
    int rating; 
    Product* next;
};

class LinkedList {
private:
    Product* head;

    bool dominates(Product* a, Product* b) {
        bool betterOrEqualHarga = a->harga <= b->harga;
        bool betterOrEqualRating = a->rating >= b->rating;
        bool strictlyBetter = (a->harga < b->harga || a->rating > b->rating);
        return betterOrEqualHarga && betterOrEqualRating && strictlyBetter;
    }

public:
    LinkedList() : head(nullptr) {}

    void insert(int id, string label, int attr1, int attr2) {
        Product* newProduct = new Product{id, label, attr1, attr2, nullptr};
        if (!head) {
            head = newProduct;
        } else {
            Product* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newProduct;
        }
    }

    void skyline() {
        Product* outer = head;
        while (outer) {
            Product* inner = head;
            bool dominated = false;

            while (inner) {
                if (inner != outer && dominates(inner, outer)) {
                    dominated = true;
                    break;
                }
                inner = inner->next;
            }

            if (!dominated) {
                cout << "ID: " << outer->id
                     << " | " << outer->label
                     << " | Harga: " << outer->harga
                     << " | Rating: " << outer->rating << endl;
            }

            outer = outer->next;
        }
    }
};

void exampleFunction()
{
  for (int i = 0; i < 1000000; ++i)
  {
    // Operasi sederhana
    int x = i * i;
  }
}

void loadCSV(const string& filename, LinkedList& list) {
    ifstream file(filename);
    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, label, attr1Str, attr2Str;
        getline(ss, idStr, ',');
        getline(ss, label, ',');
        getline(ss, attr1Str, ',');
        getline(ss, attr2Str, ',');

        int id = stoi(idStr);
        int attr1 = stoi(attr1Str);
        int attr2 = stoi(attr2Str);

        list.insert(id, label, attr1, attr2);
    }
}

int main() {
    LinkedList list;
    loadCSV("ind_1000_2_product.csv", list);
    cout << "=== Produk Terbaik (Skyline) ===" << endl;
    list.skyline();

    auto start = std::chrono::high_resolution_clock::now();
    exampleFunction();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Waktu eksekusi: " << duration.count() << " detik" << std::endl;

    return 0;
}