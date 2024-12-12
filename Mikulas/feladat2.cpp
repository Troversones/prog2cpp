#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Gyerek {
protected:
  int boldogsag = 0;
  string nev = "gyerek";
public:
  Gyerek() = default;

  Gyerek(const string& n) : nev(n) { }

  int getBoldogsag() const {
    return boldogsag;
  }

  Gyerek& setBoldogsag( int b ) {
    boldogsag = b;
    return *this;
  }

  const string& getNev() const {
    return nev;
  }

  ~Gyerek() = default;
};


class Ajandek {
protected:
  string uzenet;
public:
  Ajandek(const string& u) : uzenet(u) { }

  virtual void ajandekoz(Gyerek& gy) const {
    cout << uzenet << endl;
  }

  virtual ~Ajandek() = default;

  virtual Ajandek* clone() const {
    return new Ajandek(*this);
  }
};

class Vonat : public Ajandek {
  int boldogsag;
public:
  Vonat(const string& u, unsigned b) : Ajandek(u), boldogsag(b) { }

  Ajandek* clone() const override {
    return new Vonat(*this);
  }

  void ajandekoz(Gyerek &gy) const override {
    cout << uzenet << endl;
    gy.setBoldogsag(boldogsag);
  }
};

class Virgacs : public Ajandek {
public:
  Virgacs() : Ajandek("jaj") { }

  Ajandek* clone() const override {
    return new Virgacs(*this);
  }

  void ajandekoz(Gyerek &gy) const override {
    cout << uzenet << endl;
    if(gy.getBoldogsag() > 0) {
      gy.setBoldogsag(gy.getBoldogsag() / 2);
    }
    else {
      gy.setBoldogsag(gy.getBoldogsag() * 2);
    }
  }
};

class Mikulas {
  set<string> nevek;
  vector<Ajandek*> ajandekok;

public:
  Mikulas() = default;

  Mikulas& operator <<(const Ajandek& a) {
    this->ajandekok.push_back(a.clone());
    return *this;
  }

  Mikulas& operator>>(Gyerek& gy) {
    if (!ajandekok.empty() && !nevek.contains(gy.getNev())) {
            auto* lastAjandek = ajandekok.back();
            lastAjandek->ajandekoz(gy);

            delete lastAjandek;
            ajandekok.pop_back();

            nevek.insert(gy.getNev());
        }

        return *this;
  }

  Mikulas& operator <<(const Mikulas& m) {
    for(unsigned i = 0; i < m.ajandekok.size(); i++) {
      ajandekok.push_back(m.ajandekok[i]->clone());
    }
    for(auto& e : m.nevek) {
      nevek.insert(e);
    }

    return *this;
  }

  ~Mikulas() {
    for(unsigned i = 0; i < ajandekok.size(); i++) {
      delete ajandekok[i];
    }
    ajandekok.clear();

    nevek.clear();
  }
};


#ifndef TEST_BIRO

int main() {
  Vonat mav( "MAV vonat", -10 );
  Vonat tgv( "TGV", 100 );
  Vonat kisvasut( "Kisvasut", 2 );
  Virgacs virgacs;

  Gyerek kisfiu;
  cout << kisfiu.getBoldogsag() << endl << endl;
  // 0

  mav.ajandekoz(kisfiu);
  cout << kisfiu.getBoldogsag() << endl << endl;
  // MAV vonat
  // -10
  // 100

  Mikulas miki;
  miki >> kisfiu;
  miki << mav << tgv << kisvasut;
  miki >> kisfiu;
  cout << kisfiu.getBoldogsag() << endl << endl;
  // Kisvasut
  // 2

  Mikulas m2;
  m2 << miki;
  m2 >> kisfiu;

  Gyerek gy2("..");
  m2 >> gy2;
  // TGV
}

#endif