#ifndef XML_CLASS_H
#define XML_CLASS_H

#include <iostream>
#include "classes.h"
#include "variables.h"
#include "functions.h"
#include <fstream>
#include <string>

using namespace std;

// Funkjca która wczytyje dane z XML do klasy
void xml_giveData(User &user, Account &account, Currency &currency, Loan_Type &loan_type, Loan &loan, Deposit &deposit)
{
	ifstream db(db_name);
	
	if(!db.is_open()) 
    {
        cout << error01 << endl;
        return;
    }
    cout << "\n----WCZYTWYWANIE DANYCH-----\n";
    while(getline(db, line)) 
    {
        // Ignorowanie linijek XML
        if(line.find("<?xml") != string::npos || line.find("</Users>") != string::npos ||
        line.find("</Accounts>") != string::npos || line.find("</Currencys>") != string::npos ||
        line.find("<Data>") != string::npos || line.find("</Data>") != string::npos)  continue;
        //Dodawanie klasy User
        if(line.find("<User>") != string::npos)
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
        if(line.find("<Account>") != string::npos)
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
        else if(line.find("</Account>") != string::npos) 
        {
            account.addAccount(xml_id, xml_owner_id, xml_currency_id, xml_account_number, xml_balance);
            cout << "---Dane zostałt wczytane dla klasy: \"Account\"---\n"; 
        }
        // Dodawanie klasy Currency
        if(line.find("<Currency>") != string::npos)
        {
            // Ustawienie Flagi;
            xml_isUser = 0;
            xml_isAccount = 0;
            xml_isCurrency = 1;
            xml_isLoan_type = 0;
            xml_isLoan = 0;
            xml_isDeposit = 0;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych
            xml_id = -1;
            xml_cName = "";
            continue;
        }
        else if(line.find("</Currency>") != string::npos) 
        {
            currency.addCurrency(xml_id, xml_cName, xml_cValue);
            cout << "---Dane zostałt wczytane dla klasy: \"Currency\"---\n"; 
        }
        // Dodawanie klasy Loan_Type
        if(line.find("<Loan_Type>") != string::npos)
        {
            // Ustawienie Flagi;
            xml_isUser = 0;
            xml_isAccount = 0;
            xml_isCurrency = 0;
            xml_isLoan_type = 1;
            xml_isLoan = 0;
            xml_isDeposit = 0;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych
            xml_id = -1;
            xml_interest = 0.0;
            xml_loan_type = "";
            continue;
        }
        else if(line.find("</Loan_Type>") != string::npos) 
        {
            loan_type.addLoanType(xml_id, xml_interest, xml_loan_type);
            cout << "---Dane zostałt wczytane dla klasy: \"Loan_type\"---\n"; 
        }
        // Dodawanie klasy Loan
        if(line.find("<Loan>") != string::npos)
        {
            // Ustawienie Flagi;
            xml_isUser = 0;
            xml_isAccount = 0;
            xml_isCurrency = 0;
            xml_isLoan_type = 0;
            xml_isLoan = 1;
            xml_isDeposit = 0;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych użytkownika
            xml_id = -1;
            xml_owner_id = -1;
            xlm_currency_name = "";
            xml_loan_type = "";
            xlm_balance_left = 0.0;
            continue;
        }
        else if(line.find("</Loan>") != string::npos) 
        {
            loan.addLoan(xml_id, xml_owner_id, xlm_currency_name, xml_loan_type, xlm_balance_left);
            cout << "---Dane zostałt wczytane dla klasy: \"Loan\"---\n"; 
        }
        // Dodawanie klasy Deposit
        if(line.find("<Deposit>") != string::npos)
        {
            // Ustawienie Flagi;
            xml_isUser = 0;
            xml_isAccount = 0;
            xml_isCurrency = 0;
            xml_isLoan_type = 0;
            xml_isLoan = 0;
            xml_isDeposit = 1;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych użytkownika
            xml_id = -1;
            xml_owner_id = 0;
            xml_deposit_amount = 0.0;
            xlm_currency_name = "";
            xml_duration_months = 0;
            xml_interest_rate = 0.0;
            xml_start_date = "";
            xml_remaing_time = 0;
            continue;
        }
        else if(line.find("</Deposit>") != string::npos) 
        {
            deposit.addDeposit(xml_id, xml_owner_id, xml_deposit_amount, xlm_currency_name, xml_duration_months,
            xml_interest_rate, xml_start_date, xml_remaing_time);
            cout << "---Dane zostałt wczytane dla klasy: \"Deposit\"---\n"; 
        }

        // Sprawdzenie wartości pliku XML
        if(xml_isUser)
        {
            if(line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if(line.find("<first_name>") != string::npos) 
            {
                xml_first_name = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if(line.find("<last_name>") != string::npos) 
            {
                xml_last_name = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if(line.find("<login>") != string::npos) 
            {
                xml_login = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if(line.find("<password>") != string::npos) 
            {
                xml_password = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);

            }
            if(line.find("<admin>") != string::npos) 
            {
                string admin_value = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_admin = (admin_value == "true");
            }
        }

        if(xml_isAccount)
        {
            if(line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if(line.find("<owner_id>") != string::npos) 
            {
                string ow_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_owner_id = stoi(ow_str);  // Konwersja na int
            } 
            if(line.find("<currency_id>") != string::npos) 
            {
                string cr_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_currency_id = stoi(cr_str);  // Konwersja na int
            } 
            if(line.find("<account_number>") != string::npos) 
            {
                xml_account_number = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if(line.find("<balance>") != string::npos) 
            {
                string bl_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_balance = stod(bl_str); // Konwersja na double
            }
        }
        if(xml_isCurrency)
        {
            if(line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if(line.find("<name>") != string::npos) 
            {
                xml_cName = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            }
             if(line.find("<value>") != string::npos) 
            {
                string c_valuetemp = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_cValue = stod(c_valuetemp); // konwersja na double
            } 
        }
        if(xml_isLoan_type)
        {
            if(line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if(line.find("<interest>") != string::npos) 
            {
                string it_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_interest = stod(it_str); // Konwersja na double
            }
            if(line.find("<loan_type_name>") != string::npos) 
            {
                xml_loan_type = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
        }
        if(xml_isLoan)
        {
            if(line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if(line.find("<owner_id>") != string::npos) 
            {
                string oi_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_owner_id = stoi(oi_str);  // Konwersja na int
            }
            if(line.find("<currency_name>") != string::npos) 
            {
                xlm_currency_name = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if(line.find("<loan_type_name>") != string::npos) 
            {
                xml_loan_type = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            }
            if(line.find("<balance_left>") != string::npos) 
            {
                string bl_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xlm_balance_left = stod(bl_str); // Konwersja na double
            }
        }
        if(xml_isDeposit)
        {
            if(line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if(line.find("<owner_id>") != string::npos) 
            {
                string oi_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_owner_id = stoi(oi_str);  // Konwersja na int
            }
            if(line.find("<deposit_amount>") != string::npos) 
            {
                string da_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_deposit_amount = stod(da_str); // Konwersja na double
            }
            if(line.find("<currency_name>") != string::npos) 
            {
                xlm_currency_name = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            }
            if(line.find("<duration_months>") != string::npos) 
            {
                string dm_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_duration_months = stoi(dm_str);  // Konwersja na int
            }
            if(line.find("<interest_rate>") != string::npos) 
            {
                string ir_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_interest_rate = stod(ir_str); // Konwersja na double
            }
            if(line.find("<start_date>") != string::npos) 
            {
                xml_start_date = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            }
            if(line.find("<remaining_time>") != string::npos) 
            {
                string rt_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_remaing_time = stoi(rt_str);  // Konwersja na int
            }
        }
    }
    db.close();
}

// Funkcja która sprawdza spójnośc danych XML a danymi w programie.
void xml_checkData(User &user, Account &account, Currency &currency, Loan_Type &loan_type, Loan &loan, Deposit &deposit)
{
	ifstream db(db_name);
	if(!db.is_open()) 
    {
        cout << error01 << endl;
        return;
    }
    cout << "\n----SPRAWDZANIE SPOJNOSCI KLAS-----\n";
    while(getline(db, line)) 
    {
        // Ignorowanie linijek XML
        if(line.find("<?xml") != string::npos || line.find("</Users>") != string::npos ||
        line.find("</Accounts>") != string::npos || line.find("</Currencys>") != string::npos)  continue;
        // Sprawdzanie klasy User
        if(line.find("<Users>") != string::npos) licznik = -1; // Reset licznika
        if(line.find("<User>") != string::npos)
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
            if(line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if(line.find("<first_name>") != string::npos) 
            {
                xml_first_name = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if(line.find("<last_name>") != string::npos) 
            {
                xml_last_name = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if(line.find("<login>") != string::npos) 
            {
                xml_login = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if(line.find("<password>") != string::npos) 
            {
                xml_password = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);

            }
            if(line.find("<admin>") != string::npos) 
            {
                string admin_value = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_admin = (admin_value == "true");
            }

            if(line.find("</User>") != string::npos) 
            {
                if(xml_id == user.getId(licznik) &&
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
        if(line.find("<Accounts>") != string::npos) licznik = -1; // Reset licznika
        if(line.find("<Account>") != string::npos)
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
            if(line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if(line.find("<owner_id>") != string::npos) 
            {
                string ow_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_owner_id = stoi(ow_str);  // Konwersja na int
            } 
            if(line.find("<currency_id>") != string::npos) 
            {
                string cr_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_currency_id = stoi(cr_str);  // Konwersja na int
            } 
            if(line.find("<account_number>") != string::npos) 
            {
                xml_account_number = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if(line.find("<balance>") != string::npos) 
            {
                string bl_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_balance = stod(bl_str); // Konwersja na double
            }
            if(line.find("</Account>") != string::npos) 
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
        if(line.find("<Currencys>") != string::npos) licznik = -1; // Reset licznika
        if(line.find("<Currency>") != string::npos)
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
           if(line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if(line.find("<name>") != string::npos) 
            {
                xml_cName = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            }
             if(line.find("<value>") != string::npos) 
            {
                string c_valuetemp = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_cValue = stod(c_valuetemp); // konwersja na double
            } 
            if(line.find("</Currency>") != string::npos) 
            {
                if (xml_id == currency.getId(licznik) && xml_cName == currency.getName(licznik) && xml_cValue == currency.getValue(licznik))
                {
                    cout << xml_id << "\tTEST PASSED: \"Currency\"" << endl;
                } 
                else cout << xml_id << "\tTEST FAILED: \"Currency\"" << endl;
            }
        }

        // Sprawdzanie klasy Loan_Type;
        if(line.find("<Loan_Types>") != string::npos) licznik = -1; // Reset licznika
        if(line.find("<Loan_Type>") != string::npos)
        {
            // licznik
            licznik++;
            // Ustawienie Flagi;
            xml_isUser = 0;
            xml_isAccount = 0;
            xml_isCurrency = 0;
            xml_isLoan_type = 1;
            xml_isLoan = 0;
            xml_isDeposit = 0;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych
            xml_id = -1;
            xml_interest = 0.0;
            xml_loan_type = "";
            continue;
        }
        if(xml_isLoan_type)
        {
            if(line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if(line.find("<balance>") != string::npos) 
            {
                string it_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_interest = stod(it_str); // Konwersja na double
            }
            if(line.find("<loan_type_name>") != string::npos) 
            {
                xml_loan_type = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            }
            if(line.find("</Loan_Type>") != string::npos) 
            {
                if ((xml_id == loan_type.getId(licznik)) && (xml_interest == loan_type.getInterest(licznik)) && 
                (xml_loan_type == loan_type.getLoanTypeName(licznik)))
                {
                    cout << xml_id << "\tTEST PASSED: \"Loan_Type\"" << endl;
                } 
                else  cout << xml_id << "\tTEST FAILED: \"Loan_type\"" << endl;
                
            }
        }
        
        // Sprawdzanie klasy Loan;
        if(line.find("<Loans>") != string::npos) licznik = -1; // Reset licznika
        if(line.find("<Loan>") != string::npos)
        {
            // licznik
            licznik++;
            // Ustawienie Flagi;
            xml_isUser = 0;
            xml_isAccount = 0;
            xml_isCurrency = 0;
            xml_isLoan_type = 0;
            xml_isLoan = 1;
            xml_isDeposit = 0;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych użytkownika
            xml_id = -1;
            xml_owner_id = -1;
            xlm_currency_name = "";
            xml_loan_type = "";
            xlm_balance_left = 0.0;
            continue;
        }
        if(xml_isLoan)
        {
            if(line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if(line.find("<owner_id>") != string::npos) 
            {
                string oi_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_owner_id = stoi(oi_str);  // Konwersja na int
            }
            if(line.find("<currency_name>") != string::npos) 
            {
                xlm_currency_name = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            } 
            if(line.find("<loan_type_name>") != string::npos) 
            {
                xml_loan_type = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            }
            if(line.find("<balance_left>") != string::npos) 
            {
                string bl_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xlm_balance_left = stod(bl_str); // Konwersja na double
            }
            if(line.find("</Loan>") != string::npos) 
            {
                if (xml_id == loan.getId(licznik) && xml_owner_id == loan.getOwnerId(licznik) &&
                xlm_currency_name == loan.getCurrencyName(licznik) && xml_loan_type == loan.getLoanTypeName(licznik) &&
                xlm_balance_left == loan.getBalanceLeft(licznik))
                {
                    cout << xml_id << "\tTEST PASSED: \"Loan\"" << endl;
                } 
                else cout << xml_id << "\tTEST FAILED: \"Loan\"" << endl;
            }
        }

        // Sprawdzanie klasy Deposit;
        if(line.find("<Deposits>") != string::npos) licznik = -1; // Reset licznika
        if(line.find("<Deposit>") != string::npos)
        {
            // licznik
            licznik++;
            // Ustawienie Flagi;
             // Ustawienie Flagi;
            xml_isUser = 0;
            xml_isAccount = 0;
            xml_isCurrency = 0;
            xml_isLoan_type = 0;
            xml_isLoan = 0;
            xml_isDeposit = 1;
            // Zerowanie wartości, bo zaczynamy nowy zestaw danych użytkownika
            xml_id = -1;
            xml_owner_id = 0;
            xml_deposit_amount = 0.0;
            xlm_currency_name = "";
            xml_duration_months = 0;
            xml_interest_rate = 0.0;
            xml_start_date = "";
            xml_remaing_time = 0;
            continue;
        }
        if(xml_isDeposit)
        {
            if(line.find("<id>") != string::npos) 
            {
                string id_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_id = stoi(id_str);  // Konwersja na int
            }
            if(line.find("<owner_id>") != string::npos) 
            {
                string oi_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_owner_id = stoi(oi_str);  // Konwersja na int
            }
            if(line.find("<deposit_amount>") != string::npos) 
            {
                string da_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_deposit_amount = stod(da_str); // Konwersja na double
            }
            if(line.find("<currency_name>") != string::npos) 
            {
                xlm_currency_name = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            }
            if(line.find("<duration_months>") != string::npos) 
            {
                string dm_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_duration_months = stoi(dm_str);  // Konwersja na int
            }
            if(line.find("<interest_rate>") != string::npos) 
            {
                string ir_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_interest_rate = stod(ir_str); // Konwersja na double
            }
            if(line.find("<start_date>") != string::npos) 
            {
                xml_start_date = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
            }
            if(line.find("<remaining_time>") != string::npos) 
            {
                string rt_str = line.substr(line.find(">") + 1, line.rfind("<") - line.find(">") - 1);
                xml_remaing_time = stoi(rt_str);  // Konwersja na int
            }
            if(line.find("</Deposit>") != string::npos) 
            {
                if (xml_id == deposit.getId(licznik) && xml_owner_id == deposit.getOwnerId(licznik) &&
                xml_deposit_amount == deposit.getDepositAmount(licznik) && xlm_currency_name == deposit.getCurrencyName(licznik) &&
                xml_duration_months == deposit.getDurationMonths(licznik) && xml_interest_rate == deposit.getInterestRate(licznik) &&
                xml_start_date == deposit.getStartDate(licznik) && xml_remaing_time == deposit.getRemainingTime(licznik))
                {
                    cout << xml_id << "\tTEST PASSED: \"Deposit\"" << endl;
                } 
                else cout << xml_id << "\tTEST FAILED: \"Deposit\"" << endl;
            }
        }

    }
    db.close();
}


// Funkcja zapisująca dane do pliku XML
void xml_save(User user, Account account, Currency currency, Loan_Type loan_type, Loan loan, Deposit deposit) 
{
	ofstream db(db_name);

    // Warunek który sprawdza czy plik jest utowrzony. Jeżeli utowrzony (True) to zapisuje klasę do pliku XML
	if(!db.is_open())
	{
        cout << error02 << endl;
        return;
    }
     //nagłówek pliku xml
	db << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";
    db << "<Data>\n";
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
        db << "\t\t\t<value>" << currency.getValue(i) << "</value>\n";
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
        db << "\t\t\t<loan_type_name>" << loan.getLoanTypeName(i) << "</loan_type_name>\n";
        db << "\t\t\t<balance_left>" << loan.getBalanceLeft(i) << "</balance_left>\n";
        // Zamknięcie obiektu
        db << "\t\t</Loan>\n";
    }
    db << "\t</Loans>\n";

    // Dodawanie do klasy Deposit
    db << "\t<Deposits>\n";
         for(int i = 0; i < deposit.getElementDeposit(); i++)
    {
        // Otwarcie obiektu
        db << "\t\t<Deposit>\n"; 
        db << "\t\t\t<id>" << deposit.getId(i) << "</id>\n";
        db << "\t\t\t<owner_id>" << deposit.getOwnerId(i) << "</owner_id>\n";
        db << "\t\t\t<deposit_amount>" << deposit.getDepositAmount(i) << "</deposit_amount>\n";
        db << "\t\t\t<currency_name>" << deposit.getCurrencyName(i) << "</currency_name>\n";
        db << "\t\t\t<duration_months>" << deposit.getDurationMonths(i) << "</duration_months>\n";
        db << "\t\t\t<interest_rate>" << deposit.getInterestRate(i) << "</interest_rate>\n";
        db << "\t\t\t<start_date>" << deposit.getStartDate(i) << "</start_date>\n";
        db << "\t\t\t<remaining_time>" << deposit.getRemainingTime(i) << "</remaining_time>\n";
        // Zamknięcie obiektu
        db << "\t\t</Deposit>\n";
    }
    db << "\t</Deposits>\n";

    db << "</Data>";
    db.close();
    cout << "---KLASY ZOSTAŁY ZAPISE DO PLIKU XML" << endl;
}

// Funkcja która tworzy lub sprawdza czy plik został utowrzony. Jeżeli plik istenieje zostaje wywołana funkcja odpoedzialna za sparwdzanie spójności plików
void xml_chf(User user)
{
	ifstream db(db_name);
	if(db) cout << "---PLIK XML ZOSTAL ODNALEZIONY---" << endl;
	else
	{
		cout << "---PLIK XML ZOSTAL UTWORZONY---" << endl;
		db.close();
	}
}

#endif