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
Deposit deposit; 

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
// Dotyczy klasy user
string xml_first_name, xml_last_name, xml_login;
string xml_password;
bool xml_admin = false;
// Dotyczy klasy Account
int xml_owner_id, xml_currency_id;
string xml_account_number;
double xml_balance;
// Dotyczy klasy Currency
string xml_cName;
// Dotyczy klasy Loan;
double xml_interest;
string xml_loan_type;
// Dotyczy klasy Loan
string xlm_currency_name;
double xlm_balance_left;
// Dotyczy Deposit
double xml_deposit_amount;
int xml_duration_months;
double xml_interest_rate;
string xml_start_date;
int xml_remaing_time;

string line; // Zapis lini XML
int licznik; // Licznik od -1 ponieważ dlaej jest iterator który i tak zmieni wartosc na 0
// Flagi
bool xml_isUser = 0; // Flaga dla klasy User
bool xml_isAccount = 0;  // Flaga dla klasy Accoutn
bool xml_isCurrency = 0;  // Flaga dla klasy Currency
bool xml_isLoan_type = 0; // Flaga do klasy Loan_Type
bool xml_isLoan = 0; // Flaga do klasy Loan
bool xml_isDeposit = 0; // flaga do klasy Deposit

#endif