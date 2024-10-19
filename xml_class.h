#include <iostream>
#include "classes.h"
//#include "functions.h"
#include "variables.h"
#include <fstream>
#include <string>

using namespace std;

string db_name = "classes.xml";

void xml_save() // funkcja która sluszy do zapisu
{
	ofstream db(db_name);

	if (db.is_open()) //spradzanie czy plik jest ptwraty poprawnie
	{

		db << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"; //nagłówek pliku xml
	
		db << "<Users>"; // nazwa klasy

    // Tutaj ogólnie będzie zpais class ale gdy program będzie uruchamiany piewrsz raz. a zarazem przy zamknęciu 

		db << "/<Users>"; //zamknięcie klasy

		db.close();
		cout << "Dane zostały zapisane do pliku XML!\n" << std::endl;
	}
	else
	{
		cout << "Plik dziala niepoprawnie\n";
	}
}


void xml_chf() //sprawdzanie czy plik istenieje
{
	ifstream db(db_name);
	if (db)
	{
		cout << "Plik istenieje, czyli działa to poprawnie\n";
	}
	else
	{
		cout << "Plik został utworzony\n" << endl;
		xml_save();// Wywołanie funckji do zapisu;
		db.close();
	}
}