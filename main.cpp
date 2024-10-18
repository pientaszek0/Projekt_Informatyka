#include <iostream>
#include <vector>

#include "classes.h"
#include "functions.h"
#include "variables.h"

using namespace std;

int main() 
{
    cout << "Hello World" << endl;
    temprrary_data(); // Wywołanie funkcji dodającej tymczasowe dane do testów
    cout << users.at(4).getId(); // Testowe odczytanie id użytkownika
    return 0;
}

 
