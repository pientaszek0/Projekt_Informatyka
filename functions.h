#include <iostream>
#include "classes.h"
using namespace std;



























// Funkcje klasy Currency

//Konstruktor
Currency::Currency(int id, string name) : id(id), name(name) {}

// Funkcja zwracająca ID
int Currency::getId() const {
    return id;
}

// Funkcja zwracająca ID właściciela
string Currency::getName() const {
    return name;
}



// Funkcji klasy Loan_Type

// Konstruktor
Loan_Type::Loan_Type(int id, double interest, string loan_type) : id(id), interest(interest), loan_type(loan_type) {}

// Funkcja zwracająca stopę procentową
double Loan_Type::getInterest() const {
    return interest;
}

// Funkcja zwracająca nazwę typu kredytu
string Loan_Type::getLoanTypeName() const {
    return loan_type;
}

// Funkcja obliczająca odsetki     loan_type.calcInterest(wartość kredytu, liczba lat)
double Loan_Type::calcInterest(double loanAmount, int years) const {
    return loanAmount * interest * years / 100;
}



// Funkcji klasy Loan

// Konstruktor
Loan::Loan(int owner_id, Loan_Type loan_type, int currency_id, double balance_left) :
    owner_id(owner_id), loan_type(loan_type), currency_id(currency_id), balance_left(balance_left) {}

// Funkcja do spłaty kredytu     loan.makePayment(wartość spłaty)
void Loan::makePayment(double payment) {
    if (payment > 0 && payment <= balance_left) {
        balance_left -= payment;
        cout << "Spłacono " << payment << ". Pozostało do spłaty: " << balance_left << endl;
    } else {
        cout << "Nieprawidłowa kwota płatności." << endl;
    }
}

// Funkcja zwracająca pozostałą kwotę kredytu
double Loan::getBalanceLeft() const {
    return balance_left;
}

// Funkcja zwracająca ID właściciela
int Loan::getOwnerId() const {
    return owner_id;
}

// Funkcja zwracająca nazwę typu kredytu
string Loan::getLoanTypeName() const {
    return loan_type.getLoanTypeName();
}
