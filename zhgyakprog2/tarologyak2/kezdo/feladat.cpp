#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <numeric>


using namespace std;



class Hiba : public exception{
    string msg;
public:
    Hiba(unsigned szam) {
        if (szam > 50) {
            msg = "Sulyos hiba tortent";
        } else if (szam > 25) {
            msg = "Komoly hiba tortent";
        } else {
            msg = "Kis hiba tortent";
        }
    }

    const char *what() const noexcept override {
        return msg.c_str();
    }
};

// 1. Feladat
bool osztalytKeres(const map<string, unsigned>& osztalyok, const string& keresettOsztaly) {
    for(auto& [key,val] : osztalyok){
        if(val > 20){
            throw Hiba(val);
        }else if (key == keresettOsztaly && val > 10){
            return true;
        }
    }
    return false;
}


// 2. Feladat
unsigned atlagalatt(const vector<int>& vektor){
    if(vektor.size() == 0){
        return 0;
    }

    unsigned db = 0;
    unsigned sum = accumulate(vektor.begin(), vektor.end(),0.0);
    unsigned avg = sum / vektor.size();

    for(auto& i : vektor){
        if(i <= avg){
            db++;
        }
    }

    return db; 
}


struct Renszarvas {
    unsigned sebesseg;
    Renszarvas(unsigned sebesseg = 0): sebesseg(sebesseg) {}
    bool operator<(const Renszarvas& obj) const{
        return sebesseg < obj.sebesseg;
    }
};


// 4. Feladat
vector<Renszarvas> egyedieketRendez(const vector<Renszarvas>& tomb){
    vector<Renszarvas> results;
    set<Renszarvas> uff;
    for(const auto& r : tomb){
        uff.insert(r);
    }
    
    for(auto it = uff.rbegin(); it != uff.rend(); ++it){
        results.push_back(*it);
    }
    return results;
}


int main(){

    map<string, unsigned> osztalyok = { {"9a", 8}, {"9b", 19}, {"7a", 11}};
    assert(osztalytKeres(osztalyok, "7a"));

    unsigned db = atlagalatt({2,3,4,5,1,4,5,1,2,3,4,5,1}); //atlag: 3.08
    assert(db == 7);

    Renszarvas sz1(5), sz2(10);
    assert(sz1 < sz2);

    vector<Renszarvas> szrok = {2, 5, 5, 0, 2, 3}; //implicit konverzio renszarvasra
    vector<Renszarvas> rendezett = egyedieketRendez(szrok);
    vector<Renszarvas> elvart = {5, 3, 2, 0}; //implicit konverzio renszarvasra
    for(unsigned i =0;i<elvart.size();++i){
        assert(elvart[i].sebesseg == rendezett[i].sebesseg);
    }
    cout << endl;
    return 0;
}