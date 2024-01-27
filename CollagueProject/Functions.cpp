#include "Functions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

#define financial_file "finanse.txt"

vector<Produkt> wczytajProduktyZPliku() {
    vector<Produkt> produkty;
    ifstream plik("magazyn.txt");
    string linia;

    while (getline(plik, linia)) {
        istringstream ss(linia);
        Produkt produkt;
        string element;

        getline(ss, produkt.nazwa, '|');
        getline(ss, element, '|');
        produkt.ilosc = stoi(element);
        getline(ss, element, '|');
        produkt.cena = stod(element);
        getline(ss, element, '|');
        produkt.marza = stod(element);
        getline(ss, produkt.firma);

        produkty.push_back(produkt);
    }

    return produkty;
}

vector<Sprzedaz> wczytajFinanseZPliku() {
    vector<Sprzedaz> produkty;
    ifstream plik(financial_file);
    string linia;

    while (getline(plik, linia)) {
        istringstream ss(linia);
        Sprzedaz pozycja;;
        string element;

        getline(ss, pozycja.data, '|');
        getline(ss, pozycja.nazwa, '|');
        getline(ss, element, '|');
        pozycja.ilosc = stoi(element);
        getline(ss, element);
        pozycja.zysk = stod(element);

        produkty.push_back(pozycja);
    }

    return produkty;
}

void addFinancial(string nazwaProduktu, double marza, int ilosc) {
    ofstream plikFinanse(financial_file, ios::app);
    if (!plikFinanse.is_open()) {
        cout << "Nie mo¿na otworzyæ pliku finanse!" << endl;
        return;
    }

    char bufor[80];
    time_t czasTeraz = time(nullptr);
    tm lokalnyCzas;

    localtime_s(&lokalnyCzas, &czasTeraz);
    strftime(bufor, 80, "%Y-%m-%d", &lokalnyCzas);

    plikFinanse << bufor << "|" << nazwaProduktu << "|" << ilosc << "|"
        << marza<< endl;

    plikFinanse.close();
}

void usunProduktZPliku(const string& nazwa, const string& firma){
    vector<Produkt> produkty = wczytajProduktyZPliku();
    vector<Produkt> noweProdukty;

    for (auto& produkt : produkty) {
        if (produkt.nazwa != nazwa || (!firma.empty() && produkt.firma != firma)) {
            noweProdukty.push_back(produkt);
        }
    }

    ofstream plik("magazyn.txt");
    for (auto& produkt : noweProdukty) {
        plik << produkt.nazwa << "|" << produkt.ilosc << "|" << produkt.cena << "|" << produkt.marza << "|" << produkt.firma << endl;
    }
    plik.close();
}

void sellProduct() {
    vector<Produkt> produkty = wczytajProduktyZPliku();

    double sumaDoZaplaty = 0;

    string nazwaProduktu;

    do
    {
        cout << "Wpisz nazwê produktu lub wpisz e, aby zakoñczonyæ: ";
        cin >> nazwaProduktu;
        vector<Produkt> dostepneProdukty;
        for (auto& produkt : produkty) {
            if (produkt.nazwa == nazwaProduktu) {
                dostepneProdukty.push_back(produkt);
            }
        }

        if (dostepneProdukty.empty()) {
            cout << "Nie ma takiego produktu." << endl;
            return;
        }

        string nazwaFirmy;
        if (dostepneProdukty.size() > 1) {
            cout << "Wybierz firmê: " << endl;
            for (auto& produkt : dostepneProdukty) {
                cout << produkt.firma << endl;
            }
            cin >> nazwaFirmy;
        }
        else {
            nazwaFirmy = dostepneProdukty[0].firma;
        }

        int ilosc;
        double marza = 0;
        cout << "Wpisz iloœæ: ";
        cin >> ilosc;

        for (auto& produkt : dostepneProdukty) {
            if (produkt.firma == nazwaFirmy) {
                sumaDoZaplaty += ilosc * (produkt.cena + produkt.marza);
                marza = produkt.marza;
                break;
            }
        }
        
        if (nazwaFirmy.empty()) {
            usunProduktZPliku(nazwaProduktu, "");
            addFinancial(nazwaProduktu, marza, ilosc);
        }
        else {
            usunProduktZPliku(nazwaProduktu, nazwaFirmy);
            addFinancial(nazwaProduktu, marza, ilosc);
        }

    } while (nazwaProduktu!="e");




    cout << "Suma do zap³aty: " << sumaDoZaplaty << endl;





}

void showAvailability() {
    vector<Produkt> produkty = wczytajProduktyZPliku();
    for (const auto& produkt : produkty) {
        cout << "Nazwa: " << produkt.nazwa
            << ", Iloœæ: " << produkt.ilosc
            << ", Cena: " << produkt.cena
            << ", Mar¿a: " << produkt.marza
            << ", Firma: " << produkt.firma << endl;
    }
}

void wypiszPozycjeZRoku(const vector<Sprzedaz>& produkty, const string& rok) {
    double suma = 0;
    for (const auto& pozycja : produkty) {
        if (pozycja.data.substr(0, 4) == rok) {
            cout << pozycja.data << " | " << pozycja.nazwa << " | "
                << pozycja.ilosc << " | " << pozycja.zysk << endl;
            suma += pozycja.zysk;
        }
    }
    cout << "Zysk za podany rok wynosi: " << suma << endl;
}

void wyszukajDzien(const vector<Sprzedaz>& produkty, const string& dzien) {
    double suma = 0;
    for (const auto& pozycja : produkty) {
        if (pozycja.data == dzien) {
            cout << pozycja.data << " | " << pozycja.nazwa << " | "
                << pozycja.ilosc << " | " << pozycja.zysk << endl;
            suma += pozycja.zysk;

        }
    }
    cout << "Zysk za podany rok wynosi: " << suma << endl;

}

void addInvoice() {
    ofstream plik(financial_file, ios::app);
    if (!plik.is_open()) {
        cout << "Nie mo¿na otworzyæ pliku!" << endl;
        return;
    }

    string nazwaFirmy, nazwaProduktu;
    int ilosc, iloscProduktow;
    double cena, marza;

    cout << "WprowadŸ nazwê firmy: ";
    cin.ignore();
    getline(cin, nazwaFirmy);

    cout << "WprowadŸ liczbê produktów: ";
    cin >> iloscProduktow;
    cin.ignore();

    for (size_t i = 0; i < iloscProduktow; ++i) {
        cout << "WprowadŸ nazwê produktu: ";
        getline(cin, nazwaProduktu);

        cout << "WprowadŸ iloœæ: ";
        cin >> ilosc;
        cin.ignore();

        cout << "WprowadŸ cenê: ";
        cin >> cena;
        cin.ignore();

        cout << "WprowadŸ mar¿ê: ";
        cin >> marza;
        cin.ignore();

        plik << nazwaProduktu << "|" << ilosc << "|" << cena << "|" << marza << "|" << nazwaFirmy << "\n";
    }

    plik.close();
    cout << "Faktura zosta³a dodana." << endl;
}

void checkFinanse() {
    int financalType;
    string data, rok;
    vector<Sprzedaz> produkty = wczytajFinanseZPliku();
    cout << "1. Sprawozdanie roczne \n";
    cout << "2. Statystki dnia \n";
    cin >> financalType;

    switch (financalType) {
    case 1:
        cout << "Wpisz rok: \n";
        cin >> rok;
        wypiszPozycjeZRoku(produkty, rok);
        break;
    case 2:
        cout << "Wpisz datê (rok-misi¹c-dzieñ): \n";
        cin >> data;
        wyszukajDzien(produkty, data);
        break;
    default:
        cout << "Nieprawid³owa treœæ. Spróbuj ponownie." << endl;
    }
}

void chooseOptions() {
    cout << "1. Sprzeda¿" << endl;
    cout << "2. Stan Magazynowy" << endl;
    cout << "3. Wprowadzenie Faktury" << endl;
    cout << "4. Bilans Finansowy" << endl;
    cout << "5. Wyjœcie" << endl;
}
