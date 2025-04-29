#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int maxRow = 10;
int transactionCounter = 1;

const string error = "Not Found or Invalid Input! Check spelling on the list provided";

struct Log {
    int id;
    double amount;
    string billType;
    char sym;
    string selectedCurrency;
    double convertedAmount;
    string method; // "Crypto to Bill" or "Bill to Crypto"
};

vector<Log> logList;

string cryptoCurrencies[maxRow] = {
    "Bitcoin",
    "Ethereum",
    "Binance",
    "Solana",
    "Cardano",
    "Dogecoin",
    "Polkadot",
    "ShibaInu",
    "Polygon",
};

string cryptoCurrenciesSubName[maxRow] = {
    "btc",
    "eth",
    "bnb",
    "sol",
    "ada",
    "doge",
    "dot",
    "shib",
    "matic",
};

double cryptoValueInPeso[maxRow] = {
    3743272.85,
    108022.97,
    35836.30,
    7236.75,
    39.98,
    10.37,
    269.79,
    0.0007314,
    5.89
};

double cryptoValueInUsd[maxRow] = {
    63880.00,
    1843.52,
    606.79,
    125.59,
    0.684236,
    0.171148,
    4.14,
    0.00001269,
    0.205779
};

double cryptoValueInEur[maxRow] = {
    59000.00,
    1700.00,
    560.00,
    115.00,
    0.63,
    0.16,
    3.80,
    0.000011,
    0.19
};

double cryptoValueInJpy[maxRow] = {
    10000000.00,
    300000.00,
    90000.00,
    20000.00,
    100.00,
    25.00,
    600.00,
    1.00,
    30.00
};

void displayMenu();
void addCrypto();
void deleteCrypto(string search);
void updateCrypto(string search);
void cryptoList();
void cryptoToBill();
void billToCrypto();
void historyTransaction(double bill, string selectCurrency, string billType, char billSym, double convertedAmount, const string& method);
void displayTransactionHistory();
void checkIfValid(bool opt, string billType, char billSym, double bill);
void displayCryptoConvertedSelected(double bill, string billType, char billSym, string selectcurrency, bool opt);
void displayCryptoConvertedAll(double bill, string billType, char billSym, bool opt);
void aboutUs();

int main() {

    char option;
    string search;
    do{
        displayMenu();
        cout << "\nOption ->  ";
        cin >> option;
        option = tolower(option);

        switch(option) {
            case '1':
                cryptoToBill();
                break;
            case '2':
                billToCrypto();
                break;
            case '3':
                addCrypto();
                break;
            case '4':
                cryptoList();
                break;
            case '5':
                cryptoList();
                cout << "\t\tEnter Crypto Name or Sub Name to delete: ";
                cin >> search;
                deleteCrypto(search);
                break;
            case '6':
                cryptoList();
                cout << "\t\tEnter Crypto Name or Sub Name to update: ";
                cin >> search;
                updateCrypto(search);
                break;
            case '7':
                displayTransactionHistory();
                break;
            case '8':
                aboutUs();
                break;
            case 'q':
                cout << "\n\t\tThanks for using our converting tool, Have a nice day!" << endl;
                break;
            default:
                cout << "\n\n\t\tInvalid option, please try again." << endl;
        }
    }while(option != 'q');

    return 0;
}

void displayMenu() {
    cout << "\n\n\t\tWelcome to the Crypto Coins Currency Converter!\n\n";
    cout << "\t[1]. Crypto to Bill" << endl;
    cout << "\t[2]. Bill to Crypto" << endl;
    cout << "\t[3]. Add Crypto Currency" << endl;
    cout << "\t[4]. View Crypto" << endl;
    cout << "\t[5]. Delete Crypto Currency" << endl;
    cout << "\t[6]. Update Crypto Currency" << endl;
    cout << "\t[7]. View Transaction Records" << endl;
    cout << "\t[8]. About Us " << endl;
    cout << "\t[q]. Quit" << endl;
}

void cryptoList() {
    bool hasCrypto = false;

    for (int i = 0; i < maxRow; i++) {
        if (!cryptoCurrencies[i].empty()) {
            hasCrypto = true;
            break;
        }
    }

    if (!hasCrypto) {
        cout << "\n\t\t*** No crypto currencies available at the moment. ***\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\t|====================================================================================================|\n";
    cout << "\t\t\t\tLIST OF AVAILABLE CRYPTO CURRENCIES AND VALUE\n";
    cout << "\t|====================================================================================================|\n";
    cout << "\t  Crypto Names\t\t(Peso)\t\t(Dollar)\t(Euro)\t\t(Yen)\n";
    cout << "\t|----------------------------------------------------------------------------------------------------|\n";

    for (int i = 0; i < maxRow; i++) {
        if (cryptoCurrencies[i] != "") {
            cout << "\t  [" << setw(4) << left << cryptoCurrenciesSubName[i] << "] "
                 << setw(12) << left << cryptoCurrencies[i]
                 << "\t" << setw(12) << cryptoValueInPeso[i]
                 << "\t" << setw(12) << cryptoValueInUsd[i]
                 << "\t" << setw(12) << cryptoValueInEur[i]
                 << "\t" << setw(12) << cryptoValueInJpy[i]
                 << "\n";
        }
    }

    cout << "\t|====================================================================================================|\n";
}

void checkIfValid(bool opt, string billType, char billSym, double amount, string selectCurrency) {
    bool valid = false;

    do {
        for (int i = 0; i < maxRow; i++) {
            if (selectCurrency == cryptoCurrenciesSubName[i] ||
                selectCurrency == cryptoCurrencies[i] ||
                selectCurrency == "all") {

                if (selectCurrency == "all") {
                    displayCryptoConvertedAll(amount, billType, billSym, opt);
                } else {
                    displayCryptoConvertedSelected(amount, billType, billSym, selectCurrency, opt);
                }

                valid = true;
                break;
            }
        }

        if (!valid) {
            cout << "\n\n\t\t\t*** Error ***\n\tInvalid currency name. Please try again.\n\n";
            cryptoList();
            cout << "Type Crypto Available above: --> ";
            cin >> selectCurrency;
        }

    } while (!valid);
}

// Option 1
void cryptoToBill() {
    bool opt1 = true;
    char option;
    string selectCurrency;
    double crypto;
    char billSym;
    string billType;

    bool keepConverting = true;

    while (keepConverting) {
        cryptoList();
        cout << "\t  [all] To convert all current list crypto currency\n\n";
        cout << "\tType Crypto Available above: --> ";
        cin >> selectCurrency;
        cout << "\tEnter your Crypto Value: ";
        cin >> crypto;

        cout << "\n\n\t[1]. Peso\n";
        cout << "\t[2]. Dollar\n";
        cout << "\t[3]. Euro\n";
        cout << "\t[4]. Yen\n";
        cout << "\t[b]. Back\n";
        cout << "Select The Bill you want to Convert -> ";
        cin >> option;

        switch(option) {
            case '1':
                billType = "Peso";
                billSym = 'P';
                checkIfValid(opt1, billType, billSym, crypto, selectCurrency);
                break;
            case '2':
                billType = "Dollar";
                billSym = '$';
                checkIfValid(opt1, billType, billSym, crypto, selectCurrency);
                break;
            case '3':
                billType = "Euro";
                billSym = 'E';
                checkIfValid(opt1, billType, billSym, crypto, selectCurrency);
                break;
            case '4':
                billType = "Yen";
                billSym = 'Y';
                checkIfValid(opt1, billType, billSym, crypto, selectCurrency);
                break;
            case 'b':
                cout << "Exiting the conversion menu.\n";
                keepConverting = false;
                continue;
            default:
                cout << "Invalid option, please try again.\n";
                continue;
        }

        char again;
        cout << "\nDo you want to convert another currency? (y/n): ";
        cin >> again;

        if (tolower(again) != 'y') {
            keepConverting = false;
        }

        cout << "\n\n";
    }
}


// Option 2
void billToCrypto() {
    bool opt2 = false;
    char option;
    string selectCurrency;
    double bill;
    char billSym;
    string billType;
    do
    {
        cout << "\t\tBill To Crypto Converter\n\n";
        cout << "\t[1]. Peso\n";
        cout << "\t[2]. Dollar\n";
        cout << "\t[3]. Euro\n";
        cout << "\t[4]. Yen\n";
        cout << "\t[b]. Back\n";
        cout << "Select The Bill you want to Convert -> ";
        cin >> option;

        switch(option) {
            case '1':
                billType = "Peso";
                billSym = 'P';

                cout << "Enter your Peso Bill Value: ";
                cin >> bill;

                cryptoList();
                cout << "\t  [all] To convert all current list crypto currency\n\n";
                cout << "Type Crypto Available above: --> ";
                cin >> selectCurrency;

                checkIfValid(opt2, billType, billSym, bill, selectCurrency);

                break;
            case '2':
                billType = "Dollar";

                billSym = '$';

                cout << "Enter your Dollar Bill Value: ";
                cin >> bill;

                cryptoList();
                cout << "\t  [all] To convert all current list crypto currency\n\n";
                cout << "Type Crypto Available above: --> ";
                cin >> selectCurrency;

                checkIfValid(opt2, billType, billSym, bill, selectCurrency);

                break;
            case '3':
                billType = "Euro";
                billSym = 'E';

                cout << "Enter your Euro Bill Value: ";
                cin >> bill;

                cryptoList();
                cout << "\t  [all] To convert all current list crypto currency\n\n";
                cout << "Type Crypto Available above: --> ";
                cin >> selectCurrency;

                checkIfValid(opt2, billType, billSym, bill, selectCurrency);

                break;
            case '4':
                billType = "Yen";
                billSym = 'Y';

                cout << "Enter your Yen Bill Value: ";
                cin >> bill;

                cryptoList();
                cout << "\t  [all] To convert all current list crypto currency\n\n";
                cout << "Type Crypto Available above: --> ";
                cin >> selectCurrency;

                checkIfValid(opt2, billType, billSym, bill, selectCurrency);

                break;
            case 'b':
                break;
            default:
                cout << "Invalid option, please try again." << endl;
        }
        cout << "\n\n";
    } while (option != 'b');
}

void displayCryptoConvertedSelected(double bill, string billType, char billSym, string selectcurrency, bool opt){

    double converted = 0;

    if (opt == true )
    {
        cout << "\n\t\tCrypto Vallue: '" << bill << selectcurrency << "'" << endl;
        cout << "\t\t-----------------------\n";
        cout << "\t\t" << selectcurrency <<" --> " << billType << endl;
        cout << "\t\t-----------------------\n";

        for (int i = 0; i < maxRow; i++)
        {
            if (selectcurrency == cryptoCurrenciesSubName[i] || selectcurrency == cryptoCurrencies[i] )
            {
                if (billSym == 'P')
                {
                    converted = bill * cryptoValueInPeso[i];
                    cout << "\t\t\t" << billSym << fixed << setprecision(2) << converted << endl;
                }else if (billSym == '$')
                {
                    converted = bill * cryptoValueInUsd[i];
                    cout << "\t\t\t" << billSym << fixed << setprecision(2) << converted << endl;
                }else if (billSym == 'E'){
                    converted = bill * cryptoValueInEur[i];
                    cout << "\t\t\t" << billSym << fixed << setprecision(2) << converted << endl;
                }else{
                    converted = bill * cryptoValueInJpy[i];
                    cout << "\t\t\t" << billSym << fixed << setprecision(2) << converted << endl;
                }

                historyTransaction(bill, selectcurrency, billType, billSym, converted, "Crypto to Bill");
            }
        }
        cout << "\t\t-----------------------\n";


    }else
    {
        cout << "\n\t\t" << billType << " Bill Vallue: '" << billSym << bill << "'" << endl;
        cout << "\t\t--------------------------\n";
        cout << "\t\t" << billType << " --> " << selectcurrency << endl;
        cout << "\t\t---------------------------\n";

        for (int i = 0; i < maxRow; i++)
        {
            if (selectcurrency == cryptoCurrenciesSubName[i] || selectcurrency == cryptoCurrencies[i])
            {
                if (billSym == 'P')
                {
                    converted = bill / cryptoValueInPeso[i];
                    cout << "\t\t\t" << fixed << setprecision(8) << converted << " (" << cryptoCurrenciesSubName[i] << ")"<< endl;
                }else if (billSym == '$')
                {
                    converted = bill / cryptoValueInUsd[i];
                    cout << "\t\t\t" << fixed << setprecision(8) << converted << " (" << cryptoCurrenciesSubName[i] << ")"<< endl;
                }else if (billSym == 'E'){
                    converted = bill / cryptoValueInEur[i];
                    cout << "\t\t\t" << fixed << setprecision(8) << converted << " (" << cryptoCurrenciesSubName[i] << ")"<< endl;
                }else{
                    converted = bill / cryptoValueInEur[i];
                    cout << "\t\t\t" << fixed << setprecision(8) << converted << " (" << cryptoCurrenciesSubName[i] << ")"<< endl;
                }

                historyTransaction(bill, selectcurrency, billType, billSym, converted, "Bill to Crypto");

                cout << "\t\t---------------------------\n";
            }
        }
    }
}

void displayCryptoConvertedAll(double bill, string billType, char billSym, bool opt) {

    if (opt == true) {
        cout << fixed << setprecision(2);

        cout << "\t\t+-----------------------------------------------+\n";
        cout << "\t\t|\tCrypto Value: '" << bill << "' into " << billType << "\t|\n";
        cout << "\t\t+-----------------------------------------------+" << endl;

        for (int i = 0; i < maxRow; i++) {

            if (cryptoCurrencies[i] != "") {
                cout << "\t\t " << cryptoCurrencies[i] << "(" << cryptoCurrenciesSubName[i] << ")\t\t-->\t";

                if (billSym == 'P') {
                    cout << billSym << bill * cryptoValueInPeso[i] << "\n";
                } else if (billSym == '$') {
                    cout << billSym << bill * cryptoValueInUsd[i]  << "\n";
                } else if (billSym == 'E') {
                    cout << billSym << bill * cryptoValueInEur[i]  << "\n";
                } else {
                    cout << billSym << bill * cryptoValueInJpy[i]  << "\n";
                }
            }

        }
        cout << "\t\t+-----------------------------------------------+" << endl;

    } else {
        cout << fixed << setprecision(8);

        cout << "\n\t\tList of Crypto Converted:" << endl;
        cout << "\t\t-----------------------------------------\n";
        cout << "\t\t" << billType << "Bill Value: '" << bill << "' into Crypto Coins" << endl;
        cout << "\t\t------------------------------------------" << endl;

        for (int i = 0; i < maxRow; i++) {
            if (cryptoCurrencies[i] != "")
            {
                cout << "\t\t";
                if (billSym == 'P') {
                    cout << bill / cryptoValueInPeso[i] << " (" << cryptoCurrenciesSubName[i] << ")"  << endl;
                } else if (billSym == '$') {
                    cout << bill / cryptoValueInUsd[i]  << " (" << cryptoCurrenciesSubName[i] << ")" << endl;
                } else if (billSym == 'E') {
                    cout << bill / cryptoValueInEur[i]  << " (" << cryptoCurrenciesSubName[i] << ")" << endl;
                } else {
                    cout << bill / cryptoValueInJpy[i]  << " (" << cryptoCurrenciesSubName[i] << ")" << endl;
                }
            }
        }
        cout << "\t\t------------------------------------------" << endl;
    }
}

void addCrypto() {

    bool isValid = true;
    int errorHandling = 0;
    string cryptoName;
    string subName;
    double cryptoValuePeso;
    double cryptoValueUsd;
    double cryptoValueEur;
    double cryptoValueJpy;

    cryptoList();
    cout << "\n\t\t\tAdd Crypto Currency\n\n";
    cout << "*** Not allowed same crypto name or sub name ***\n";
    cout << "Crypto Name: ";
    cin >> cryptoName;
    cout << "Crypto Sub Name: ";
    cin >> subName;

    for(int i=0; i < maxRow; i++) {
        if (cryptoName == cryptoCurrencies[i] || subName == cryptoCurrenciesSubName[i]) {
            isValid = false;
        }
    }

    if (isValid == true) {
        for (int i=0; i < maxRow; i++)
        {
            if (cryptoCurrencies[i] == "") {

                errorHandling++;

                cout << "Crypto Value in Peso: ";
                cin >> cryptoValuePeso;
                cout << "Crypto Value in Dollar: ";
                cin >> cryptoValueUsd;
                cout << "Crypto Value in Euro: ";
                cin >> cryptoValueEur;
                cout << "Crypto Value in Yen: ";
                cin >> cryptoValueJpy;

                cryptoCurrencies[i] = cryptoName;
                cryptoCurrenciesSubName[i] = subName;
                cryptoValueInPeso[i] = cryptoValuePeso;
                cryptoValueInUsd[i] = cryptoValueUsd;
                cryptoValueInEur[i] = cryptoValueEur;
                cryptoValueInJpy[i] = cryptoValueJpy;

                cryptoList();

                cout << "\n\n\t\tSuccessfully Added!\n\n";

                break;
            }
        }
    }

    if (errorHandling == 0 && isValid == false){
        cout << "\n\n\t\t*** Not Allowed same Crypto, Recheck the list again! ***\n\n";
    }

    if(errorHandling == 0 && isValid == true){
        cout << "\n\n\t\t*** Crypto Storage has been reached! ***\n\n";
    }
}

void deleteCrypto(string search){

    int errorHandling = 0;

    for (int i = 0; i < maxRow; i++)
    {
        if(cryptoCurrenciesSubName[i] == search || cryptoCurrencies[i] == search){
            errorHandling++;

            cryptoCurrencies[i] = "";
            cryptoCurrenciesSubName[i] = "";
            cryptoValueInPeso[i] = 0;
            cryptoValueInUsd[i] = 0;
            cryptoValueInEur[i] = 0;
            cryptoValueInJpy[i] = 0;

            cryptoList();

            cout << "\nSuccessfully Deleted!\n";
            break;
        }
    }

    if (errorHandling  == 0){
        cout << "\n\n\t\t*** No Crypto Found, Recheck the list again! ***\n\n";
    }
}

void updateCrypto(string search){
    int errorHandling = 0;
    string CryptoName;
    string subName;
    double cryptoValuePeso;
    double cryptoValueUsd;
    double cryptoValueEur;
    double cryptoValueJpy;


    for (int i = 0; i < maxRow; i++)
    {
        if(cryptoCurrenciesSubName[i] == search || cryptoCurrencies[i] == search){
            errorHandling++;

            cout << "Crypto Name: ";
            cin >> CryptoName;
            cout << "Crypto Sub Name: ";
            cin >> subName;
            cout << "Crypto Value in Peso: ";
            cin >> cryptoValuePeso;
            cout << "Crypto Value in Dollar: ";
            cin >> cryptoValueUsd;
            cout << "Crypto Value in Euro: ";
            cin >> cryptoValueEur;
            cout << "Crypto Value in Yen: ";
            cin >> cryptoValueJpy;

            cryptoCurrencies[i] = CryptoName;
            cryptoCurrenciesSubName[i] = subName;
            cryptoValueInPeso[i] = cryptoValuePeso;
            cryptoValueInUsd[i] = cryptoValueUsd;
            cryptoValueInEur[i] = cryptoValueEur;
            cryptoValueInJpy[i] = cryptoValueJpy;

            cryptoList();

            cout << "\nSuccessfully Updated!\n";
            break;
        }
    }

    if (errorHandling == 0){
        cout << "\n\n\t\t*** No Crypto Found, Recheck the list again! ***\n\n";
    }
}

void aboutUs() {
    cout << "==============================================\n";
    cout << "|               ABOUT US                     |\n";
    cout << "==============================================\n";
    cout << "| Project Title: Crypto Currency Converter   |\n";
    cout << "| Date Created : April 27, 2025              |\n";
    cout << "| Members:                                   |\n";
    cout << "|   * Rexie Villanueva                       |\n";
    cout << "|      -Programmer                           |\n";
    cout << "|   * Rain Santiago                          |\n";
    cout << "|      -Documentation                        |\n";
    cout << "|   * Trisha Ann Santos                      |\n";
    cout << "|      -Documentation                        |\n";
    cout << "|   * Reyneil De Guzman                      |\n";
    cout << "|      -Documentation                        |\n";
    cout << "==============================================\n";
    cout << "|   Thank you for checking out our project!  |\n";
    cout << "==============================================\n";
}

void historyTransaction(double bill, string selectCurrency, string billType, char billSym, double convertedAmount, const string& method) {
    Log history;
    history.id = transactionCounter++;
    history.amount = bill;
    history.sym = billSym;
    history.billType = billType;
    history.selectedCurrency = selectCurrency;
    history.convertedAmount = convertedAmount;
    history.method = method;

    logList.push_back(history);
}

void displayTransactionHistory() {
    if (logList.empty()) {
        cout << "\n\t\tNo transaction history found.\n";
        return;
    }

    cout << "\n\t\t========== Transaction History ==========\n";
    cout << "\t---------------------------------------------------------------------------------------------\n";
    cout << "\t" << left << setw(5) << "ID"
         << setw(18) << "Amount"
         << setw(18) << "Crypto Currency"
         << setw(12) << "Bill Type"
         << setw(8) << "Symbol"
         << setw(15) << "Converted"
         << setw(20) << "Method" << "\n";
    cout << "\t---------------------------------------------------------------------------------------------\n";

    for (const auto& entry : logList) {
            if (entry.method == "Crypto to Bill"){
                cout << "\t" << left << setw(5) << entry.id
             << setw(18) << fixed << setprecision(2) << entry.amount
             << setw(18) << entry.selectedCurrency
             << setw(12) << entry.billType
             << setw(8) << entry.sym
             << setw(15) << fixed << setprecision(2) << entry.convertedAmount
             << setw(20) << entry.method << "\n";
        }else{
            cout << "\t" << left << setw(5) << entry.id
             << setw(18) << fixed << setprecision(2) << entry.amount
             << setw(18) << entry.selectedCurrency
             << setw(12) << entry.billType
             << setw(8) << entry.sym
             << setw(15) << fixed << setprecision(8) << entry.convertedAmount
             << setw(20) << entry.method << "\n";
        }
    }
    cout << "\t---------------------------------------------------------------------------------------------\n";
}
