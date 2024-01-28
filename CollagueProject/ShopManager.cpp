#include <iostream>
#include "Functions.h"

using namespace std;


int main() {
    setlocale(LC_CTYPE, "Polish");
    int status = 0;
    int choose;

    while (status == 0) {
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
            status = 1;
            break;
        default:
            cout << "Nieprawid³owa treœæ. Spróbuj ponownie." << endl;
        }
    }

    return 0;
}
