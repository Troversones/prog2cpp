#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * ZeneLejatszo osztaly, melynek van egy gyartoja, alapból 0 zenét képes lejátszani és új zenét nem lehet hozzáadni.
 */
class ZeneLejatszo {
protected:
  std::string _gyarto;
public:
  ZeneLejatszo( std::string gyarto ) : _gyarto ( gyarto ) {}

  operator std::string () const {
    return _gyarto;
  }

  virtual unsigned szamok() const { return 0; }

  virtual void lejatszas() const {
    cout << "Zene lejatszasa" << endl;
  }

  virtual ZeneLejatszo& operator += ( const std::string& zeneszam ) {
    throw "Nem tamogatott muvelet";
  }

  virtual ~ZeneLejatszo() = default;
};

/**
 * MP3Lejatszo osztály, amely a ZeneLejatszo osztályból származik.
 */
class MP3Lejatszo : public ZeneLejatszo {
private:
    std::vector<std::string> lejatszasiLista;

public:
    MP3Lejatszo(const std::string& gyarto) : ZeneLejatszo(gyarto) {}

    MP3Lejatszo& operator+=(const std::string& zeneszam) override {
        lejatszasiLista.push_back(zeneszam);
        return *this;
    }

    unsigned szamok() const override {
        return lejatszasiLista.size();
    }

    void lejatszas() const override {
        for (const auto& zene : lejatszasiLista) {
            std::cout << "Aktualis: " << zene << std::endl;
        }
    }
};

/**
 * Ember osztály, amely polimorfikusan kezeli a ZeneLejatszo példányokat.
 */
class Ember {
private:
    std::vector<ZeneLejatszo*> lejatszok;

public:
    ~Ember() {
        for (auto* lejatszo : lejatszok) {
            delete lejatszo;
        }
    }

    Ember& operator<<(ZeneLejatszo* ujLejatszo) {
        lejatszok.push_back(ujLejatszo);
        return *this;
    }

    void operator!() const {
        for (const auto* lejatszo : lejatszok) {
            lejatszo->lejatszas();
        }
    }

    ZeneLejatszo& operator~() const {
        if (lejatszok.empty()) {
            throw 0;
        }

        return **std::max_element(lejatszok.begin(), lejatszok.end(),
            [](const ZeneLejatszo* a, const ZeneLejatszo* b) {
                return a->szamok() < b->szamok();
            });
    }

    void add(const std::string& zeneszam) {
        for (auto* lejatszo : lejatszok) {
            try {
                if (lejatszo->szamok() < 5) {
                    *lejatszo += zeneszam;
                }
            } catch (...) {
                // Ha egy lejátszó nem támogatja a hozzáadást, figyelmen kívül hagyjuk
            }
        }
    }
};

#ifndef TEST_BIRO
int main() {
    ZeneLejatszo* zl = new ZeneLejatszo("zl");
    MP3Lejatszo* mp3 = new MP3Lejatszo("mp3");

    try {
        *mp3 += "1";
        *mp3 += "2";
    } catch (const char* e) {
        std::cerr << e << std::endl;
    }

    Ember ember;
    ember << zl;
    ember << mp3;

    // Az összes lejátszó zenéinek kiírása
    !ember;

    // A legtöbb zenével rendelkező lejátszó lejátszása
    try {
        (~ember).lejatszas();
    } catch (int) {
        std::cerr << "Nincs lejátszó!" << std::endl;
    }

    // Új zeneszám hozzáadása
    ember.add("3");

    // Az összes lejátszó zenéinek ismételt kiírása
    !ember;

    return 0;
}
#endif
