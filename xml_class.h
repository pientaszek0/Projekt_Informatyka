#include <iostream>
#include "classes.h"
#include "variables.h"
#include <fstream>
#include <string>

using namespace std;

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
    while(getline(db, line)) 
    {
        // Ignorowanie linijek XML
        if (line.find("<?xml") != string::npos || line.find("</Users>") != string::npos ||
        line.find("</Accounts>") != string::npos)  continue;

        if (line.find("<Users>") != string::npos) user_count = -1; // Reste licznika
        if (line.find("<User>") != string::npos)
        {
            // Przechodzimy do kolejnego użytkownika
            user_count++;
            // Ustawienie Flagi;
            xml_isUser = 1;
            xml_isAccount = 0;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych użytkownika
            xml_id = -1;
            xml_first_name = "";
            xml_last_name = "";
            xml_login = "";
            xml_password = "";
            xml_admin = false;
            continue;
        }
        else if (line.find("</User>") != string::npos) 
        {
                user.addUser(xml_id, xml_first_name, xml_last_name, xml_login, xml_password, xml_admin);
                cout << "---dane zostaly wczytane---\n";
        }

        if (line.find("<Accounts>") != string::npos) user_count = -1;
        if (line.find("<Account>") != string::npos)
        {
            // Przechodzimy do kolejnego użytkownika
            user_count++;
            // Ustawienie Flagi;
            xml_isUser = 0;
            xml_isAccount = 1;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych użytkownika
            xml_id = -1;
            xml_owner_id = -1;
            xml_currency_id =1;
            xml_account_number ="";
            xml_balance = 0.00;
            continue;
        }
        else if (line.find("</Account>") != string::npos) 
        {
            //currency.addCurrency(xml_id, xml_owner_id, xml_currency_id, xml);
            cout << "---dane zostaly wczytane---\n";   
        }

        // Sprawdzenie wartości pliku XML
        if(xml_isUser)
        {
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
        }

        if(xml_isAccount)
        {
            if (line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if (line.find("<owner_id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_owner_id = stoi(id_str);  // Konwersja na int
            } 
            if (line.find("<currency_id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_currency_id = stoi(id_str);  // Konwersja na int
            } 
            if (line.find("<account_number>") != string::npos) 
            {
                xml_account_number = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if (line.find("<balance>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_balance = stod(id_str); // Konwersja na double
            }
        }
    }
    db.close();
}

// Funkcja która sprawdza spójnośc danych XML a danymi w programie.
void xml_checkData(User user)
{
	ifstream db(db_name);
	if (!db.is_open()) 
    {
        cout << error01 << endl;
        return;
    }
    cout << "\n----SPRAWDZANIE SPOJNOSCI KLAS(y User)-----\n";
    while (getline(db, line)) 
    {
        // Ignorowanie linijek XML
        if (line.find("<?xml") != string::npos || line.find("</Users>") != string::npos) continue;
        if (line.find("<Users>") != string::npos) user_count = -1; // Reset licznika
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


// Funkcja zapisująca dane do pliku XML
void xml_save(User user, Account account, Currency currency) 
{
	ofstream db(db_name);

    // Warunek który sprawdza czy plik jest utowrzony. Jeżeli utowrzony (True) to zapisuje klasę do pliku XML
	if (!db.is_open())
	{
        cout << error02 << endl;
        return;
    }
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
    // Zamknięcie całej klasy User
    db << "</Users>\n";

    // Otwracie klasy Account
    db << "<Accounts>\n";
    // Pętla która służy do zpaisu Klasy "Account"
    for(int i = 0; i < account.getElemenAccount(); i++)
    {
        // Otwarcie obiektu
        db << "\t<Account>\n"; 
        db << "\t\t<id>" << account.getId(i) << "</id>\n";
        db << "\t\t<owner_id>" << account.getOwner_id(i) << "</owner_id>\n";
        db << "\t\t<currency_id>" << account.getCurrency_id(i) << "</currency_id>\n";
        db << "\t\t<account_number>" << account.getAccountNumber(i) << "</account_number>\n";
        db << "\t\t<balance>" << account.getBalance(i) << "</balance>\n"; 
        // Zamknięcie obiektu
        db << "\t</Account>\n";
    }
    // Zmkanięcie klasy Account
    db << "</Accounts>\n"; 

    db << "<Currencys>\n";

         for(int i = 0; i < currency.getElementCurrency(); i++)
    {
        // Otwarcie obiektu
        db << "\t<Currency>\n"; 
        db << "\t\t<id>" << currency.getId(i) << "</id>\n";
        db << "\t\t<name>" << currency.getName(i) << "</name>\n";
        // Zamknięcie obiektu
        db << "\t</Currency>\n";
    }

    db << "</Currencys>";
    db.close();
    cout << "---KLASY ZOSTAŁY ZAPISE DO PLIKU XML" << endl;
}

// Funkcja która tworzy lub sprawdza czy plik został utowrzony. Jeżeli plik istenieje zostaje wywołana funkcja odpoedzialna za sparwdzanie spójności plików
void xml_chf(User user)
{
	ifstream db(db_name);
	if (db) cout << "---PLIK XML ZOSTAL ODNALEZIONY---" << endl;
	else
	{
		cout << "---PLIK XML ZOSTAL UTWORZONY---" << endl;
		db.close();
	}
}

//Funkcja do dodawania danych, NIE DZIAŁA JESZCZE
void xml_addData(User user)
{
    ifstream db(db_name);
    ofstream dbs("temp.xml");

    if(!db.is_open()) 
    {
        cout << error01 << endl;
        return;
    }
    cout << "---DODAWANIE DANYCH---";
    
    while(getline(db, line)) 
    {
        if(line.find(user.getId(user.getElementUser() - 1)) != string::npos)
        { 
            cout << user.getId(user.getElementUser() - 1);
        }
    }

}