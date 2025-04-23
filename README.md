# Project-Tengah-Semester---Skyline-Query-Problem-Kelompok-1

**Anggota**

1. Rizqi Akbar Sukirman Putra 5027241044
2. Fika Arka Nuriyah 5027241071
3. Putu Yudi Nandanjaya Wiraguna 5027241080
4. Rayhan Agnan Kusuma 5027241102
5. Naruna Vicranthyo Putra Gangga 5027241105
6. Zahra Hafizhah 5027241121

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



# Array

***Dibuat oleh : Rayhan Agnan Kusuma 5027241044***

Membuat query skyline menggunakan linked liost dengan 1000 data

Dengan kode:
```
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Struktur data untuk menyimpan informasi produk
struct Item {
    int id;
    string name;
    double price;
    double review;
};

// Fungsi untuk mengecek dominasi antar produk
bool dominates(const Item& A, const Item& B) {
    return (A.price <= B.price && A.review >= B.review) &&
           (A.price < B.price || A.review > B.review);
}

// Fungsi utama skyline query
vector<Item> skylineQuery(const vector<Item>& items) {
    vector<Item> skyline;
    for (const auto& itemA : items) {
        bool isDominated = false;
        for (const auto& itemB : items) {
            if (&itemA != &itemB && dominates(itemB, itemA)) {
                isDominated = true;
                break;
            }
        }
        if (!isDominated) {
            skyline.push_back(itemA);
        }
    }
    return skyline;
}

// Fungsi yang membungkus semua proses — seperti contoh dosen
void exampleFunction() {
    ifstream file("E:\\KULIAH\\SEMESTER 2\\Struktur Data dan Pemrograman Berorientasi Objek (A)\\Project 1 - Skyline Query Problem\\ind_1000_2_product.csv");
    string line;
    vector<Item> items;

    // Lewati header
    getline(file, line);

    // Baca isi file baris per baris
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, priceStr, reviewStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        getline(ss, reviewStr, ',');

        Item item;
        item.id = stoi(idStr);
        item.name = name;
        item.price = stod(priceStr);
        item.review = stod(reviewStr);
        items.push_back(item);
    }

    cout << "Jumlah item yang dibaca: " << items.size() << endl;

    // Jalankan skyline query
    vector<Item> skyline = skylineQuery(items);

    // Cetak hasil
    cout << "=== Produk Terbaik (Skyline) ===\n";
    for (const auto& item : skyline) {
        cout << "ID: " << item.id
             << " | " << item.name
             << " | Harga: " << item.price
             << " | Rating: " << item.review << endl;
    }
}

int main() {
    // Mulai pengukuran waktu
    auto start = high_resolution_clock::now();

    // Jalankan fungsi utama
    exampleFunction();

    // Selesai pengukuran waktu
    auto end = high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    // Cetak waktu eksekusi dalam detik
    cout << "Waktu eksekusi: " << duration.count() << " detik" << endl;

    return 0;
}

```

Dengan Hasil :
```
Jumlah item yang dibaca: 1000
Skyline Query selesai dalam 1 ms
Skyline result:
Price: 8, Review: 231
Price: 104, Review: 283
Price: 63, Review: 263
Price: 23, Review: 240
Price: 17, Review: 236
Price: 61, Review: 257
Price: 28, Review: 244
Price: 43, Review: 245
Price: 5, Review: 195
```

Dengan menggunakan linked list dan menggunakan 1000 data, hasil waktu yang dihasilkan adalah 1 detik.

