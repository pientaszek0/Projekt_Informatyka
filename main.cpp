#include <iostream>
#include <vector>

#include "classes.h"
#include "functions.h"
#include "variables.h"
#include "xml_class.h"

using namespace std;

int main() 
{
    User user;
    cout << "test Prymasa";
    xml_chf();
    temprrary_data(user); // Wywołanie funkcji dodającej tymczasowe dane do testów

    sign_in(user); // Wywolanie funkcji logowania

    // Oczekuje na wejście żeby konsola się nie zamykała
    int zatrzymanie;
    cin >> zatrzymanie;
    
    //cout << users[4].getId(); // Testowe oduserczytanie id użytkownika

    return 0;
}

 
