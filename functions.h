#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

#include "classes.h"
#include "variables.h"

using namespace std;

// Funkcja dodająca tymczasowe przykladowe dane do testowania aplikacji
void temprrary_data(User &user, Account &account, Currency &currency) {
    user.addUser(20, "Jan", "Kowalski", "admin", "admin", true);
    user.addUser(43, "Adrian", "Prymas", "user1", "user1", false);
    user.addUser(25, "Jan", "Pietka", "user2", "user2", false);
    user.addUser(21, "Andrzej", "Nowak", "user3", "user3", false);
    user.addUser(53, "Michal", "Ryba", "user4", "user4", false);
    account.addAccount(34, 20, 0, "PL01345678901234567890123456", 1.37);
    account.addAccount(35, 20, 0, "PL02345678901234567890123456", 2.37);
    account.addAccount(36, 20, 1, "PL03345678901234567890123456", 3.37);
    account.addAccount(38, 20, 2, "PL04345678901234567890123456", 4.37);
    account.addAccount(42, 43, 0, "PL05370078901234567890123456", 21.37);
    account.addAccount(66, 25, 2, "EU06345678901234567890123456", 21.37);
    account.addAccount(21, 21, 0, "PL07345678901234567890122137", 21.37);
    account.addAccount(37, 43, 1, "US08345678901234567890123456", 21.37);
    currency.addCurrency(0, "PLN");
    currency.addCurrency(1, "USD");
    currency.addCurrency(2, "EUR");
    return; 
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

        if (accountAmount) {
            cout << "0 - Wyjdz do pulpitu" << endl;
            cout << "Aby wykonac przelew wybierz konto zrodlowe wpisujac liczbe porzadkowa: ";
            int menu;
            cin >> menu;

            if (menu == 0) {
                system("cls");
                return;
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
                            cout << "Niewystarczajace srodki na koncie. " << endl;
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
            
        } else {
            cout << "Nie masz zadnych kont.";
            // Tutaj opcja powrotu i dodawania konta
        }
    }
    
    return;
}

// Jan Piętka
// Funkcja obslugujaca menu kredytow
void loansMenu(User user, int courent_user) {

    return;
}

// Jan Piętka
// Funkcja obslugujaca menu lokat
void depositsMenu(User user, int courent_user) {

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
            // Tutaj Wywolac funkcje zapisujaca do xml
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
    log << logs << endl;
}