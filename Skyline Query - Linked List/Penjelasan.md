# Linked List

***Dibuat oleh : Rizqi Akbar Sukirman Putra 5027241044***

Membuat query skyline menggunakan linked liost dengan 1000 data

Dengan kode:
```
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
```

Dengan Hasil :
```
=== Produk Terbaik (Skyline) ===
ID: 109 | product-109 | Harga: 8 | Rating: 231
ID: 160 | product-160 | Harga: 104 | Rating: 283
ID: 335 | product-335 | Harga: 63 | Rating: 263
ID: 351 | product-351 | Harga: 23 | Rating: 240
ID: 419 | product-419 | Harga: 17 | Rating: 236
ID: 488 | product-488 | Harga: 61 | Rating: 257
ID: 947 | product-947 | Harga: 28 | Rating: 244
ID: 954 | product-954 | Harga: 43 | Rating: 245
ID: 964 | product-964 | Harga: 5 | Rating: 195
Waktu eksekusi: 0.0006452 detik
```

Dengan menggunakan linked list dan menggunakan 1000 data, hasil waktu yang dihasilkan adalah 0.0006452 detik.
