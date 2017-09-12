//////////////////////////////////////////////
//	Cai Gwatkin								//
//////////////////////////////////////////////
//	This application outputs the sum of		//
//	two big numbers read from a text file	//
//////////////////////////////////////////////

#include "BigNumbers.h"

// List constructor
template <class T>
List<T>::List()
{
	front = NULL;
	current = NULL;
}

// List destructor
template <class T>
List<T>::~List()
{
	if (front == NULL) return;
	while (front != NULL)
	{
		current = front;
		front = front->next;
		delete current;
	}
}

// adds newthing to front of List
template <class T>
void List<T>::AddToFront(const T newthing)
{
	Node *temp;
	temp = new Node;
	temp->data = newthing;
	temp->next = front;
	front = temp;
}

// if List has items: sets current to front item, copies data to &item and returns true
template <class T>
bool List<T>::FirstItem(T &item)
{
	if (front == NULL) return false;
	item = front->data;
	current = front;
	return true;
}

// if next item exists: sets current to next item, copies data to &item and returns true
template <class T>
bool List<T>::NextItem(T &item)
{
	current = current->next;
	if (current == NULL) return false;
	item = current->data;
	return true;
}

// reverses order of List
template <class T>
bool List<T>::Reverse()
{
	if (front == NULL) return false;
	Node *temp1, *temp2;
	current = front->next;
	temp2 = front;
	while (current != NULL)
	{
		temp1 = current->next;
		current->next = front;
		front = current;
		current = temp1;
	}
	temp2->next = NULL;
	return true;
}

// copies contents of List to L
template <class T>
bool List<T>::MakeCopy(List &L)
{
	if (front == NULL) return false;
	Node *temp;
	temp = front;
	while (temp != NULL)
	{
		L.AddToFront(temp->data);
		temp = temp->next;
	}
	L.Reverse();
	return true;
}

// BigNumber constructor
BigNumber::BigNumber() { }

// BigNumber destructor
BigNumber::~BigNumber() { }

// reads string of decimal values into List
void BigNumber::ReadFromString(const string decimalString)
{
	int numberOfDigits = decimalString.length();
	for (int i = 0; i < numberOfDigits; i++)
	{
		if ((decimalString[i] != '\n') && (decimalString[i] != '\r')) Digits.AddToFront(decimalString[i]);
	}
}

// returns error code if BigNumber is empty
int errEmptyBigNumber()
{
	cout << "Error: one or more of the BigNumbers is empty" << endl;
	return 3;
}

// adds two BigNumbers together and saves as a third BigNumber
int BigNumber::AddBigNumbers(BigNumber &B1, BigNumber &B2)
{
	char digitB1, digitB2;
	int sum = 0, carry = 0;
	bool okB1 = B1.Digits.FirstItem(digitB1), okB2 = B2.Digits.FirstItem(digitB2);
	
	// returns error if either BigNumber is empty
	if (!okB1 || !okB2) return errEmptyBigNumber();
	
	// while both BigNumbers still have digits
	while (okB1 && okB2)
	{
		sum = (digitB1 - 48) + (digitB2 - 48) + carry;

		// check if carry needed
		if (sum > 9)
		{
			sum -= 10;
			carry = 1;
		}
		else carry = 0;

		// adds sum to Sum
		Digits.AddToFront(sum + 48);

		// checks that each BigNumber has another digit and gets that value
		okB1 = B1.Digits.NextItem(digitB1);
		okB2 = B2.Digits.NextItem(digitB2);
	}

	// updates Sum if B1 still has digits
	while (okB1)
	{
		sum = (digitB1 - 48) + carry;

		// check if carry needed
		if (sum > 9)
		{
			sum -= 10;
			carry = 1;
		}
		else carry = 0;

		// adds sum to Sum
		Digits.AddToFront(sum + 48);

		// checks that B1 has another digit and gets that value
		okB1 = B1.Digits.NextItem(digitB1);
	}

	// updates Sum if B2 still has digits
	while (okB2)
	{
		sum = (digitB2 - 48) + carry;

		// check if carry needed
		if (sum > 9)
		{
			sum -= 10;
			carry = 1;
		}
		else carry = 0;

		// adds sum to Sum
		Digits.AddToFront(sum + 48);

		// checks that B2 has another digit and gets that value
		okB2 = B2.Digits.NextItem(digitB2);
	}

	// adds carry to Sum if necessary
	if (carry == 1) Digits.AddToFront('1');

	return 0;
}

// reverses order of BigNumber Digits
void BigNumber::Reverse()
{
	Digits.Reverse();
}

// prints BigNumber to console
void BigNumber::PrintBigNumber()
{
	// itterate through Digits, printing each digit
	char digit;
	bool ok = Digits.FirstItem(digit);
	while (ok)
	{
		cout << digit;
		ok = Digits.NextItem(digit);
	}
	cout << endl;
}

int main(const int argc, const char **argv)
{
    // returns error code if not enough arguments
    if (argc != 2) return errArguments();

    // runs program
    return runProgram(argv[1]);
}

// returns error code if not enough arguments
int errArguments()
{
	cout << "Error: need 2 arguments" << endl;
	return 1;
}

// returns error code if file cannot be opened
int errFile(const char *file)
{
	cout << "Error: could not read file \"" << file << "\"" << endl;
	return 2;
}

// reads BigNumbers from file
int readNumbers(const char *file, BigNumber &B1, BigNumber &B2)
{
	// returns error code if file cannot be opened
	ifstream inFile(file);
	if (!inFile) return errFile(file);

	// read in BigNumbers from file
	string numberString;
	int lineNumber = 0;
	while (!inFile.eof())
	{
		// read line one
		getline(inFile, numberString);
		if (lineNumber == 0)
		{
			B1.ReadFromString(numberString);
			lineNumber++;
		}
		// read line two
		else if (lineNumber == 1)
		{
			B2.ReadFromString(numberString);
			lineNumber++;
		}
	}

	return 0;
}

// reverses order of BigNumber Digits so they are ready for printing
void reverseBigNumbers(BigNumber &B1, BigNumber &B2)
{
	B1.Reverse();
	B2.Reverse();
}

// prints out each BigNumber
void printBigNumbers(BigNumber &B1, BigNumber &B2, BigNumber &Sum)
{
	B1.PrintBigNumber();
	cout << "+" << endl;
	B2.PrintBigNumber();
	cout << "=" << endl;
	Sum.PrintBigNumber();
}

// runs program
int runProgram(const char *file)
{
	// reads BigNumbers from file
	BigNumber B1, B2;
	int err = readNumbers(file, B1, B2);
	if (err != 0) return err;

	// calculates Sum of B1 and B2
	BigNumber Sum;
	err = Sum.AddBigNumbers(B1, B2);
	if (err != 0) return err;

	// reverses order of BigNumber Digits so they are ready for printing
	reverseBigNumbers(B1, B2);

	// prints out each BigNumber
	printBigNumbers(B1, B2, Sum);

	return err;
}

