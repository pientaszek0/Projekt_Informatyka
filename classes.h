#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================== Klasa użytkowników =======================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class User {
    private:
        vector<int> id;
        vector<string> first_name, last_name, login, password;
        vector<bool> admin; // Jeśli 1 to użytkownik jest administratorem
    public:
        // Metoda do zwracania ilości elemntów
        size_t getElementUser() {
            return id.size();
        }
        // Metoda zwracająca id użytkownika
        int getId(int index) {
            return this->id[index];
        }
        // Metoda zwracająca imie urzytkownika
        string getFirst_name(int index) {
            return this->first_name[index];
        }
        // Metoda zwracająca nazwisko urzytkownika
        string getLast_name(int index) {
            return this->last_name[index];
        }
        // Metoda zwracająca login urzytkownika
        string getLogin(int index) {
            return this->login[index];
        }
        // Metoda zwracająca hasło urzytkownika
        string getPassword(int index) {
            return this->password[index];
        }
        // Metoda zwracająca 1 jeśli użytkownik jest adminem i 0 jeśli nie jest
        bool isAdmin(int index) {
            return this->admin[index];
        }
        // Metoda do dodawania użytkowników za pomocą vectora
        void addUser(int u_id, string u_first_name, string u_last_name, string u_login, string u_password, bool u_admin) {
            id.emplace_back(u_id);
            first_name.emplace_back(u_first_name);
            last_name.emplace_back(u_last_name);
            login.emplace_back(u_login);
            password.emplace_back(u_password);
            admin.emplace_back(u_admin);
        }
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ============== Klasa kont należących do użytkowników ==============
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Account {
    private:
        vector<int> id, owner_id, currency_id;
        vector<string> account_number;
        vector<double> balance;
    public:
        // Metoda zwracają ilość kont
        int getElemenAccount() {
            return id.size();
        }
        // Metoda zwracająca id konta
        int getId(int index) {
            return this->id[index];
        }
        // Metoda zwracająca id właściciela konta
        int getOwner_id(int index) {
            return this->owner_id[index];
        }
        // Metoda zwracająca id waluty konta
        int getCurrency_id(int index) {
            return this->currency_id[index];
        }
        // Metoda zwracająca numer konta
        string getAccountNumber(int index) {
            return this->account_number[index];
        }
        // Metoda zwracająca stan konta
        double getBalance(int index) {
            return this->balance[index];
        }
        // Metoda zwiększająca stan konta   account1.increaseBalance(numer konta w wektorze, o ile zwiększyć stan konta)
        void increaseBalance(int index, double amount) {
            this->balance[index] += amount;
            return;
        }
        // Metoda zmniejszająca stan konta   account1.decreaseBalance(numer konta w wektorze, o ile zmniejszyć stan konta)
        void decreaseBalance(int index, double amount) {
            this->balance[index] -= amount;
            return;
        }
        // Metoda dodajaca nowe konto  account.addAccount(id_konta, id_wlasciciela, id_waluty_konta, numer_konta, stan_konta)
        void addAccount(int a_id, int a_owner_id, int a_currency_id, string a_account_number, double a_balance) {
            id.emplace_back(a_id);
            owner_id.emplace_back(a_owner_id);
            currency_id.emplace_back(a_currency_id);
            account_number.emplace_back(a_account_number);
            balance.emplace_back(a_balance);
            return;
        }
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================== Klasa typów walut ========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Currency {
    private:
        vector<int> id;
        vector<string> name;

    public:
        //Metoda zwracająca ilosc walut
        int getElementCurrency() {
            return id.size();
        }
        // Tymczasowa Metoda na potrzeby XML - zapsuje waluty;
         void addCurrency(int c_id, string c_name) {
            id.emplace_back(c_id);
            name.emplace_back(c_name);
            return;
        }
        // Metoda zwracająca ID
        int getId(int index) {
            return this->id[index];
        }
        // Metoda zwracająca ID właściciela
        string getName(int index) {
            return this->name[index];
        }

};
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ====================== Klasa typów kredytów =======================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Loan_Type {
    private:
        vector<int> id;
        vector<double> interest;  // Stopa procentowa
        vector<string> loan_type;

    public:
        // Metoda do zwracania ilości Loan Typow
        int getElementLoanType() {
            return id.size();
        }
        // Metoda zwracająca ID
        int getId(int index) {
            return this->id[index];
        }
        // Metoda zwracająca stopę procentową
        double getInterest(int index) {
            return this->interest[index];
        }
        // Metoda zwracająca nazwę typu kredytu
        string getLoanTypeName(int index) {
            return this->loan_type[index];
        }
        // Funkcja do splaty kredytu   loan.makePayment(wartosc splaty)
        double calcInterest(int index,double loanAmount, int years) {
            return loanAmount * (interest[index] / 100) * years ;
        }
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ========= Klasa kredytów zaciągniętych przez użytkowników =========
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Loan {
    private:
        vector<int> id;
        vector<int> owner_id;
        vector<string> currency_name;
        vector<string> loan_type;
        vector<double> balance_left; // Ile jeszcze zostało do spłacenia kredytu

    public:
        // Metoda do zwracania ilości Loanow
        int getElementLoan() {
            return id.size();
        }
        // Metoda zwracajaca Id
        int getId(int index) {
            return this->id[index];
        }
        // Metoda zwracająca ID właściciela
        int getOwnerId(int index) {
            return this->owner_id[index];
        }
        // Metoda zwracająca pozostałą kwotę kredytu
        double getBalanceLeft(int index) {
            return this->balance_left[index];
        }
        // Metoda zwracająca nazwe waluty
        string getCurrencyName(int index) {
            return this->currency_name[index];
        }
        // Funkcja zwracająca nazwe typu kredytu
        string getLoanTypeName(int index) {
            return this->loan_type[index];
        }
        // Funkcja do splaty kredytu   loan.makePayment(index, wartosc splaty)
        void makePayment(int index, double payment) {
            if (payment > 0 && payment <= balance_left[index]) {
                balance_left[index] -= payment;
                cout << "Splacono " << payment << ". Pozostalo do splaty: " << balance_left[index] << endl;
            } else {
                cout << "Nieprawidlowa kwota platnosci." << endl;
            }
        }

        // Funkcja zaciągania kredytu loan.takeLoan(wartosc kredytu, typ kredytu, nazwa waluty);
        void takeLoan(int index, double loanAmount, string loanType, string currencyName) {
            // Warunki: Sprawdzenie, czy kwota jest poprawna (wieksza niz 0)
            if (loanAmount > 0) {
                balance_left[index] += loanAmount;
                loan_type[index] = loanType;
                currency_name[index] = currencyName;
                cout << "Zaciągnięto kredyt w wysokosci: " << loanAmount << endl;
                cout << "Typ kredytu: " << loanType << endl;
                cout << "Waluta: " << currencyName << endl;
            } else {
                cout << "Nie spelniasz warunkow aby zaciagnac kredyt." << endl;
        }
}
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ============ Klasa lokat zalozonych przez użytkowników ============
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Deposit {
    private:

    public:
};

#endif
