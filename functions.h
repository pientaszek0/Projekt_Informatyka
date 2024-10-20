#include <iostream>
#include <vector>

#include "classes.h"
#include "variables.h"

using namespace std;

// Funkcja dodająca tymczasowe przykladowe dane do testowania aplikacji
void temprrary_data(User &user) {
    user.addUser(20, "Jan", "Kowalski", "admin", "admin", true);
    user.addUser(43, "Adrian", "Prymas", "user1", "user1", false);
    user.addUser(25, "Jan", "Pietka", "user2", "user2", false);
    user.addUser(21, "Andrzej", "Nowak", "user3", "user3", false);
    user.addUser(53, "Michal", "Ryba", "user4", "user4", false);
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
// Funkcja wyświetlajaca i obslugujaca pupit aktualnie zalogowanego uzytkownika  destop(obiekt z wektorami, numer w wektorze zalogowanego uzytkownika)
void desktop(User user, int courent_user) {
    int menu;
    system("cls");

    while (true) {
        cout << "Zalogowano jako: " << user.getFirst_name(courent_user) << " " << user.getLast_name(courent_user) << endl;
        cout << "1 - Konta" << endl;
        cout << "2 - Kredyty" << endl;
        cout << "3 - Lokaty" << endl;
        if (user.isAdmin(courent_user)) {
            cout << "10 - Menu Administratora" << endl;
        }
        cout << "Wybierz opcje przez wpisanie jej numeru: ";
        cin >> menu;

        switch (menu) {
        case 1: {
            system("cls");
            cout << "Twoje Konta:" << endl;
            break;
        }
        case 2: {
            system("cls");
            cout << "Twoje Kredyty:" << endl;
            break;
        }
        case 3: {
            system("cls");
            cout << "Twoje Lokaty:" << endl;
            break;
        }
        case 10: {
            system("cls");
            cout << "Panel Administratora:" << endl;
            cout << "Wybierz opcje przez wpisanie jej numeru: ";



            cin >> menu;
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

void accountsMenu() {

    return;
}

void loansMenu() {

    return;
}

void depositsMenu() {

    return;
}

void adminMenu() {

    return;
}
