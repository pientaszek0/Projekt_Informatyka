#include <iostream>
#include <vector>

#include "classes.h"
#include "functions.h"
#include "variables.h"
#include "xml_class.h"


using namespace std;

int main() 
{
    //test
    xml_chf(user); // Wywołanie funkcji do odczytu pliku xml 
    xml_giveData(user, account, currency, loan_type, loan, deposit); // Wywołanie funkcja która wczytuje dane z XML
    xml_checkData(user, account, currency, loan_type, loan, deposit); // Wywołanie funkcji sparwdza poprawność czy dane zostały dobrze wczytane !!TYLKO "User!!"
    xml_save(user, account, currency, loan_type, loan, deposit);
    txt_log("Test");
    //cout << "Test " << checkPass("admin", user.getPassword(0));
    while (true) { // Nieskonczona petla zeby mozna bylo sie wylogowac i zalogowac na innego uzytkownika
        sign_in(user); // Wywolanie funkcji logowania
        desktop(user, courent_user); // Wywolanie funkcji pokazujacej pulpit uzytkownika
    }

    return 0;
}

 
