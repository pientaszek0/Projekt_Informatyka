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
    //!UWAGA Wczytuje dane tylko klasy "User"!!!!
    xml_giveData(user); // Wywołanie funkcja która wczytuje dane z XML
    xml_checkData(user); // Wywołanie funkcji sparwdza poprawność czy dane zostały dobrze wczytane !!TYLKO "User!!"

    //xml_addData(user);

    sign_in(user); // Wywolanie funkcji logowania
    desktop(user, courent_user); // Wywolanie funkcji pokazujacej pulpit uzytkownika

    // Oczekuje na wejście żeby konsola się nie zamykała
    int zatrzymanie;
    cin >> zatrzymanie;

    return 0;
}

 
