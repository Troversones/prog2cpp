#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Gyerek {
  int boldogsag = 0;
public:
  int getBoldogsag() const {
    return boldogsag;
  }

  Gyerek& setBoldogsag( int b ) {
    boldogsag = b; return *this;
  }
};

class Ajandek {
protected:
  string uzenet;


public:

  Ajandek(const string& u) : uzenet(u) { }

  virtual ~Ajandek()=default;

  virtual void ajandekoz(Gyerek& gy) const {
    cout << uzenet << endl;
  }

  virtual Ajandek* clone() const=0;

  virtual unsigned getTipus() const=0;
};

class Vonat : public Ajandek {
  int boldogsag;
public:
  Vonat(const string& u, unsigned b) : Ajandek(u), boldogsag(b) { }

  void ajandekoz(Gyerek& gy) const override{
    cout << uzenet << endl;
    gy.setBoldogsag(boldogsag);
  }

  Vonat* clone( )const {
    return new Vonat(*this);
  }

  unsigned getTipus() const override {
    return 1;
  }

};

class Virgacs : public Ajandek {
public:
  Virgacs() : Ajandek("jaj") { }

  void ajandekoz(Gyerek& gy) const override{
    cout << uzenet << endl;
    if(gy.getBoldogsag()>0) {
      gy.setBoldogsag(gy.getBoldogsag()/2);
    }
    else {
      gy.setBoldogsag(gy.getBoldogsag()*2);
    }

  }

  Virgacs* clone() const {
    return new Virgacs(*this);
  }

  unsigned getTipus() const override {
    return 2;
  }

};

class Mikulas {
protected:
  vector<Ajandek*> ajandekok;

  unsigned hanyadik=0;


public:
  Mikulas()=default;

  ~Mikulas() {
    for(auto ajandek:ajandekok) {
      delete ajandek;
    }
    ajandekok.clear();
  }

  Mikulas(const Mikulas& masik):hanyadik(masik.hanyadik){
    for(auto ajandek:masik.ajandekok) {
      ajandekok.push_back(ajandek->clone());
    }
  }

  Mikulas& operator=(const Mikulas& masik) {
    if(this==&masik) {
      return *this;
    }

    for(auto ajandek:ajandekok) {
      delete ajandek;
    }
    ajandekok.clear();

    hanyadik=masik.hanyadik;
    for(auto ajandek:masik.ajandekok) {
      ajandekok.push_back(ajandek->clone());
    }
    return *this;

  }



  Mikulas& operator<<(const Ajandek* ajandek) {
    ajandekok.push_back(ajandek->clone());
    return *this;
  }

  Mikulas& operator>>(Gyerek& gy) {
    if(hanyadik==ajandekok.size()) {
      hanyadik=0;
    }
    ajandekok[hanyadik]->ajandekoz(gy);
    hanyadik++;
    return *this;
  }


  void operator^(const Ajandek* a) {
    ajandekok.erase(
      remove_if(ajandekok.begin(), ajandekok.end(), [&](Ajandek* aj) {
        if (a->getTipus() == aj->getTipus()) {
          delete aj;
          return true;
        }
      return false;
    }),
    ajandekok.end());
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
  
  virgacs.ajandekoz(kisfiu);
  cout << kisfiu.getBoldogsag() << endl << endl;
  // jaj
  // -20
  
  tgv.ajandekoz(kisfiu);
  cout << kisfiu.getBoldogsag() << endl << endl;
  // TGV
  // 100
  
  Mikulas mikulas;
  mikulas << &kisvasut << &virgacs;
  mikulas >> kisfiu;
  cout << kisfiu.getBoldogsag() << endl << endl;
  // Kisvasut
  // 2
  
  mikulas >> kisfiu;
  cout << kisfiu.getBoldogsag() << endl << endl;
  // jaj
  // 1
  
  mikulas >> kisfiu;
  cout << kisfiu.getBoldogsag() << endl << endl;
  // Kisvasut
  // 2

  Mikulas mikulas2 = mikulas;
  mikulas2 >> kisfiu;
  cout << kisfiu.getBoldogsag() << endl << endl;
  // jaj
  // 1

  mikulas^&tgv;
  mikulas >> kisfiu;
  cout << kisfiu.getBoldogsag() << endl << endl;
  // jaj
  // 0

  mikulas >> kisfiu;
  cout << kisfiu.getBoldogsag() << endl << endl;
  // jaj
  // 0

}

#endif
