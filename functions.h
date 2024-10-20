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


    // Mała edycja tej funckji dostosowanej do vectorów
    do {
        cout << "Podaj login: ";
        cin >> login;
        cout << "Podaj haslo: ";
        cin >> password;
        int i = 0;
        cout << i <<endl;

        for (i =0 ; i < user.getElementUser(); i++) {
            cout << i;
            if (login == user.getLogin(i) && password == user.getPassword(i)) {
                courent_user = i;
                system("cls");
                loged_in = 1;
                cout << "Zalogowano jako: " << user.getFirst_name(i) << " " << user.getLast_name(i);
                return;
            }
        }
        cout << i;
       //system("cls");
       // cout << "Nieprawidlowy login lub haslo." << endl;

    } while (!loged_in);
}

// Jan Piętka
// Funkcja wyświetlajaca pupit aktualnie zalogowanego uzytkownika
void showDesktop() {
    
    return;
}
