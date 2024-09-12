#include <iostream>

using namespace std;

int main(){
	int n = 0;
	cin >> n;
	string elrabolt_xd;
	int sikertelen = 0;
	for (int i = 0; i < n; i++)
	{
		string nev;
		int tomeg;

		cin >> nev >> tomeg;
		if(tomeg >= 50 || nev == "Olga" || nev.length() > 3){
			elrabolt_xd += nev + " ";
		}else{
			sikertelen++;
		}
	}

	cout << "Elrabolt dögök: " + elrabolt_xd << endl;
	cout << "Sikertelen rablások: " + to_string(sikertelen) << endl;
	string str = "Sikertelen rablások: " + to_string(sikertelen);
	try
	{
		cout << stoi(str) << endl;
	}
	catch(invalid_argument e)
	{
		cerr << e.what() << endl;
	}
	
	

	return 0;
}
