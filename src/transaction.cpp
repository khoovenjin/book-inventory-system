#include <bits/stdc++.h>
#include "book.h"
#include "transaction.h"
#include "csvReadWrite.h"

using namespace std;

extern deque<book> *inventorydata;              //To Link with Global Static Deque in Main.cpp
extern deque<transaction> *transactiondata;

transaction::transaction(int a, string b, float c) : transactionid(a), transactiontime(b), transactionprice(c){}    //Member Initializers & Member Syntax (Constructor)
int transaction::gettransactionid(){
    return transactionid;                           //Return Transaction ID : Integer
}
string transaction::gettransactiontime(){
    return transactiontime;                         //Return Transaction Time : String
}
float transaction::gettransactionprice(){
    return transactionprice;                        //Return Transaction Price : Float
}
deque<book>* transaction::gettransactiondetail(){
    return transactiondetail;                       //Return Transaction Detail : Deque<book>* (pointer)
}
string transaction::getDisplay(){
    return to_string(gettransactionid()) + "\t" + gettransactiontime() + "\t" + to_string(gettransactionprice());   //Return all data : String
}
void transaction::settransactionid(int transactionid){
    this->transactionid = transactionid;            //Set Transaction ID : Integer
}
void transaction::settransactiontime(string transactiontime){
    this->transactiontime = transactiontime;        //Return Transaction Time : String
}
void transaction::settransactionprice(float transactionprice){
    this->transactionprice = transactionprice;      //Return Transaction Price : Float
}
void transaction::pushtransactiondetail(book transactioninput){
    transactiondetail->push_back(transactioninput); //Push book into Transaction Detail : Book
}
void transaction::addTransaction(){
    unordered_map<string, int> umap;                //Hash Map : Unordered Map
    queue<book> auxdata;
    vector<string> tempinvname;
    string bookname;
    float bookprice;
    int bookquantity;
    string bookcategory;

    deque<transaction> temptransactionholder = *transactiondata;

    deque <book> :: iterator ptr;                   //Store all Book Name into a vector : String
    for (ptr = (*inventorydata).begin(); ptr != (*inventorydata).end(); ++ptr){
        tempinvname.push_back(ptr->getname());
    }

    bool addtransactiontrigger = true;
    int transactioncounter = 0;
    cout << "Adding new transaction in database..." << endl;
    cout << "Recording New Transaction..." << endl;
    cout << "To checkout transaction, enter !" << endl;
    cout << "To terminate transaction, enter @" << endl;

    while(addtransactiontrigger){                   //For Controlled Loop : While
        string addtransactionname;
        cout << "Book Name: ";
        if(transactioncounter==0){
            cin.ignore();                           //Ignore first auto-CIN
        }
        getline(cin, addtransactionname);
        if(addtransactionname=="!"){                //Checkout : !
            if(transactioncounter==0){              //First Record : Cancel
                cout << "Transaction canceled successfully!" << endl;
                return;
            }else{
                //submit transaction;
                transaction::generateID();          //Generate Unique ID : Static INT
                time_t now = time(0);               //Generate Current Date Time
                tm *ltm = localtime(&now);
                string year = to_string(1900 + ltm->tm_year);
                string month = to_string(1 + ltm->tm_mon);
                string day = to_string(ltm->tm_mday);
                string time = to_string(5+ltm->tm_hour) + ":" + to_string(30+ltm->tm_min) + ":" + to_string(ltm->tm_sec);
                string currentdatetime = year + " " + month + " " + day + " " + time;

                transaction *newtransaction = new transaction(transaction::counterid, currentdatetime, umap["TOTALPRICE"]); //Create Transaction Detail

                while(!auxdata.empty()){            //Push into Transaction Node
                    newtransaction->pushtransactiondetail(auxdata.front());
                    auxdata.pop();
                }

                //Update minus stock in inventorydata
                for (auto x : umap){
                    vector<string>::iterator itt = find(tempinvname.begin(), tempinvname.end(), (string)x.first);
                    if (itt != tempinvname.end()){
                        int tempindex = itt - tempinvname.begin();
                        book tempbook2 = (*inventorydata)[tempindex];
                        int auxquantityplacement = (int)x.second;
                        (*inventorydata)[tempindex].setquantity(tempbook2.getquantity()-auxquantityplacement);
                        csvReadWrite::writeInventory();
                    }
                }

                transactiondata->push_back(*newtransaction);            //Update Transaction Data : Deque

                while(!temptransactionholder.empty()){
                    transactiondata->push_front(temptransactionholder.back());
                    temptransactionholder.pop_back();
                }

                cout << "Transaction added successfully!" << endl;
                csvReadWrite::writeTransaction();                       //Write to Transaction Excel File
                break;
            }
        }
        if(addtransactionname=="@"){                                    //Terminate Transaction : @
            cout << "Transaction canceled successfully!" << endl;
            return;
        }

        vector<string>::iterator it = find(tempinvname.begin(), tempinvname.end(), addtransactionname); //Search Book Name
        if (it != tempinvname.end()){
            int index = it - tempinvname.begin();           //Indexing
            book tempbook = (*inventorydata)[index];        //Cloning
            bookname = addtransactionname;
            bookprice = tempbook.getprice();
            bookquantity = (tempbook.getquantity())-umap[bookname]; //Calculate remaining stock : -Hash Map
            bookcategory= tempbook.getcategory();

            string addtransactionquantity;
            cout << "Book Quantity: ";
            getline(cin, addtransactionquantity);       //Get Quantity

            bool booleantrigger =true;
            while(booleantrigger){
                if(addtransactionquantity=="!"){        //Attempt Checkout : ! ; Fail -> Repeat Loop
                    cout << "You can't checkout transaction here, check out is only available during \"Book Name\" enquiry, please enter a quantity" << endl;
                    cout << "Book Quantity: ";
                    getline(cin, addtransactionquantity);
                }else if(addtransactionquantity=="@"){  //Terminate Transaction : @
                    cout << "Transaction canceled successfully!" << endl;
                    return;
                }else{
                    int tempcounter = 0;                    //Validate Input : Alphabet Checker
                    bool alphachecker = false;
                    while(addtransactionquantity[tempcounter]!='\0'){
                        if(isalpha(addtransactionquantity[tempcounter])){
                            alphachecker = true;
                        }
                        tempcounter++;
                    }
                    while(alphachecker){
                        cout << "Invalid Input" << endl;
                        cout << "Book Quantity: ";
                        getline(cin, addtransactionquantity);
                        tempcounter = 0;
                        alphachecker = false;
                        if(addtransactionquantity=="!"){
                            break;
                        }
                        if(addtransactionquantity=="@"){
                            cout << "Transaction canceled successfully!" << endl;
                            return;
                        }
                        while(addtransactionquantity[tempcounter]!='\0'){
                            if(isalpha(addtransactionquantity[tempcounter])){
                                alphachecker = true;
                            }
                            tempcounter++;
                        }
                    }
                    if(addtransactionquantity=="!"){            //2nd Validation : Attempt Checkout (!) -> Skip Rest of Code and Repeat to Disallow
                        continue;                               //Back to Line 143
                    }
                    int realtransactionquantity;
                    realtransactionquantity = stoi(addtransactionquantity);

                    while(realtransactionquantity>bookquantity){                    //Validate Value : Must be less than Current Stock
                        cout << "Value is more than inventory, try again" << endl;
                        cout << "Value in inventory is " << bookquantity << endl;
                        string tempquantity;
                        cout << "Book Quantity: ";
                        getline(cin, tempquantity);
                        if(addtransactionquantity=="@"){                            //Terminate Transaction : @
                            cout << "Transaction canceled successfully!" << endl;
                            return;
                        }
                        realtransactionquantity = stoi(tempquantity);
                    }

                    bookprice *= realtransactionquantity;               //Calculate Total Price per transaction detail record

                    book *transactionbookdetail = new book(bookname, bookprice, realtransactionquantity, bookcategory);
                    auxdata.push(*transactionbookdetail);               //Push-Collect Transaction Detail into Queue

                    umap[bookname] += realtransactionquantity;          //Hash Map : Keep track of remaining stock
                    umap["TOTALPRICE"] += bookprice;                    //Hash Map : Accumulate Total Price of entire transaction

                    booleantrigger = false;                             //Break Repeat : Boolean[False]
                    transactioncounter++;
                }
            }
        }else{
            cout << "Book Name entered is non-existence" << endl;       //Book Not Exists
            return;
        }
    }
}
void transaction::displayTransaction(){
    cout << "Displaying all transactions..." << endl;
    cout << "Transaction ID\tTime\tTotal Price" << endl;

    deque <transaction> :: iterator ptr;            //Iterate-Display Transaction
    for (ptr = transactiondata->begin(); ptr != transactiondata->end(); ++ptr){
        cout << ptr->getDisplay() << endl;
    }
}
void transaction::detailTransaction(){
    vector<int> temptransid;
    int transactionpicker;
    cout << "Viewing details of transaction..." << endl;
    transaction::displayTransaction();              //Display Transaction
    cout << "To display transaction details, enter the Transaction ID" << endl;
    cout << "Transaction ID: ";
    cin >> transactionpicker;

    deque <transaction> :: iterator ptr;                    //Store all Transaction ID into a vector : Integer
    for (ptr = (*transactiondata).begin(); ptr != (*transactiondata).end(); ++ptr){
        temptransid.push_back(ptr->gettransactionid());
    }

    vector<int>::iterator it = find(temptransid.begin(), temptransid.end(), transactionpicker); //Search Transaction ID
    if (it != temptransid.end()){       //Found Transaction : True
        int index = it - temptransid.begin();       //Indexing
        transaction temptrans = (*transactiondata)[index];      //Cloning
        cout << "Displaying select transaction record..." << endl;
        deque<book> *auxtransactiondetail = temptrans.gettransactiondetail();
        cout << "Book Name\t\tPrice\tQuantity\tCategory" << endl;
        deque <book> :: iterator ptr2;                          //Iterate-Display Transaction Detail Node in Transaction
        for (ptr2 = auxtransactiondetail->begin(); ptr2 != auxtransactiondetail->end(); ++ptr2){
            cout << ptr2->getDisplay() << endl;
        }
        cout << "Transaction ID: " << to_string(temptrans.gettransactionid()) << endl;      //Summary Report of Transaction
        cout << "Transaction Time: " << temptrans.gettransactiontime() << endl;
        cout << "Transaction Total Price: " << to_string(temptrans.gettransactionprice()) << endl;
    }else{
        cout << "Transaction ID entered is non-existence" << endl;      //Book Not Exist
        return;
    }
}
void transaction::sortTransaction(){
    string sortselection;
    int finalselection;
    cout << "Sorting transaction records..." << endl;
    cout << "SORTING OPTION:" << endl;
    cout << "To select a sort (Number ONLY), enter " << endl;
    cout << "1 for Transaction ID (Low-High)" << endl;
    cout << "2 for Transaction Time (Earliest-Most Recent)" << endl;
    cout << "3 for Transaction Price (Low-High)" << endl;
    cout << "4 to exit" << endl;
    cin.ignore();
    getline(cin, sortselection);

    int tempcounter = 0;                        //Validate Input : Alphabet Checker
    bool alphachecker = false;
    while(sortselection[tempcounter]!='\0'){
        if(isalpha(sortselection[tempcounter])){
            alphachecker = true;
        }
        tempcounter++;
    }
    while(alphachecker){
        cout << "Invalid Input" << endl;
        getline(cin, sortselection);
        tempcounter = 0;
        alphachecker = false;
        while(sortselection[tempcounter]!='\0'){
            if(isalpha(sortselection[tempcounter])){
                alphachecker = true;
            }
            tempcounter++;
        }
    }

    finalselection = stoi(sortselection);
    while(finalselection!=4){                   //Repeat : Not Sort Option
        switch (finalselection){
        case 1:
            sort(transactiondata->begin(),transactiondata->end(),sortalgo1);        //Sort Transaction : ID (Selection Sort)
            cout << "Transaction Records have been sorted based on Transaction ID successfully!" << endl;
            csvReadWrite::writeTransaction();       //Write to Transaction Excel File
            transaction::displayTransaction();
            return;
        case 2:
            sort(transactiondata->begin(),transactiondata->end(),sortalgo2);        //Sort Transaction : Time (Selection Sort)
            cout << "Transaction Records have been sorted based on Transaction Time successfully!" << endl;
            csvReadWrite::writeTransaction();       //Write to Transaction Excel File
            transaction::displayTransaction();
            return;
        case 3:
            sort(transactiondata->begin(),transactiondata->end(),sortalgo3);        //Sort Transaction : Price (Selection Sort)
            cout << "Transaction Records have been sorted based on Transaction Price successfully!" << endl;
            csvReadWrite::writeTransaction();       //Write to Transaction Excel File
            transaction::displayTransaction();
            return;
        default: cout << "Invalid selection." << endl;
        }
        cout << "Sort book in the transaction..." << endl;
        cout << "SORTING OPTION:" << endl;
        cout << "To select a sort (Number ONLY), enter " << endl;
        cout << "1 for Transaction ID (Low-High)" << endl;
        cout << "2 for Transaction Time (Earliest-Most Recent)" << endl;
        cout << "3 for Transaction Price (Low-High)" << endl;
        cout << "4 to exit" << endl;
        cin >> finalselection;
    }
}
void transaction::generateID(){     //Generate Unique Transaction ID : Change Static INT
    int currentid, highestid;
    deque<transaction> *temptransaction = transactiondata;
    if(!temptransaction->empty()){  //Iterate-Check-Compare All Transaction ID : Integer
        currentid = (temptransaction->front()).gettransactionid();
        highestid = currentid;
        temptransaction->pop_front();
        while(!temptransaction->empty()){
            currentid = (temptransaction->front()).gettransactionid();
            if(highestid<currentid){
                highestid = currentid;
            }
            temptransaction->pop_front();
        }
        transaction::counterid = highestid+1;   //Unique Next ID
    }
}
bool transaction::sortalgo1(transaction a,transaction b){   //Selection Sort Algorithm 1 (Using Boolean), Logically
    int firsttransactionid = a.gettransactionid();
    int secondtransactionid = b.gettransactionid();
    return firsttransactionid<secondtransactionid;
}
bool transaction::sortalgo2(transaction a,transaction b){   //Selection Sort Algorithm 2 (Using Boolean), Logically
    string firsttransactiontime = a.gettransactiontime();
    string secondtransactiontime = b.gettransactiontime();
    return firsttransactiontime<secondtransactiontime;
}
bool transaction::sortalgo3(transaction a,transaction b){   //Selection Sort Algorithm 3 (Using Boolean), Logically
    float firsttransactionprice = a.gettransactionprice();
    float secondtransactionprice = b.gettransactionprice();
    return firsttransactionprice<secondtransactionprice;
}
int transaction::counterid = 1; //Transaction ID : Static INT -> Default: 1
transaction::~transaction(){}   //Deconstructor
