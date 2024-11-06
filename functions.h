#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>

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

// Michal Wierzbicki
// Funkcja do liczenia pozostalego czasu

int calculateRemainingTime(int durationMonths, tm &startDate) {
    time_t now = time(0); //Pobieranie czasu w sekundach 
    tm currentDate;
    localtime_s(&currentDate, &now); //Przeksztalcanie now na lokalna date i zapis do currentDate

    int yearsPassed = currentDate.tm_year - startDate.tm_year;
    int monthsPassed = yearsPassed * 12 + (currentDate.tm_mon - startDate.tm_mon);

    int remainingMonths = durationMonths - monthsPassed;
    return remainingMonths > 0 ? remainingMonths : 0; //Zwraca remainingMonths a jesli remainingMonths sa ujemne zwraca 0
}
tm getCurrentDate() {
    time_t actual_time = time(0);       //Pobieranie czasu w sekundach 
    tm currentDate; 
    localtime_s(&currentDate, &actual_time); //Przeksztalcanie actual_time na lokalna date i zapis do currentDate
    return currentDate;             //Zwraca currentDate
}

// Funkcja konvertująca string na tm
tm convertStringToTm(const string &dateString) {

    tm tm = {};         //Inicjalizowanie zmiennej tm
    istringstream data(dateString);       //Tworzenie obiektu istringstream o nazwie data
    data >> get_time(&tm, "%a %b %d %H:%M:%S %Y");        //Wydobywanie danych z string

    return tm;
}

// Michal Wierzbicki
// Funkcja obslugujaca menu kredytow
void loansMenu() {
    system("cls");

    while (true) {
        vector<int> userLoans;
        int loanCount = 0;

        cout << "Twoje Kredyty:" << endl;
        cout << "Lp.           Typ Kredytu          Pozostala Kwota do Splaty          Waluta" << endl;

        // Zbieranie kredytów użytkownika
        for (int i = 0; i < loan.getElementLoan(); i++) {
            if (loan.getOwnerId(i) == user.getId(courent_user)) {
                userLoans.push_back(i);
                loanCount++;
                cout << loanCount << "      -      " << loan.getLoanTypeName(i) << "      -      " << loan.getBalanceLeft(i) << " ";
                for (int n = 0; n < currency.getElementCurrency(); n++) {
                    if (loan.getCurrencyName(i) == currency.getName(n)) {
                        cout << currency.getName(n) << endl;
                    }
                }
            }
        }

        // Opcje menu
        cout << loanCount + 1 << " - Zaciagnij nowy kredyt" << endl;
        cout << "0 - Wyjdz do pulpitu" << endl;

        if (loanCount) {
            cout << "Aby wykonac splate, wybierz kredyt wpisujac liczbe porzadkowa: ";
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
        if (menu > 0 && menu <= loanCount) {
            vector<int> userAccounts;
            double paymentAmount;
            int accountAmount = 0;

            // Wyswietlenie wszystkich kont aktualnego uzytkownika
            for (int i = 0; i < account.getElemenAccount(); i++) {
                if (account.getOwner_id(i) == user.getId(courent_user)) {
                    userAccounts.push_back(i);
                    accountAmount++;
                    cout << accountAmount << "      -      " << account.getAccountNumber(i) << "      -      " << account.getBalance(i) << " ";
                    for (int n = 0; n < currency.getElementCurrency(); n++) {
                        if (account.getCurrency_id(i) == currency.getId(n)) {
                            cout << currency.getName(n) << endl;
                        }
                    }
                }
            }
            cout<<"Wybierz numer porzadkowy konta za pomoca ktorego chcesz spalcic kredyt:";
            int konto;
            cin>>konto;

            if (konto<1 || konto>accountAmount) { // Nieprawidlowy wybor konta
                system("cls");
                cout << "Nieprawidlowy wybor." << endl;
                continue;
            }

            int accountIndex = userAccounts[konto - 1];
            int currencyId = account.getCurrency_id(accountIndex);
            string currencyName = currency.getName(currencyId);

            cout << "Podaj kwote splaty: ";
            cin >> paymentAmount;

            if ((paymentAmount * 100) - int(paymentAmount * 100) != 0 || paymentAmount <= 0) {
                system("cls");
                cout << "Nieprawidlowa kwota." << endl;
            } else if (paymentAmount > loan.getBalanceLeft(userLoans[menu - 1])) {
                system("cls");
                cout << "Kwota splaty przewyzsza saldo kredytu." << endl;
            } else if (currencyName != loan.getCurrencyName(userLoans[menu - 1])) {
                system("cls");
                cout << "Waluta konta nie zgadza sie z waluta kredytu." << endl;
            } else {
                loan.makePayment(userLoans[menu - 1], paymentAmount);
                account.decreaseBalance(userAccounts[konto-1], paymentAmount);
                txt_log("User:" + to_string(user.getId(courent_user)) + " splacil:" + to_string(paymentAmount) + " . -Kredyt");
                txt_log("Z konta nr: " + account.getAccountNumber(userAccounts[konto-1]) + " pobrano: " + to_string(paymentAmount));
                system("cls");
                cout << "Splacono " << paymentAmount << " z kredytu." << endl;
                if (loan.getBalanceLeft(userLoans[menu - 1]) == 0) {
                    userLoans.erase(userLoans.begin() + (menu - 1)); // Usuwamy wskaźnik z wektora
                    cout << "Kredyt splacony i usuniety." << endl;
                }
            }
        }

        // Zaciąganie nowego kredytu
        else if (menu == loanCount + 1) {
            vector<int> userAccounts;
            double newLoanAmount;
            int loanTypeIndex;
            int accountAmount = 0;

            // Wyswietlenie wszystkich kont aktualnego uzytkownika
            for (int i = 0; i < account.getElemenAccount(); i++) {
                if (account.getOwner_id(i) == user.getId(courent_user)) {
                    userAccounts.push_back(i);
                    accountAmount++;
                    cout << accountAmount << "      -      " << account.getAccountNumber(i) << "      -      " << account.getBalance(i) << "       ";
                    for (int n = 0; n < currency.getElementCurrency(); n++) {
                        if (account.getCurrency_id(i) == currency.getId(n)) {
                            cout << currency.getName(n) << endl;
                        }
                    }
                }
            }
            cout<<"Wybierz numer porzadkowy konta na ktory chcesz zaciagnac kredyt:";
            int konto;
            cin>>konto;

            if (konto<1 || konto>accountAmount) { // Nieprawidlowy wybor konta
                system("cls");
                cout << "Nieprawidlowy wybor." << endl;
                continue;
            }

            int accountIndex = userAccounts[konto - 1];
            int currencyId = account.getCurrency_id(accountIndex);
            string currencyName = currency.getName(currencyId);

            cout << "Podaj kwote kredytu: ";
            cin >> newLoanAmount;
            
            if (newLoanAmount <= 0) {
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
            loanTypeIndex--;
            
            if (loanTypeIndex < 0 || loanTypeIndex >= loan_type.getElementLoanType()) {
                system("cls");
                cout << "Nieprawidlowy wybor typu kredytu." << endl;
                continue;
            }

            // Długość trwania kredytu
            cout << "Podaj dlugosc trwania kredytu w latach: ";
            int years;
            cin >> years;

            if (years <= 0) {
                system("cls");
                cout << "Nieprawidlowa ilosc lat." << endl;
                continue;
            }
            
            bool powtorzenie = 0;
            int noweId;
            do { // Generowanie losowego id konta i sprawdzanie czy takie juz istnieje do skutku
                powtorzenie = 0;
                noweId = rand();
                for (int i = 0; i < account.getElemenAccount(); i++) {
                    if (noweId == account.getId(i)) {
                        powtorzenie = 1;
                        break;
                    }
                }
            } while (powtorzenie);

            // Liczenie całkowitego kwoty końcowej
            double totalLoanAmount = newLoanAmount + loan_type.calcInterest(loanTypeIndex, newLoanAmount, years);

            // Dodanie nowego kredytu
            loan.addLoan(noweId, user.getId(courent_user), currencyName, loan_type.getLoanTypeName(loanTypeIndex) , totalLoanAmount);
            account.increaseBalance(userAccounts[konto-1], totalLoanAmount);
            txt_log("User:" + to_string(user.getId(courent_user)) + " zaciagnal nowy kredyt " + loan_type.getLoanTypeName(loanTypeIndex) + " w wysowosci:" + to_string(newLoanAmount));
            txt_log("Na konto nr: " + account.getAccountNumber(userAccounts[konto-1]) + " wpłyneło: " + to_string(totalLoanAmount));
            system("cls");
            cout << "Zaciagnieto nowy kredyt w wysokosci: " << totalLoanAmount << endl;
            cout << "Typ kredytu: " << loan_type.getLoanTypeName(loanTypeIndex) << endl;
            cout << "Waluta: " << currencyName << endl;
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
void depositsMenu() {
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

                int durationM = deposit.getDurationMonths(i); // Pobierz czas trwania i datę rozpoczęcia lokaty
                string startDateS = deposit.getStartDate(i);
                tm startDate = convertStringToTm(startDateS); // Konwertuj string na tm
                int remainingTime = calculateRemainingTime(durationM, startDate); // Oblicz aktualny pozostały czas
                deposit.setRemainingTime(i, remainingTime); // Zmiana pozostałego czasu na aktualny

                cout << depositCount << "      -      " << deposit.getDepositAmount(i) << "      -      " << deposit.getInterestRate(i) << "%      -      " 
                     << deposit.getDurationMonths(i) << " mies.      -      " << deposit.getCurrencyName(i) 
                     << "      -      " << deposit.getRemainingTime(i) << " mies." << endl;
            }
        }

        // Opcje dla użytkownika
        cout << depositCount+1 << " - Zaloz nowa lokate" << endl;
        cout << "0 - Wyjdz do pulpitu" << endl;

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
        if (menu > 0 && menu <= depositCount) {
            vector<int> userAccounts;
            int accountAmount = 0;

            // Wyswietlenie wszystkich kont aktualnego uzytkownika
            for (int i = 0; i < account.getElemenAccount(); i++) {
                if (account.getOwner_id(i) == user.getId(courent_user)) {
                    userAccounts.push_back(i);
                    accountAmount++;
                    cout << accountAmount << "      -      " << account.getAccountNumber(i) << "      -      " << account.getBalance(i) << " ";
                    for (int n = 0; n < currency.getElementCurrency(); n++) {
                        if (account.getCurrency_id(i) == currency.getId(n)) {
                            cout << currency.getName(n) << endl;
                        }
                    }
                }
            }
            cout<<"Wybierz numer porzadkowy konta na ktory chcesz wplacic lokate:";
            int konto;
            cin>>konto;

            if (konto<1 || konto>accountAmount) { // Nieprawidlowy wybor konta
                system("cls");
                cout << "Nieprawidlowy wybor." << endl;
                continue;
            }
            int depositIndex = userDeposits[menu - 1];
            double interestAmount = deposit.calculateInterest(depositIndex);
            double payoutAmount = deposit.getDepositAmount(depositIndex) + interestAmount;

            int accountIndex = userAccounts[konto - 1];
            int currencyId = account.getCurrency_id(accountIndex);
            string currencyName = currency.getName(currencyId);
            if(currencyName != deposit.getCurrencyName(userDeposits[menu - 1])){
                system("cls");
                cout << "Waluta konta nie zgadza sie z waluta lokaty." << endl;
            }else{
                // Zakończenie lokaty i przelew środków
                deposit.endDeposit(depositIndex);
                account.increaseBalance(userAccounts[konto - 1], payoutAmount);

                // Usunięcie lokaty
                deposit.removeDeposit(depositIndex);
                userDeposits.erase(userDeposits.begin() + (menu - 1)); // Usuwamy wskaźnik z wektora
                cout << "Deposit splacony i usuniety." << endl;

                // Dodawanie logów
                txt_log("User:" + to_string(user.getId(courent_user)) + " zakonczyl lokate. Wypłacono: " + to_string(payoutAmount));
                txt_log("Do konta nr: " + account.getAccountNumber(userAccounts[konto - 1]) + " wpłynęło: " + to_string(payoutAmount));
            }
        }

        // Założenie nowej lokaty
        else if (menu == depositCount+1) {
            vector<int> userAccounts;
            double depositAmount, interestRate;
            int durationMonths;
            int accountAmount = 0;

            // Wyswietlenie wszystkich kont aktualnego uzytkownika
            for (int i = 0; i < account.getElemenAccount(); i++) {
                if (account.getOwner_id(i) == user.getId(courent_user)) {
                    userAccounts.push_back(i);
                    accountAmount++;
                    cout << accountAmount << "      -      " << account.getAccountNumber(i) << "      -      " << account.getBalance(i) << " ";
                    for (int n = 0; n < currency.getElementCurrency(); n++) {
                        if (account.getCurrency_id(i) == currency.getId(n)) {
                            cout << currency.getName(n) << endl;
                        }
                    }
                }
            }
            cout<<"Wybierz numer porzadkowy konta z ktorego chcesz wplacic na lokate:";
            int konto;
            cin>>konto;

            if (konto<1 || konto>accountAmount) { // Nieprawidlowy wybor konta
                system("cls");
                cout << "Nieprawidlowy wybor." << endl;
                continue;
            }

            cout << "Podaj kwote lokaty: ";
            cin >> depositAmount;

            if (depositAmount <= 0) {
                system("cls");
                cout << "Nieprawidlowa kwota." << endl;
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

            // Ustal oprocentowanie lokaty
            if (durationMonths <= 6) {
                interestRate = 2.0;
            } else if (durationMonths <= 12) {
                interestRate = 3.0;
            } else if (durationMonths <= 24) {
                interestRate = 3.5;
            } else {
                interestRate = 4.0;
            }

            bool powtorzenie = 0;
            int noweId;
            do { // Generowanie losowego id konta i sprawdzanie czy takie juz istnieje do skutku
                powtorzenie = 0;
                noweId = rand();
                for (int i = 0; i < account.getElemenAccount(); i++) {
                    if (noweId == account.getId(i)) {
                        powtorzenie = 1;
                        break;
                    }
                }
            } while (powtorzenie);

            // Wydobywanie nazwy waluty
            int accountIndex = userAccounts[konto - 1];
            int currencyId = account.getCurrency_id(accountIndex);
            string currencyName = currency.getName(currencyId);

            // Liczenie całkowitego kwoty końcowej
            double interestFactor = interestRate / 100;
            double interestAmount = depositAmount * interestFactor;
            double totalAmount = depositAmount + interestAmount;

            // Dodanie nowej lokaty
            deposit.addDeposit(noweId, user.getId(courent_user), totalAmount, currencyName, durationMonths, interestRate, czas(), durationMonths);
            account.decreaseBalance(userAccounts[konto-1], totalAmount);
            txt_log("User:"+to_string(user.getId(courent_user))+" zalozyl nowa lokate w wysowosci:"+to_string(totalAmount));
            txt_log("Z konta nr: " + account.getAccountNumber(userAccounts[konto-1]) + " pobrano: " + to_string(totalAmount));
            system("cls");
            cout << "Zalozono nowa lokate." << endl;
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
// Funkcja zwracajaca zhashowany ciag znakow   ciag = hashowanie(haslo)
string hashowanie(string haslo) {
    string ciag = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    int dlugosc;
    if (haslo.length() > 30) {
        dlugosc = 30;
    } else {
        dlugosc = haslo.length();
    }
    
    for (int n = 0, i = 0; i < 30; i++, n++) {
        if (n == dlugosc) {
            n = 0;
        }
        
        if (haslo[n] >= 33 && haslo[n] <= 123) {
            if (haslo[n]+3 == 60 || haslo[n]+3 == 62) {
                ciag[i] = haslo[n] + 1;
            } else {
                ciag[i] = haslo[n] + 3;
            }
        } else {
            ciag[i] = haslo[n] - 91;
        }
    }

    return ciag;
}


// Jan Piętka
// Funkcja logowania urzytkownika
void sign_in() {
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
            if (login == user.getLogin(i) && hashowanie(password) == user.getPassword(i)) { 
                courent_user = i;
                system("cls");
                txt_log("Uzytkownik ID:" + to_string(user.getId(i))+ " - " + user.getFirst_name(i) + " " + user.getLast_name(i) + " zalogowal sie.");
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
void accountsMenu() {
    system("cls");

    while (true) {
        vector<int> userAccounts; // Wektor indeksow kont nalezacych do aktualnego uzytkownika
        int accountAmount = 0; // Ilosc kont posiadanych przez aktualnego uzytkownika

        cout << "Twoje Konta:" << endl;
        cout << "Lp.           Numer Konta          Stan Konta" << endl;

        // Wyswietlenie wszystkich kont aktualnego uzytkownika
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

        if (menu == 0) { // Wyjscie do pulpitu
            system("cls");
            return;
        } else if (menu == accountAmount+1) { // Tworzenie nowego konta
            system("cls");
            cout << "Tworzenie konta." << endl;

            for (int i = 0; i < currency.getElementCurrency(); i++) {
                cout << i+1 << " - " << currency.getName(i) << endl;
            }

            cout << "Wybierz walute konta: ";
            int waluta;
            cin >> waluta;

            if (waluta > currency.getElementCurrency() || waluta <= 0) {
                system("cls");
                cout << "NIeprawidlowy wybor waluty." << endl;
            } else {
                bool powtorzenie = 0;
                string nowyNumer = "PL";
                do { // Generowanie losowego numeru konta i sprawdzanie czy taki juz istnieje do skutku
                    powtorzenie = 0;
                    nowyNumer = "PL";
                    for (int i = 0; i < 26; i++) {
                        nowyNumer += to_string(rand()%10);
                    }
                    for (int i = 0; i < account.getElemenAccount(); i++) {
                        if (nowyNumer == account.getAccountNumber(i)) {
                            powtorzenie = 1;
                            break;
                        }
                    }
                    
                } while (powtorzenie);

                powtorzenie = 0;
                int noweId;
                do { // Generowanie losowego id konta i sprawdzanie czy takie juz istnieje do skutku
                    powtorzenie = 0;
                    noweId = rand();
                    for (int i = 0; i < account.getElemenAccount(); i++) {
                        if (noweId == account.getId(i)) {
                            powtorzenie = 1;
                            break;
                        }
                    }
                } while (powtorzenie);

                account.addAccount(noweId, user.getId(courent_user), currency.getId(waluta-1), nowyNumer, 0);
                txt_log("Uzytkownik ID:" + to_string(user.getId(courent_user))+ " - " + user.getFirst_name(courent_user) + " " + user.getLast_name(courent_user) + " Utworzyl konto: " + nowyNumer);
                system("cls");
                cout << "Utworzono nowe konto." << endl;
            }
            
        } else if (menu<1 || menu>accountAmount) { // Nieprawidlowy wybor w menu kont
            system("cls");
            cout << "Nieprawidlowy wybor." << endl;

        } else { // Wykonywanie przelewu
            string accountNumber; // Numer konta docelowego
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
                        txt_log("Uzytkownik ID:" + to_string(user.getId(courent_user))+ " - " + user.getFirst_name(courent_user) + " " + user.getLast_name(courent_user) + " Wykonal przelew z konta " + account.getAccountNumber(userAccounts[menu-1]) + " na konto " + account.getAccountNumber(i));
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

// Jan Piętka
// Funkcja obslugujaca menu administratora
void adminMenu() {
    system("cls");

    while (true) {
        cout << "Panel Administratora:" << endl;
        cout << "1 - Dodaj urzytkownika" << endl;
        cout << "2 - Wplac pieniadze" << endl;
        cout << "3 - Wyplac pieniadze" << endl;
        cout << "0 - Wyjdz do pulpitu" << endl;
        cout << "Wybierz opcje przez wpisanie jej numeru: ";
        int menu;
        cin >> menu;
        
        switch (menu) {
        case 1: { // Tworzenie nowego uzytkownika
            bool powtorzenie = 0;
            int noweId;
            string firstName, lastName, login, password;

            do {
                powtorzenie = 0;
                noweId = rand();
                for (int i = 0; i < account.getElemenAccount(); i++) {
                    if (noweId == account.getId(i)) {
                        powtorzenie = 1;
                        break;
                    }
                }
            } while (powtorzenie);

            cout << "Podaj imie: ";
            cin >> firstName;
            cout << "Podaj nazwisko: ";
            cin >> lastName;
            cout << "Podaj login: ";
            cin >> login;
            cout << "Podaj haslo: ";
            cin >> password;

            user.addUser(noweId, firstName, lastName, login, hashowanie(password), 0);
            txt_log("Administrator ID:" + to_string(user.getId(courent_user))+ " - " + user.getFirst_name(courent_user) + " " + user.getLast_name(courent_user) + " Utworzyl nowego uzytkownika " + firstName + " " + lastName);
            system("cls");
            cout << "Utworzono urzytkownika." << endl;
            break;
        }
        case 2: { // Wplacanie pieniedzy na czyjes konto
            string accountNumber;
            double amount;
            cout << "Przykladowy numer konta: PL12345678901234567890123456" << endl;
            cout << "Numer konta docelowego: ";
            cin >> accountNumber;

            for (int i = 0; i < account.getElemenAccount(); i++) {
                if (account.getAccountNumber(i) == accountNumber) {
                    cout << "Podaj kwote wplaty: ";
                    cin >> amount;

                    if ((amount*100)-int(amount*100) != 0 || amount <= 0) {
                        system("cls");
                        cout << "Nieprawidlowa kwota." << endl;
                    } else {
                        account.increaseBalance(i, amount);
                        txt_log("Administrator ID:" + to_string(user.getId(courent_user))+ " - " + user.getFirst_name(courent_user) + " " + user.getLast_name(courent_user) + " dokonal wplaty na konto " + account.getAccountNumber(i));
                        system("cls");
                        cout << "Dokonano wplaty." << endl;;
                    }
                    break;

                } else if (i+1 >= account.getElemenAccount()) {
                    system("cls");
                    cout << "Nieprawidlowy numer konta." << endl;
                }
            }
            break;
        }
        case 3: { // Wyplacenie pieniedzy z czyjegos konta
            string accountNumber;
            double amount;
            cout << "Przykladowy numer konta: PL12345678901234567890123456" << endl;
            cout << "Numer konta docelowego: ";
            cin >> accountNumber;

            for (int i = 0; i < account.getElemenAccount(); i++) {
                if (account.getAccountNumber(i) == accountNumber) {
                    cout << "Podaj kwote wyplaty: ";
                    cin >> amount;

                    if ((amount*100)-int(amount*100) != 0 || amount <= 0) {
                        system("cls");
                        cout << "Nieprawidlowa kwota." << endl;
                    } else {
                        account.decreaseBalance(i, amount);
                        txt_log("Administrator ID:" + to_string(user.getId(courent_user))+ " - " + user.getFirst_name(courent_user) + " " + user.getLast_name(courent_user) + " dokonal wuplaty z konta " + account.getAccountNumber(i));
                        system("cls");
                        cout << "Dokonano wyplaty." << endl;;
                    }
                    break;

                } else if (i+1 >= account.getElemenAccount()) {
                    system("cls");
                    cout << "Nieprawidlowy numer konta." << endl;
                }
            }
            break;
        }
        case 0: { // Wyjscie do pulkpitu
            system("cls");
            return;
        }
        default:
            system("cls");
            cout << "Nieprawidlowy numer opcji." << endl;
            break;
        }
    }
    
    return;
}

// Jan Piętka
// Funkcja wyświetlajaca i obslugujaca pupit aktualnie zalogowanego uzytkownika  destop(obiekt z wektorami, numer w wektorze zalogowanego uzytkownika)
void desktop() {
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
            accountsMenu();
            break;
        }
        case 2: {
            loansMenu();
            break;
        }
        case 3: {
            depositsMenu();
            break;
        }
        case 0: { // Wylogowanie uzytkownika i zapisanie danych
            log_out = 0;
            txt_log("Uzytkownik ID:" + to_string(user.getId(courent_user))+ " - " + user.getFirst_name(courent_user) + " " + user.getLast_name(courent_user) + " wylogowal sie i zapisal dane.");
            xml_save(user, account, currency, loan_type, loan, deposit);
            break;
        }
        case 10: { // wejscie do menu administratora
            if (user.isAdmin(courent_user)) {
                adminMenu();
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