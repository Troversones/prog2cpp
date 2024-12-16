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
    //bovitheto
  }

};

class Zene{
protected:
  string nev;
public:
  Zene(const string& n):nev(n){}
  const string& getNev() const { return nev; }
  operator string() const { return ""; }
  virtual mufaj getMufaj() const = 0;
};

class Nepdal: public Zene{
  string nepcsoport;
public:
  Nepdal(const string& n, const string& ncs): Zene(n), nepcsoport(ncs){}
  operator string() const {
    return nev + "(" + nepcsoport + ")";
  }

};

class Klasszikus: public Zene{
  string eloado;
  string szerzo;

public:
  Klasszikus(const string& n, const string& eloado, const string& sz): Zene(n), eloado(eloado), szerzo(sz){

  }

};




int main(){
  /*Ember e1("Kovacs Bela", {klasszikus});

  Klasszikus k("Zvonicei harangok", "Szegedi szimfonikus zenekar","Dvorak");
  Klasszikus k2("Kis Eji zene", "Nemzeti filhamonikus zenekar","Mozart");

  Nepdal n1("Kerek vilag", "moldvai csangok");


  Zenegep zg;

  zg << &k << &n1 << &k2;

  zg.kiir();

  zg >> e1;
  zg >> e1;
  zg >> e1;
  zg >> e1;*/
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



