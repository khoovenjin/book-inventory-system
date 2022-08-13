#include <bits/stdc++.h>
#include "book.h"
#include "transaction.h"
#include "csvReadWrite.h"

using namespace std;

extern deque<book> *inventorydata;              //To Link with Global Static Deque in Main.cpp
extern deque<transaction> *transactiondata;

csvReadWrite::csvReadWrite(){}
void csvReadWrite::readInventory(){             //Read from Inventory Excel File
    //string,float,int,string
    ifstream myFile;
    myFile.open("inventorydata.csv");

    vector<string> linestorage;
    int counter = 0;
    while(myFile.good()){
        string line;
        if(counter==3 || (counter-3)%4==0){
            getline(myFile, line, '/');
        }else{
            getline(myFile, line, ',');
        }
        linestorage.push_back(line);
        counter++;
    }

    int tempcounter = 0, firstpointer =0, lastpointer = firstpointer+3;
    if((linestorage.size()-1)%4==0){
        while(tempcounter<((linestorage.size()-1)/4)){
            float newbookprice = stof(linestorage[firstpointer+1]);
            int newbookquantity = stoi(linestorage[firstpointer+2]);
            book *newbook = new book(linestorage[firstpointer],newbookprice,newbookquantity,linestorage[lastpointer]);
            inventorydata->push_back(*newbook);
            firstpointer = lastpointer+1;
            lastpointer = firstpointer+3;
            tempcounter++;
        }
    }else{
        cout << "Oops its an error" << endl;
        myFile.close();
        return;
    }
    myFile.close();
    for(int i =0; i<tempcounter; i++){
        inventorydata->pop_back();
    }
}
void csvReadWrite::readTransaction(){           //Read from Transaction Excel File
    //int,string,float,deque<book>
    ifstream myFile;
    myFile.open("transactiondata.csv");

    vector<string> linestorage;
    int counter = 0;
    while(myFile.good()){
        string line;
        if(counter==2 || (counter-2)%3==0){
            getline(myFile, line, '/');
        }else{
            getline(myFile, line, ',');
        }
        linestorage.push_back(line);
        counter++;
    }

    int tempcounter = 0, firstpointer =0, lastpointer = firstpointer+2;
    if((linestorage.size()-1)%3==0){
        while(tempcounter<((linestorage.size()-1)/3)){
            int newtransactionid = stoi(linestorage[firstpointer]);
            float newtransactionprice = stof(linestorage[lastpointer]);
            deque<book> tempbook = csvReadWrite::readTransactionDetail(to_string(newtransactionid));        //Using Read to retrieve transaction detail
            transaction *newtransaction = new transaction(newtransactionid,linestorage[firstpointer+1],newtransactionprice);

            while(!tempbook.empty()){
                newtransaction->pushtransactiondetail(tempbook.front());
                tempbook.pop_front();
            }

            transactiondata->push_back(*newtransaction);
            firstpointer = lastpointer+1;
            lastpointer = firstpointer+2;
            tempcounter++;
        }
    }else{
        cout << "Oops its an error" << endl;
        myFile.close();
        return;
    }
    myFile.close();
    for(int i =0; i<tempcounter; i++){
        transactiondata->pop_back();
    }
}
deque<book> csvReadWrite::readTransactionDetail(string transactionid){      //Read from Transaction Detail (Number) Excel File
    ifstream myFile;
    string filename = "transaction" + transactionid + ".csv";
    myFile.open(filename);

    vector<string> linestorage;
    deque<book> tempdeque;
    int counter = 0;
    while(myFile.good()){
        string line;
        if(counter==3 || (counter-3)%4==0){
            getline(myFile, line, '/');
        }else{
            getline(myFile, line, ',');
        }
        linestorage.push_back(line);
        counter++;
    }

    int tempcounter = 0, firstpointer =0, lastpointer = firstpointer+3;
    if((linestorage.size()-1)%4==0){
        while(tempcounter<((linestorage.size()-1)/4)){
            float newbookprice = stof(linestorage[firstpointer+1]);
            int newbookquantity = stoi(linestorage[firstpointer+2]);
            book *newbook = new book(linestorage[firstpointer],newbookprice,newbookquantity,linestorage[lastpointer]);
            tempdeque.push_back(*newbook);
            firstpointer = lastpointer+1;
            lastpointer = firstpointer+3;
            tempcounter++;
        }
    }else{
        cout << "Oops its an error" << endl;
        myFile.close();
        return tempdeque;
    }
    myFile.close();
    return tempdeque;
}
void csvReadWrite::writeInventory(){            //Write to Inventory Excel File
    //string,float,int,string
    ofstream myFile;
    myFile.open("inventorydata.csv");

    vector<string> linestorage;
    string appendingline = "";
    int counter = 0; //added
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
void csvReadWrite::writeTransaction(){              //Write to Transaction Excel File
    //int,string,float,deque<book>
    ofstream myFile;
    myFile.open("transactiondata.csv");

    vector<string> linestorage;
    string appendingline = "";
    int counter = 0; //added
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
void csvReadWrite::writeTransactionDetail(string transactionid,deque<book> temptransactiondetail){      //Write to Transaction Detail (Number) Excel File
    //string,float,int,string
    ofstream myFile;
    string filename = "transaction" + transactionid + ".csv";
    myFile.open(filename);

    vector<string> linestorage;
    string appendingline = "";
    int counter = 0; //added

    while(!temptransactiondetail.empty()){
        stringstream templine(temptransactiondetail.front().getDisplay());
        temptransactiondetail.pop_front();

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
void csvReadWrite::deletefile(char filename[]){         //To delete Excel File
    bool status = remove(filename);
}
csvReadWrite::~csvReadWrite(){}
