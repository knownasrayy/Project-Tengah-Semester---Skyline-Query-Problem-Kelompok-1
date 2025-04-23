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

    bool dominates(Product* a, Product* b) const {
        bool betterOrEqualHarga = a->harga <= b->harga;
        bool betterOrEqualRating = a->rating >= b->rating;
        bool strictlyBetter = (a->harga < b->harga || a->rating > b->rating);
        return betterOrEqualHarga && betterOrEqualRating && strictlyBetter;
    }

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head) {
            Product* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(int id, const string& label, int harga, int rating) {
        Product* newProduct = new Product{id, label, harga, rating, nullptr};
        if (!head) {
            head = newProduct;
        } else {
            Product* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newProduct;
        }
    }

    void skyline() const {
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

void loadCSV(const string& filename, LinkedList& list) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Gagal membuka file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, label, hargaStr, ratingStr;

        if (!getline(ss, idStr, ',') ||
            !getline(ss, label, ',') ||
            !getline(ss, hargaStr, ',') ||
            !getline(ss, ratingStr, ',')) {
            cerr << "Format baris salah: " << line << endl;
            continue;
        }

        try {
            int id = stoi(idStr);
            int harga = stoi(hargaStr);
            int rating = stoi(ratingStr);
            list.insert(id, label, harga, rating);
        } catch (const exception& e) {
            cerr << "Gagal parsing baris: " << line << " | Error: " << e.what() << endl;
        }
    }
}

int main() {
    LinkedList list;

    // Waktu mulai untuk load data
    auto startLoad = chrono::high_resolution_clock::now();
    loadCSV("ind_1000_2_product.csv", list);
    auto endLoad = chrono::high_resolution_clock::now();

    // Waktu mulai untuk skyline
    auto startSkyline = chrono::high_resolution_clock::now();
    cout << "=== Produk Terbaik (Skyline) ===" << endl;
    list.skyline();
    auto endSkyline = chrono::high_resolution_clock::now();

    // Hitung dan tampilkan waktu
    chrono::duration<double> loadDuration = endLoad - startLoad;
    chrono::duration<double> skylineDuration = endSkyline - startSkyline;

    cout << "\nWaktu load data     : " << loadDuration.count() << " detik" << endl;
    cout << "Waktu proses skyline: " << skylineDuration.count() << " detik" << endl;

    return 0;
}
