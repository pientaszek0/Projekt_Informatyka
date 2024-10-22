#include <iostream>
#include <vector>

#include "classes.h"
#include "functions.h"
#include "variables.h"
#include "xml_class.h"

using namespace std;

int main() 
{
    xml_chf(user); // Wywołanie funkcji do odczytu pliku xml 
    xml_giveData(user, account, currency, loan_type); // Wywołanie funkcja która wczytuje dane z XML
    xml_checkData(user, account, currency); // Wywołanie funkcji sparwdza poprawność czy dane zostały dobrze wczytane !!TYLKO "User!!"

    while (true) { // Nieskonczona petla zeby mozna bylo sie wylogowac i zalogowac na innego uzytkownika
        sign_in(); // Wywolanie funkcji logowania
        desktop(); // Wywolanie funkcji pokazujacej pulpit uzytkownika
    }

    return 0;
}

 
