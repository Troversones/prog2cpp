#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Uzenet {
protected:
    string felado, szoveg;
public:
    Uzenet(const string& f, const string& s) : felado(f), szoveg(s) {}

    virtual string getUzenet() const {
        return felado + ": " + szoveg;
    }

    virtual ~Uzenet() = default;
};

class MeetingMeghivas : public Uzenet {
    unsigned idopont;
public:
    MeetingMeghivas(const string& f, const string& s, unsigned i)
        : Uzenet(f, s), idopont(i) {}

    string getUzenet() const override {
        return Uzenet::getUzenet() + ", " + to_string(idopont);
    }
};

class TitkosUzenet : public Uzenet {
    bool titkositva;
public:
    TitkosUzenet(const string& f, const string& s, bool t)
        : Uzenet(f, s), titkositva(t) {}

    string getUzenet() const override {
        if (!titkositva)
            return Uzenet::getUzenet();
        string str;
        str.append(felado.length(), '*');
        str += ": ";
        str.append(szoveg.length(), '*');
        return str;
    }

    bool getTitkositva() const {
        return titkositva;
    }

    bool& getTitkositva() {
        return titkositva;
    }
};

class Postafiok {
    vector<Uzenet*> uzenetek;

public:
    Postafiok() = default;

    ~Postafiok() {
        for (auto u : uzenetek)
            delete u;
    }

    Postafiok(const Postafiok& other) {
        for (auto u : other.uzenetek)
            uzenetek.push_back(new Uzenet(*u));
    }

    Postafiok& operator=(const Postafiok& other) {
        if (this == &other) return *this;

        for (auto u : uzenetek)
            delete u;
        uzenetek.clear();

        for (auto u : other.uzenetek)
            uzenetek.push_back(new Uzenet(*u));

        return *this;
    }

    Postafiok& operator<<(Uzenet* u) {
        uzenetek.push_back(u);
        return *this;
    }

    void kiir() const {
        for (const auto& u : uzenetek) {
            cout << u->getUzenet() << endl;
        }
    }

    friend ostream& operator<<(ostream& os, const Postafiok& p) {
        for (const auto& u : p.uzenetek) {
            os << u->getUzenet() << endl;
        }
        return os;
    }

    Postafiok& operator>>(int n) {
        while (n-- > 0 && !uzenetek.empty()) {
            Uzenet* u = uzenetek.back();
            cout << u->getUzenet() << endl;
            delete u;
            uzenetek.pop_back();
        }
        return *this;
    }

    Postafiok& operator<<(const Postafiok& other) {
        for (const auto& u : other.uzenetek) {
            auto titkos = dynamic_cast<TitkosUzenet*>(u);
            if (!titkos || !titkos->getTitkositva()) {
                uzenetek.push_back(new Uzenet(*u));
            }
        }
        return *this;
    }
};

#ifndef TEST_BIRO
int main() {
    Uzenet* u = new Uzenet("TO", "valami ....");
    cout << u->getUzenet() << endl << endl;

    TitkosUzenet* tu = new TitkosUzenet("TO", "valami ....", false);
    cout << tu->getUzenet() << endl << endl;

    tu->getTitkositva() = true;
    cout << tu->getUzenet() << endl << endl;

    MeetingMeghivas* m = new MeetingMeghivas("P2", "surgosen segiteni kell", 4);
    cout << m->getUzenet() << endl << endl;

    Postafiok p;
    p << u << tu << m;
    cout << p << endl;

    Postafiok p2, p3;
    for (unsigned i = 0; i < 5; ++i)
        p2 << new Uzenet("felado " + to_string(i), "valami uzenet")
           << new MeetingMeghivas("partner " + to_string(i), "valami meeting", i)
           << new TitkosUzenet("titkos rajongo " + to_string(i), "titkos uzenet", i % 2);

    p3 << p2;
    p2 >> 15;
    cout << endl;
    p3 >> 25;
}
#endif
