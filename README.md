# Project-Tengah-Semester---Skyline-Query-Problem-Kelompok-1

**Anggota**

1. Rizqi Akbar Sukirman Putra 5027241044
2. Fika Arka Nuriyah 5027241071
3. Putu Yudi Nandanjaya Wiraguna 5027241080
4. Rayhan Agnan Kusuma 5027241102
5. Naruna Vicranthyo Putra Gangga 5027241105
6. Zahra Hafizhah 5027241121

# Analisis Hasil 
1. struktur data yang paling efisisen dalam memproses skyline query ?
2. mengapa?


# Laporan Akhir

## Hasil Performa 6 struktur data

| NAMA | DETIK |
| ------------- | ------------- |
|  Array | 1 |
| Stack  |  0.010486 |
| Linked List | 0.0006452  |
| Queue  | 0.000252  |
| Map  | 0.0174   |
| Hash  | .... |


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
#include <iomanip>

using namespace std;
using namespace std::chrono;


struct Item {
    int id;
    string name;
    double price;
    double review;
};


bool dominates(const Item& A, const Item& B) {
    return (A.price <= B.price && A.review >= B.review) &&
           (A.price < B.price || A.review > B.review);
}


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


void exampleFunction() {
    ifstream file("E:\\KULIAH\\SEMESTER 2\\Struktur Data dan Pemrograman Berorientasi Objek (A)\\Project 1 - Skyline Query Problem\\ind_1000_2_product.csv");
    string line;
    vector<Item> items;


    getline(file, line);


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


    vector<Item> skyline = skylineQuery(items);


    cout << "=== Produk Terbaik (Skyline) ===\n";
    for (const auto& item : skyline) {
        cout << "ID: " << item.id
             << " | " << item.name
             << " | Harga: " << item.price
             << " | Rating: " << item.review << endl;
    }
}

int main() {

    auto start = high_resolution_clock::now();


    exampleFunction();


    auto end = high_resolution_clock::now();
    chrono::duration<double> duration = end - start;


    cout << fixed << setprecision(7); // Tampilkan 7 angka di belakang koma
    cout << "Waktu eksekusi: " << duration.count() << " detik" << endl;

    return 0;
}

```

Dengan Hasil :
```
Jumlah item yang dibaca: 1000
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
Waktu eksekusi: 0.0265260 detik
```

Dengan menggunakan linked list dan menggunakan 1000 data, hasil waktu yang dihasilkan adalah  0.0265260 detik detik.


# Stack

***Dibuat oleh : Naruna Vicranthyo Putra Gangga 5027241105***

Membuat query skyline menggunakan stack dengan 1000 data

Dengan kode:
```C++
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Struktur data produk
struct Item {
    int id;
    string name;
    double price;
    double review;
};

// Fungsi dominasi: true jika A mendominasi B
bool dominates(const Item& A, const Item& B) {
    return (A.price <= B.price && A.review >= B.review) &&
           (A.price < B.price || A.review > B.review);
}

// Skyline query menggunakan pendekatan stack-style logic
vector<Item> skylineUsingStackLikeArray(const vector<Item>& items) {
    vector<Item> skyline;

    for (const auto& item : items) {
        bool isDominated = false;
        vector<Item> newSkyline;

        // Cek apakah item didominasi elemen lain di skyline
        for (const auto& skyItem : skyline) {
            if (dominates(skyItem, item)) {
                isDominated = true;
                break;
            }
        }

        // Jika tidak didominasi, tambahkan ke skyline
        if (!isDominated) {
            // Hapus elemen yang didominasi oleh item ini
            for (const auto& skyItem : skyline) {
                if (!dominates(item, skyItem)) {
                    newSkyline.push_back(skyItem);
                }
            }
            newSkyline.push_back(item); // Tambahkan item ke skyline
            skyline = newSkyline;
        }
    }

    return skyline;
}

// Fungsi utama untuk membaca data dan menjalankan skyline query
void runSkyline() {
    ifstream file("ind_1000_2_product.csv");
    string line;
    vector<Item> items;

    // Lewati header
    getline(file, line);

    // Baca file baris per baris
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, priceStr, reviewStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        getline(ss, reviewStr, ',');

        try {
            Item item;
            item.id = stoi(idStr);
            item.name = name;
            item.price = stod(priceStr);
            item.review = stod(reviewStr);
            items.push_back(item);
        } catch (...) {
            continue; // Skip jika ada error parsing
        }
    }

    cout << "Jumlah item yang dibaca: " << items.size() << endl;

    // Jalankan skyline query
    vector<Item> skyline = skylineUsingStackLikeArray(items);

    // Cetak hasil (maksimal 9 baris)
    cout << "Skyline result:\n";
    int count = 0;
    for (const auto& item : skyline) {
        cout << "ID: " << item.id
             << " | " << item.name
             << " | harga: " << item.price
             << " | rating: " << item.review << endl;
        if (++count >= 9) break;
    }
}

int main() {
    auto start = high_resolution_clock::now();

    runSkyline();

    auto end = high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Waktu eksekusi: " << duration.count() << " detik" << endl;

    return 0;
}
```

Dengan Hasil :
```
Jumlah item yang dibaca: 1000
Skyline result:
ID: 109 | product-109 | harga: 8 | rating: 231
ID: 160 | product-160 | harga: 104 | rating: 283
ID: 335 | product-335 | harga: 63 | rating: 263
ID: 351 | product-351 | harga: 23 | rating: 240
ID: 419 | product-419 | harga: 17 | rating: 236
ID: 488 | product-488 | harga: 61 | rating: 257
ID: 947 | product-947 | harga: 28 | rating: 244
ID: 954 | product-954 | harga: 43 | rating: 245
ID: 964 | product-964 | harga: 5 | rating: 195
Waktu eksekusi: 0.010486 detik
```

Dengan menggunakan stack dan 1000 data sebagai inputnya, hasil waktu yang dihasilkan adalah 0.010486 detik.


# Queue

***Dibuat oleh : Fika Arka Nuriyah 5027241071***

Membuat query skyline menggunakan queue dengan 1000 data

Dengan kode:

```C++
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

// Struktur untuk menyimpan data produk
struct Produk {
    int id;
    string nama;
    int harga;    // attr_1 (semakin kecil semakin baik)
    int rating;   // attr_2 (semakin besar semakin baik)
};

// Fungsi untuk membaca data dari file CSV
vector<Produk> bacaData(const string& namaFile) {
    vector<Produk> data;
    ifstream file(namaFile);
    string line;

    // Lewati header
    getline(file, line);

    while (getline(file, line)) {
        size_t pos = 0;
        vector<string> tokens;

        // Pisahkan baris berdasarkan koma
        while ((pos = line.find(',')) != string::npos) {
            tokens.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);

        if (tokens.size() >= 4) {
            Produk p;
            p.id = stoi(tokens[0]);
            p.nama = tokens[1];
            p.harga = stoi(tokens[2]);
            p.rating = stoi(tokens[3]);
            data.push_back(p);
        }
    }

    return data;
}

// Fungsi untuk mengecek apakah produk a mendominasi produk b
bool apakahDominasi(const Produk& a, const Produk& b) {
    return (a.harga <= b.harga && a.rating >= b.rating) && 
           (a.harga < b.harga || a.rating > b.rating);
}

// Fungsi utama skyline query menggunakan queue
vector<Produk> cariSkyline(const vector<Produk>& semuaProduk) {
    queue<Produk> antrian;
    vector<Produk> skyline;

    // Masukkan semua produk ke dalam queue
    for (const auto& p : semuaProduk) {
        antrian.push(p);
    }

    while (!antrian.empty()) {
        Produk saatIni = antrian.front();
        antrian.pop();
        bool didominasi = false;

        // Cek dominasi dengan produk skyline yang sudah ada
        for (const auto& s : skyline) {
            if (apakahDominasi(s, saatIni)) {
                didominasi = true;
                break;
            }
        }

        if (!didominasi) {
            // Hapus produk skyline yang didominasi oleh produk saat ini
            vector<Produk> skylineBaru;
            for (const auto& s : skyline) {
                if (!apakahDominasi(saatIni, s)) {
                    skylineBaru.push_back(s);
                }
            }
            skylineBaru.push_back(saatIni);
            skyline = skylineBaru;
        }
    }

    return skyline;
}

int main() {
    string namaFile = "ind_1000_2_product.csv";

    // Baca data dari file
    vector<Produk> semuaProduk = bacaData(namaFile);

    // Mulai pengukuran waktu
    clock_t mulai = clock();

    // Cari produk skyline
    vector<Produk> hasilSkyline = cariSkyline(semuaProduk);

    // Hitung waktu eksekusi
    clock_t selesai = clock();
    double waktuEksekusi = double(selesai - mulai) / CLOCKS_PER_SEC;

    // Tampilkan hasil
    cout << "Total produk: " << semuaProduk.size() << endl;
    cout << "Produk skyline ditemukan: " << hasilSkyline.size() << endl;
    cout << "Waktu eksekusi: " << waktuEksekusi << " detik\n\n";

    // Tampilkan semua produk skyline
    cout << " Hasil Skyline:\n";
    cout << "ID\tNama\t\tHarga\tRating\n";
    cout << "----------------------------------------\n";

    for (const auto& p : hasilSkyline) {
        cout << p.id << "\t" << p.nama << "\t" << p.harga << "\t" << p.rating << endl;
    }

    return 0;
}

```

output : 

![image](https://github.com/user-attachments/assets/415e2b4b-394e-46a1-971f-6cd16dfdb34b)

Dengan menggunakan stack dan 1000 data sebagai inputnya, hasil waktu yang dihasilkan adalah  0.000252 detik.

# Map

***Dibuat oleh : Zahra Hafizhah 5027241121***

Dengan kode :
```
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>

class Baju {
public:
    int id;
    int harga;
    float ulasan;

    Baju() : id(0), harga(0), ulasan(0.0f) {}
    Baju(int id, int harga, float ulasan) : id(id), harga(harga), ulasan(ulasan) {}
};

class PemilihanBaju {
private:
    std::map<int, Baju> daftarBaju;

public:
    void bacaCSV(const std::string& namaFile) {
        std::ifstream file(namaFile);
        if (!file.is_open()) {
            std::cerr << "Gagal membuka file: " << namaFile << std::endl;
            return;
        }

        std::string baris;
        std::getline(file, baris); // Skip header

        while (std::getline(file, baris)) {
            std::stringstream ss(baris);
            std::string idStr, nama, hargaStr, ulasanStr;

            std::getline(ss, idStr, ',');
            std::getline(ss, nama, ','); // Nama tidak digunakan
            std::getline(ss, hargaStr, ',');
            std::getline(ss, ulasanStr, ',');

            if (idStr.empty() || hargaStr.empty() || ulasanStr.empty()) {
                std::cerr << "[Warning] Data tidak lengkap: " << baris << "\n";
                continue;
            }

            try {
                int id = std::stoi(idStr);
                int harga = std::stoi(hargaStr);
                float ulasan = std::stof(ulasanStr);
                daftarBaju[id] = Baju(id, harga, ulasan);
            } catch (const std::exception& e) {
                std::cerr << "Gagal parsing: " << baris << " (" << e.what() << ")\n";
                continue;
            }
        }

        file.close();
    }

    Baju cariDenganRatingTertinggi() {
        Baju terbaik;
        float maxRating = -1.0f;

        for (const auto& [id, baju] : daftarBaju) {
            if (baju.ulasan > maxRating) {
                maxRating = baju.ulasan;
                terbaik = baju;
            }
        }

        return terbaik;
    }
};

int main() {
    std::string namaFile = "baju.csv";  // Ganti sesuai nama file kamu
    auto mulai = std::chrono::high_resolution_clock::now();

    PemilihanBaju pemilih;
    pemilih.bacaCSV(namaFile);
    Baju terbaik = pemilih.cariDenganRatingTertinggi();

    auto selesai = std::chrono::high_resolution_clock::now();
    auto durasi = std::chrono::duration_cast<std::chrono::nanoseconds>(selesai - mulai).count();

    // Output hasil
    if (terbaik.ulasan > 0) {
        std::cout << "== Baju dengan Rating Tertinggi ==\n";
        std::cout << "ID     : " << terbaik.id << "\n";
        std::cout << "Harga  : " << terbaik.harga << "\n";
        std::cout << "Rating : " << terbaik.ulasan << "\n";
    } else {
        std::cout << "Tidak ada data valid.\n";
    }
    
    // CETAK WAKTU DI LUAR IF agar SELALU tampil
    std::cout << "Waktu komputasi: " << durasi << " nanodetik\n";    

    return 0;
}
```

Dengan hasil

```
== Baju dengan Rating Tertinggi ==
ID     : 160
Harga  : 104
Rating : 283
Waktu komputasi: 17398451 nanodetik
```

Dengan menggunakan map waktu yang dibutuhkan adalah 17398451 nanodetik atau sama dengan 0.0174 detik.
