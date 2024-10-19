#include <iostream>
#include <vector>

#include "classes.h"
#include "variables.h"

using namespace std;
// Jan Piętka
// Funkcja logowania urzytkownika
void sign_in() {
    string login;
    string password;
    bool loged_in = 0;
    system("cls");
    cout << "Witaj w Banku PWP!" << endl;
    User user;

    // Mała edycja tej funckji dostosowanej do vectorów
    do {
        cout << "Podaj login: ";
        cin >> login;
        cout << "Podaj haslo: ";
        cin >> password;

        for (int i = 0; i < user.getElementUser(); i++) {
            if (login == user.getLogin(i) && password == user.getPassword(i)) {
                courent_user = i;
                system("cls");
                loged_in = 1;
                cout << "Zalogowano jako: " << user.getFirst_name(i) << " " << user.getLast_name(i);
                return;
            }
        }

        system("cls");
        cout << "Nieprawidlowy login lub haslo." << endl;

    } while (!loged_in);
}

// Funkcja dodająca tymczasowe przykladowe dane do testowania aplikacji
void temprrary_data() {
   /* User user1(20, "Jan", "Kowalski", "admin", "admin", 1);
    users.push_back(user1);
    User user2(43, "Adrian", "Prymas", "user1", "user1", 0);
    users.push_back(user2);
    User user3(25, "Jan", "Pietka", "user2", "user2", 0);
    users.push_back(user3);
    User user4(21, "Andrzej", "Nowak", "user3", "user3", 0);
    users.push_back(user4);
    User user5(53, "Michal", "Ryba", "user4", "user4", 0);
    users.push_back(user5);*/
    User user;

    user.addUser(20, "Jan", "Kowalski", "admin", "admin", true);
    user.addUser(43, "Adrian", "Prymas", "user1", "user1", false);
    user.addUser(25, "Jan", "Pietka", "user2", "user2", false);
    user.addUser(21, "Andrzej", "Nowak", "user3", "user3", false);
    user.addUser(53, "Michal", "Ryba", "user4", "user4", false);
    return; 
}
