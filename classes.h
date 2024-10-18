#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <vector>

using namespace std;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================== Klasa użytkowników =======================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class User {
    private:
        int id;
        string first_name, last_name, login, password;
        bool admin; // Jeśli 1 to użytkownik jest administratorem
    public:
        // Konstruktor metody  User user1(id, imie, nazwisko, login, hasło, 1 lub 0 )
        User(int id, string first_name, string last_name, string login, string password, bool admin) {
            this->id = id;
            this->first_name = first_name;
            this->last_name = last_name;
            this->login = login;
            this->password = password;
            this->admin = admin;
        }
        // Metoda zwracająca id użytkownika
        int getId() {
            return this->id;
        }
        // Metoda zwracająca imie urzytkownika
        string getFirst_name() {
            return this->first_name;
        }
        // Metoda zwracająca nazwisko urzytkownika
        string getLast_name() {
            return this->last_name;
        }
        // Metoda zwracająca login urzytkownika
        string getLogin() {
            return this->login;
        }
        // Metoda zwracająca hasło urzytkownika
        string getPassword() {
            return this->password;
        }
        // Metoda zwracająca 1 jeśli użytkownik jest adminem i 0 jeśli nie jest
        bool isAdmin() {
            return this->admin;
        }
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ============ Klasa kont należących do użytkowników ================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Account {
    private:
        int id, owner_id, currency_id;
        double balance;
    public:
        // Konstruktor klasy Account account1(id, id_właściciela, id_waluty, stan_konta)
        Account(int id, int owner_id, int currency_id, double balance) {
            this->id = id;
            this->owner_id = owner_id;
            this->currency_id = currency_id;
            this->balance = balance;
        }
        // Metoda zwracająca id konta
        int getId() {
            return this->id;
        }
        // Metoda zwracająca id właściciela konta
        int getOwner_id() {
            return this->owner_id;
        }
        // Metoda zwracająca id waluty konta
        int getCurrency_id() {
            return this->currency_id;
        }
        // Metoda zwracająca stan konta
        double getBalance() {
            return this->balance;
        }
        // Metoda zwiększająca stan konta   account1.increaseBalance(o ile zwiększyć stan konta)
        void increaseBalance(double amount) {
            this->balance += amount;
        }
        // Metoda zmniejszająca stan konta   account1.decreaseBalance(o ile zmniejszyć stan konta)
        void decreaseBalance(double amount) {
            this->balance -= amount;
        }
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

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ====================== klasa typów kredytów =======================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======= Klasa kredytów zaciągniętych przez użytkowników ===========
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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