#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include <string>
using namespace std;

struct Product {
    string name;
    int count;
    double price;
    string company;
    string nip;
};

vector<Produkt> wczytajProduktyZPliku(const string& nazwaPliku);
void addFinancial(string nazwaPlikuFinanse, string nazwaProduktu, int ilosc, int marza);
void chooseOptions();
void sellProduct();
void addInvoice();
void checkAvailability(const vector<Product>& products);
void checkFinanse();

#endif 
