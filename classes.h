#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
using namespace std;

// Klasa użytkowników
class User {
    private:
        int id;
        string first_name, last_name, login, password;
        bool admin; // Jeśli 1 to użytkownik jest administratorem
};

// Klasa kont należących do użytkowników
class Account {
    private:
        int id, owner_id, currency_id;
        double balance;
};

// Klasa typów walut
class Currency {
    private:
        int id;
        string name;

    public:
        // Konstruktor
        Currency(int id, string name) : id(id), name(name) {}

        //Funkcje
        int getId() const;
        string getName() const;
};



// klasa typów kredytów
class Loan_Type {
    private:
        int id;
        double interest;  // Stopa procentowa
        string loan_type;

    public:
        // Konstruktor
        Loan_Type(int id, double interest, string loan_type) : id(id), interest(interest), loan_type(loan_type) {};

        //Funkcje
        double getInterest() const;
        string getLoanTypeName() const;
        double calcInterest(double loanAmount, int years) const;
};

// Klasa kredytów zaciągniętych przez użytkowników
class Loan {
    private:
        int owner_id;
        int currency_id;
        Loan_Type loan_type;
        double balance_left; // Ile jeszcze zostało do spłacenia kredytu

    public:
        // Konstruktor
        Loan(int owner_id, int currency_id, Loan_Type loan_type, double balance_left) : owner_id(owner_id), currency_id(currency_id), loan_type(loan_type), balance_left(balance_left) {}

        // Funkcje
        void makePayment(double payment);
        double getBalanceLeft() const;
        int getOwnerId() const;
        string getLoanTypeName() const;
};

#endif