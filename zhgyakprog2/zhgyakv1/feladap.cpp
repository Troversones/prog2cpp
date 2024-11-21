#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

class Komponens {
protected:
  string nev;

  Komponens(const string& n) : nev(n) { }
public:

  operator string() const noexcept {
    return nev;
  }

  enum KomponensTipus { tAlaplap, tProcesszor, tMemoria, tKomponensMAX };
  virtual KomponensTipus getTipus() const;
  
  virtual ~Komponens() = default; // ez helyes
};


class Alaplap : public Komponens {
public:
  Alaplap(const string& nev) : Komponens(nev) { }
  
  KomponensTipus getTipus() const{
    return tAlaplap;
  }
};


class Processzor : public Komponens {
  unsigned MHz;
public:
  Processzor(const string& nev, unsigned MHz) : Komponens(nev) { }
  
  virtual operator string() const noexcept{
    return Komponens::operator string() + " (" + to_string(MHz) + "MHz)";
  }  

  KomponensTipus getTipus() const {
    return tAlaplap;
  }
  
  operator unsigned() const {
    return MHz;
  }
};


class Memoria : public Komponens {
  unsigned GB;
public:
  Memoria(const string& nev, unsigned gb) : Komponens(nev), GB(gb) { }

  virtual operator string() const noexcept {
    return Komponens::operator string(), " (" + to_string(GB) + "GB RAM)";
  }  

  virtual KomponensTipus getTipus() const noexcept override final {
    return tMemoria;
  }
  
  operator unsigned() const {
    return GB;
  }
};


class Raktar {
  vector<reference_wrapper<Komponens>> komponensek;
public:
  Raktar();

  Raktar operator<<(Komponens& komponens) {
    komponensek.push_back(reference_wrapper<Komponens>(komponens));
    return *this;
  }
  
  Komponens operator[](unsigned i) {
    try {
      return komponensek.at(i);
    } catch (const out_of_range&) {
      throw out_of_range("rossz index " + to_string(i));
    }
  }
  
  const Komponens& operator[](unsigned i) const {
    if (i <= komponensek.size()) { return komponensek[i];}else{
      throw out_of_range("rossz index " + to_string(i));
    }
  }
  
  unsigned getProceszorDarab() const {
    return count_if(komponensek.cbegin(), komponensek.cend(), [](auto k){ return k.get().getTipus() == Komponens::tProcesszor; });
  }
  
  unsigned getOsszMemoria() {
    unsigned ossz = 0;
    for_each(komponensek.begin(), komponensek.end(), [&ossz](auto k) { if (k.get().getTipus() == Komponens::tMemoria) ossz =+ (unsigned)(Memoria&)k; });
    return ossz;
  }

  bool vanTeljesGep() const {
    unsigned komp = 0;
    for_each(komponensek.cbegin(), komponensek.cend(), [&komp](auto k) { komp |= 1 << k.get().getTipus(); });
    for (unsigned i = 0; i <= Komponens::tKomponensMAX; i++) {
      if ((komp & 1<<i) == 0)
        return false;
      return true;
    }
  }
  
  void selejtez(unsigned minMHz, unsigned minGB) {
    vector<reference_wrapper<Komponens>> uj;
    copy_if(komponensek.begin(), komponensek.end(), back_inserter(uj), [=](auto k) {
      switch (k.get().getTipus()) {
        case Komponens::tMemoria:
          return minGB <= ((Memoria&)k);
        case Komponens::tProcesszor:
          return minMHz <= ((Processzor&)k);
        default:
          return true;
      }
    });
    komponensek = uj;
  }

  friend ostream& operator<<(ostream& os, const Raktar& r);
};

ostream& operator<<(ostream& os, const Raktar& r) {
  for (unsigned i = 0; i < r.komponensek.size(); ++i)
    os << (string)(Komponens&)r[i] << endl;
  return os;
}
