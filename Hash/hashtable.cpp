#include <iostream>
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <set>
#include <memory>

struct Product {
    int id;
    std::string label;
    int price;
    int review;

    Product(int id = 0, std::string label = "", int price = 0, int review = 0)
        : id(id), label(label), price(price), review(review) {}
};

class SkylineQuery {
public:
    virtual void loadData(const std::string& filename) = 0;
    virtual std::list<Product> computeSkyline() = 0;
    virtual ~SkylineQuery() {}
};

class CSVReader {
public:
    std::unordered_map<int, Product> readCSV(const std::string& filename) {
        std::ifstream file(filename);
        std::unordered_map<int, Product> data;
        std::string line;
        getline(file, line); 

        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string id_str, label, price_str, review_str;
            getline(ss, id_str, ',');
            getline(ss, label, ',');
            getline(ss, price_str, ',');
            getline(ss, review_str, ',');

            int id = std::stoi(id_str);
            int price = std::stoi(price_str);
            int review = std::stoi(review_str);

            Product p(id, label, price, review);
            data[id] = p;
        }
        return data;
    }
};

class SkylineUnorderedMap : public SkylineQuery {
private:
    std::unordered_map<int, Product> products;

public:
    void loadData(const std::string& filename) override {
        CSVReader reader;
        products = reader.readCSV(filename);
    }

    std::list<Product> computeSkyline() override {
        std::list<Product> skyline;
        std::set<std::pair<int, int>> seen;

        for (const auto& [id1, p] : products) {
            bool dominated = false;
            for (const auto& [id2, q] : products) {
                if (id1 == id2) continue;

                bool allBetterOrEqual = q.price <= p.price && q.review >= p.review;
                bool atLeastOneBetter = q.price < p.price || q.review > p.review;

                if (allBetterOrEqual && atLeastOneBetter) {
                    dominated = true;
                    break;
                }
            }
            if (!dominated) {
                auto key = std::make_pair(p.price, p.review);
                if (seen.count(key) == 0) {
                    skyline.push_back(p);
                    seen.insert(key);
                }
            }
        }
        return skyline;
    }
};

int main() {
    std::unique_ptr<SkylineQuery> query = std::make_unique<SkylineUnorderedMap>();

    std::string filename = "file.csv";
    query->loadData(filename);

    auto start = std::chrono::high_resolution_clock::now();
    std::list<Product> result = query->computeSkyline();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Skyline products using unordered_map:\n";
    for (const auto& p : result) {
        std::cout << p.label << " (Price: " << p.price << ", Review: " << p.review << ")\n";
    }
    std::cout << "Computation time: " << duration.count() << " seconds\n";

    return 0;
}
