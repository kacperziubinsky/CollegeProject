#include <iostream>
#include "Functions.h"

using namespace std;


int main() {
    setlocale(LC_CTYPE, "Polish");

    int choose;
    string nazwaPliku = "magazyn.txt";
    while (true) {
        chooseOptions();
        cin >> choose;

        switch (choose) {
        case 1:
            sellProduct();
            break;
        case 2:
            showAvailability();
            break;
        case 3:
            addInvoice();
            break;
        case 4:
            checkFinanse();
            break;
        case 5:
            return 0;
        default:
            cout << "Nieprawid³owa treœæ. Spróbuj ponownie." << endl;
        }
    }

    return 0;
}
