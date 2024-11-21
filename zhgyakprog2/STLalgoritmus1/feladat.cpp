#include<algorithm>
#include<iostream>
#include<map>
#include<set>
#include<string>
#include<vector>

using namespace std;

#ifndef TEST_BIRO
  #define TEST_KEDVENC_SZAMOK
  #define TEST_UVEGGOLYOK
  #define TEST_UTICELOK
  //#define TEST_NAGY_KEZDOBETU
  //#define TEST_PENZVALTAS
#endif // TEST_BIRO


#ifdef TEST_KEDVENC_SZAMOK

// IDE DOLGOZZ!!!
int kedvenc_szamok(vector<int>& container, vector<int>& favourites) {
  int count = 0;

  for (int szam : container) {
    string tmp = std::to_string(szam);

    if (tmp.size() >= 2 && tmp.substr(tmp.size() - 2) == "13") {
      favourites.push_back(szam);
      count++;
    }
  }
  return count;
}

#ifndef TEST_BIRO
void test_kedvenc_szamok() {
  vector<int> sz { 18, 13, 813, 1313, 9, 44, 42, 113, 131 };
  vector<int> k;
  cout << kedvenc_szamok(sz, k) << "db kedvenc szam van" << endl;
  for (int i : k)
    cout << i << endl;

  // kimenet
  // 4
  // 13
  // 813
  // 1313
  // 113
}
#endif // TEST_BIRO
#endif // TEST_KEDVENC_SZAMOK


#ifdef TEST_UVEGGOLYOK

// IDE DOLGOZZ!!!
map<string, int> uveggolyok_osszeszamolasa(const vector<string>& szinek){
  map<string, int> ret;
  for(auto &i : szinek){
    if(ret.find(i) == ret.end()){
      ret.insert(pair<string, int>(i,1));
    }else{
      ret[i]++;
    }
  }
  return ret;
}

#ifndef TEST_BIRO
void test_uveggolyok_osszeszamolasa() {
  string s[] = { "piros", "kek", "zold", "sarga", "fekete", "feher" };
  
  cout << "az uveggolyok rendezve es osszeszamolva:" << endl;
  for (auto &[szin, db] : uveggolyok_osszeszamolasa( { s[0], s[2], s[2], s[1], s[3], s[4], s[2], s[0], s[5], s[4], s[5], s[5] } ) )
    cout << szin << " : " << db << endl;
}
#endif // TEST_BIRO
#endif // TEST_UVEGGOLYOK


#ifdef TEST_UTICELOK

void utazas(map<string, unsigned>& varos, const vector<unsigned>& nyeremeny, map<unsigned /* nyeremeny */, unsigned /* uticelok szama */>& uticelok_szama) {
  // IDE DOLGOZZ!!!
  for (auto& prizeMoney : nyeremeny) {
    unsigned count = 0;

    for (const auto& [cityName, travelCost] : varos) {
      if (travelCost <= prizeMoney) {
        count++;
      }
    }
    uticelok_szama[prizeMoney] = count;
  }
}

#ifndef TEST_BIRO
void test_utazas() {
  map<string, unsigned> varos {
    { "Budapest",  160 },
    { "New York", 7150 },
    { "London",   1590 },
    { "Berlin",    850 }
  };
  vector<unsigned> nyeremeny { 200, 1000, 3000, 4000 };
  map<unsigned, unsigned> hova;
  utazas(varos, nyeremeny, hova);

  for (const auto& [tav, db] : hova)
    cout << tav << " " << db << endl;
  
  // kimenet
  // 200 1
  // 1000 2
  // 3000 3
  // 4000 3
}
#endif // TEST_BIRO
#endif // TEST_UTICELOK


#ifdef TEST_NAGY_KEZDOBETU

// IDE DOLGOZZ!!!

#ifndef TEST_BIRO
void test_nagy_kezdobetuk() {
  cout << nagy_kezdobetuk( { "Alma", "Korte", "barack, Sargabarack", "szilva", "Dio" } ) << endl;
  
  // kimenet
  // 3
}
#endif // TEST_BIRO
#endif // TEST_NAGY_KEZDOBETU


#ifdef TEST_PENZVALTAS

// IDE DOLGOZZ!!!

#ifndef TEST_BIRO
void test_penzvaltas() {
  cout << penzvaltas({ 5 }) << endl;
  cout << penzvaltas({ 5, 10 }) << endl;
  cout << penzvaltas({ 5, 17, 102 }) << endl;
  cout << penzvaltas({ 5, 17, 102, 1000 }) << endl;
  
  // kiement
  // 5
  // 6
  // 16
  // 26
}
#endif // TEST_BIRO
#endif // TEST_PENZVALTAS


#ifndef TEST_BIRO

int main() {
#ifdef TEST_KEDVENC_SZAMOK  
  test_kedvenc_szamok();
#endif // TEST_KEDVENC_SZAMOK

#ifdef TEST_UVEGGOLYOK
  test_uveggolyok_osszeszamolasa();
#endif // TEST_UVEGGOLYOK
  
#ifdef TEST_UTICELOK
  test_utazas();
#endif // TEST_UTICELOK

#ifdef TEST_NAGY_KEZDOBETU
  test_nagy_kezdobetuk();
#endif // TEST_NAGY_KEZDOBETU

#ifdef TEST_PENZVALTAS
  test_penzvaltas();
#endif // TEST_PENZVALTAS
  
  return 0; 
}

#endif // TEST_BIRO
