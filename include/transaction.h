#ifndef TRANSACTION_H
#define TRANSACTION_H

using namespace std;

class transaction
{
    public:
        transaction(int, string, float);
        int gettransactionid();
        string gettransactiontime();
        float gettransactionprice();
        deque<book>* gettransactiondetail();
        string getDisplay();
        void settransactionid(int);
        void settransactiontime(string);
        void settransactionprice(float);
        void pushtransactiondetail(book);
        static void addTransaction();
        static void displayTransaction();
        static void detailTransaction();
        static void sortTransaction(); //Sort by ID, Time & Price
        static void generateID();
        static bool sortalgo1(transaction,transaction);
        static bool sortalgo2(transaction,transaction);
        static bool sortalgo3(transaction,transaction);
        virtual ~transaction();
    private:
        static int counterid;
        int transactionid;
        string transactiontime;
        float transactionprice; //Total Price per Transaction
        deque<book> *transactiondetail = new deque<book>();
};

#endif // TRANSACTION_H

