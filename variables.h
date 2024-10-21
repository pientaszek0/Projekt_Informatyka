#ifndef VARIABLES_H
#define VARIABLES_H

#include <iostream>
#include <vector>

using namespace std;

int courent_user; // Zmienna przechowująca numer w wektorach aktualnie zalogowanego użytkownika
User user; // Obiekt przechowujący wektory z wszystkimi użytkownnikami pobranymi z pliku xml
Account account; // Obiekt przechowujący wektory z wszystkimi kontami pobranymi z pliku xml
Currency currency; // Obiekt przechowujący wektory z wszystkimi walutami pobranymi z pliku xml
Loan_Type loan_type; // Obiekt przechowujący wektory z wszystkimi typami kredyto pobranymi z pliku xml
Loan loan; // Obiekt przechowujący wektory z wszystkimi kredytami pobranymi z pliku xml

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================== STALŁE BLEDOW ===========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const string error01 = "ERROR-01 -> Nie mozna utworzyc pliku";
const string error02 = "ERROR-02 -> Plik nie został poprawnie otworzony lub nieistnieje";

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================== ZMIENNE XML == ===========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// nazwa pliku xml
string db_name = "classes.xml";
// Zmienne lokalne stworzone na porzeby dzilania tej funkcji
int xml_id = -1;
string xml_first_name, xml_last_name, xml_login, xml_password;
bool xml_admin = false;
int count_element = 0;
string line;
int user_count; // Licznik użytkowników od -1 ponieważ dlaej jest iterator który i tak zmieni wartosc na 0
bool xml_isUser = 0;
#endif