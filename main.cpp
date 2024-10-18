#include <iostream>
#include <vector>

#include "classes.h"
#include "functions.h"
#include "variables.h"
#include "xml_class.h"

using namespace std;

int main() 
{
    cout << "Witaj w Banku PWP!" << endl;
    temprrary_data(); // Wywołanie funkcji dodającej tymczasowe dane do testów

    sign_in(); // Wywolanie funkcji logowania


    // Oczekuje na wejście żeby konsola się nie zamykała
    int zatrzymanie;
    cin >> zatrzymanie;

    //cout << users[4].getId(); // Testowe odczytanie id użytkownika


    return 0;
}

 
