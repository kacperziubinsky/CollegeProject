#include "Source.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;
struct Produkt {
    string nazwa;
    int ilosc;
    double cena;
    double marza;
    string firma;
};

vector<Produkt> wczytajProduktyZPliku(const string& nazwaPliku) {
    vector<Produkt> produkty;
    ifstream plik(nazwaPliku);
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

void addFinancial(string nazwaPlikuFinanse, string nazwaProduktu, int ilosc, int marza) {
    ofstream plikFinanse(nazwaPlikuFinanse, ios::app);
    if (!plikFinanse.is_open()) {
        cout << "Nie mo�na otworzy� pliku finanse!" << endl;
        return;
    }

    char bufor[80];
    time_t czasTeraz = time(nullptr);
    tm lokalnyCzas;

    localtime_s(&lokalnyCzas, &czasTeraz);
    strftime(bufor, 80, "%Y-%m-%d", &lokalnyCzas);

    plikFinanse << bufor << "|" << nazwaProduktu << "|" << ilosc << "|"
        << marza * ilosc << endl;

    plikFinanse.close();
}

void usunProduktZPliku(const string& nazwaPliku, const string& nazwa, const string& firma = "") {
    vector<Produkt> produkty = wczytajProduktyZPliku(nazwaPliku);
    vector<Produkt> noweProdukty;

    for (auto& produkt : produkty) {
        if (produkt.nazwa != nazwa || (!firma.empty() && produkt.firma != firma)) {
            noweProdukty.push_back(produkt);
        }
    }

    ofstream plik(nazwaPliku);
    for (auto& produkt : noweProdukty) {
        plik << produkt.nazwa << "|" << produkt.ilosc << "|" << produkt.cena << "|" << produkt.marza << "|" << produkt.firma << endl;
    }
    plik.close();
}


void sellProduct(const string& nazwaPlikuMagazyn, const string& nazwaPlikuFinanse) {
    vector<Produkt> produkty = wczytajProduktyZPliku(nazwaPlikuMagazyn);

    string nazwaProduktu;
    cout << "Wpisz nazw� produktu: ";
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
        cout << "Wybierz firm�: " << endl;
        for (auto& produkt : dostepneProdukty) {
            cout << produkt.firma << endl;
        }
        cin >> nazwaFirmy;
    }
    else {
        nazwaFirmy = dostepneProdukty[0].firma;
    }

    int ilosc, marza;
    cout << "Wpisz ilo��: ";
    cin >> ilosc;

    double sumaDoZaplaty = 0;
    for (auto& produkt : dostepneProdukty) {
        if (produkt.firma == nazwaFirmy) {
            sumaDoZaplaty = ilosc * (produkt.cena + produkt.marza);
            marza = produkt.marza;
            break;
        }
    }

    cout << "Suma do zap�aty: " << sumaDoZaplaty << endl;

    addFinancial("finanse.txt", nazwaProduktu, ilosc, marza);

    usunProduktZPliku("magazyn.txt", nazwaProduktu, nazwaFirmy);
}


void showAvailability(const string& nazwaPliku) {
    vector<Produkt> produkty = wczytajProduktyZPliku(nazwaPliku);
    for (const auto& produkt : produkty) {
        cout << "Nazwa: " << produkt.nazwa
            << ", Ilo��: " << produkt.ilosc
            << ", Cena: " << produkt.cena
            << ", Mar�a: " << produkt.marza
            << ", Firma: " << produkt.firma << endl;
    }
}

void addInvoice(const string& nazwaPliku) {
    ofstream plik(nazwaPliku, ios::app);
    if (!plik.is_open()) {
        cout << "Nie mo�na otworzy� pliku!" << endl;
        return;
    }

    string nazwaFirmy, nazwaProduktu;
    int ilosc, iloscProduktow;
    double cena, marza;

    cout << "Wprowad� nazw� firmy: ";
    cin.ignore();
    getline(cin, nazwaFirmy);

    cout << "Wprowad� liczb� produkt�w: ";
    cin >> iloscProduktow;
    cin.ignore();

    for (size_t i = 0; i < iloscProduktow; ++i) {
        cout << "Wprowad� nazw� produktu: ";
        getline(cin, nazwaProduktu);

        cout << "Wprowad� ilo��: ";
        cin >> ilosc;
        cin.ignore();

        cout << "Wprowad� cen�: ";
        cin >> cena;
        cin.ignore();

        cout << "Wprowad� mar��: ";
        cin >> marza;
        cin.ignore();

        plik << nazwaProduktu << "|" << ilosc << "|" << cena << "|" << marza << "|" << nazwaFirmy << "\n";
    }

    plik.close();
    cout << "Faktura zosta�a dodana." << endl;
}


void checkFinanse() {
    cout << "checkFinanse" << endl;
}

void chooseOptions() {
    cout << "1. Sprzeda�" << endl;
    cout << "2. Stan Magazynowy" << endl;
    cout << "3. Wprowadzenie Faktury" << endl;
    cout << "4. Bilans Finansowy" << endl;
    cout << "5. Wyj�cie" << endl;
}
