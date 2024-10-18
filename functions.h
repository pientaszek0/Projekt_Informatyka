#include <iostream>
#include "classes.h"
using namespace std;



























// Funkcje klasy Currency


// Funkcja zwracająca ID
int Currency::getId() const {
    return id;
}

// Funkcja zwracająca ID właściciela
string Currency::getName() const {
    return name;
}



// Funkcji klasy Loan_Type


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
