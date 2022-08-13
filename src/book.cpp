#include <bits/stdc++.h>
#include "book.h"
#include "transaction.h"
#include "csvReadWrite.h"

using namespace std;

extern deque<book> *inventorydata;              //To Link with Global Static Deque in Main.cpp
extern deque<transaction> *transactiondata;     //

book::book(string a, float b, int c, string d) : name(a), price(b), quantity(c), category(d){}  //Member Initializers & Member Syntax (Constructor)
string book::getname(){
    return name;                        //Return Book Name : String
}
float book::getprice(){
    return price;                       //Return Book Price : Float
}
int book::getquantity(){
    return quantity;                    //Return Book Quantity : Integer
}
string book::getcategory(){
    return category;                    //Return Book Category : String
}
string book::getDisplay(){
    return getname() + "\t" + to_string(getprice()) + "\t" + to_string(getquantity()) + "\t" + getcategory();   //Return all data : String
}
void book::setname(string name){
    this->name = name;                  //Set Book Name : String
}
void book::setprice(float price){
    this->price = price;          //Set Book Price : Float
}
void book::setquantity(int quantity){
    this->quantity = quantity;          //Set Book Quantity : Integer
}
void book::setcategory(string category){
    this->category = category;          //Set Book Category : String
}
void book::addBook(){

    vector<string> tempinvname;
    string bookname, addstockanswer;
    int addstock = 1;                               //Minimum Stock : 1
    cout << "Adding book to the inventory..." << endl;
    cout << "Book Name: ";
    cin.ignore();                                   //Ignoring first auto-CIN
    getline(cin, bookname);

    deque <book> :: iterator ptr;                   //Store all Book Name into a vector : String
    for (ptr = (*inventorydata).begin(); ptr != (*inventorydata).end(); ++ptr){
        tempinvname.push_back(ptr->getname());
    }

    vector<string>::iterator it = find(tempinvname.begin(), tempinvname.end(), bookname);   //Search for Book Name
    if (it != tempinvname.end()){                   //Detect If Book Record Name Exist : Add More Stock

        int index = it - tempinvname.begin();       //Book Indexing
        int currentquantity;

        book tempbook = (*inventorydata)[index];    //Clone Book Index
        currentquantity = tempbook.getquantity();

        cout << "Same Book Name has been detected, Do you want to add more stock? [Yes | No]" << endl;
        getline(cin, addstockanswer);

        while(addstockanswer!="Yes" && addstockanswer!="No"){       //Validate Input Only : Yes|No
            cout << "Invalid Input" << endl;
            cout << "Same Book Name has been detected, do you want to add more stock? [Yes | No]" << endl;
            getline(cin, addstockanswer);
        }

        if(addstockanswer=="Yes"){                                  //Input : Yes

            cout << "The current stock left for \"" << bookname << "\" is " << currentquantity << endl; //Display Current Name & Quantity

            cout << "How many stock do you wan to add?" << endl;
            cout << "Number of books [>=1]: ";
            cin >> addstock;

            while(addstock<1){                                      //Validate Input : Negative Value
                cout << "Invalid Input [>=1]" << endl;
                cout << "The current stock left for \"" << bookname << "\" is " << currentquantity << endl;
                cout << "How many stock do you wan to add?" << endl;
                cout << "Number of books [>=1]: ";
                cin >> addstock;
            }

            int presentquantity = currentquantity + addstock;       //Adding Stock
            (*inventorydata)[index].setquantity(presentquantity);
            cout << "Book Stock has been added successfully!" << endl;

            csvReadWrite::writeInventory();                         //Write to Inventory Excel
        }else{
            return;                                                 //Input : No
        }

    }else{

        float newprice;                                             //Book Record Name Not Exist : Create New Record
        int newquantity;
        string newcategory;
        cout << "Book Name is new to the system.\nDo you want to make a new record with this name? [Yes | No]" << endl;
        getline(cin, addstockanswer);

        while(addstockanswer!="Yes" && addstockanswer!="No"){       //Validate Input Only : Yes|No
            cout << "Invalid Input" << endl;
            cout << "Book Name is new to the system.\nDo you want to make a new record with this name? [Yes | No]" << endl;
            getline(cin, addstockanswer);
        }

        if(addstockanswer=="Yes"){                                  //Input : Yes
            cout << "What will be the price of the book? Price [>0]: ";
            cin >> newprice;

            while(newprice<=0){                                     //Validate Price : Negative Value
                cout << "Invalid Input" << endl;
                cout << "What will be the price of the book? Price [>0]: ";
                cin >> newprice;
            }

            cout << "What will be the quantity of the book? Quantity [>0]: ";
            cin >> newquantity;

            while(newquantity<=0){                                  //Validate Quantity : Negative Value
                cout << "Invalid Input" << endl;
                cout << "What will be the quantity of the book? Quantity [>0]: ";
                cin >> newquantity;
            }

            cout << "What will be the category of the book? Category [Characters ONLY]: ";
            cin.ignore();
            getline(cin, newcategory);

            int tempcounter = 0;                                    //Validate Category : Numerical Checker
            bool numchecker = false;
            while(newcategory[tempcounter]!='\0'){
                if(isdigit(newcategory[tempcounter])){
                    numchecker = true;
                }
                tempcounter++;
            }
            while(numchecker){
                cout << "Invalid Input" << endl;
                cout << "What will be the category of the book? Category [Characters ONLY]: ";
                getline(cin, newcategory);
                tempcounter = 0;
                numchecker = false;
                while(newcategory[tempcounter]!='\0'){
                    if(isdigit(newcategory[tempcounter])){
                        numchecker = true;
                    }
                    tempcounter++;
                }
            }

            book *newbook = new book(bookname, newprice, newquantity, newcategory);     //Adding New Record
            inventorydata->push_back(*newbook);
            cout << "New book has been entered successfully!" << endl;

            book::displayBook();                                //Display Book

            csvReadWrite::writeInventory();
        }else{
            return;                                             //Input : No
        }
    }
}
void book::updateBook(){

    vector<string> tempinvname;
    string bookname, updatestatus;
    float bookprice;
    int bookquantity;
    string newbookname, newbookprice, newbookcategory, newbookquantity;
    cout << "Update book in the inventory..." << endl;

    book::displayBook();                                        //Display Book

    cout << "Type the Book Name You would like to Update (Word-by-Word): ";
    cin.ignore();
    getline(cin, bookname);

    deque <book> :: iterator ptr;                               //Store all Book Name into a vector : String
    for (ptr = (*inventorydata).begin(); ptr != (*inventorydata).end(); ++ptr){
        tempinvname.push_back(ptr->getname());
    }

    vector<string>::iterator it = find(tempinvname.begin(), tempinvname.end(), bookname);   //Search for Book Name
    if (it != tempinvname.end()){                           //Detect If Book Record Name Exist : Add More Stock

        int index = it - tempinvname.begin();               //Book Indexing
        book tempbook = (*inventorydata)[index];            //Clone Book Index

        cout << "Your desired Book has been detected, Do you want to update the record? [Yes | No]" << endl;
        getline(cin, updatestatus);

        while(updatestatus!="Yes" && updatestatus!="No"){   //Validate Input Only : Yes|No
            cout << "Invalid Input" << endl;
            cout << "Your desired Book has been detected, Do you want to update the record? [Yes | No]" << endl;
            getline(cin, updatestatus);
        }

        if(updatestatus=="Yes"){                            //Input : Yes
            cout << "Displaying select book record..." << endl;             //Display Book Record Details
            cout << "Book Name: " << tempbook.getname() << endl;
            cout << "Book Price: " << tempbook.getprice() << endl;
            cout << "Book Quantity: " << tempbook.getquantity() << endl;
            cout << "Book Category: " << tempbook.getcategory() << endl;

            cout << "Change Book Name to [REMAIN | TYPE_YOUR_BOOK_NAME] (Characters ONLY): ";
            getline(cin, newbookname);

            int tempcounter = 0;
            bool numchecker = false;
            while(newbookname[tempcounter]!='\0'){              //Validate Input : Numerical Checker
                if(isdigit(newbookname[tempcounter])){
                    numchecker = true;
                }
                tempcounter++;
            }
            while(numchecker){
                cout << "Invalid Input" << endl;
                cout << "Change Book Name to [REMAIN | TYPE_YOUR_BOOK_NAME] (Characters ONLY): ";
                getline(cin, newbookname);
                tempcounter = 0;
                numchecker = false;
                while(newbookname[tempcounter]!='\0'){
                    if(isdigit(newbookname[tempcounter])){
                        numchecker = true;
                    }
                    tempcounter++;
                }
            }

            if(newbookname=="REMAIN"){              //For Remain
                newbookname = bookname;
            }

            cout << "Change Book Price to [REMAIN | TYPE_YOUR_BOOK_PRICE]: ";
            getline(cin, newbookprice);

            if(newbookprice=="REMAIN"){             //For Remain
                bookprice = tempbook.getprice();
            }else{
                bookprice = stof(newbookprice);

                while(bookprice<=0){                //Validate Price : Negative Value
                cout << "Invalid Input" << endl;
                cout << "Change Book Price to (>0): ";
                cin >> bookprice;
                }
            }

            cout << "Change Book Quantity to [REMAIN | TYPE_YOUR_BOOK_QUANTITY]: ";
            getline(cin, newbookquantity);

            if(newbookquantity=="REMAIN"){          //For Remain
                bookquantity = tempbook.getquantity();
            }else{
                bookquantity = stoi(newbookquantity);

                while(bookquantity<=0){             //Validate Quantity : Negative Value
                cout << "Invalid Input" << endl;
                cout << "Change Book Quantity to (>0): ";
                cin >> bookquantity;
                }
            }

            cout << "Change Book Category to [REMAIN | TYPE_YOUR_BOOK_CATEGORY] (Characters ONLY): ";
            getline(cin, newbookcategory);

            int tempcounter2 = 0;                   //Validate Category : Numerical Checker
            bool numchecker2 = false;
            while(newbookcategory[tempcounter2]!='\0'){
                if(isdigit(newbookcategory[tempcounter2])){
                    numchecker2 = true;
                }
                tempcounter2++;
            }
            while(numchecker2){
                cout << "Invalid Input" << endl;
                cout << "Change Book Category to [REMAIN | TYPE_YOUR_BOOK_CATEGORY] (Characters ONLY): ";
                getline(cin, newbookcategory);
                tempcounter2 = 0;
                numchecker2 = false;
                while(newbookcategory[tempcounter2]!='\0'){
                    if(isdigit(newbookcategory[tempcounter2])){
                        numchecker2 = true;
                    }
                    tempcounter2++;
                }
            }

            if(newbookcategory=="REMAIN"){              //For Remain
                newbookcategory= tempbook.getcategory();
            }

            (*inventorydata)[index].setname(newbookname);       //Updating Inventory Record
            (*inventorydata)[index].setprice(bookprice);
            (*inventorydata)[index].setquantity(bookquantity);
            (*inventorydata)[index].setcategory(newbookcategory);
            cout << "Book record has been updated successfully!" << endl;

            csvReadWrite::writeInventory();                     //Write to Inventory Excel File

            cout << "Displaying updated book record..." << endl;        //Display Book Detail
            cout << "Book Name: " << (*inventorydata)[index].getname() << endl;
            cout << "Book Price: " << to_string((*inventorydata)[index].getprice()) << endl;
            cout << "Book Quantity: " << to_string((*inventorydata)[index].getquantity()) << endl;
            cout << "Book Category: " << (*inventorydata)[index].getcategory() << endl;
            //
        }else{
            return;                                             //Input : No
        }
    }else{
        cout << "Book Name entered is non-existence" << endl;   //Input : No Book Detected
        return;
    }
}
void book::deleteBook(){
    vector<string> tempinvname;
    string bookname;
    cout << "Delete book in the inventory..." << endl;
    book::displayBook();                    //Display Book
    cout << "Type the Book Name You would like to Delete (Word-by-Word): ";
    cin.ignore();
    getline(cin, bookname);

    deque <book> :: iterator ptr;                                           //Store all Book Name into a vector : String
    for (ptr = (*inventorydata).begin(); ptr != (*inventorydata).end(); ++ptr){
        tempinvname.push_back(ptr->getname());
    }

    vector<string>::iterator it = find(tempinvname.begin(), tempinvname.end(), bookname);   //Search for Book Name
    if (it != tempinvname.end()){

        queue<book> auxdata;

        while(!inventorydata->empty()){                         //Pop Only : The Book Record
            if(inventorydata->front().getname()==bookname){
                inventorydata->pop_front();
            }else{
                auxdata.push(inventorydata->front());
                inventorydata->pop_front();
            }
        }

        while(!auxdata.empty()){                                //Process : Pop to queue, pop back to deque
            inventorydata->push_back(auxdata.front());
            auxdata.pop();
        }

        cout << "Book Record has been deleted successfully!" << endl;

        csvReadWrite::writeInventory();                         //Write to Inventory Excel File

    }else{
        cout << "Book Name entered is non-existence" << endl;   //Book Not Detected
        return;
    }
}
void book::displayBook(){
    cout << "Displaying book in the inventory..." << endl;
    cout << "Book Name\t\tPrice\tQuantity\tCategory" << endl;

    deque <book> :: iterator ptr;                               //Iterate-Display Book
    for (ptr = inventorydata->begin(); ptr != inventorydata->end(); ++ptr){
        cout << ptr->getDisplay() << endl;
    }
}
void book::searchBook(){
    string searchinput;
    cout << "Search book in the inventory..." << endl;
    cout << "Search Engine (Enter your search): " << endl;
    cin.ignore();
    getline(cin, searchinput);

    queue<book> searchresults;                  //Queue to store Search Results
    deque<book> tempinventory = *inventorydata;

    while(!tempinventory.empty()){             //Filter Records, Place to queue
        string bookname = tempinventory.front().getname();
        string bookprice = to_string(tempinventory.front().getprice());
        string bookquantity = to_string(tempinventory.front().getquantity());
        string bookcategory = tempinventory.front().getcategory();

        size_t foundname = bookname.find(searchinput);
        size_t foundprice = bookprice.find(searchinput);
        size_t foundquantity = bookquantity.find(searchinput);
        size_t foundcategory = bookcategory.find(searchinput);

        if(foundname!=string::npos || foundprice!=string::npos || foundquantity!=string::npos || foundcategory!=string::npos){
            searchresults.push(tempinventory.front());
        }
        tempinventory.pop_front();
    }

    if(searchresults.empty()){          //No Search Found
        cout << "We're sorry, we couldn't find any matches" << endl;
    }else{
        while (!searchresults.empty()){ //Display Search Results
        cout << "Search Found! This is What We Have" << endl;
        cout << "Book Name\t\tPrice\tQuantity\tCategory" << endl;
		cout << searchresults.front().getDisplay() << endl;
		searchresults.pop();
        }
    }
}
void book::filterBook(){
    vector<string> tempinvcategory;
    deque<string> trackingcategory;
    string filterinput;
    int counter = 1, filterfinal;
    cout << "Filter book in the inventory..." << endl;
    cout << "FILTER OPTION:" << endl;
    cout << "To select a filter (Number ONLY), enter " << endl;

    deque <book> :: iterator ptr;                       //Store all Book Category into a vector : String
    for (ptr = (*inventorydata).begin(); ptr != (*inventorydata).end(); ++ptr){
        tempinvcategory.push_back(ptr->getcategory());
    }

    set<string> s(tempinvcategory.begin(), tempinvcategory.end());  //Filter Category : Repetition
    tempinvcategory.assign(s.begin(), s.end());

    while(!tempinvcategory.empty()){        //Display Selection List
        cout << to_string(counter) + " to filter Book Category by " + tempinvcategory.back() << endl;
        counter++;
        trackingcategory.push_back(tempinvcategory.back());
        tempinvcategory.pop_back();
    }
    cout << to_string(counter) + " to exit" << endl;

    cin >> filterinput;                 //Validate Input : Alphabet Checker
    int tempcounter = 0;
    bool alphachecker = false;
    while(filterinput[tempcounter]!='\0'){
        if(isalpha(filterinput[tempcounter])){
            alphachecker = true;
        }
        tempcounter++;
    }
    while(alphachecker){
        cout << "Invalid Input" << endl;
        cin >> filterinput;
        tempcounter = 0;
        alphachecker = false;
        while(filterinput[tempcounter]!='\0'){
            if(isalpha(filterinput[tempcounter])){
                alphachecker = true;
            }
            tempcounter++;
        }
    }

    filterfinal = stoi(filterinput);
    while(filterfinal!=counter){                    //Repeat : Not Filter Option
        if(filterfinal>0 && filterfinal<=counter){  //If Filter Option
            for(int i=1; i<counter; i++){
                if(filterfinal==i){                 //Detect Option
                    queue<book> filterresults;
                    deque<book> tempinventory = *inventorydata;

                    while(!tempinventory.empty()){  //Filter Category
                        string bookcategory = tempinventory.front().getcategory();
                        size_t foundcategory = bookcategory.find(trackingcategory[filterfinal-1]);
                        if(foundcategory!=string::npos){
                            filterresults.push(tempinventory.front());
                        }
                        tempinventory.pop_front();
                    }

                    cout << "Book Inventory has been filtered successfully!" << endl;
                    cout << "Book Name\t\tPrice\tQuantity\tCategory" << endl;
                    while (!filterresults.empty()){                 //Display Filter Results
                        cout << filterresults.front().getDisplay() << endl;
                        filterresults.pop();
                    }
                    return;
                }
            }
        }
        cout << "Invalid selection." << endl;
        cout << "Please select your filter accordingly" << endl;
        cin >> filterfinal;
    }
}
void book::sortBook(){
    string sortselection;
    int finalselection;
    cout << "Sort book in the inventory..." << endl;
    cout << "SORTING OPTION:" << endl;
    cout << "To select a sort (Number ONLY), enter " << endl;
    cout << "1 for Alphabetical Order (A-Z)" << endl;
    cout << "2 for Price (Low-High)" << endl;
    cout << "3 for Quantity (Low-High)" << endl;
    cout << "4 to exit" << endl;
    cin.ignore();
    getline(cin, sortselection);

    int tempcounter = 0;                            //Validate Input : Alphabet Checker
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
    while(finalselection!=4){           //Repeat : Not Sort Option
        switch (finalselection){
        case 1:
            sort(inventorydata->begin(),inventorydata->end(),sortalgo1);    //Sort Data : Alphabetical Order (Selection Sort)
            cout << "Book Records have been sorted based on Alphabetical Order successfully!" << endl;
            csvReadWrite::writeInventory();         //Write to Inventory Excel File
            book::displayBook();
            return;
        case 2:
            sort(inventorydata->begin(),inventorydata->end(),sortalgo2);    //Sort Data : Price Order (Selection Sort)
            cout << "Book Records have been sorted based on Prices successfully!" << endl;
            csvReadWrite::writeInventory();         //Write to Inventory Excel File
            book::displayBook();
            return;
        case 3:
            sort(inventorydata->begin(),inventorydata->end(),sortalgo3);    //Sort Data : Quantity Order (Selection Sort)
            cout << "Book Records have been sorted based on Quantity successfully!" << endl;
            csvReadWrite::writeInventory();         //Write to Inventory Excel File
            book::displayBook();
            return;
        default: cout << "Invalid selection." << endl;
        }
        cout << "Sort book in the inventory..." << endl;
        cout << "SORTING OPTION:" << endl;
        cout << "To select a sort (Number ONLY), enter " << endl;
        cout << "1 for Alphabetical Order (A-Z)" << endl;
        cout << "2 for Price (Low-High)" << endl;
        cout << "3 for Quantity (Low-High)" << endl;
        cout << "4 to exit" << endl;
        cin >> finalselection;
    }
}
bool book::sortalgo1(book a,book b){    //Selection Sort Algorithm 1 (Using Boolean), Logically
    string firstbookname = a.getname();
    string secondbookname = b.getname();
    return firstbookname<secondbookname;
}
bool book::sortalgo2(book a,book b){    //Selection Sort Algorithm 2 (Using Boolean), Logically
    float firstbookprice = a.getprice();
    float secondbookprice = b.getprice();
    return firstbookprice<secondbookprice;
}
bool book::sortalgo3(book a,book b){    //Selection Sort Algorithm 3 (Using Boolean), Logically
    int firstbookquantity = a.getquantity();
    int secondbookquantity = b.getquantity();
    return firstbookquantity<secondbookquantity;
}
book::~book(){}         //Deconstructor


