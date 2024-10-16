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
        string name;

    public:
        // Konstruktor
        Loan_Type(int id_, double interest_, string name_) : id(id_), interest(interest_), name(name_) {}

        // Funkcja zwracająca stopę procentową
        double getInterest() const {
            return interest;
        }

        // Funkcja zwracająca nazwę typu kredytu
        string getName() const {
            return name;
        }

        // Funkcja ustawiająca nową stopę procentową
        void setInterest(double newInterest) {
            interest = newInterest;
        }

        // Funkcja obliczająca całkowite odsetki na podstawie kwoty kredytu i lat
        double calcInterest(double loanAmount, int years) const {
            return loanAmount * interest * years / 100; // Prosty wzór na odsetki
        }
};

// Klasa kredytów zaciągniętych przez użytkowników
class Loan {
    private:
        int id, owner_id, loan_type_id, currency_id;
        double balance_left; // Ile jeszcze zostało do spłacenia kredytu

    public:
        // Konstruktor
        Loan(int id_, int owner_id_, int loan_type_id_, int currency_id_, double balance_left_) :
            id(id_), owner_id(owner_id_), loan_type_id(loan_type_id_), currency_id(currency_id_), balance_left(balance_left_) {}

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
        int getLoanTypeId() const {
            return loan_type_id;
        }
};
