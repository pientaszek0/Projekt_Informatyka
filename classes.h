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
        vector<double> value;

    public:
        //Metoda zwracająca ilosc walut
        int getElementCurrency() {
            return id.size();
        }
        // Metoda na potrzeby XML - zapsuje waluty;
        void addCurrency(int c_id, string c_name, double c_value) {
            id.emplace_back(c_id);
            name.emplace_back(c_name);
            value.emplace_back(c_value);
            return;
        }
        // Metoda zwracająca ID
        int getId(int index) {
            return this->id[index];
        }
        // Metoda zwracająca ID waluty
        string getName(int index) {
            return this->name[index];
        }
        // Metoda zwracająca wartosc waluty
        double getValue(int index) {
            return this->value[index];
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
        // Metoda na potrzeby XML - zapisuje Typy kerdytów;
        void addLoanType(int lt_id, double lt_interest, string lt_loan_type) {
            id.emplace_back(lt_id);
            interest.emplace_back(lt_interest);
            loan_type.emplace_back(lt_loan_type);
            return;
        }
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
        // Funkcja liczaca interest
        double calcInterest(int index, double loanAmount, int years) {
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
        // Funkcja zaciągania kredytu loan.takeLoan(id ,owner id,nazwa waluty, typ kredytu, wartosc kredytu);
        void addLoan(int l_id, int l_owner_id, string l_currency_name, string l_loan_type, double l_balance_left) {
            id.emplace_back(l_id);
            owner_id.emplace_back(l_owner_id);
            currency_name.emplace_back(l_currency_name);
            loan_type.emplace_back(l_loan_type);
            balance_left.emplace_back(l_balance_left);
            return;
        }
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
            balance_left[index] -= payment;
            system("cls");
            if (balance_left[index] <= 0) {
                cout << "Kredyt zostal calkowicie splacony." << endl;
                removeLoan(index);
            }else{
                cout << "Splacono: " << payment << ". Pozostalo do splaty: " << balance_left[index] << endl;
            }
        }

        // Funkcja do usunięcia kredytu
        void removeLoan(int index) {
            if (index >= 0 && index < Loan::getElementLoan()) {
                id.erase(id.begin() + index);
                owner_id.erase(owner_id.begin() + index);
                currency_name.erase(currency_name.begin() + index);
                loan_type.erase(loan_type.begin() + index);
                balance_left.erase(balance_left.begin() + index);
            }
        }
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ============ Klasa lokat zalozonych przez użytkowników ============
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Deposit {
    private:
        vector<int> id;
        vector<int> owner_id;              // ID właściciela lokaty
        vector<double> deposit_amount;     // Kwota lokaty
        vector<string> currency_name;      // Waluta lokaty
        vector<int> duration_months;       // Czas trwania lokaty w miesiącach
        vector<double> interest_rate;      // Oprocentowanie
        vector<string> start_date;         // Data założenia lokaty
        vector<int> remaining_time;        // Pozostały czas do zakończenia (w miesiącach)

    public:
        // Funkcja zaciągania lokaty loan.addDeposit(id, owner id, wartosc lokaty, nazwa waluty, dlugosc(mies), interest, data poczatkowa, data koncowa);
        void addDeposit(int d_id, int d_owner_id, double d_deposit_amount, string d_currency_name, int d_duration_months,
         double d_interest_rate, string d_dstart_date, int d_remaining_time)
        {
            id.emplace_back(d_id);
            owner_id.emplace_back(d_owner_id);
            deposit_amount.emplace_back(d_deposit_amount);
            currency_name.emplace_back(d_currency_name);
            duration_months.emplace_back(d_duration_months);
            interest_rate.emplace_back(d_interest_rate);
            start_date.emplace_back(d_dstart_date);
            remaining_time.emplace_back(d_remaining_time);
        }
        // Metoda do zwracania ilości Loanow
        int getElementDeposit() {
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
        // Metoda zwracająca kwotę lokaty
        double getDepositAmount(int index) {
            return this->deposit_amount[index];
        }
        // Metoda zwracająca walutę lokaty
        string getCurrencyName(int index) {
            return this->currency_name[index];
        }
        // Metoda zwracająca czas trwania lokaty
        int getDurationMonths(int index) {
            return this->duration_months[index];
        }
        // Metoda zwracająca oprocentowanie
        double getInterestRate(int index) {
            return this->interest_rate[index];
        }
        // Metoda zwracająca datę założenia lokaty
        string getStartDate(int index) {
            return this->start_date[index];
        }
        // Metoda zwracająca pozostały czas do zakończenia lokaty
        int getRemainingTime(int index) {
            return this->remaining_time[index];
        }
        // Metoda zmieniająca pozostały czas na aktualny
        void setRemainingTime(int index, int time) {
            this->remaining_time[index] = time; 
        }
        // Metoda obliczająca odsetki dla lokaty
        double calculateInterest(int index) {
            return deposit_amount[index] * (interest_rate[index] / 100) * (duration_months[index] / 12.0);
        }
        // Funkcja do zakończenia lokaty
        void endDeposit(int index) {
            system("cls");
            cout << "Lokata zakonczona. Kwota wyplacona: " << deposit_amount[index] + calculateInterest(index) << endl;
            deposit_amount[index] = 0; // Resetowanie lokaty po zakończeniu
        }
        // Funkcja do usunięcia lokaty
        void removeDeposit(int index) {
            if (index >= 0 && index < getElementDeposit()) {
                id.erase(id.begin() + index);
                owner_id.erase(owner_id.begin() + index);
                deposit_amount.erase(deposit_amount.begin() + index);
                currency_name.erase(currency_name.begin() + index);
                duration_months.erase(duration_months.begin() + index);
                interest_rate.erase(interest_rate.begin() + index);
                start_date.erase(start_date.begin() + index);
                remaining_time.erase(remaining_time.begin() + index);
            }
        }
};

#endif