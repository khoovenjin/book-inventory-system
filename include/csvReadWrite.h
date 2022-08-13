#ifndef CSVREADWRITE_H
#define CSVREADWRITE_H

using namespace std;

class csvReadWrite
{
    public:
        csvReadWrite();
        static void readInventory();
        static void readTransaction();
        static deque<book> readTransactionDetail(string);
        static void writeInventory();
        static void writeTransaction();
        static void writeTransactionDetail(string,deque<book>);
        static void deletefile(char[]);
        virtual ~csvReadWrite();
};

#endif // CSVREADWRITE_H
