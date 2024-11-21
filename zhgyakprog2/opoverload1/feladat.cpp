#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Allat {
    string nev;
    unsigned jollakott; 
public:
    Allat(string nev = "allat", unsigned jollakott = 10): nev(nev), jollakott(jollakott){}

    const string& getNev() const{
        return nev;
    }

    bool operator!() const{
        return jollakott;
    }

    Allat& operator--() {
        --jollakott;
        return *this;
    }
};

class Allatkert {
    vector<Allat> allatok;
    size_t max;

public:
    Allatkert(unsigned darab = 5): max(darab < 10 ? darab : 10){};
    
    Allat& operator[](size_t i){
        if(i < allatok.size()){
            return allatok[i];
        }
        throw out_of_range("Rossz index");
    }

    Allatkert& operator+=(const Allat& a){
        if(allatok.size() < max){
            this->allatok.push_back(a);
        }else{
            cout << "Az allatkert tele van" << endl;
        }
        return *this;
    }

    unsigned operator-(){
        unsigned ret = 0;
        for (size_t i = 0; i < allatok.size(); i++){
            ret += !!--(*this)[i];
        }
        return ret;
    }
};
