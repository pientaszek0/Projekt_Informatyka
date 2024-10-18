#include <iostream>
#include <vector>

#include "classes.h"
#include "variables.h"

using namespace std;


// Funkcje klasy Currency



// Funkcji klasy Loan_Type


// Funkcja obliczająca odsetki     loan_type.calcInterest(wartość kredytu, liczba lat)
double Loan_Type::calcInterest(double loanAmount, int years) const {
    return loanAmount * interest * years / 100;
}



// Funkcji klasy Loan


// Funkcja do spłaty kredytu     loan.makePayment(wartość spłaty)
void Loan::makePayment(double payment) {
    if (payment > 0 && payment <= balance_left) {
        balance_left -= payment;
        cout << "Spłacono " << payment << ". Pozostało do spłaty: " << balance_left << endl;
    } else {
        cout << "Nieprawidłowa kwota płatności." << endl;
    }
}

// Funkcja zwracająca nazwę typu kredytu
string Loan::getLoanTypeName() const {
    return loan_type.getLoanTypeName();
}


// Funkcja logowania urzytkownika (nie działa jeszcze)
void sign_in() {
    cout << "Podaj login: ";
    string login;
    cin >> login;
    cout << "Podaj hasło: ";
    string password;
    cin >> password;
    cout << "Zalogowano jako " << login << endl;
    return;
}

// Funkcja dodająca tymczasowe przykładowe dane do testowania aplikacji
void temprrary_data() {
    User user1(20, "Jan", "Kowalski", "admin", "admin", 1);
    users.push_back(user1);
    User user2(43, "Adrian", "Prymas", "user1", "user1", 0);
    users.push_back(user2);
    User user3(25, "Jan", "Piętka", "user2", "user2", 0);
    users.push_back(user3);
    User user4(21, "Andrzej", "Nowak", "user3", "user3", 0);
    users.push_back(user4);
    User user5(53, "Michał", "Ryba", "user4", "user4", 0);
    users.push_back(user5);
    return;
}