#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#ifndef MY_VONAT //ne torold ki

class Vonat {
    string azonosito;
    unsigned sebesseg;

public:
    Vonat(const string& a, unsigned s) : azonosito(a), sebesseg(s) {

    }

    const string& getAzonosito() const {
        return azonosito;
    }

    unsigned getSebesseg() const {
        return sebesseg;
    }

    Vonat& operator++() {
        ++sebesseg;
        return *this;
    }

    virtual operator string () const{
        return this->azonosito + " " + to_string(this->sebesseg) + "km/h";
    }

    virtual unsigned getTipus() const{
        return 1;
    } 

};

class IC : public Vonat
{
private:
    unsigned utasszam;
public:
    IC(string azonosito, unsigned sebesseg, unsigned utasszam): Vonat(azonosito, sebesseg), utasszam(utasszam){}
    
    operator string () const override{
        return this->getAzonosito() + " " + to_string(this->getSebesseg()) + "km/h " + to_string(utasszam) + "db";
    }

    unsigned getTipus() const override{
        return 2;
    }
};

class sajatHiba : public exception{
    string message;
    public:
        sajatHiba(const string& message): message(message){};

        const char* what() const noexcept override{
            return message.c_str();
        }
};

class Vasutallomas
{
private:
    vector<reference_wrapper<Vonat>> vonatok;
public:
    void increaseSebesseg() {
        for (auto& vonat : vonatok) {
            ++(vonat.get());
        }
    }

    void operator+=(Vonat& vonat) {
        for(auto& i : vonatok){
            if(i.get().getAzonosito() == vonat.getAzonosito()){
                throw sajatHiba(vonat.getAzonosito());
            }
        }
        vonatok.push_back(vonat);
    }

    operator string() const {
        string res;

        for (int i = 0; i < vonatok.size(); i++)
        {
            res += static_cast<string>(vonatok[i].get());
            if(i != vonatok.size() - 1){
                res += ";";
            }
        }
        return res;
    }

    bool operator!() const {
        int hagyomanyosVonatok = 0;
        for (auto& vonat : vonatok) {
            if (vonat.get().getTipus() == 1) {
                ++hagyomanyosVonatok;
            }
        }
        return hagyomanyosVonatok > vonatok.size() / 2;
    }

    void gyorsit(){
        for_each(vonatok.begin(), vonatok.end(), [](reference_wrapper<Vonat> i) {
            ++i.get();
        });
    }

    bool operator>(unsigned sebesseg) const{
        if (vonatok.empty()) {
            return false;
        }
        auto res = find_if(vonatok.begin(), vonatok.end(), [sebesseg](reference_wrapper<Vonat> i){
            return i.get().getSebesseg() <= sebesseg;
        });
        return res == vonatok.end();
    }
};

#endif //ne torold ki



int main()
{
    Vonat v("H34", 65);
    cout << (string) v << endl;
    IC i("HUB234", 130, 400);
    cout << (string)i << endl;
    
    
    Vasutallomas va;
    cout << "Tobbsegben vannak az 1-es vonatok:" << !va << endl; //false kell legyen
    va += v;
    cout << "Tobbsegben vannak az 1-es vonatok:" << !va << endl; //true kell legyen
    va += i;
    cout << (string)va << endl;

    if (va > 65) {
        cout << "Minden vonat gyorsabb 65 km/h-nal" << endl; //gyorsitas elott true
    }
    else {
        cout << "Van 65 km/h-s vagy lassabb vonat" << endl;
    }

    cout << "Gyorsulnak a vonatok" << endl;
    va.gyorsit();


    cout << (string)va << endl;

    if (va > 65) {
        cout << "Minden vonat gyorsabb 65 km/h-nal" << endl;
    }
    else {
        cout << "Van 65 km/h-s vagy lassabb vonat" << endl; //gyorsitas utan true
    }


    cout << "Tobbsegben vannak az 1-es vonatok:" << !va << endl; //false kell legyen


    return 0; //ne torold ki!!!!!!
}

