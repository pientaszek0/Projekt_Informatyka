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
        Currency(int id, string name);
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
        Loan_Type(int id, double interest, string loan_type);

        //Funkcje
        double getInterest() const;
        string getLoanTypeName() const;
        double calcInterest(double loanAmount, int years) const;
};

// Klasa kredytów zaciągniętych przez użytkowników
class Loan {
    private:
        int owner_id, currency_id;
        Loan_type loan_type;
        double balance_left; // Ile jeszcze zostało do spłacenia kredytu

    public:
        // Konstruktor
        Loan(int owner_id, Loan_type loan_type, int currency_id, double balance_left);

        // Funkcje
        void makePayment(double payment);
        double getBalanceLeft() const;
        int getOwnerId() const;
        string getLoanType() const;
};
