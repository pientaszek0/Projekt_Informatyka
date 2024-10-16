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
};

// klasa typów kredytów
class Loan_Type {
    private:
        int id;
        double intrest;
        string name;
};

// Klasa kredytów zaciągnietych przez użytkowników
class Loan {
    private:
        int id, owner_id, loan_type_id, currency_id;
        double balance_left; // Ile jeszcze zostało do spłacenia kredytu
};