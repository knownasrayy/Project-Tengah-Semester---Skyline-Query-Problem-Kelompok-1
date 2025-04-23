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
