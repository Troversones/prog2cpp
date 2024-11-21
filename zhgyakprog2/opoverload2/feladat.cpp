#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>

using namespace std;

class Plane{
private:
    string call_sign;
    bool is_prioritized;
    unsigned fuel_amount;
public:
    Plane(string callSign = "AIR-123", bool priority = false, unsigned fuelAmount = 1600): call_sign(callSign), is_prioritized(priority), fuel_amount(fuelAmount) {}

    const string& getCallSign() const {
        return this->call_sign;
    }

    const bool& isPrioritized() const {
        return this->is_prioritized;
    }

    const unsigned& getFuelAmount() const {
        return this->fuel_amount;
    }

    void setCallSign(string val){
        this->call_sign = val;
    }

    void setIsPrioritized(bool val){
        this->is_prioritized = val;
    }

    void setFuelAmount(unsigned val){
        this->fuel_amount = val;
    }

    string to_string() const {
        ostringstream ret;
        ret << "Plane: " << this->call_sign
            << ", take off=" << (this->is_prioritized ? "priority" : "normal")
            << ", fuel=" << this->fuel_amount << "gal;";

        return ret.str();
    }

};

class Airport{
private:
    string iata_code;
    Plane takeoff_schedule[5];
    int takeoff_index;
public:
    Airport(string iaCode = "LHBP", int index = 0): iata_code(iaCode), takeoff_index(index), takeoff_schedule() {}
    
    const string getIataCode() const {
        return this->iata_code;
    }

    const int getTakeoffIndex() const {
        return this->takeoff_index;
    }

    void setIataCode(string val) {
        this->iata_code = val;
    }

    void setTakeoffIndex(int val) {
        this->takeoff_index = val;
    }

    Airport& operator+=(const Plane& p) {
        if(takeoff_index >= 5){
            throw exception();
        }

        if(p.isPrioritized()){
            if(takeoff_index < 5){
                for (int i = takeoff_index; i > 0; --i) {
                    takeoff_schedule[i] = takeoff_schedule[i - 1];
                }
                takeoff_schedule[0] = p;
                takeoff_index++;
            }
        }else{
            takeoff_schedule[takeoff_index++] = p; 
        }
        return *this;
    }

    string print_takeoff_schedule() const {
        ostringstream ret;

        ret << "Takeoff schedule for " << iata_code << ":";
        for (int i = 0; i < takeoff_index; i++){
            ret << "\n" << (i + 1) << ") " << takeoff_schedule[i].to_string();
        }
        
        return ret.str();
    }

};

int main(){
    return 0;
}