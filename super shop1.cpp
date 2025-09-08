#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;

public:
    Bill() : Item(""), Rate(0), Quantity(0) {}

    void setItem(string item) { Item = item; }
    void setRate(int rate) { Rate = rate; }
    void setQuant(int quant) { Quantity = quant; }

    string getItem() { return Item; }
    int getRate() { return Rate; }
    int getQuant() { return Quantity; }

    void addItem() {
        bool close = false;
        while (!close) {
            int choice;
            cout << "\t1. Add Item" << endl;
            cout << "\t2. Close" << endl;
            cout << "\tEnter Choice: ";
            cin >> choice;

            if (choice == 1) {
                system("cls");
                string item;
                int rate, quant;

                cout << "\nEnter Item Name: ";
                cin >> item;
                setItem(item);

                cout << "\nEnter Rate of Item: ";
                cin >> rate;
                setRate(rate);

                cout << "\nEnter Quantity of Item: ";
                cin >> quant;
                setQuant(quant);

                ofstream out("D:/Bill.txt", ios::app);
                if (!out) {
                    cout << "\nError: File Can't Open!" << endl;
                } else {
                    out << getItem() << ":" << getRate() << ":" << getQuant() << endl;
                    cout << "\nItem Added Successfully" << endl;
                }
                out.close();
                Sleep(2000);
            } else if (choice == 2) {
                system("cls");
                close = true;
                cout << "\nBack to main Menu!" << endl;
                Sleep(2000);
            }
        }
    }

    void printBill() {
        system("cls");
        int total = 0;
        bool close = false;

        while (!close) {
            int choice;
            cout << "\t1. Add Item to Bill" << endl;
            cout << "\t2. Close and Print Total" << endl;
            cout << "\tEnter Choice: ";
            cin >> choice;

            if (choice == 1) {
                string item;
                int quant;
                cout << "\nEnter Item: ";
                cin >> item;
                cout << "\nEnter Quantity: ";
                cin >> quant;

                ifstream in("D:/Bill.txt");
                ofstream out("D:/Temp.txt");
                string line;
                bool found = false;

                while (getline(in, line)) {
                    stringstream ss(line);
                    string itemName;
                    int itemRate, itemQuant;
                    char delim;

                    getline(ss, itemName, ':');
                    ss >> itemRate >> delim >> itemQuant;

                    if (item == itemName) {
                        found = true;
                        if (quant <= itemQuant) {
                            int amount = itemRate * quant;
                            cout << "\n Item | Rate | Quantity | Amount\n";
                            cout << " " << itemName << " | " << itemRate << " | " << quant << " | " << amount << endl;

                            int newQuant = itemQuant - quant;
                            total += amount;
                            if (newQuant > 0) {
                                out << itemName << ":" << itemRate << ":" << newQuant << endl;
                            }
                        } else {
                            cout << "\nSorry, only " << itemQuant << " available." << endl;
                            out << line << endl;
                        }
                    } else {
                        out << line << endl;
                    }
                }

                if (!found) {
                    cout << "\nItem Not Available!" << endl;
                }

                in.close();
                out.close();
                remove("D:/Bill.txt");
                rename("D:/Temp.txt", "D:/Bill.txt");

                Sleep(2000);
            } else if (choice == 2) {
                close = true;
                cout << "\nTotal Bill: " << total << endl;
                cout << "Thanks for shopping!" << endl;
                Sleep(3000);
            }
        }
    }
};

// MAIN FUNCTION
int main() {
    Bill b;
    bool exit = false;

    while (!exit) {
        system("cls");
        int val;
        cout << " Welcome to Super Market Billing System\n";
        cout << "\t1. Add Item\n";
        cout << "\t2. Print Bill\n";
        cout << "\t3. Exit\n";
        cout << "\nEnter Choice: ";
        cin >> val;

        if (val == 1) {
            b.addItem();
        } else if (val == 2) {
            b.printBill();
        } else if (val == 3) {
            exit = true;
            cout << "\nGood Luck!" << endl;
            Sleep(2000);
        }
    }

    return 0;
}

