#ifndef BOOK_H
#define BOOK_H

using namespace std;

class book
{
    public:
        book(string,float,int,string);
        string getname();
        float getprice();
        int getquantity();
        string getcategory();
        string getDisplay();
        void setname(string);
        void setprice(float);
        void setquantity(int);
        void setcategory(string);
        static void addBook();
        static void updateBook();
        static void deleteBook();
        static void displayBook();
        static void searchBook();
        static void filterBook();
        static void sortBook();
        static bool sortalgo1(book,book);
        static bool sortalgo2(book,book);
        static bool sortalgo3(book,book);
        virtual ~book();
    private:
        string name, category;
        float price;
        int quantity;
};

#endif // BOOK_H
