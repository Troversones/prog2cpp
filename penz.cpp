#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class Penz {
protected:
    unsigned ertek;

public:
    Penz(unsigned e) : ertek(e) {}
    virtual ~Penz() = default;

    unsigned getErtek() const { return ertek; }

    virtual string toString() const = 0;
};

class Erme : public Penz {
    string anyag;
    unsigned atmero;

public:
    Erme(unsigned e, const string& a, unsigned at) : Penz(e), anyag(a), atmero(at) {}

    string toString() const override {
        return anyag + ":" + to_string(atmero);
    }
};

class Bankjegy : public Penz {
    string abra;

public:
    Bankjegy(unsigned e, const string& a) : Penz(e), abra(a) {}

    string toString() const override {
        return abra;
    }
};

class Penztarca {
    vector<unique_ptr<Penz>> penzek;

public:
    Penztarca() = default;

    Penztarca(const Penztarca& other) {
    for (const auto& p : other.penzek) {
        if (auto e = dynamic_cast<Erme*>(p.get())) {
            penzek.push_back(make_unique<Erme>(*e));
        } else if (auto b = dynamic_cast<Bankjegy*>(p.get())) {
            penzek.push_back(make_unique<Bankjegy>(*b));
        }
        }
    }

    Penztarca& operator=(const Penztarca& other) {
        if (this == &other) return *this;

        penzek.clear();
        for (const auto& p : other.penzek) {
            if (auto e = dynamic_cast<Erme*>(p.get())) {
                penzek.push_back(make_unique<Erme>(*e));
            } else if (auto b = dynamic_cast<Bankjegy*>(p.get())) {
                penzek.push_back(make_unique<Bankjegy>(*b));
            }
        }
        return *this;
    }

    Penztarca& operator<<(const Penz& p) {
        if (auto e = dynamic_cast<const Erme*>(&p)) {
            penzek.push_back(make_unique<Erme>(*e));
        } else if (auto b = dynamic_cast<const Bankjegy*>(&p)) {
            penzek.push_back(make_unique<Bankjegy>(*b));
        }
        return *this;
    }

    unsigned osszeg() const {
        unsigned sum = 0;
        for (const auto& p : penzek) {
            sum += p->getErtek();
        }
        return sum;
    }

    void kiszor() {
        auto it = remove_if(penzek.begin(), penzek.end(), [](const unique_ptr<Penz>& p) {
            return dynamic_cast<Erme*>(p.get()) != nullptr;
        });
        penzek.erase(it, penzek.end());
    }

    friend ostream& operator<<(ostream& os, const Penztarca& pt) {
        for (const auto& p : pt.penzek) {
            os << p->toString() << endl;
        }
        return os;
    }
};

#ifndef TEST_BIRO
int main() {
    Penztarca pt;
    pt << Erme(100, "arany", 20) << Bankjegy(5000, "Szent Istvan") << Erme(50, "ezust", 15);
    cout << pt;
    cout << "Osszeg: " << pt.osszeg() << endl;

    pt.kiszor();
    cout << "Kiszoritas utan:" << endl << pt;
}
#endif
