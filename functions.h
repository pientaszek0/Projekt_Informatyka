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
// Michal Wierzbicki
// Funkcja do liczenia pozostalego czasu
int calculateRemainingTime(int durationMonths, const tm& startDate) {
            time_t now = time(0);
            tm currentDate;
            localtime_s(&currentDate, &now);

            int yearsPassed = currentDate.tm_year - startDate.tm_year;
            int monthsPassed = yearsPassed * 12 + (currentDate.tm_mon - startDate.tm_mon);

            int remainingMonths = durationMonths - monthsPassed;
            return remainingMonths > 0 ? remainingMonths : 0;
}
tm getCurrentDate() {
    time_t actual_time = time(0);
    tm currentDate;
    localtime_s(&currentDate, &actual_time);
    return currentDate;
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

            cout << "Podaj kwote splaty: ";
            cin >> paymentAmount;

            if ((paymentAmount * 100) - int(paymentAmount * 100) != 0 || paymentAmount <= 0) {
                system("cls");
                cout << "Nieprawidlowa kwota." << endl;
            } else if (paymentAmount > loan.getBalanceLeft(userLoans[menu - 1])) {
                system("cls");
                cout << "Kwota splaty przewyzsza saldo kredytu." << endl;
            } else {
                loan.makePayment(userLoans[menu - 1], paymentAmount);
                account.decreaseBalance(userAccounts[konto-1], paymentAmount);
                txt_log("User:" + to_string(user.getId(courent_user)) + " splacil:" + to_string(paymentAmount) + " . -Kredyt");
                txt_log("Z konta nr: " + account.getAccountNumber(userAccounts[konto-1]) + " pobrano: " + to_string(paymentAmount));
                system("cls");
                cout << "Splacono " << paymentAmount << " z kredytu." << endl;
            }
        }

        // Zaciąganie nowego kredytu
        else if (menu == loanCount + 1) {
            vector<int> userAccounts;
            double newLoanAmount;
            int loanTypeIndex, currencyIndex;
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
            cout<<"Wybierz numer porzadkowy konta na ktory chcesz zaciagnac kredyt:";
            int konto;
            cin>>konto;

            if (konto<1 || konto>accountAmount) { // Nieprawidlowy wybor konta
                system("cls");
                cout << "Nieprawidlowy wybor." << endl;
                continue;
            }

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
            loan.addLoan(noweId, user.getId(courent_user), currency.getName(currencyIndex), loan_type.getLoanTypeName(loanTypeIndex) , totalLoanAmount);
            account.increaseBalance(userAccounts[konto-1], totalLoanAmount);
            txt_log("User:" + to_string(user.getId(courent_user)) + " zaciagnal nowy kredyt " + loan_type.getLoanTypeName(loanTypeIndex) + " w wysowosci:" + to_string(newLoanAmount));
            txt_log("Na konto nr: " + account.getAccountNumber(userAccounts[konto-1]) + " wpłyneło: " + to_string(totalLoanAmount));
            system("cls");
            cout << "Zaciagnieto nowy kredyt w wysokosci: " << totalLoanAmount << endl;
            cout << "Typ kredytu: " << loan_type.getLoanTypeName(loanTypeIndex) << endl;
            cout << "Waluta: " << currency.getName(currencyIndex) << endl;
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
                cout << depositCount << " - " << deposit.getDepositAmount(i) << " - " << deposit.getInterestRate(i) << "% - " 
                     << deposit.getDurationMonths(i) << " mies. - " << deposit.getCurrencyName(i) 
                     << " - " << deposit.getRemainingTime(i) << " mies." << endl;
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
            deposit.endDeposit(courent_user);
            account.increaseBalance(userAccounts[konto-1], (deposit.getDepositAmount(courent_user) + deposit.calculateInterest(courent_user)));
            txt_log("User:"+to_string(user.getId(courent_user))+" zakonczyl lokate. Wyplacono kwote w wysowosci:"+to_string((deposit.getDepositAmount(courent_user) + deposit.calculateInterest(courent_user))));
            txt_log("Do konta nr: " + account.getAccountNumber(userAccounts[konto-1]) + " wpłyneło: " + to_string((deposit.getDepositAmount(courent_user) + deposit.calculateInterest(courent_user))));
        }

        // Założenie nowej lokaty
        else if (menu == depositCount+1) {
            vector<int> userAccounts;
            double depositAmount, interestRate;
            int currencyIndex, durationMonths;
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

            // Liczenie całkowitego kwoty końcowej
            double interestFactor = interestRate / 100;
            double interestAmount = depositAmount * interestFactor;
            double totalAmount = depositAmount + interestAmount;

            // Inicjowanie daty
            tm startDate = getCurrentDate();

            // Dodanie nowej lokaty
            deposit.addDeposit(noweId, user.getId(courent_user), totalAmount, currency.getName(currencyIndex), durationMonths, interestRate, czas(), calculateRemainingTime(durationMonths, startDate));
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
            if (login == user.getLogin(i) && password == user.getPassword(i)) { 
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
                cout << accountAmount << "      -      " << account.getAccountNumber(i) << "      -      " << account.getBalance(i) << " ";
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

            user.addUser(noweId, firstName, lastName, login, password, 0);
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