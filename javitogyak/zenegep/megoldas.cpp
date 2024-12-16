#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

enum mufaj{
  klasszikus, nepdal
};

class Ember {
  set<mufaj> izles;
  string nev;


public:
  set<string> meghalgatott;
  const set<mufaj> &getIzles() const {
    return izles;
  }

  const string &getNev() const {
    return nev;
  }

  Ember(const string& nev, const set<mufaj>& i):izles(i), nev(nev){
  }

  void hallgat(const string& mit){
    cout << nev << " zenet hallgat: " << mit << endl;

  }

  [[nodiscard]] set<string> get_meghalgatott() const {
    return meghalgatott;
  }
};

class Zene{
protected:
  string nev;
public:
  Zene(const string& n):nev(n){}
  const string& getNev() const { return nev; }
  virtual operator string() const { return ""; }
  virtual mufaj getMufaj() const = 0;
  virtual Zene* clone() const = 0;

  virtual ~Zene() = default;
};

class Nepdal: public Zene{
  string nepcsoport;
public:
  Nepdal(const string& n, const string& ncs): Zene(n), nepcsoport(ncs){}

  [[nodiscard]] mufaj getMufaj() const override {
    return mufaj::nepdal;
  }
  operator string() const override {
    return nev + "(" + nepcsoport + ")";
  }
  Zene* clone() const override {
    return new Nepdal(*this);
  }

  ~Nepdal() override = default;
};

class Klasszikus: public Zene{
  string eloado;
  string szerzo;

public:
  Klasszikus(const string& n, const string& eloado, const string& sz): Zene(n), eloado(eloado), szerzo(sz){

  }
  operator string() const override {
    return eloado + ":" + nev + "(" +szerzo + ")";
  }
  Zene* clone() const override {
    return new Klasszikus(*this);
  }
  [[nodiscard]] mufaj getMufaj() const override {
    return mufaj::klasszikus;
  }

  ~Klasszikus() override = default;
};
class Zenegep {
  vector<Zene*> zenek;
public:
  ~Zenegep() {
    for(auto* zene : zenek) {
        delete zene;
    }
    zenek.clear();
  }
  Zenegep() = default;

  Zenegep(const Zenegep& z) {
    for (const auto* xd : z.zenek) {
      zenek.push_back(xd->clone());
    }
  }

  Zenegep& operator<<(const Zene* zene) {
    zenek.push_back(zene->clone());
    return *this;
  }
  Zenegep& operator=(const Zenegep& z) {
    if(this==&z) {
      return *this;
    }
    for(auto *zs : zenek) {
      delete zs;
    }
    zenek.clear();

    for(const auto* zs : z.zenek) {
      zenek.push_back(zs->clone());
    }
    return *this;
  }

  void kiir() const {
    for (const Zene* zene : zenek) {
    string asd = *zene;
        cout << asd << endl;
    }
  }

  Zenegep& operator>>(Ember& ember) {
    unsigned db = 0;
    for (const Zene* zene : zenek) {
      string asd = *zene;
      if(ember.getIzles().contains(zene->getMufaj()) && !ember.get_meghalgatott().contains(asd) ){
          ember.hallgat(asd);
          ember.meghalgatott.insert(asd);
          db++;
          break;
      }
    }
    if(db == 0) {
      cout << ember.getNev() + " unatkozik" << endl;
    }
    return *this;
  }




};



int main(){
  Ember e1("Kovacs Bela", {klasszikus});

  Klasszikus k("Zvonicei harangok", "Szegedi szimfonikus zenekar","Dvorak");
  Klasszikus k2("Kis Eji zene", "Nemzeti filhamonikus zenekar","Mozart");

  Nepdal n1("Kerek vilag", "moldvai csangok");


  Zenegep zg;

  zg << &k << &n1 << &k2;

  zg.kiir();

  zg >> e1;
  zg >> e1;
  zg >> e1;
  zg >> e1;
  return 0;

  //Elvart output:

  //Tarolt zenek:
  //Szegedi szimfonikus zenekar:Zvonicei harangok(Dvorak)
  //Kerek vilag(moldvai csangok)
  //Nemzeti filhamonikus zenekar:Kis Eji zene(Mozart)
  //Kovacs Bela zenet hallgat: Szegedi szimfonikus zenekar:Zvonicei harangok(Dvorak)
  //Kovacs Bela zenet hallgat: Nemzeti filhamonikus zenekar:Kis Eji zene(Mozart)
  //Kovacs Bela unatkozik
  //Kovacs Bela unatkozik

}



