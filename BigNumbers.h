#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// defines List class template which can be used with different data types
template <class T>
class List {
private:
    struct Node
    {
        T data;
        Node *next;
    };
    Node *front, *current;

public:
    List();
    ~List();
    void AddToFront(const T newthing);
    bool FirstItem(T &item);
    bool NextItem(T &item);
    bool Reverse();
    bool MakeCopy(List &L);
};

// defines the class which stores the BigNumbers
class BigNumber
{
private:
    List<char> Digits;
    // DEBUG: might need more

public:
    BigNumber();
    ~BigNumber();
    void ReadFromString(const string decimalString);
    int AddBigNumbers(BigNumber &B1, BigNumber &B2);
    void Reverse();
    void PrintBigNumber();
};


int errEmptyBigNumber();                                    // returns error code if BigNumber is empty
int errArguments();                                         // returns error code if not enough arguments
int errFile(const char *file);                              // returns error code if file cannot be opened
int readNumbers(const char *file, BigNumber &B1, BigNumber &B2);        // reads BigNumbers from file
void reverseBigNumbers(BigNumber &B1, BigNumber &B2);       // reverses order of BigNumber Digits so they are ready for printing
void printBigNumbers(BigNumber &B1, BigNumber &B2, BigNumber &Sum);     // prints out each BigNumber
int runProgram(const char *file);                           // runs program

