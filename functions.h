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
    account.addAccount(34, 20, 0, "PL12 3456 7890 1234 5678 9012 3456", 21.37);
    account.addAccount(42, 43, 0, "PL21 3700 7890 1234 5678 9012 3456", 21.37);
    account.addAccount(66, 25, 2, "EU12 3456 7890 1234 5678 9012 3456", 21.37);
    account.addAccount(21, 21, 0, "PL12 3456 7890 1234 5678 9012 2137", 21.37);
    account.addAccount(37, 43, 1, "US12 3456 7890 1234 5678 9012 3456", 21.37);
    currency.addCurrency(0, "Zloty");
    currency.addCurrency(1, "Dolar Amerykanski");
    currency.addCurrency(2, "Euro");
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
    cout << "Twoje Konta:" << endl;
    
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
        cout << "4 - Wyloguj i zapisz zmiany" << endl;
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
        case 4: {
            log_out = 0;
            // Tutaj Wywolac funkcje zapisujaca do xml
            break;
        }
        case 10: {
            adminMenu(user, courent_user);
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