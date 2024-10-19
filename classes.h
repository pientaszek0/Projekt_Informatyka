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
        // Konstruktor metody  User user1(id, imie, nazwisko, login, hasło, 1 lub 0 )
       User(vector<int> id, vector<string> first_name, vector<string> last_name, vector<string> login, vector<string> password, vector<bool> admin) {
            this->id = id;
            this->first_name = first_name;
            this->last_name = last_name;
            this->login = login;
            this->password = password;
            this->admin = admin;
        }

       User() {}; //Jest to domyślny konstruktor Potrzebny do vectorów bo bez tego nie działa XD

        // Metoda do zwracania ilości elemntów
        size_t getElementUser()
        {
            return id.size();
        }
       
        // do każdej metody jest zmiena index

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
        void addUser(int u_id, string u_first_name, string u_last_name, string u_login, string u_password, bool u_admin)
        {
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

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================== Klasa typów walut ========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Currency {
    private:
        vector<int> id;
        vector<string> name;

    public:
        // Konstruktor metody Currency currency1(id, nazwa waluty)
        Currency(vector<int> id, vector<string> name) {
            this->id = id;
            this->name = name;
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
        // Konstruktor metody Loan_Type morgage1(id, stopa procentowa, nazwa typu kredytu)
        Loan_Type(vector<int> id, vector<double> interest, vector<string> loan_type) {
            this->id = id;
            this->interest = interest;
            this->loan_type = loan_type;
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
        vector<int> owner_id;
        vector<Currency> currency_name;
        vector<Loan_Type> loan_type;
        vector<double> balance_left; // Ile jeszcze zostało do spłacenia kredytu

    public:
        // Konstruktor metody Loan loan1(id_właściciela, waluta, typ kredytu, ile zostało do spłaty)
        Loan(vector<int> owner_id, vector<Currency> currency_name, vector<Loan_Type> loan_type, vector<double> balance_left) {
            this->owner_id = owner_id;
            this->currency_name = currency_name;
            this->loan_type = loan_type;
            this->balance_left = balance_left;
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
            return currency_name[index].getName(0); // Use 0 if there's only one loan type
        }
        // Funkcja zwracająca nazwe typu kredytu
        string getLoanTypeName(int index) {
            return loan_type[index].getLoanTypeName(0); // Use 0 if there's only one currency name
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
        void takeLoan(int index, double loanAmount, Loan_Type loanType, Currency currencyName) {
            // Warunki: Sprawdzenie, czy kwota jest poprawna (wieksza niz 0)
            if (loanAmount > 0) {
                balance_left[index] += loanAmount;
                loan_type[index] = loanType;
                currency_name[index] = currencyName;

                cout << "Zaciągnięto kredyt w wysokosci: " << loanAmount << endl;
                cout << "Typ kredytu: " << loanType.getLoanTypeName(0) << endl;        // Use 0 if there's only one loan type
                cout << "Waluta: " << currencyName.getName(0) << endl;      // Use 0 if there's only one currency name
            } else {
                cout << "Nie spelniasz warunkow aby zaciagnac kredyt." << endl;
        }
}
};

#endif
