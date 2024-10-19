#include <iostream>
#include "classes.h"
#include "variables.h"
#include <fstream>
#include <string>
//#include <sstream>

using namespace std;

string db_name = "classes.xml";

//funkcja która usuwa biale znaki


void xml_save(User user) // funkcja która sluszy do zapisu
{
	ofstream db(db_name);

	if (db.is_open()) //spradzanie czy plik jest ptwraty poprawnie
	{

		db << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"; //nagłówek pliku xml
	
		 db << "<Users>\n"; // Rozpoczęcie znacznika "Users"

        for(int i = 0; i < user.getElementUser(); i++) // Iteracja po użytkownikach
        {
            db << "  <User>\n"; // Każdy użytkownik otoczony własnym znacznikiem <User>
            db << "<id>\n" << user.getId(i) <<endl << "</id>\n";
            db << " <first_name>\n" << user.getFirst_name(i) << endl << "</first_name>\n";
            db << "<last_name>\n" << user.getLast_name(i) << "</last_name>\n";
            db << "<login>\n" << user.getLogin(i) << endl <<"</login>\n";
            db << "<password>\n" << user.getPassword(i) << endl << "</password>\n";
            db << "<admin>\n" << (user.isAdmin(i) ? "true" : "false") << endl << "</admin>\n";
            db << "</User>\n"; // Zamknięcie znacznika "User"
        }

        db << "</Users>"; // Zamknięcie znacznika "Users"

		db.close();
		cout << "Dane zostały zapisane do pliku XML!\n" << std::endl;
	}
	else
	{
		cout << "Plik dziala niepoprawnie\n";
	}
}

void xml_chd(User user) //Funkcja do sparwdzania spójnosci XML i  classy
{
	ifstream db(db_name);
	
	if (db.is_open())
	{
		cout <<"\n----\nSPrawdzanie plków\n-----\n";
		string line; //zmienna do odczytu linjki xml

		int i = 0;

		while(getline(db, line)) //Odczytuje linijke jezeli true dziala dalej a jak sie skonczy plik konczy z wartoscia falase;
		{
			int i;
			bool id = 0;
			bool first_name = 0;
			bool last_naem = 0;
			bool login = 0;
			bool password = 0;
			bool admin = 0;
			bool zgodnosc = 0;

			//ignorowanie linijek xml;
			if(line.find("<?xml version=\"1.0\" encoding=\"UTF-8\"?>") != string::npos) continue;
			if(line.find("<Users>") != string::npos) continue;
			if(line.find("</Users>") != string::npos) continue;
			if(line.find("<User>") != string::npos) continue;
			if(line.find("</User>") != string::npos) continue;
			if(line.find("</id>") != string::npos) continue;
			if(line.find("</first_name>") != string::npos) continue;
			if(line.find("</last_name>") != string::npos) continue;
			if(line.find("</login>") != string::npos) continue;
			if(line.find("</password>") != string::npos) continue;
			if(line.find("</admin>") != string::npos) continue;
			if(line.find("</User>") != string::npos) continue;

			// Sprawdzenie wartosci pliku xml

			if(line.find("<first_name>") != string::npos) continue;
			if(line.find("<last_name>") != string::npos) continue;
			if(line.find("<id>") != string::npos) continue;
			if(line.find("<password>") != string::npos) continue;
			if(line.find("<admin>") != string::npos) continue;

			if(line.find("<id>") != string::npos)
			{
				i++;
				cout << i << endl;
				continue;
			}
			if(line.find("<login>") !=string::npos) 
			{
				login = 1;
				continue;
			}
			if(login == 1)
			{

			}
		}
		db.close();
	}
	else
	{
		cout << "ERROR";
	}
}


void xml_chf(User user) //sprawdzanie czy plik istenieje
{
	ifstream db(db_name);
	if (db)
	{
		cout << "Plik istenieje, czyli działa to poprawnie\n";
		xml_chd(user);
	}
	else
	{
		cout << "Plik został utworzony\n" << endl;
		xml_save(user);// Wywołanie funckji do zapisu;
		db.close();
	}
}