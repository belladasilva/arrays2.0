#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// Isabella Da Silva
// Assignment 3 - Reservation flight

using namespace std;

const int SIZE = 12;

// prototypes
int loadArrays(ifstream&, string[], int[][2]);
void printReport(ofstream&, string[], int[][2], int);
void findPassenger(const string&, const string[], int&, int);
bool reserveSeat(string[], int[][2], int&);
int validateSeat(int, int);


int main()
{
	int reservation[SIZE][2];
	string name[SIZE];
	int noPassengers = 0;
	int position;

	ifstream fin("reservations.dat");
	if (!fin.is_open())
	{
		cout << "error opening reservations.dat file - contact systems";
		system("pause");
		exit(-1);
	}
	ofstream fout("reservations.rpt");
	if (!fout.is_open())
	{
		cout << "error opening reservations.rpt file - contact systems";
		system("pause");
		exit(-2);
	}
	cout << "Search for non passenger \n";
	findPassenger("Superman", name, position, noPassengers);
	cout << "Passenger: Superman";
	if (position < noPassengers)
		cout << " is seated in row " << reservation[position][0]
		<< " seat " << reservation[position][1];
	else
		cout << " is not found ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);
	cout << "Load arrays\n";
	noPassengers = loadArrays(fin, name, reservation);
	printReport(fout, name, reservation, noPassengers);

	cout << "Search for existing passenger \n";
	findPassenger("J. Doe", name, position, noPassengers);
	cout << "Passenger: J. Doe";
	if (position < noPassengers)
		cout << " is seated in row " << reservation[position][0]
		<< " seat " << reservation[position][1];
	else
		cout << " is not found ";
	cout << endl;
	cout << "#1 Reserve for Superman in unoccupied seat (4, 1) : \n";
	if (reserveSeat(name, reservation, noPassengers))
		cout << "reservation made ";
	else
		cout << "reservation not made ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);

	cout << "#1 Reserve for Batman in Superman's seat (4, 1): \n";
	if (reserveSeat(name, reservation, noPassengers))
		cout << "reservation made ";
	else
		cout << "reservation not made ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);

	cout << "#1 Reserve for Batman again in unoccupied seat (4, 2):\n";
	if (reserveSeat(name, reservation, noPassengers))
		cout << "reservation made ";
	else
		cout << "reservation not made ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);

	cout << "#1 Reserve for Cat woman in unoccupied seat (4, 3)\n";
	if (reserveSeat(name, reservation, noPassengers))
		cout << "reservation made ";
	else
		cout << "reservation not made ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);
	cout << "program ended successfully" << endl;
	cout << "\nDump of Reservations.dat file\n";
	system("type reservations.dat");
	cout << "\nPrintout of Reservations Report\n";
	system("type reservations.rpt");
	system("pause");

}

int loadArrays(ifstream& fin, string passengerNames[], int passengerInfo[][2])
{
	int passengersAdded = 0;
	for (int index = 0; index < SIZE; index++)
	{
		getline(fin, passengerNames[index]);
		if (fin.eof())
			break;

		fin >> passengerInfo[index][0] >> passengerInfo[index][1];
		fin.ignore(80, '\n');
		passengersAdded++;
	}
	return passengersAdded;
}

void printReport(ofstream& fout, string passengerNames[], int passengerInfo[][2], int numPassengers)
{
	fout << left << setw(14) << "Passenger" << setw(8) << "Row" << "Seat" << endl;
	for (int index = 0; index < numPassengers; index++)
	{
		fout << left << setw(15) << passengerNames[index] << setw(8) << passengerInfo[index][0] << passengerInfo[index][1] << endl;
	}
}

void findPassenger(const string& targetPassenger, const string passengerNames[], int& position, int numPassengers)
{
	position = numPassengers;
	for (int index = 0; index < numPassengers; index++)
	{
		if (passengerNames[index] == targetPassenger)
		{
			position = index;
			return;
		}
	}
}

bool reserveSeat(string passengerNames[], int passengerInfo[][2], int& numPassengers) {
	int row, seat;
	string name;
	cout << "Enter row number: ";
	cin >> row;
	cout << "Enter seat number: ";
	cin >> seat;
	cout << "Enter passenger name: ";
	cin >> name;

	if (numPassengers >= SIZE)
	{
		cout << "The array is full. Cannot add more seats." << endl;
		return false;
	}
	for (int index = 0; index < numPassengers; index++)
	{
		if (passengerInfo[index][0] == row && passengerInfo[index][1] == seat)
		{
			cout << "Seat " << row << ", " << seat << " is already reserved." << endl;
			return false;
		}
	}

	passengerInfo[numPassengers][0] = row;
	passengerInfo[numPassengers][1] = seat;
	passengerNames[numPassengers] = name;
	numPassengers++;
	return true;
}

int validateSeat(int value, int maxValue)
{
	int input;
	do
	{
		cout << "Enter seat number: ";
		cin >> input;
		if (input >= 1 && input <= maxValue)
			break;
		else
			cout << "Invalid input. Seat number must be between 1 and " << maxValue << ". Please try again." << endl;
	} while (true);
	return input;
}

/*
Search for non passenger
Passenger: Superman is not found
Load arrays
Search for existing passenger
Passenger: J. Doe is seated in row 1 seat 2
#1 Reserve for Superman in unoccupied seat (4, 1) :
Enter row number: 4
Enter seat number: 1
Enter passenger name: Superman
reservation made
#1 Reserve for Batman in Superman's seat (4, 1):
Enter row number: 4
Enter seat number: 1
Enter passenger name: Batman
Seat 4, 1 is already reserved.
reservation not made
#1 Reserve for Batman again in unoccupied seat (4, 2):
Enter row number: 4
Enter seat number: 2
Enter passenger name: Batman
reservation made
#1 Reserve for Cat woman in unoccupied seat (4, 3)
Enter row number: 4
Enter seat number: 3
Enter passenger name: Cat woman
reservation made
program ended successfully

Dump of Reservations.dat file
J. Doe
1   2
P. Smith
5       3
T. Jones
3       1
M. Marc
4   5
J. Bieber
3   3
H. Lance
6   2
Printout of Reservations Report
Passenger     Row     Seat
J. Doe         1       2
P. Smith       5       3
T. Jones       3       1
M. Marc        4       5
J. Bieber      3       3
H. Lance       6       2
Passenger     Row     Seat
J. Doe         1       2
P. Smith       5       3
T. Jones       3       1
M. Marc        4       5
J. Bieber      3       3
H. Lance       6       2
Superman       4       1
Passenger     Row     Seat
J. Doe         1       2
P. Smith       5       3
T. Jones       3       1
M. Marc        4       5
J. Bieber      3       3
H. Lance       6       2
Superman       4       1
Passenger     Row     Seat
J. Doe         1       2
P. Smith       5       3
T. Jones       3       1
M. Marc        4       5
J. Bieber      3       3
H. Lance       6       2
Superman       4       1
Batman         4       2
Passenger     Row     Seat
J. Doe         1       2
P. Smith       5       3
T. Jones       3       1
M. Marc        4       5
J. Bieber      3       3
H. Lance       6       2
Superman       4       1
Batman         4       2
Cat            4       3
Press any key to continue . . .
*/