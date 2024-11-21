#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int array_to_set(const unsigned input[], const unsigned hossz, set<unsigned> &output){
  int res = 0;
  for (int i = 0; i < hossz; i++){
    if (output.find(input[i]) == output.end()){
        output.insert(input[i]);
    }else{
        res += input[i]; 
    }
  }
  
  return res;
}

int main(){
    unsigned input [] = {42 ,4 ,5 ,42};
    set <unsigned> output ;
    unsigned result = array_to_set ( input , 4 , output ) ;
    cout << result << endl ;
    map<string, unsigned> test;
    test.insert(pair<string, int>("fasz", 10));
    test.insert(pair<string, int>("hehe", 20));
    test.insert(pair<string, int>("haha", 30));
    test.insert(pair<string, int>("kek", 40));
    test.insert(pair<string, int>("enitt", 50));

    for(auto const& [key, val] : test){
        cout << key
             << ':'
             << val
             << endl;
    }

    
    return 0;
}