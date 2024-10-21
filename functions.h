#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

#include "classes.h"
#include "variables.h"

using namespace std;

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

// Funkcja obslugujaca menu kredytow
void loansMenu(User user, int courent_user) {

    return;
}

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
    log << logs << endl;
}