// Title
//
// A program to demonstrate the management of a small database of operational
// amplifiers.
//
// General description
//
// The database contains up to DATABASE_MAX operational amplifier elements. Each
// element contains the operation amplifier name, the number of pins in the package
// and stores the slew rate of the device.
//
// New elements can be added into the database by the user. The database can be saved
// to disk or loaded from disk. The database elements can be sorted either by name or
// by slew rate. There is also the facility to display the elements.
//
// Only a single database is required and the file name is fixed in the code (as 
// DATABASE_FILENAME). This means that each time the database is saved to disk,
// any previous data in the file is overwritten. Also, when a database is loaded
// from a file it should overwrite any data already in memory.

#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm> //std:: sort
using namespace std;

// Class containing OpAmp parameters
// Provides functions that access the private members and overloaded the stream operators
class OpAmps
{
private:
	char Name[20];				// the name of the op - amp (e.g. "741")
	unsigned int PinCount;		// the number of pins in the package
	double SlewRate;			// the slew rate in volts per microsecond

public:
	OpAmps();					// constructor 
	~OpAmps(); 					// destructor

	void SetOpAmpValues();		// setting OpAmp parameters function
	void DisplayOpAmpValues();  // displaying op-amps

	string GetNameOpAmp();		// provides access to private Name
	int GetPinCountOpAmp();		// provides access to private PinCount
	double GetSlewRateOpAmp();	// provides access to private SlewRate

	friend ostream &operator << (ostream &, OpAmps &);	 // overloaded output operator function
	friend ifstream &operator >> (ifstream &, OpAmps &); // overloaded input operator function
};

//Constructor and destructor functions
OpAmps::OpAmps() // constructor definition of class-OpAmps with initialised values
{
	Name[0] = '\0';	// the name of the op - amp (e.g. "741")
	PinCount = 0;	// the number of pins in the package
	SlewRate = 0;	// the slew rate in volts per microsecond
}

OpAmps::~OpAmps() // destructor function definition
{
	cout << ".Goodbye." << endl;
}

// Structure for ArrayOfOpAmps-objects 
void OpAmps::SetOpAmpValues() //Input user data to alter database length by adding an ArrayOfOpAmps-object
{
	cout << "Add new data" << endl;
	cout << "------------" << endl;
	cout << "Enter op-amp name: ";
	cin >> Name;
	cout << "Enter number of pins: ";
	cin >> PinCount;
	cout << "Enter slew rate: ";
	cin >> SlewRate;
	cout << endl;
}

void OpAmps::DisplayOpAmpValues() // Display current ArrayOfOpAmps-objects in the database and their parameters
{
	// display a title
	cout << endl;
	cout << "Name	Number of pins	Slew rate" << endl;

	// display the elements
	cout << Name << "		";
	cout << PinCount << "	  ";
	cout << SlewRate << " ";
	cout << endl;
}

// Fucntions for private member access
string OpAmps::GetNameOpAmp() // function to access private members of class-OpAmps
{
	return Name;
}

int OpAmps::GetPinCountOpAmp() // function to access private members of class-OpAmps
{
	return PinCount;
}

double OpAmps::GetSlewRateOpAmp() // function to access private members of class-OpAmps
{
	return SlewRate;
}

// Stream operator overloading
// Currently these two functions are defined as friend functions which could be undesirable
// due to breaking the natural encapsulation process , however since it is implemented for overloading, 
// it should not provide anything threatening to the program.
ostream &operator<<(ostream& outstream, OpAmps& ArrayOfOpAmps) // output overloaded function definition
{
	outstream << ArrayOfOpAmps.Name << endl;
	outstream << ArrayOfOpAmps.PinCount << endl;
	outstream << ArrayOfOpAmps.SlewRate << endl << endl;
	return outstream;
}

ifstream &operator >>(ifstream& instream, OpAmps& ArrayOfOpAmps) // input overloaded function definition
{
	instream >> ArrayOfOpAmps.Name;
	instream >> ArrayOfOpAmps.PinCount;
	instream >> ArrayOfOpAmps.SlewRate;
	return instream;
}

// Class containing a pointer to OpAmp object,
// also contains functions needed to operate the console.
// Sort functions were not succesfully implemented, therefore are commented out
class OpAmpDatabase
{
private:
	OpAmps *ArrayOfOpAmps;	// Creating a pointer to an op amp object
	unsigned long database_length;

	//member function prototypes
public:
	OpAmpDatabase(OpAmps*);	// Constructor function initialised
	~OpAmpDatabase();		// Destructor
	void Enter();
	void Display();
	void Save();
	void Load();
	//	void Sort();
	//	int SortSlewRate(const void *First, const void* Second);
	//	int SortName(const void *First, const void* Second);
};

//Construct and destructor functions of the OpAmpDatabase-class
OpAmpDatabase::OpAmpDatabase(OpAmps* DatabasePointer)
{
	ArrayOfOpAmps = DatabasePointer;
	database_length = 0;
}

OpAmpDatabase::~OpAmpDatabase()
{
	cout << ".Goodbye." << endl;
}

// the length of the fixed array to be used for database - must be at least one
// and no greater the maximum value allowed in an unsigned long (see the file 
// limits.h)
#define DATABASE_MAX 10

// file used for the database
#define DATABASE_FILENAME "database.txt"

// Control the entering, saving, loading, sorting and displaying of elements in 
// the database
// Arguments: None
// Returns: 0 on completion
int main()
{
	OpAmps OpAmpArray[DATABASE_MAX];		// The database being created in a format of the array of op amp objects.
	OpAmpDatabase TheDatabase(OpAmpArray);  // Creates an array of the database

	char UserInput;

	// loop until the user wishes to exit
	while (1)
	{
		// show the menu of options
		cout << endl;
		cout << "Op-amp database menu" << endl;
		cout << "--------------------" << endl;
		cout << "1. Enter a new op-amp into the database" << endl;
		cout << "2. Save the database to disk" << endl;
		cout << "3. Load the database from disk" << endl;
		cout << "4. Sort the database" << endl;
		cout << "5. Display the database" << endl;
		cout << "6. Exit from the program" << endl << endl;

		// get the user's choice
		cout << "Enter your option: ";
		cin >> UserInput;
		cout << endl;

		// act on the user's input
		switch (UserInput)
		{
		case '1':
			TheDatabase.Enter();
			break;

		case '2':
			TheDatabase.Save();
			break;

		case '3':
			TheDatabase.Load();
			break;

		case '4':
			//TheDatabase.Sort();
			break;

		case '5':
			TheDatabase.Display();
			break;

		case '6':
			return 0;

		default:
			cout << "Invalid entry" << endl << endl;
			break;
		}
	}
}

// Allow the user to enter a new element into the database. Note that the data 
// is simply added to the end the database (if not full) and no sorting is
// carried out.
// Arguments:
//   (1) the element in the database to be entered
//   (2) the position of the element in the database
// Returns: void
void OpAmpDatabase::Enter()
{
	// if the database is full, inform the user
	if (database_length == DATABASE_MAX)
	{
		cout << "The database is full" << endl;
	}

	// if the database is not full, get the data from the user and alter the database
	// length
	else
	{
		ArrayOfOpAmps[database_length].SetOpAmpValues();
		database_length++;
	}
}

// Save the database to the file specified by DATABASE_FILENAME. If the file
// exists it is simply overwritten without asking the user
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
void OpAmpDatabase::Save()
{
	fstream outstream;  // file stream for output

	outstream.open(DATABASE_FILENAME, ios::out); // open the file

	outstream << database_length << endl << endl;
	for (unsigned long i = 0; i < database_length; i++)
	{
		outstream << ArrayOfOpAmps[i];
	}

	outstream.close();
}

// Load the database from the file specified by DATABASE_FILENAME. If the file
// exists it simply overwrites the data currently in memory without asking
// the user
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
void OpAmpDatabase::Load()
{
	ifstream instream;  // file stream for input

	instream.open(DATABASE_FILENAME, ios::in);	 // open the file

	instream >> database_length;
	for (unsigned long i = 0; i < database_length; i++)
	{
		instream >> ArrayOfOpAmps[i];
	}

	// close the file
	instream.close();
}

// //Sort the database either using the name of the op-amps or using the slew rate
// //values
// //Arguments:
// //  (1) the database
// //  (2) the length of the database
// //Returns: void
//void OpAmpDatabase::Sort()
//{
//	char UserInput;
//
//	// show the menu of options
//	cout << endl;
//	cout << "Sorting options" << endl;
//	cout << "---------------" << endl;
//	cout << "1. To sort by name" << endl;
//	cout << "2. To sort by slew rate" << endl;
//	cout << "3. No sorting" << endl << endl;
//
//	// get the user's choice of sorting operation required
//	cout << "Enter your option: ";
//	cin >> UserInput;
//	cout << endl;
//
//	// act on the user's input
//	switch (UserInput)
//	{
//	case '1':
//		// sort according to name (in alphabetical order)
//		std::sort(ArrayOfOpAmps, (ArrayOfOpAmps + database_length), SortName);
//		break;
//
//	case '2':
//		// sort according to slew rate (in increasing slew rate order)
//		std::sort(ArrayOfOpAmps, (ArrayOfOpAmps + database_length), SortSlewRate);
//		break;
//
//	case '3':
//		return;
//
//	default:
//		cout << "Invalid entry" << endl << endl;
//		break;
//	}
//}

//// Compare function for SORT (C++), to help sort the elements by the Name member of 
//// OpAmps.
//// Items should be sorted in alphabetical order.
//// Arguments:
////   (1) a database item
////   (2) a database item
//// Returns: result of the comparison
//int OpAmpDatabase::SortName(const void *First, const void* Second)
//{
//	return strcmp(((OpAmps *)First)->GetNameOpAmp, ((OpAmps *)Second)->GetNameOpAmp);
//}

//// Compare function for SORT (C++), to help sort the elements by the SlewRate member 
//// of OpAmps.
//// Items should be sorted in increasing value of slew rate.
//// Arguments:
////   (1) a database item
////   (2) a database item
//// Returns: result of the comparison
//int OpAmpDatabase::SortSlewRate(const void *First, const void* Second)
//{
//	return (double)((((OpAmps *)First)->GetSlewRateOpAmp > ((OpAmps *)Second)->GetSlewRateOpAmp) ? 1 : -1);
//}


// Display all of the messages in the database.
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void

void OpAmpDatabase::Display()
{
	// if the database is empty, display an error statement
	if (database_length == 0)
	{
		cout << "No elements in the database" << endl;
	}

	// if the database is not empty, display all the elements in the database
	else
	{
		cout << endl;
		for (unsigned long i = 0; i < database_length; i++)
		{
			ArrayOfOpAmps[i].DisplayOpAmpValues(); //display current op amps contained in the database
		}
	}
}