#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
using namespace std;

struct Produkt {
    string nazwa;
    int ilosc = 0;
    double cena = 0;
    double marza = 0;
    string firma;
};

struct Sprzedaz {
    string data;
    string nazwa;
    int ilosc = 0;
    double zysk = 0;
};

vector<Produkt> wczytajProduktyZPliku();
vector<Sprzedaz> wczytajFinanseZPliku();
void addFinancial (string nazwaProduktu, double marza, int ilosc);
void usunProduktZPliku(const string& nazwa, const string& firma = "");
void wypiszPozycjeZRoku(const vector<Sprzedaz>& produkty, const string& rok);
void wyszukajDzien(const vector<Sprzedaz>& produkty, const string& dzien);
void sellProduct();
void showAvailability();
void addInvoice();
void checkFinanse();
void chooseOptions();


#endif 
