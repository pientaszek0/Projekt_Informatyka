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
        double interest;  // Stopa procentowa
        string loan_type;

    public:
        // Konstruktor
        Loan_Type(int id_, double interest_, string loan_type_) : id(id_), interest(interest_), loan_type(loan_type_) {}

        // Funkcja zwracająca stopę procentową
        double getInterest() const {
            return interest;
        }

        // Funkcja zwracająca nazwę typu kredytu
        string getLoanTypeName() const {
            return loan_type;
        }

        // Funkcja obliczająca całkowite odsetki na podstawie kwoty kredytu i lat
        double calcInterest(double loanAmount, int years) const {
            return loanAmount * interest * years / 100; // Prosty wzór na odsetki
        }
};

// Klasa kredytów zaciągniętych przez użytkowników
class Loan {
    private:
        int owner_id, currency_id;
        string loan_type;
        double balance_left; // Ile jeszcze zostało do spłacenia kredytu

    public:
        // Konstruktor
        Loan(int owner_id_, string loan_type_, int currency_id_, double balance_left_) :
            owner_id(owner_id_), loan_type(loan_type_), currency_id(currency_id_), balance_left(balance_left_) {}

        // Funkcja do spłaty części kredytu
        void makePayment(double payment) {
            if (payment > 0 && payment <= balance_left) {
                balance_left -= payment;
                cout << "Spłacono " << payment << ". Pozostało do spłaty: " << balance_left << endl;
            } else {
                cout << "Nieprawidłowa kwota płatności." << endl;
            }
        }

        // Funkcja zwracająca ile pozostało do spłacenia
        double getBalanceLeft() const {
            return balance_left;
        }

        // Funkcja zwracająca ID właściciela
        int getOwnerId() const {
            return owner_id;
        }
        
        // Funkcja zwracająca ID typu kredytu
        int getLoanType() const {
            return loan_type;
        }
};
