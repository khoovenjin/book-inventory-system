#include <bits/stdc++.h>
#include "book.h"
#include "transaction.h"
#include "csvReadWrite.h"

using namespace std;

deque<book> *inventorydata = new deque<book>();                 //Inventory-Transaction Deques : Pointer(*)
deque<transaction> *transactiondata = new deque<transaction>();

void showSelection();           //Early-Initialization : Methods/Functions
void showInventory();
void showTransaction();
void storesampleinventory();
void storesampletransaction();

void showSelection(){           //Home Page Template : void
    cout << "*** Welcome to Our Inventory System by C++ ***" << endl;
    cout << "To select an action, enter " << endl;
    cout << "1 to access Inventory" << endl;
    cout << "2 to access Transaction" << endl;
    cout << "3 to Exit" << endl;
}
void showInventory(){           //Inventory Template : void
    cout << "*** This is Your Inventory ***" << endl;
    cout << "To select an action, enter " << endl;
    cout << "1 to Add Book" << endl;
    cout << "2 to Update Book" << endl;
    cout << "3 to Delete Book" << endl;
    cout << "4 to Display Book" << endl;
    cout << "5 to Search Book" << endl;
    cout << "6 to Filter Book" << endl;
    cout << "7 to Sort Back" << endl;
    cout << "8 to Go Back" << endl;
}
void showTransaction(){         //Transaction Template : void
    cout << "*** This is Your Transaction ***" << endl;
    cout << "To select an action, enter " << endl;
    cout << "1 to Add Transaction" << endl;
    cout << "2 to Display Transaction" << endl;
    cout << "3 to View Transaction Details" << endl;
    cout << "4 to Sort Transaction" << endl;
    cout << "5 to Exit" << endl;
}
void interfaceInventory(){
    int choice;
    showInventory();

    cin >> choice;

    while (choice != 8){            //Repeat : Not Inventory Option
        switch (choice){            //Calling Methods/Functions from Book.cpp : Static void
        case 1:
            book::addBook();
            break;
        case 2:
            book::updateBook();
            break;
        case 3:
            book::deleteBook();
            break;
        case 4:
            book::displayBook();
            break;
        case 5:
            book::searchBook();
            break;
        case 6:
            book::filterBook();
            break;
        case 7:
            book::sortBook();
            break;
        default: cout << "Invalid selection." << endl;
        }
        showInventory();
        cin >> choice;
    }
    return;
}
void interfaceTransaction(){
    int choice;
    showTransaction();

    cin >> choice;

    while (choice != 5){                        //Repeat : Not Transaction Option
        switch (choice){                        //Calling Methods/Functions from Transaction.cpp : Static void
        case 1:
            transaction::addTransaction();
            break;
        case 2:
            transaction::displayTransaction();
            break;
        case 3:
            transaction::detailTransaction();
            break;
        case 4:
            transaction::sortTransaction();
            break;
        default: cout << "Invalid selection." << endl;
        }
        showTransaction();
        cin >> choice;
    }
    return;
}
int main()
{
    storesampleinventory();             //Custom set-up of Inventory, Transaction, Transaction Detail Excel File (Optional)
    storesampletransaction();           //
    csvReadWrite::readInventory();      //Load Inventory Excel File to Inventory Deque
    csvReadWrite::readTransaction();    //Load Transaction Excel File to Transaction Deque

    int choice;
    showSelection();

    cin >> choice;

    while (choice != 3){                //Repeat : Not Selection Option
        switch (choice){
        case 1:
            interfaceInventory();       //Call Inventory Template
            break;
        case 2:
            interfaceTransaction();     //Call Transaction Template
            break;
        default: cout << "Invalid selection." << endl;
        }
        showSelection();
        cin >> choice;
    }
    return 0;
}
void storesampleinventory(){        //Custom set-up Inventory Excel File : Sample (Optional)
    ofstream myFile;
    myFile.open("inventorydata.csv");

    vector<string> linestorage;
    string appendingline = "";
    int counter = 0; //added

    book *newbook2 = new book("Pet Sematary", 33.92, 8, "Horror");
    book *newbook3 = new book("Doctor Sleep", 36.47, 14, "Horror");
    book *newbook4 = new book("Hidden in Plain Sight", 39.02, 4, "Crime");
    book *newbook5 = new book("The Shadow Friend", 39.53, 9, "Crime");
    book *newbook6 = new book("Five Hundred Miles From You", 39.02, 18, "Romance");
    book *newbook7 = new book("It's In His Kiss", 39.02, 3, "Romance");
    inventorydata->push_back(*newbook2);
    inventorydata->push_back(*newbook3);
    inventorydata->push_back(*newbook4);
    inventorydata->push_back(*newbook5);
    inventorydata->push_back(*newbook6);
    inventorydata->push_back(*newbook7);

    deque<book> tempinventorydata = *inventorydata;

    while(!tempinventorydata.empty()){
        stringstream templine(tempinventorydata.front().getDisplay());
        tempinventorydata.pop_front();

        while(getline(templine, appendingline, '\t')){
            linestorage.push_back(appendingline);
        }
        vector <string> :: iterator ptr;
        for (ptr = linestorage.begin(); ptr < linestorage.end(); ptr++){
            appendingline += *ptr;
            if(counter==3){
                appendingline += "/,";
            }else{
                appendingline += ",";
            }

            counter++;
            if(counter==4){
                counter = 0;
                string indexing = *ptr;
                int stringindexing = indexing.size();
                appendingline.erase(0,stringindexing);

                appendingline.pop_back();
                myFile << appendingline << endl;
                appendingline = "";
                linestorage.clear();
            }

        }
    }
    myFile << appendingline << endl;
    myFile.close();
}
void storesampletransaction(){              //Custom set-up Transaction Excel File : Sample (Optional)
    ofstream myFile;
    myFile.open("transactiondata.csv");

    vector<string> linestorage;
    string appendingline = "";
    int counter = 0; //added

    queue<book> auxdata2;
    queue<book> auxdata3;
    queue<book> auxdata4;

    book *transactionbookdetail2 = new book("Pet Sematary", 67.84, 2, "Horror");
    book *transactionbookdetail5 = new book("Hidden in Plain Sight", 78.04, 2, "Crime");
    auxdata2.push(*transactionbookdetail2);
    auxdata2.push(*transactionbookdetail5);
    book *transactionbookdetail3 = new book("The Shadow Friend", 79.06, 2, "Crime");
    auxdata3.push(*transactionbookdetail3);
    book *transactionbookdetail4 = new book("It's In His Kiss", 78.04, 2, "Romance");
    auxdata4.push(*transactionbookdetail4);

    transaction *newtransaction2 = new transaction(1, "2021 5 10 8:48:07", 145.88);
    transaction *newtransaction3 = new transaction(2, "2021 5 10 8:48:26", 79.06);
    transaction *newtransaction4 = new transaction(3, "2021 5 10 8:48:35", 78.04);
    transactiondata->push_back(*newtransaction2);
    transactiondata->push_back(*newtransaction3);
    transactiondata->push_back(*newtransaction4);

    while(!auxdata2.empty()){
        newtransaction2->pushtransactiondetail(auxdata2.front());
        auxdata2.pop();
    }

    while(!auxdata3.empty()){
        newtransaction3->pushtransactiondetail(auxdata3.front());
        auxdata3.pop();
    }

    while(!auxdata4.empty()){
        newtransaction4->pushtransactiondetail(auxdata4.front());
        auxdata4.pop();
    }

    deque<transaction> temptransactiondata = *transactiondata;
    deque<transaction> temptransactiondata2 = temptransactiondata;

    while(!temptransactiondata.empty()){
        stringstream templine(temptransactiondata.front().getDisplay());
        temptransactiondata.pop_front();

        while(getline(templine, appendingline, '\t')){
            linestorage.push_back(appendingline);
        }
        vector <string> :: iterator ptr;
        for (ptr = linestorage.begin(); ptr < linestorage.end(); ptr++){
            appendingline += *ptr;
            if(counter==2){
                appendingline += "/,";
            }else{
                appendingline += ",";
            }

            counter++;
            if(counter==3){
                counter = 0;
                string indexing = *ptr;
                int stringindexing = indexing.size();
                appendingline.erase(0,stringindexing);

                appendingline.pop_back();
                myFile << appendingline << endl;
                appendingline = "";
                linestorage.clear();
            }

        }
    }

    while(!temptransactiondata2.empty()){
        string id = to_string(temptransactiondata2.front().gettransactionid());
        deque<book> *temptransactiondetail = temptransactiondata2.front().gettransactiondetail();
        csvReadWrite::writeTransactionDetail(id,*temptransactiondetail);
        temptransactiondata2.pop_front();
    }
    myFile << appendingline << endl;
    myFile.close();
}

