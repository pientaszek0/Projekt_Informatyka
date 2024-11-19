#include <iostream>
#include <vector>

#include "classes.h"
#include "functions.h"
#include "variables.h"
#include "xml_class.h"

using namespace std;

int main() {
    xml_chf(user); // Wywołanie funkcji do odczytu pliku xml 
    xml_giveData(user, account, currency, loan_type, loan, deposit); // Wywołanie funkcja która wczytuje dane z XML
    xml_checkData(user, account, currency, loan_type, loan, deposit); // Wywołanie funkcji sparwdza poprawność czy dane zostały dobrze wczytane !!TYLKO "User!!"
    xml_save(user, account, currency, loan_type, loan, deposit);

    // Tymczasowe dodawania wartosci walut zanim xml bedzie dzialac
    currency.setValue(1); // Zlotowki
    currency.setValue(0.24); // Dolar
    currency.setValue(0.23); // Euro
    currency.setValue(0.19); // Funt
    currency.setValue(0.22); // Frank
    // Pamietac zeby usunac metode currency.setValue()
    
    while (true) { // Nieskonczona petla zeby mozna bylo sie wylogowac i zalogowac na innego uzytkownika
        sign_in(); // Wywolanie funkcji logowania
        desktop(); // Wywolanie funkcji pokazujacej pulpit uzytkownika
    }

    return 0;
}