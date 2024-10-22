#include <iostream>
#include "classes.h"
#include "variables.h"
#include <fstream>
#include <string>

using namespace std;

// Funkjca która wczytyje dane z XML do klasy
void xml_giveData(User &user, Account &account, Currency &currency)
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
        line.find("</Accounts>") != string::npos || line.find("</Currencys>") != string::npos ||
        line.find("<Data>") != string::npos || line.find("</Data>") != string::npos)  continue;
        //Dodawanie klasy User
        if (line.find("<User>") != string::npos)
        {
            // Ustawienie Flagi;
            xml_isUser = 1;
            xml_isAccount = 0;
            xml_isCurrency = 0;
            xml_isLoan_type = 0;
            xml_isLoan = 0;
            xml_isDeposit = 0;
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
            cout << "---Dane zostałt wczytane dla klasy: \"User\"---\n";
        }
        // Dodawania klasy Account
        if (line.find("<Account>") != string::npos)
        {
            // Ustawienie Flagi;
            xml_isUser = 0;
            xml_isAccount = 1;
            xml_isCurrency = 0;
            xml_isLoan_type = 0;
            xml_isLoan = 0;
            xml_isDeposit = 0;
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
            account.addAccount(xml_id, xml_owner_id, xml_currency_id, xml_account_number, xml_balance);
            cout << "---Dane zostałt wczytane dla klasy: \"Account\"---\n"; 
        }
        // Dodawanie klasy Currency
        if (line.find("<Currency>") != string::npos)
        {
            // Ustawienie Flagi;
            xml_isUser = 0;
            xml_isAccount = 0;
            xml_isCurrency = 1;
            xml_isLoan_type = 0;
            xml_isLoan = 0;
            xml_isDeposit = 0;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych użytkownika
            xml_id = -1;
            xml_cName = "";
            continue;
        }
        else if (line.find("</Currency>") != string::npos) 
        {
            currency.addCurrency(xml_id, xml_cName);
            cout << "---Dane zostałt wczytane dla klasy: \"Currency\"---\n"; 
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
                string ow_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_owner_id = stoi(ow_str);  // Konwersja na int
            } 
            if (line.find("<currency_id>") != string::npos) 
            {
                string cr_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_currency_id = stoi(cr_str);  // Konwersja na int
            } 
            if (line.find("<account_number>") != string::npos) 
            {
                xml_account_number = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if (line.find("<balance>") != string::npos) 
            {
                string bl_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_balance = stod(bl_str); // Konwersja na double
            }
        }
        if(xml_isCurrency)
        {
            if (line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if (line.find("<name>") != string::npos) 
            {
                xml_cName = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
        }
    }
    db.close();
}

// Funkcja która sprawdza spójnośc danych XML a danymi w programie.
void xml_checkData(User &user, Account &account, Currency &currency)
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
        if (line.find("<?xml") != string::npos || line.find("</Users>") != string::npos ||
        line.find("</Accounts>") != string::npos || line.find("</Currencys>") != string::npos)  continue;
        // Sprawdzanie klasy User
        if (line.find("<Users>") != string::npos) licznik = -1; // Reset licznika
        if (line.find("<User>") != string::npos)
        {
            // Przechodzimy do kolejnego użytkownika
            licznik++;
             // Ustawienie Flagi;
            xml_isUser = 1;
            xml_isAccount = 0;
            xml_isCurrency = 0;
            xml_isLoan_type = 0;
            xml_isLoan = 0;
            xml_isDeposit = 0;

            // Zerowanie wartości, bo zaczynamy nowy zestaw danych użytkownika
            xml_id = -1;
            xml_first_name = "";
            xml_last_name = "";
            xml_login = "";
            xml_password = "";
            xml_admin = false;
            continue;
        }
        if(xml_isUser)
        {
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
                if (xml_id == user.getId(licznik) &&
                    xml_first_name == user.getFirst_name(licznik) &&
                    xml_last_name == user.getLast_name(licznik) &&
                    xml_login == user.getLogin(licznik) &&
                    xml_password == user.getPassword(licznik) &&
                    xml_admin == user.isAdmin(licznik)) 
                {
                    cout << xml_id << "\tTEST PASSED: \"User\"" << endl;
                } 
                else cout << xml_id << "\tTEST FAILED: \"User\"" << endl;
            }
        }

        // Sprawdzanie klasy Account
        if (line.find("<Accounts>") != string::npos) licznik = -1; // Reset licznika
        if (line.find("<Account>") != string::npos)
        {
            // Przechodzimy do kolejnego użytkownika
            licznik++;
            // Ustawienie Flagi;
            xml_isUser = 0;
            xml_isAccount = 1;
            xml_isCurrency = 0;
            xml_isLoan_type = 0;
            xml_isLoan = 0;
            xml_isDeposit = 0;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych użytkownika
            xml_id = -1;
            xml_owner_id = -1;
            xml_currency_id =1;
            xml_account_number ="";
            xml_balance = 0.00;
            continue;
        }
        if(xml_isAccount)
        {
            // Sprawdzenie wartości pliku XML
            if (line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if (line.find("<owner_id>") != string::npos) 
            {
                string ow_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_owner_id = stoi(ow_str);  // Konwersja na int
            } 
            if (line.find("<currency_id>") != string::npos) 
            {
                string cr_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_currency_id = stoi(cr_str);  // Konwersja na int
            } 
            if (line.find("<account_number>") != string::npos) 
            {
                xml_account_number = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if (line.find("<balance>") != string::npos) 
            {
                string bl_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_balance = stod(bl_str); // Konwersja na double
            }
            if (line.find("</Account>") != string::npos) 
            {
                if (xml_id == account.getId(licznik) &&
                    xml_owner_id == account.getOwner_id(licznik) &&
                    xml_currency_id == account.getCurrency_id(licznik) &&
                    xml_account_number == account.getAccountNumber(licznik) &&
                    xml_balance == account.getBalance(licznik))
                {
                    cout << xml_id << "\tTEST PASSED: \"Account\"" << endl;
                } 
                else cout << xml_id << "\tTEST FAILED: \"Account\"" << endl;
            }
        }
        // Sprawdzanie klasy Currency
        if (line.find("<Currencys>") != string::npos) licznik = -1; // Reset licznika
        if (line.find("<Currency>") != string::npos)
        {
            // Przechodzimy do kolejnego użytkownika
            licznik++;
            // Ustawienie Flagi;
            xml_isUser = 0;
            xml_isAccount = 0;
            xml_isCurrency = 1;
            xml_isLoan_type = 0;
            xml_isLoan = 0;
            xml_isDeposit = 0;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych użytkownika
            xml_id = -1;
            xml_cName = "";
            continue;
        }
        if(xml_isCurrency)
        {
            // Sprawdzenie wartości pliku XML
           if (line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if (line.find("<name>") != string::npos) 
            {
                xml_cName = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if (line.find("</Currency>") != string::npos) 
            {
                if (xml_id == currency.getId(licznik) && xml_cName == currency.getName(licznik))
                {
                    cout << xml_id << "\tTEST PASSED: \"Currency\"" << endl;
                } 
                else cout << xml_id << "\tTEST FAILED: \"Currency\"" << endl;
            }
        }
    }
    db.close();
}


// Funkcja zapisująca dane do pliku XML
void xml_save(User user, Account account, Currency currency, Loan_Type loan_type, Loan loan) 
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
    db << "<Data>\n";
	// Nazwa klasy w liczbie mnogiej
    db << "\t<Users>\n"; 
    // Pętla która służy do zpaisu Klasy "User"
    for(int i = 0; i < user.getElementUser(); i++)
    {
        // Otwarcie obiektu
        db << "\t\t<User>\n"; 
        db << "\t\t\t<id>" << user.getId(i) << "</id>\n";
        db << "\t\t\t<first_name>" << user.getFirst_name(i) <<"</first_name>\n";
        db << "\t\t\t<last_name>" << user.getLast_name(i) << "</last_name>\n";
        db << "\t\t\t<login>" << user.getLogin(i) << "</login>\n";
        db << "\t\t\t<password>" << user.getPassword(i) << "</password>\n";
        db << "\t\t\t<admin>" << (user.isAdmin(i) ? "true" : "false") << "</admin>\n";
        // Zamknięcie obiektu
        db << "\t\t</User>\n";
    }
    // Zamknięcie całej klasy User
    db << "</Users>\n";

    // Otwracie klasy Account
    db << "<Accounts>\n";
    // Pętla która służy do zpaisu Klasy "Account"
    for(int i = 0; i < account.getElemenAccount(); i++)
    {
        // Otwarcie obiektu
        db << "\t\t<Account>\n"; 
        db << "\t\t\t<id>" << account.getId(i) << "</id>\n";
        db << "\t\t\t<owner_id>" << account.getOwner_id(i) << "</owner_id>\n";
        db << "\t\t\t<currency_id>" << account.getCurrency_id(i) << "</currency_id>\n";
        db << "\t\t\t<account_number>" << account.getAccountNumber(i) << "</account_number>\n";
        db << "\t\t\t<balance>" << account.getBalance(i) << "</balance>\n"; 
        // Zamknięcie obiektu
        db << "\t\t</Account>\n";
    }
    // Zmkanięcie klasy Account
    db << "\t</Accounts>\n"; 

    // Dodawanie do klasy Currency
    db << "\t<Currencys>\n";
         for(int i = 0; i < currency.getElementCurrency(); i++)
    {
        // Otwarcie obiektu
        db << "\t\t<Currency>\n"; 
        db << "\t\t\t<id>" << currency.getId(i) << "</id>\n";
        db << "\t\t\t<name>" << currency.getName(i) << "</name>\n";
        // Zamknięcie obiektu
        db << "\t\t</Currency>\n";
    }
    db << "\t</Currencys>\n";

    // Dodawanie do klasy Loan_Type
    db << "\t<Loan_Types>\n";
         for(int i = 0; i < loan_type.getElementLoanType(); i++)
    {
        // Otwarcie obiektu
        db << "\t\t<Loan_Type>\n"; 
        db << "\t\t\t<id>" << loan_type.getId(i) << "</id>\n";
        db << "\t\t\t<interest>" << loan_type.getInterest(i) << "</interest>\n";
         db << "\t\t\t<loan_type_name>" << loan_type.getLoanTypeName(i) << "</loan_type_name>\n";
        // Zamknięcie obiektu
        db << "\t\t</Loan_Type>\n";
    }
    db << "\t</Loan_Types>\n";

        // Dodawanie do klasy Loan
    db << "\t<Loans>\n";
         for(int i = 0; i < loan.getElementLoan(); i++)
    {
        // Otwarcie obiektu
        db << "\t\t<Loan>\n"; 
        db << "\t\t\t<id>" << loan.getId(i)<< "</id>\n";
        db << "\t\t\t<owner_id>" << loan.getOwnerId(i) << "</owner_id>\n";
        db << "\t\t\t<currency_name>" << loan.getCurrencyName(i) << "</currency_name>\n";
        db << "\t\t\t<loan_type>" << loan.getLoanTypeName(i) << "</loan_type_name>\n";
        db << "\t\t\t<balance_left>" << loan.getBalanceLeft(i) << "</loan_type_name>\n";
        // Zamknięcie obiektu
        db << "\t\t</Loan>\n";
    }
    db << "\t</Loans>\n";

    db << "</Data>";
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