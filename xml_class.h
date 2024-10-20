#include <iostream>
#include "classes.h"
#include "variables.h"
#include <fstream>
#include <string>

using namespace std;

string db_name = "classes.xml";

// Funkjca która wczytyje dane z XML do klasy
void xml_giveData(User &user)
{
	ifstream db(db_name);
	
	if (!db.is_open()) 
    {
        cout << error01 << endl;
        return;
    }

    cout << "\n----WCZYTWYWANIE DANYCH-----\n";
    // Zmienne lokalne stworzone na porzeby dzilania tej funkcji
    int xml_id = -1;
    string xml_first_name, xml_last_name, xml_login, xml_password;
    bool xml_admin = false;
	int count_element = 0;
    string line;
    int user_count = -1; // Licznik użytkowników od -1 ponieważ dlaej jest iterator który i tak zmieni wartosc na 0

   while (getline(db, line)) 
    {
        // Ignorowanie linijek XML
        if (line.find("<?xml") != string::npos || line.find("<Users>") != string::npos ||
            line.find("</Users>") != string::npos) 
        {
            continue;
        }
        if (line.find("<User>") != string::npos)
        {
            // Przechodzimy do kolejnego użytkownika
            user_count++;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych użytkownika
            xml_id = -1;
            xml_first_name = "";
            xml_last_name = "";
            xml_login = "";
            xml_password = "";
            xml_admin = false;
            continue;
        }

        // Sprawdzenie wartości pliku XML
        if (line.find("<id>") != string::npos) 
        {
            string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            xml_id = stoi(id_str);  // Konwersja na int
        }
        if (line.find("<first_name>") != string::npos) 
        {
            xml_first_name = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
        } 
        if (line.find("<last_name>") != string::npos) 
        {
            xml_last_name = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
        } 
        if (line.find("<login>") != string::npos) 
        {
            xml_login = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
        } 
        if (line.find("<password>") != string::npos) 
        {
            xml_password = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);

        }
        if (line.find("<admin>") != string::npos) 
        {
            string admin_value = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            xml_admin = (admin_value == "true");
        }

         if (line.find("</User>") != string::npos) 
        {
                user.addUser(xml_id, xml_first_name, xml_last_name, xml_login, xml_password, xml_admin);
                cout << "---dane zostaly wczytane---\n";
        } 
    }
    db.close();

}


// Funkcja zapisująca dane do pliku XML
void xml_save(User user) 
{
	ofstream db(db_name);

    // Warunek który sprawdza czy plik jest utowrzony. Jeżeli utowrzony (True) to zapisuje klasę do pliku XML
	if (db.is_open())
	{
        //nagłówek pliku xml
		db << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";
        
		// Nazwa klasy w liczbie mnogiej
        db << "<Users>\n"; 
        // Pętla która służy do zpaisu Klasy "User"
        for(int i = 0; i < user.getElementUser(); i++)
        {
            // Otwarcie obiektu
            db << "\t<User>\n"; 
            db << "\t\t<id>" << user.getId(i) << "</id>\n";
            db << "\t\t<first_name>" << user.getFirst_name(i) <<"</first_name>\n";
            db << "\t\t<last_name>" << user.getLast_name(i) << "</last_name>\n";
            db << "\t\t<login>" << user.getLogin(i) << "</login>\n";
            db << "\t\t<password>" << user.getPassword(i) << "</password>\n";
            db << "\t\t<admin>" << (user.isAdmin(i) ? "true" : "false") << "</admin>\n";
            // Zamknięcie obiektu
            db << "\t</User>\n";
        }
        // Zamknięcie całej klasy
        db << "</Users>";

		db.close();

		cout << "---KLASY ZOSTAŁY ZAPISE DO PLIKU XML" << endl;
	}
	else
	{
		cout << error02 << endl;
	}
}

// Funkcja która sprawdza spójnośc danych XML a danymi w programie.
void xml_chd(User user)
{
	ifstream db(db_name);
	
	if (!db.is_open()) 
    {
        cout << error01 << endl;
        return;
    }

    cout << "\n----SPRAWDZANIE SPOJNOSCI KLAS(y User)-----\n";
    // Zmienne lokalne stworzone na porzeby dzilania tej funkcji
    int xml_id = -1;
    string xml_first_name, xml_last_name, xml_login, xml_password;
    bool xml_admin = false;
	int count_element = 0;
    string line;
    int user_count = -1; // Licznik użytkowników od -1 ponieważ dlaej jest iterator który i tak zmieni wartosc na 0

   while (getline(db, line)) 
    {
        // Ignorowanie linijek XML
        if (line.find("<?xml") != string::npos || line.find("<Users>") != string::npos ||
            line.find("</Users>") != string::npos) 
        {
            continue;
        }
        if (line.find("<User>") != string::npos)
        {
            // Przechodzimy do kolejnego użytkownika
            user_count++;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych użytkownika
            xml_id = -1;
            xml_first_name = "";
            xml_last_name = "";
            xml_login = "";
            xml_password = "";
            xml_admin = false;
            continue;
        }

        // Sprawdzenie wartości pliku XML
        if (line.find("<id>") != string::npos) 
        {
            string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            xml_id = stoi(id_str);  // Konwersja na int
        }
        if (line.find("<first_name>") != string::npos) 
        {
            xml_first_name = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
        } 
        if (line.find("<last_name>") != string::npos) 
        {
            xml_last_name = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
        } 
        if (line.find("<login>") != string::npos) 
        {
            xml_login = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
        } 
        if (line.find("<password>") != string::npos) 
        {
            xml_password = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);

        }
        if (line.find("<admin>") != string::npos) 
        {
            string admin_value = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            xml_admin = (admin_value == "true");
        }

         if (line.find("</User>") != string::npos) 
        {
            if (xml_id == user.getId(user_count) &&
                xml_first_name == user.getFirst_name(user_count) &&
                xml_last_name == user.getLast_name(user_count) &&
                xml_login == user.getLogin(user_count) &&
                xml_password == user.getPassword(user_count) &&
                xml_admin == user.isAdmin(user_count)) 
            {
                cout << xml_id << "\tTEST PASSED" << endl;
            } 
            else cout << xml_id << "\tTEST FAILED" << endl;
        }
    }
    db.close();
	
}

// Funkcja która tworzy lub sprawdza czy plik został utowrzony. Jeżeli plik istenieje zostaje wywołana funkcja odpoedzialna za sparwdzanie spójności plików
void xml_chf(User user)
{
	ifstream db(db_name);
	if (db)
	{
		cout << "---PLIK XML ZOSTAL ODNALEZIONY---" << endl;
        //xml_chd(user);
	}
	else
	{
		cout << "---PLIK XML ZOSTAL UTWORZONY---" << endl;
		//xml_save(user);
		db.close();
	}
}