#include <iostream>
#include <vector>

#include "classes.h"
#include "functions.h"
#include "variables.h"
#include "xml_class.h"

using namespace std;

int main() 
{
    temprrary_data(user, account, currency);
    //xml_chf(user); // Wywołanie funkcji do odczytu pliku xml 
    //!UWAGA Wczytuje dane tylko klasy "User"!!!!
    //xml_giveData(user); // Wywołanie funkcja która wczytuje dane z XML

    //xml_save(user, account, currency);

    //xml_checkData(user); // Wywołanie funkcji sparwdza poprawność czy dane zostały dobrze wczytane !!TYLKO "User!!"

    //cout << account.getAccountNumber(1);

    while (true) { // Nieskonczona petla zeby mozna bylo sie wylogowac i zalogowac na innego uzytkownika
        sign_in(user); // Wywolanie funkcji logowania
        desktop(user, courent_user); // Wywolanie funkcji pokazujacej pulpit uzytkownika
    }

    // Oczekuje na wejście żeby konsola się nie zamykała
    int zatrzymanie;
    cin >> zatrzymanie;

    return 0;
}

 
