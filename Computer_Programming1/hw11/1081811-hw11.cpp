#pragma region ImportStuffs

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setfill;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <vector>
using std::vector;

#pragma endregion

struct Date
{
	int year = 0;
	int month = 0;
	int day = 0;
};

struct AvailTable
{
	Date date;
	int numAvailTables[4][6] = {}; // the number of available tables,
};  // numAvailTables[ 1 ][ i ] is the number of available type i tables on 11:30
	// numAvailTables[ 2 ][ i ] is the number of available type i tables on 14:30
	// numAvailTables[ 3 ][ i ] is the number of available type i tables on 17:30

struct Reservation
{
	int numCustomers = 0;              // number of customers
	Date date;                         // reservation date
	int time = 0;                      // reservation time code
	char name[8] = "";               // name
	char mobileNumber[12] = "";      // mobile phone number
	char email[40] = "";             // email address
	char password[12] = "";          // reservation password
	char reservationNumber[12] = ""; // reservation number
};

// tableTypes[ i ] is the table type for i customers
const int tableTypes[13] = { 0, 1, 1, 2, 2, 3, 4, 4, 0, 0, 5, 5, 5 };

const int TOTAL_NUM_TABLES = 2; // suppose there are totally 2 tables for all types

#pragma region AllFunctions

// return current date
Date computeCurrentDate();

// return true if and only if year is a leap year
inline bool leapYear(int year);

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end);

// return true if and only if date1 == date2
bool equal(Date date1, Date date2);

// return true if and only if date1 < date2
bool less(Date date1, Date date2);

// return true if and only if date1 <= date2
bool lessEqual(Date date1, Date date2);

// return date + numDays
Date add(Date date, int numDays);

// delete out of date data in availTables, and append new data from rear of availTables
void initAvailTables(vector< AvailTable >& availTables, Date currentDate);

// read available table informations after currentDate, from the file AvailTables.dat
void loadAvailTables(vector< AvailTable >& availTables, Date currentDate);

// read reservation informations after or equal to currentDate, from the file Reservations.dat
void loadReservations(vector< Reservation >& reservations, Date currentDate);

// make reservation
void makeReservation(vector< Reservation >& reservations, vector< AvailTable >& availTables, Date currentDate);

// choose a date and a time
void chooseDateTime(vector< AvailTable >& availTables, Reservation& reservation, Date currentDate, int tableType);

// display dates on which there are tables available
void displayAvailDates(vector< AvailTable >& availTables, bool available[], int tableType);

// return true if there are available tables on availTables[ i ].date for corresponding table type
bool availableTables(vector< AvailTable >& availTables, size_t i, int tableType);

// --availTables[ i ].numAvailTables[ timeCode ][ tableType ], where availTables[ i ].date == date
void decreaseAvailTables(vector< AvailTable >& availTables, Date date, int timeCode, int tableType);

// use reservationNumber to make a reservation inquiry, and let user choose whether to cancel it
void reservationInquiry(vector< Reservation >& reservations, vector< AvailTable >& availTables);

// display all fields of reservation which includes
// mobileNumber, name, date, time, email, numCustomers, password and reservationNumber
void displayReservationInfo(const Reservation& reservation);

// display reservations[ i ], where
// reservations[ i ].reservationNumber is equal to the specified reservationNumber
void displayReservationInfo(const vector< Reservation >& reservations, char reservationNumber[]);

// erase reservations[ position ]
void erase(vector< Reservation >& reservations, int position);

// write availTables into the file AvailTables.dat
void saveAvailTables(const vector< AvailTable >& availTables);

// write reservations into the file Reservations.dat
void saveReservations(const vector< Reservation >& reservations);

#pragma endregion

int main()
{
	cout << "Welcome to Hi-Lai Harbour Taoyuan Location!\n";

	srand(static_cast<unsigned int>(time(0)));
	Date currentDate = computeCurrentDate();

	vector< AvailTable > availTables; // vector of all available table informations
	initAvailTables(availTables, currentDate);

	vector< Reservation > reservations; // vector of all available table informations
	loadReservations(reservations, currentDate);

	bool userExited = false; // user has not chosen to exit

	// loop while user has not chosen option to exit system
	while (!userExited)
	{
		// show main menu and get user selection
		cout << "\n1 - Book a Table\n";
		cout << "2 - My Bookings\n";
		cout << "3 - End\n\n";

		int mainMenuSelection;
		do cout << "Enter your choice: (1~3): ";
		while ((mainMenuSelection = inputAnInteger(1, 3)) == -1);

		// decide how to proceed based on user's menu selection
		switch (mainMenuSelection)
		{
		case 1:
			makeReservation(reservations, availTables, currentDate); // make reservation
			break;
		case 2:
			reservationInquiry(reservations, availTables); // reservation inquiry
			break;
		case 3: // user chose to terminate session
			saveAvailTables(availTables);
			saveReservations(reservations);
			userExited = true; // this session should end
			cout << endl;
			break;
		default: // user did not enter an integer from 1-3
			cout << "\nIncorrect choice!" << endl;
		}
	}

	system("pause");
}

Date computeCurrentDate()
{
	tm tm;
	time_t rawTime = time(0);
	localtime_s(&tm, &rawTime);

	Date d;
	d.year = tm.tm_year + 1900;
	d.month = tm.tm_mon + 1;
	d.day = tm.tm_mday;

	return d;
}

inline bool leapYear(int year)
{
	return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

int inputAnInteger(int begin, int end)
{
	char string[80];
	cin.getline(string, 80, '\n');

	if (strlen(string) == 0)
		exit(0);

	for (unsigned int i = 0; i < strlen(string); i++)
		if (string[i] < '0' || string[i] > '9')
			return -1;

	int number = atoi(string);

	if (number >= begin && number <= end)
		return number;
	else
		return -1;
}

bool equal(Date date1, Date date2)
{
	return (date1.year == date2.year &&
		date1.month == date2.month &&
		date1.day == date2.day);
}

bool less(Date date1, Date date2)
{
	if (date1.year < date2.year)
		return true;
	if (date1.year > date2.year)
		return false;

	if (date1.month < date2.month)
		return true;
	if (date1.month > date2.month)
		return false;

	if (date1.day < date2.day)
		return true;

	return false;
}

bool lessEqual(Date date1, Date date2)
{
	return less(date1, date2) || equal(date1, date2);
}

Date add(Date date, int numDays)
{
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	Date d(date);

	if (leapYear(d.year))
		days[2] = 29;

	d.day += numDays;

	while (d.day > days[d.month])
	{
		d.day -= days[d.month];
		++d.month;

		while (d.month > 12)
		{
			d.month -= 12;
			++d.year;
		}
	}

	return d;
}

void initAvailTables(vector< AvailTable >& availTables, Date currentDate)
{
	loadAvailTables(availTables, currentDate);

	AvailTable temp;
	for (int i = availTables.size() + 1; i <= 30; ++i)
	{
		temp.date = add(currentDate, i);

		for (int j = 1; j <= 3; ++j)
			for (int k = 1; k <= 5; ++k)
				temp.numAvailTables[j][k] = 2;

		availTables.push_back(temp);
	}
}

void loadAvailTables(vector< AvailTable >& availTables, Date currentDate)
{
	ifstream ifs("AvailTables.dat", ios::binary);

	if (!ifs.is_open())
	{
		cout << "File could not be loaded.";
		system("pause");
		exit(EXIT_FAILURE);
	}

	AvailTable temp;

	while (ifs.read(reinterpret_cast<char*>(&temp), sizeof(AvailTable)))
		if (less(currentDate, temp.date))
			availTables.push_back(temp);

	ifs.close();
}

void loadReservations(vector< Reservation >& reservations, Date currentDate)
{
	ifstream ifs("Reservations.dat", ios::binary);

	if (!ifs.is_open())
	{
		cout << "File could not be loaded.";
		system("pause");
		exit(EXIT_FAILURE);
	}

	Reservation temp;

	while (ifs.read(reinterpret_cast<char*>(&temp), sizeof(Reservation)))
		if (lessEqual(currentDate, temp.date))
			reservations.push_back(temp);

	ifs.close();
}

void makeReservation(vector< Reservation >& reservations, vector< AvailTable >& availTables, Date currentDate)
{
	Reservation newReservation;

	do {
		cout << "\nEnter the number of customers (1 - 7, 10 - 12): ";
		newReservation.numCustomers = inputAnInteger(1, 12);
	} while (newReservation.numCustomers == 8 ||
		newReservation.numCustomers == 9 ||
		newReservation.numCustomers == -1);

	int tableType = tableTypes[newReservation.numCustomers];

	chooseDateTime(availTables, newReservation, currentDate, tableType);

	cout << "\nEnter name: ";
	cin >> newReservation.name;

	cout << "\nEnter mobile number: ";
	cin >> newReservation.mobileNumber;

	cout << "\nEnter email address: ";
	cin >> newReservation.email;

	cout << "\nEnter reservation password: ";
	cin >> newReservation.password;
	cin.ignore();

	newReservation.reservationNumber[0] = 1 + rand() % 9 + '0';
	for (int i = 1; i < 8; i++)
		newReservation.reservationNumber[i] = rand() % 10 + '0';

	cout << setfill(' ') << endl << setw(11) << "Mobile No." << setw(10) << "Name"
		<< setw(14) << "Date" << setw(9) << "Time" << setw(30) << "Email"
		<< setw(19) << "No of Customers" << setw(12) << "Password"
		<< setw(19) << "Reservation No." << endl;

	displayReservationInfo(newReservation);

	cout << "\nReservation Completed!\n";

	reservations.push_back(newReservation);

	decreaseAvailTables(availTables, newReservation.date, newReservation.time, tableType);
}

// choose a date and a time
void chooseDateTime(vector< AvailTable >& availTables, Reservation& reservation, Date currentDate, int tableType)
{
	cout << "\nChoose a date: \n";

	bool availDate[30];
	for (int i = 0; i < 29; ++i)
	{
		for (int j = 1; j <= 3; ++j)
			if (availTables.at(i).numAvailTables[j][tableType] > 0)
			{
				availDate[i] = true;
				break;
			}
			else
				availDate[i] = false;
	}

	displayAvailDates(availTables, availDate, tableType);

	cout << "\n";
	int chosenDate;
	cin >> chosenDate;
	reservation.date = add(currentDate, chosenDate);

	const char* availTimes[] = { " ", ". 11:30", ". 14:30", ". 17:30" };
	cout << "\nChoose a time: \n";
	--chosenDate;   //make date right with input index

	for (int i = 1; i <= 3; ++i)
		if (availTables.at(chosenDate).numAvailTables[i][tableType] > 0)
			cout << i << availTimes[i] << "\n";

	cout << "\n";
	cin >> reservation.time;
}

void displayAvailDates(vector< AvailTable >& availTables, bool availableDate[], int tableType)
{
	int line = 0;

	for (int i = 0; i < 30; ++i)
	{
		if (availableDate[i])
		{
			cout << i + 1 << ". " << availTables.at(i).date.year << "/" << availTables.at(i).date.month << "/" << availTables.at(i).date.day;
			++line;

			if (line % 4 == 0)
				cout << "\n";
			else
				cout << "  ";
		}
	}
}

// returns true if there are available tables on availTables[ i ].date for corresponding table type
bool availableTables(vector< AvailTable >& availTables, size_t i, int tableType)
{
	for (int j = 1; j <= 3; ++j)
		if (availTables.at(i).numAvailTables[j][tableType])
			return true;

	return false;
}

// --availTables[ i ].numAvailTables[ timeCode ][ tableType ], where availTables[ i ].date == date
void decreaseAvailTables(vector< AvailTable >& availTables, Date date, int timeCode, int tableType)
{
	for (auto& table : availTables)
		if (equal(date, table.date))
		{
			--table.numAvailTables[timeCode][tableType];
			return;
		}
}

void reservationInquiry(vector< Reservation >& reservations, vector< AvailTable >& availTables)
{
	if (reservations.size() == 0)
	{
		cout << "\nNo reservations!\n";
		return;
	}

	cout << "\nEnter reservation number: ";
	char reservationNumber[12];
	cin >> reservationNumber;
	cin.ignore();

	Reservation temp;
	int index = -1;
	for (int i = 0; i < reservations.size(); ++i)
		if (!strcmp(reservations.at(i).reservationNumber, reservationNumber))
		{
			temp = reservations.at(i);
			index = i;
		}

	if (index == -1)
	{
		cout << "\nNo reservations with this reservation number!\n";
		return;
	}

	cout << "\nEnter reservation password: ";
	char password[12];
	cin >> password;
	cin.ignore();

	if (!strcmp(temp.password, password))
	{
		displayReservationInfo(temp);

		char yn;
		do
		{
			cout << "\nCancel this reservation ( y/n )? ";
			cin >> yn;
			cin.ignore();

			if (yn == 'y')
			{
				for (auto &availTable : availTables)
					if (equal(availTable.date, reservations.at(index).date))
					{
						++availTable.numAvailTables[reservations.at(index).time][reservations.at(index).numCustomers];
						break;
					}

				erase(reservations, index);
				cout << "\nThis reservation has been cancelled.\n";
				break;
			}
			else if (yn == 'n')
				break;
		} while (true);
	}
	else
		cout << "\nNo reservations with this reservation password!\n";
}

// displays all fields of reservation which includes
// mobileNumber, name, date, time, email, numCustomers, password and reservationNumber
void displayReservationInfo(const Reservation& reservation)
{
	char times[4][8] = { "", "11:30", "14:30", "17:30" };
	cout << setfill(' ') << setw(11) << reservation.mobileNumber
		<< setw(10) << reservation.name
		<< "    " << reservation.date.year << "/" << setfill('0')
		<< setw(2) << reservation.date.month << '/'
		<< setw(2) << reservation.date.day
		<< setfill(' ') << setw(9) << times[reservation.time]
		<< setw(30) << reservation.email
		<< setw(19) << reservation.numCustomers
		<< setw(12) << reservation.password
		<< setw(19) << reservation.reservationNumber << endl;
}

// displays reservations[ i ], where
// reservations[ i ].reservationNumber is equal to the specified reservationNumber
void displayReservationInfo(const vector< Reservation >& reservations, char reservationNumber[])
{
	cout << setfill(' ') << setw(11) << "Mobile No." << setw(10) << "Name"
		<< setw(14) << "Date" << setw(9) << "Time" << setw(30) << "Email"
		<< setw(19) << "No of Customers" << setw(12) << "Password"
		<< setw(19) << "Reservation No." << endl;

	for (size_t i = 0; i < reservations.size(); ++i)
		if (strcmp(reservations[i].reservationNumber, reservationNumber) == 0)
			break;

	char times[4][8] = { "", "11:30", "14:30", "17:30" };
	int count = 0;
	for (size_t i = 0; i < reservations.size(); ++i)
		if (strcmp(reservations[i].reservationNumber, reservationNumber) == 0)
			displayReservationInfo(reservations[i]);
}

// erase reservations[ position ]
void erase(vector< Reservation >& reservations, int position)
{
	reservations.erase(reservations.begin() + position);
}

void saveAvailTables(const vector< AvailTable >& availTables)
{
	ofstream ofs("AvailTables.dat", ios::binary);

	if (!ofs.is_open())
	{
		cout << "File could not be writed.";
		system("pause");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < availTables.size(); ++i)
		ofs.write((char*)(&availTables.at(i)), sizeof(AvailTable));

	ofs.close();
}

void saveReservations(const vector< Reservation >& reservations)
{
	ofstream ofs("Reservations.dat", ios::binary);

	if (!ofs.is_open())
	{
		cout << "File could not be writed.";
		system("pause");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < reservations.size(); ++i)
		ofs.write((char*)(&reservations.at(i)), sizeof(AvailTable));

	ofs.close();
}