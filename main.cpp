#include <iostream>
#include <vector>

#include "classes.h"
#include "functions.h"
#include "variables.h"
#include "xml_class.h"

using namespace std;

int main() 
{
    temprrary_data(user); // Wywołanie funkcji dodającej tymczasowe dane do testów
    xml_chf(user);
    sign_in(user); // Wywolanie funkcji logowania

    // Oczekuje na wejście żeby konsola się nie zamykała
    int zatrzymanie;
    cin >> zatrzymanie;

    return 0;
}

 
