#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <iomanip> // Untuk setprecision

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

    // Cetak waktu eksekusi dalam detik dengan presisi tinggi
    cout << fixed << setprecision(7); // Tampilkan 7 angka di belakang koma
    cout << "Waktu eksekusi: " << duration.count() << " detik" << endl;

    return 0;
}
