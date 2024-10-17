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
        Loan_Type(int id, double interest, string loan_type) : id(id), interest(interest), loan_type(loan_type) {}

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
        Lone_type loan_type;
        double balance_left; // Ile jeszcze zostało do spłacenia kredytu

    public:
        // Konstruktor
        Loan(int owner_id, Lone_type loane_type, int currency_id, double balance_left) :
            owner_id(owner_id), loan_type(loan_type), currency_id(currency_id), balance_left(balance_left) {}

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
        
        // Funkcja zwracająca typ kredytu
        string getLoanType() const {
            return loan_type.getLoanTypeName();
        }
};
