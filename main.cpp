#include <iostream>
#include "classes.h"
#include "functions.h"
#include "variables.h"
using namespace std;

// Funkcja obliczająca miesięczną ratę kredytu
double obliczRateKredytu(double kwotaKredytu, double stopaRoczna, int liczbaLat) {
    // Przekształcamy stopę roczną na miesięczną
    double stopaMiesieczna = stopaRoczna / 12 / 100;
    // Liczba miesięcy
    int liczbaMiesiecy = liczbaLat * 12;
    
    double rata = (kwotaKredytu * stopaMiesieczna * pow(1 + stopaMiesieczna, liczbaMiesiecy)) / (pow(1 + stopaMiesieczna, liczbaMiesiecy) - 1);
    
    return rata;
}

int main() {
    double kwotaKredytu;
    double stopaRoczna;
    int liczbaLat;
    
    // Pobieranie danych od użytkownika
    cout << "Podaj kwotę kredytu: ";
    cin >> kwotaKredytu;

    cout << "Podaj roczną stopę procentową (w %): ";
    cin >> stopaRoczna;

    cout << "Podaj liczbę lat kredytu: ";
    cin >> liczbaLat;

    // Obliczenie i wyświetlenie miesięcznej raty
    double rata = obliczRateKredytu(kwotaKredytu, stopaRoczna, liczbaLat);
    cout << "Miesięczna rata kredytu wynosi: " << rata << std::endl;

    return 0;
}

 
