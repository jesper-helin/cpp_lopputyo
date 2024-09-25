// Helin Jesper
// c++ ohjelmoinnin perusteet -lopputyo

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

class Rooms
{
public:
	int reservationNumber;
	int roomNumber;
	string customerName;
	int reservedFor;
	bool isReserved;
	int size;
};

vector<Rooms> populateRooms(int amountOfRooms)
{
	std::vector<Rooms> rooms(amountOfRooms);

	// Loop to initialize the rooms array with data
	for (int i = 0; i <= amountOfRooms - 1; i++)
	{
		rooms[i].isReserved = 0;
		rooms[i].roomNumber = i + 1;
		rooms[i].reservedFor = 0;
		rooms[i].reservationNumber = 0;
		if (i < amountOfRooms / 2)
		{
			rooms[i].size = 1;
		}
		else
		{
			rooms[i].size = 2;
		}
	}

	return rooms;
}

bool checkInputIsChar(string input)
{
	return input.length() == 1;
}

int checkInputIsInt()
{
	int input;

	cin >> input;

	while (cin.fail() || input < 1)
	{
		cin.clear();
		cin.ignore(256, '\n');
		if (input < 1)
		{
			cout << "Anna positiivinen kokonaisluku" << endl;
		}
		cin >> input;
	}

	return input;
}

string checkInputIsString()
{
	string input;

	getline(cin >> ws, input);

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(256, '\n');
		getline(cin >> ws, input);
	}

	return input;
}

vector<Rooms> reserveRoom(int roomNumber, vector<Rooms> rooms)
{
	int howManyNights;
	string reservationName;
	int discountPercent;
	double totalPrice;
	string userInput;
	int reservationNumber;
	int singleRoomPrice = 100;
	int doubleRoomPrice = 150;

	cout << "Kuinka moneksi yoksi haluat varata huoneen?" << endl;
	howManyNights = checkInputIsInt();

	cout << "Milla nimella varaus tehdaan?" << endl;
	reservationName = checkInputIsString();
	uniform_int_distribution<> reservationNumberRange(10000, 99999);

	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<> dist(20, 150);
	reservationNumber = reservationNumberRange(gen);

	int randomDiscount = rand() % 3;
	switch (randomDiscount)
	{
	case 0:
		discountPercent = 0;
		break;
	case 1:
		discountPercent = 10;
		break;
	case 2:
		discountPercent = 20;
		break;
	}

	if (rooms[roomNumber].size == 1)
	{
		totalPrice = singleRoomPrice * howManyNights - ((discountPercent / 100.0) * 100 * howManyNights);
	}
	else
	{
		totalPrice = doubleRoomPrice * howManyNights - ((discountPercent / 100.0) * 150 * howManyNights);
	}

	cout << "Varauksen tiedot:" << endl
		 << "-----------------------------" << endl
		 << "Huoneen numero: " << rooms[roomNumber].roomNumber << endl
		 << "Varauksen kesto: " << howManyNights << " yota" << endl
		 << "Kokonaishinta, johon laskettu " << discountPercent << " % alennus: " << totalPrice << endl
		 << "Varaajan nimi: " << reservationName << endl 
		 << "Varausnumero: " << reservationNumber << endl
		 << "Haluatko varata huoneen (y, e)" << endl;

	while (true)
	{
		cin >> userInput;

		if (checkInputIsChar(userInput))
		{
			if (userInput == "y" || userInput == "Y")
			{
				rooms[roomNumber].customerName = reservationName;
				rooms[roomNumber].reservationNumber = reservationNumber;
				rooms[roomNumber].reservedFor = howManyNights;
				rooms[roomNumber].isReserved = 1;
				cout << rooms[roomNumber].isReserved << endl;
				cout << "Huone varattu. Kiitos asioinnista! Palautetaan etusivulle...\n\n";
				break;
			}
			else if (userInput == "e" || userInput == "E")
			{
				cout << "Huonetta ei varattu. Palaat etusivulle... Kiitos asioinnista!\n"
					 << endl;
				break;
			}
			else
			{
				continue;
			}
		}
	}

	return rooms;
}

int searchForReservation(vector<Rooms> rooms, int amountOfRooms)
{
	string choiceInput;
	string searchInput;

	cout << "Hae varausta joko (v)araajan nimella tai varaus(n)umerolla (v, n)" << endl;
	cin >> choiceInput;

	if (checkInputIsChar(choiceInput))
	{
		if (choiceInput == "v" || choiceInput == "V")
		{
			cout << "Syota varaajan nimi" << endl;
			searchInput = checkInputIsString();

			// Loop through all the rooms to find the searched room.
			// Bad implementation, but couldnt get a lambda func to work
			for (int i = 0; i < amountOfRooms; i++)
			{
				if (rooms[i].customerName == searchInput)
				{
					cout << "Haulla loytyi huone " << rooms[i].roomNumber << ", jonka varausnumero on "
						 << rooms[i].reservationNumber << ". Huone on varattu " << rooms[i].reservedFor << " yoksi." << endl;
				}
			}
		}
		else if (choiceInput == "N" || choiceInput == "n")
		{
			cout << "Syota varauksen numero" << endl;
			int searchInput = checkInputIsInt();
			cout << searchInput << endl;

			for (int i = 0; i < amountOfRooms; i++)
			{
				if (rooms[i].reservationNumber == searchInput)
				{
					cout << "Haulla loytyi huone " << rooms[i].roomNumber << ", jonka varaaja on "
						 << rooms[i].customerName << ". Huone on varattu " << rooms[i].reservedFor << " yoksi." << endl;
				}
			}
		}
		else
		{
			cout << "Vaara syote. Palataan etusivulle..." << endl;
			return 0;
		}
	}
	return 0;
}

bool checkRoomAvailability(int size, vector<Rooms> rooms)
{
	int availableRooms{};

	for (int i = 0; i < rooms.size() - 1; i++)
	{
		if (size == 0 && !rooms[i].isReserved)
		{
			availableRooms += 1;
		}
		else if (rooms[i].size == size && !rooms[i].isReserved)
		{
			availableRooms += 1;
		}
	}
	if (availableRooms > 0)
		return true;
	else
		return false;
}

int main()
{
	srand(time(NULL));

	bool continueReserving;
	continueReserving = true;

	// Randomize the amount of rooms here
	//
	int amountOfRooms;
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<> dist(20, 150);

	amountOfRooms = dist(gen) * 2;

	// Call populateRooms, that creates a vector of all the rooms in the system in object type.
	// max index is 259
	std::vector<Rooms> rooms = populateRooms(amountOfRooms);

	cout << rooms.back().roomNumber << endl;

	cout << "Tervetuloa huonevarausjarjestelmaan." << endl;
	while (continueReserving)
	{
		int selected = 4;
		int selectedRoomSize;
		string input;

		cout << "Arvo huone, tai valitse yhden / kahden hengen huone (a, y, k)."
			 << "Voit myos hakea varausta varausnumerolla tai varaajan nimella (h)" << endl;
		cin >> input;

		// Check whether input matches predefined restrictions,
		// throw error if wrong input
		if (checkInputIsChar(input))
		{
			if (input == "a" || input == "A")
			{
				selected = 1;
			}
			else if (input == "y" || input == "Y")
			{
				selected = 2;
			}
			else if (input == "k" || input == "K")
			{
				selected = 3;
			}
			else if (input == "h" || input == "H")
			{
				selected = 4;
			}
			else
			{
				cout << "Vaara syote, yrita uudestaan" << endl;
				continue;
			}
		}
		// Handle user choice
		switch (selected)
		{
		case 1:
		{
			if (checkRoomAvailability(0, rooms))
			{
				// Choose a random room. If the room is already reserved
				// keep randomizing until a free one is found

				for (int i = 0; i < rooms.size() - 1; i++)
				{
					int randomRoomNumber = 1 + rand() % amountOfRooms;
					if (!rooms[randomRoomNumber].isReserved)
					{
						cout << "Huonetta " << randomRoomNumber << " ei ole varattu" << endl;
					}
					else
					{
						continue;
					}

					// - 1 from randomRoomNumber, because rooms is a vector
					cout << "Jarjestelma on arponut huoneen " << rooms[randomRoomNumber - 1].roomNumber << ", joka on "
						 << rooms[randomRoomNumber].size << " hengen huone. Arvo uusi huone tai varaa valittu (a, v)" << endl;

					// Check if user reserved room, so that we can exit from loop
					bool roomReserved = false;

					while (true)
					{
						cin >> input;
						if (checkInputIsChar(input))
						{
							if (input == "a" || input == "A")
							{
								break;
							}
							else if (input == "v" || input == "V")
							{
								rooms = reserveRoom(randomRoomNumber, rooms);
								roomReserved = true;
								break;
							}
						}
					}

					if (roomReserved)
						break;
				}
			}
			else
			{
				cout << "Jarjestelmassa ei vapaita huoneita. Palataan etusivulle..." << endl;
			}

			break;
		}
		case 2:
			// single room
			selectedRoomSize = 1;
			if (checkRoomAvailability(selectedRoomSize, rooms))
			{
				int chosenRoomNumber;

				cout << "Hae vapaita huoneita " << rooms.front().roomNumber << "-" << rooms.back().roomNumber / 2 << endl;

				while (true)
				{
					chosenRoomNumber = checkInputIsInt() - 1;

					if (chosenRoomNumber + 1 < 1 || chosenRoomNumber >= amountOfRooms)
					{
						cout << "Huoneen numerolla " << chosenRoomNumber + 1 << " ei loytynyt huoneita. Yrita uudestaan" << endl;
						continue;
					}

					if (rooms[chosenRoomNumber].isReserved)
					{
						cout << chosenRoomNumber + 1 << " huone on varattu. Hae toista huonetta..." << endl;
						continue;
					}

					if (chosenRoomNumber >= rooms.back().roomNumber / 2 && chosenRoomNumber <= rooms.back().roomNumber)
					{
						cout << "Valitsemasi huone on kahden hengen huone. Voit jatkaa tai peruuttaa (j, p)" << endl;

						string continueInput;

						cin >> continueInput;
						if (checkInputIsChar(continueInput))
						{
							if (continueInput == "j" || continueInput == "J")
							{
								rooms = reserveRoom(chosenRoomNumber, rooms);
								break;
							}
							else if (continueInput == "p" || continueInput == "P")
							{
								break;
							}
							else
							{
								cout << "Vaara syote. Palataan alkuun..." << endl;
							}
						}
					}

					rooms = reserveRoom(chosenRoomNumber, rooms);
					break;
				}
			}
			else
			{
				cout << "Yhden hengen huoneita ei saatavilla. Palataan etusivulle..." << endl;
			}
			break;
		case 3:
			// double room
			selectedRoomSize = 2;
			if (checkRoomAvailability(selectedRoomSize, rooms))
			{
				int chosenRoomNumber;

				cout << "Hae vapaita huoneita " << rooms.back().roomNumber / 2 + 1 << "-" << rooms.back().roomNumber << endl;

				while (true)
				{
					chosenRoomNumber = checkInputIsInt() - 1;

					if (chosenRoomNumber < 1 || chosenRoomNumber >= amountOfRooms)
					{
						cout << "Huoneen numerolla " << chosenRoomNumber + 1 << " ei loytynyt huoneita. Yrita uudestaan" << endl;
						continue;
					}

					if (rooms[chosenRoomNumber].isReserved)
					{
						cout << chosenRoomNumber + 1 << " huone on varattu. Hae toista huonetta..." << endl;
						continue;
					}

					if (chosenRoomNumber >= rooms.front().roomNumber && chosenRoomNumber < rooms.back().roomNumber / 2)
					{
						cout << "Valitsemasi huone on yhden hengen huone. Voit jatkaa tai peruuttaa (j, p)" << endl;

						string continueInput;

						cin >> continueInput;
						if (checkInputIsChar(continueInput))
						{
							if (continueInput == "j" || continueInput == "J")
							{
								rooms = reserveRoom(chosenRoomNumber, rooms);
								break;
							}
							else if (continueInput == "p" || continueInput == "P")
							{
								break;
							}
							else
							{
								cout << "Vaara syote. Palataan alkuun..." << endl;
							}
						}
					}

					rooms = reserveRoom(chosenRoomNumber, rooms);
					break;
				}
			}
			else
			{
				cout << "Yhden hengen huoneita ei saatavilla. Palataan etusivulle..." << endl;
			}
			break;
		case 4:
			// search resevation
			searchForReservation(rooms, amountOfRooms);
			break;
		default:
			cout << "Vaara syote, yrita uudestaan" << endl;
			break;
		}
	}

	cout << "Kiitos asioinnista" << endl;

	system("PAUSE");
	return 0;
}