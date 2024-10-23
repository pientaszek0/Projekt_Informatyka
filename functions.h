#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

#include "classes.h"
#include "variables.h"
#include "xml_class.h"

using namespace std;

// Adrian Prymas
// funckja do pobierania czasu
string czas()
{
    // Pobranie aktualnego czasu
    time_t actual_time = time(0);

    // Konwersja na czytelny format
    char* Time = ctime(&actual_time);

    // Zapisanie daty i godziny do zmiennej
    string Date = Time;

    Date.erase(Date.length() - 1);  // Usuwa ostatni znak, czyli '\n'

    return Date;
}

// Adrian Prymas
// Funkcja do Logów txt
void txt_log(string logs)
{
    ofstream log("logs.txt", ios::app); // Otwarcie w trypie nadpisu
    if(log)  cout << "---PLIK ISTNIEJE---";
    else cout << "---PLIK ZOSTAL UTWORZONY---";

    if (!log.is_open())
	{
        cout << error02 << endl;
        return;
    }
    log << czas() << " : " << logs << endl;
}

// Jan Piętka
// Funkcja logowania urzytkownika
void sign_in(User &user) 
{
    string login;
    string password;
    bool loged_in = 0;
    system("cls");
    cout << "Witaj w Banku PWP!" << endl;

    do {
        cout << "Podaj login: ";
        cin >> login;
        cout << "Podaj haslo: ";
        cin >> password;

        for (int i = 0 ; i < user.getElementUser(); i++) {
            cout << i;
            if (login == user.getLogin(i) && password == user.getPassword(i)) { 
                courent_user = i;
                system("cls");
                loged_in = 1;
                return;
            }
        }
        system("cls");
        cout << "Nieprawidlowy login lub haslo." << endl;

    } while (!loged_in);
}

// Jan Piętka
// Funkcja obslugujaca menu kont
void accountsMenu(User user, int courent_user) {
    system("cls");

    while (true) {
        vector<int> userAccounts;
        int accountAmount = 0;
        
        cout << "Twoje Konta:" << endl;
        cout << "Lp.           Numer Konta          Stan Konta" << endl;

        for (int i = 0; i < account.getElemenAccount(); i++) {
            if (account.getOwner_id(i) == user.getId(courent_user)) {
                userAccounts.push_back(i);
                accountAmount++;
                cout << accountAmount << " - " << account.getAccountNumber(i) << " - " << account.getBalance(i) << " ";
                for (int n = 0; n < currency.getElementCurrency(); n++) {
                    if (account.getCurrency_id(i) == currency.getId(n)) {
                        cout << currency.getName(n) << endl;
                    }
                }
            }
        }

        if (accountAmount == 0) {
            cout << "Nie masz zadnych kont." << endl;
        }
        
        cout << accountAmount+1 << " - Zaloz nowe konto" << endl;
        cout << "0 - Wyjdz do pulpitu" << endl;

        cout << "Aby wykonac przelew wybierz konto zrodlowe wpisujac liczbe porzadkowa: ";
        int menu;
        cin >> menu;

        if (menu == 0) {
            system("cls");
            return;
        } else if (menu == accountAmount+1) {
            system("cls");
            cout << "Tworzenie konta." << endl;
            // wypisac waluty i wygenerowac numer konta

            cout << "Wybierz walute konta: ";
            int waluta;
            cin >> waluta;
        }
        
            
        if (menu<1 || menu>accountAmount) {
            system("cls");
            cout << "Nieprawidlowy wybor." << endl;
        } else {
            string accountNumber;
            cout << "Przykladowy numer konta: PL12345678901234567890123456" << endl;
            cout << "Numer konta docelowego: ";
            cin >> accountNumber;

            for (int i = 0; i < account.getElemenAccount(); i++) {
                if (account.getAccountNumber(i) == accountNumber && accountNumber != account.getAccountNumber(userAccounts[menu-1])) {
                    double amount;
                    cout << "Podaj kwote przelewu: ";
                    cin >> amount;

                    if ((amount*100)-int(amount*100) != 0 || amount <= 0) {
                        system("cls");
                        cout << "Nieprawidlowa kwota." << endl;
                    } else if (amount > account.getBalance(userAccounts[menu-1])) {
                        system("cls");
                        cout << "Niewystarczajace srodki na koncie." << endl;
                    } else if (account.getCurrency_id(i) != account.getCurrency_id(userAccounts[menu-1])) {
                        system("cls");
                        cout << "Wybrane konta sa w roznych walutach." << endl;
                    } else {
                        account.decreaseBalance(userAccounts[menu-1], amount);
                        account.increaseBalance(i, amount);
                        system("cls");
                        cout << "Wykonano przelew." << endl;;
                    }
                    break;

                } else if (i+1 >= account.getElemenAccount()) {
                    system("cls");
                    cout << "Nieprawidlowy numer konta." << endl;
                }
            }
        }
    }
    
    return;
}

// Michal Wierzbicki
// Funkcja obslugujaca menu kredytow
void loansMenu(User user, int courent_user) {
    system("cls");

    while (true) {
        vector<int> userLoans;
        int loanAmount = 0;

        cout << "Twoje Kredyty:" << endl;
        cout << "Lp.           Typ Kredytu          Pozostala Kwota do Splaty          Waluta" << endl;

        for (int i = 0; i < loan.getElementLoan(); i++) {
            if (loan.getOwnerId(i) == user.getId(courent_user)) {
                userLoans.push_back(i);
                loanAmount++;
                cout << loanAmount << " - " << loan.getLoanTypeName(i) << " - " << loan.getBalanceLeft(i) << " ";
                for (int n = 0; n < currency.getElementCurrency(); n++) {
                    if (loan.getCurrencyName(i) == currency.getName(n)) {
                        cout << currency.getName(n) << endl;
                    }
                }
            }
        }

        cout << "0 - Wyjdz do pulpitu" << endl;
        cout << "1 - Zaciagnij nowy kredyt" << endl;

        if (loanAmount) {
            cout << "Aby wykonac splate wybierz kredyt wpisujac liczbe porzadkowa: ";
        } else {
            cout << "Nie masz zadnych kredytow. Aby zaciagnac kredyt, wybierz opcje 1." << endl;
        }

        int menu;
        cin >> menu;

        if (menu == 0) {
            system("cls");
            return;
        }

        // Spłata kredytu
        if (menu > 1 && menu <= loanAmount + 1) {
            double paymentAmount;
            cout << "Podaj kwote splaty: ";
            cin >> paymentAmount;

            if ((paymentAmount * 100) - int(paymentAmount * 100) != 0 || paymentAmount <= 0) {
                system("cls");
                cout << "Nieprawidlowa kwota." << endl;
            } else if (paymentAmount > loan.getBalanceLeft(userLoans[menu - 2])) {
                system("cls");
                cout << "Kwota splaty przewyzsza saldo kredytu." << endl;
            } else {
                loan.makePayment(userLoans[menu - 2], paymentAmount);
            }
        }

        // Zaciąganie nowego kredytu
        else if (menu == 1) {
            double loanAmount;
            int loanTypeIndex, currencyIndex;

            cout << "Podaj kwote kredytu: ";
            cin >> loanAmount;

            if (loanAmount <= 0) {
                system("cls");
                cout << "Nieprawidlowa kwota." << endl;
                continue;
            }

            // Wybór typu kredytu
            cout << "Wybierz typ kredytu: " << endl;
            for (int i = 0; i < loan_type.getElementLoanType(); i++) {
                cout << i + 1 << " - " << loan_type.getLoanTypeName(i) << " (Stopa procentowa: " << loan_type.getInterest(i) << "%)" << endl;
            }
            cin >> loanTypeIndex;
            loanTypeIndex--; // Indeksy zaczynają się od 0

            if (loanTypeIndex < 0 || loanTypeIndex >= loan_type.getElementLoanType()) {
                system("cls");
                cout << "Nieprawidlowy wybor typu kredytu." << endl;
                continue;
            }

            // Wybór waluty
            cout << "Wybierz walute kredytu: " << endl;
            for (int i = 0; i < currency.getElementCurrency(); i++) {
                cout << i + 1 << " - " << currency.getName(i) << endl;
            }
            cin >> currencyIndex;
            currencyIndex--; // Indeksy zaczynają się od 0

            if (currencyIndex < 0 || currencyIndex >= currency.getElementCurrency()) {
                system("cls");
                cout << "Nieprawidlowy wybor waluty." << endl;
                continue;
            }

            // Dodanie nowego kredytu
            loan.takeLoan(loan.getOwnerId(courent_user), loanAmount, loan_type.getLoanTypeName(loanTypeIndex), currency.getName(currencyIndex));
        }

        else {
            system("cls");
            cout << "Nieprawidlowy wybor." << endl;
        }
    }

    return;
}

// Michal Wierzbicki
// Funkcja obslugujaca menu lokat
void depositsMenu(User user, int courent_user) {
    system("cls");

    while (true) {
        vector<int> userDeposits;
        int depositCount = 0;

        cout << "Twoje Lokaty:" << endl;
        cout << "Lp.           Kwota Lokaty          Oprocentowanie          Czas Trwania          Waluta          Pozostaly Czas" << endl;

        // Wyświetlanie lokat użytkownika
        for (int i = 0; i < deposit.getElementDeposit(); i++) {
            if (deposit.getOwnerId(i) == user.getId(courent_user)) {
                userDeposits.push_back(i);
                depositCount++;
                cout << depositCount << " - " << deposit.getDepositAmount(i) << " - " << deposit.getInterestRate(i) << "% - " 
                     << deposit.getDurationMonths(i) << " mies. - " << deposit.getCurrencyName(i) 
                     << " - " << deposit.getRemainingTime(i) << " mies." << endl;
            }
        }

        // Opcje dla użytkownika
        cout << "0 - Wyjdz do pulpitu" << endl;
        cout << "1 - Zaloz nowa lokate" << endl;

        if (depositCount > 0) {
            cout << "Aby zakonczyc lokate wybierz numer porzadkowy: ";
        } else {
            cout << "Nie masz zadnych lokat. Aby zalozyc lokate, wybierz opcje 1." << endl;
        }

        int menu;
        cin >> menu;

        // Wyjście z menu
        if (menu == 0) {
            system("cls");
            return;
        }

        // Zakończenie lokaty
        if (menu > 1 && menu <= depositCount + 1) {
            int depositIndex = userDeposits[menu - 2]; // indeks lokaty w wektorze
            deposit.endDeposit(depositIndex);
        }

        // Założenie nowej lokaty
        else if (menu == 1) {
            double depositAmount;
            int currencyIndex, durationMonths;
            double interestRate;

            cout << "Podaj kwote lokaty: ";
            cin >> depositAmount;

            if (depositAmount <= 0) {
                system("cls");
                cout << "Nieprawidlowa kwota." << endl;
                continue;
            }

            // Wybór waluty
            cout << "Wybierz walute lokaty: " << endl;
            for (int i = 0; i < currency.getElementCurrency(); i++) {
                cout << i + 1 << " - " << currency.getName(i) << endl;
            }
            cin >> currencyIndex;
            currencyIndex--; // Indeksy zaczynają się od 0

            if (currencyIndex < 0 || currencyIndex >= currency.getElementCurrency()) {
                system("cls");
                cout << "Nieprawidlowy wybor waluty." << endl;
                continue;
            }

            // Wybór czasu trwania lokaty
            cout << "Podaj czas trwania lokaty w miesiacach: ";
            cin >> durationMonths;

            if (durationMonths <= 0) {
                system("cls");
                cout << "Nieprawidłowy czas trwania." << endl;
                continue;
            }

            // Ustal oprocentowanie lokaty (dla przykładu ustalamy stałe oprocentowanie na podstawie czasu trwania)
            if (durationMonths <= 6) {
                interestRate = 2.0;
            } else if (durationMonths <= 12) {
                interestRate = 3.0;
            } else if (durationMonths <= 24) {
                interestRate = 3.5;
            } else {
                interestRate = 4.0;
            }

            // Dodanie nowej lokaty
            deposit.takeDeposit(deposit.getOwnerId(courent_user), depositAmount, currency.getName(currencyIndex), durationMonths, interestRate, czas());
        }

        // Nieprawidłowy wybór
        else {
            system("cls");
            cout << "Nieprawidlowy wybor." << endl;
        }
    }

    return;
}


// Jan Piętka
// Funkcja obslugujaca menu administratora
void adminMenu(User user, int courent_user) {
    system("cls");
    cout << "Panel Administratora:" << endl;
    cout << "Wybierz opcje przez wpisanie jej numeru: ";
    return;
}

// Jan Piętka
// Funkcja wyświetlajaca i obslugujaca pupit aktualnie zalogowanego uzytkownika  destop(obiekt z wektorami, numer w wektorze zalogowanego uzytkownika)
void desktop(User user, int courent_user) {
    int menu;
    system("cls");
    int log_out = 1;

    while (log_out) {
        cout << "Zalogowano jako: " << user.getFirst_name(courent_user) << " " << user.getLast_name(courent_user) << endl;
        cout << "1 - Konta" << endl;
        cout << "2 - Kredyty" << endl;
        cout << "3 - Lokaty" << endl;
        cout << "0 - Wyloguj i zapisz zmiany" << endl;
        if (user.isAdmin(courent_user)) {
            cout << "10 - Menu Administratora" << endl;
        }
        cout << "Wybierz opcje przez wpisanie jej numeru: ";
        cin >> menu;

        switch (menu) {
        case 1: {
            accountsMenu(user, courent_user);
            break;
        }
        case 2: {
            loansMenu(user, courent_user);
            break;
        }
        case 3: {
            depositsMenu(user, courent_user);
            break;
        }
        case 0: {
            log_out = 0;
            xml_save(user, account, currency, loan_type, loan, deposit);
            break;
        }
        case 10: {
            if (user.isAdmin(courent_user)) {
                adminMenu(user, courent_user);
            } else {
                system("cls");
                cout << "Nieprawidlowy numer opcji." << endl;
            }
            break;
        }
        default:
            system("cls");
            cout << "Nieprawidlowy numer opcji." << endl;
            break;
        }
    }

    return;
}

#endif