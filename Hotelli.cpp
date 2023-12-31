#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class hotelRooms {
public:
	int roomNumber;	// Room number
	int roomPrice;	// Room price
	int nights;	// Number of nights
	bool reserved;	// Is the room reserved
	bool isDoubleRoom;	// Is it a double room

	hotelRooms(int number, bool isDouble) : roomNumber(number), roomPrice(0), nights(0), reserved(false), isDoubleRoom(isDouble){}
};

class hotelReservation {
private:
	vector<hotelRooms> rooms;	// Vector of hotel rooms

	int actualTotalRooms;	// Actual total number of rooms
	int singleRooms;	// Number of single rooms
	int doubleRooms;	// Number of double rooms

public:
	// Constructor to initialize hotel rooms
	hotelReservation(int totalRooms) {
		// Randomly generate the total number of rooms in the hotel
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> distTotalRooms(40, 300);

		int actualTotalRooms = distTotalRooms(gen);
		actualTotalRooms = max(actualTotalRooms - (actualTotalRooms % 2), 40);

		int singleRooms = actualTotalRooms / 2;
		int doubleRooms = actualTotalRooms - singleRooms;

		// Populate the vector with hotel rooms
		for (int i = 2; i <= actualTotalRooms * 2; i += 2) {
			bool isDouble = i > singleRooms * 2;
			rooms.push_back(hotelRooms(i, isDouble));
		}

		this->actualTotalRooms = actualTotalRooms;
		this->singleRooms = singleRooms;
		this->doubleRooms = doubleRooms;
	}
	
	// Display available rooms and room counts
	void displayAvailableRooms() const {
		cout << "Vapaana olevat huoneet: ";

		for (const auto &room : rooms) {
			if (!room.reserved) {
				cout << room.roomNumber << " ";
			}
		}
		cout << "\nVapaana olevien huoneiden m��r�: " << actualTotalRooms << endl;
		cout << "Vapaana olevien yhden hengen huoneiden m��r�: " << singleRooms << endl;
		cout << "Vapaana olevien kahden hengen huoneiden m��r�: " << doubleRooms << endl;
		cout << endl;
	}

	// Display reserved rooms and room counts
	void displayReservedRooms() const {
		int reservedTotalRooms = 0;
		int reservedSingleRooms = 0;
		int reservedDoubleRooms = 0;

		cout << "Varatut huoneet: ";
		for (const auto &room : rooms) {
			if (room.reserved) {
				cout << room.roomNumber << " ";
			}
			if (room.reserved && !room.isDoubleRoom) {
				reservedTotalRooms++;
				reservedSingleRooms++;
			}
			if (room.reserved && room.isDoubleRoom) {
				reservedTotalRooms++;
				reservedDoubleRooms++;
			}
		}
		cout << "\nVarattujen huoneiden m��r�: " << reservedTotalRooms << endl;
		cout << "Varattujen yhden hengen huoneiden m��r�: " << reservedSingleRooms << endl;
		cout << "Varattujen kahden hengen huoneiden m��r�: " << reservedDoubleRooms << endl;
		cout << endl;
	}

	// Reserve a room based on room number and nights
	bool reserveRoom(int roomNumber, int nights) {
		for (auto& room : rooms) {
			if (room.roomNumber == roomNumber && !room.reserved) {
				room.reserved = true;
				room.nights = nights;
				this->actualTotalRooms = actualTotalRooms - 1;
				if (!room.isDoubleRoom) {
					this->singleRooms = singleRooms - 1;
				}
				else if (room.isDoubleRoom) {
					this->doubleRooms = doubleRooms - 1;
				}
				return true;
			}
		}
		return false;
	}

	// Display the bill for reserved rooms with a random discount
	void displayBill() const {
		double totalAmount = 0.0;
		double discount = (rand() % 3) * 0.1; // Alennus 0%, 10% tai 20%;
		for (const auto& room : rooms) {
			if (room.reserved) {
				double roomCost = room.isDoubleRoom ? 150.0 : 100.0;
				double discountedAmount = roomCost * room.nights * (1.0 - discount);
				totalAmount += discountedAmount;
			}
		}
		cout << "Loppusumma: " << totalAmount << " euroa.\n";
		if (discount == 0.0) {
			cout << "Arpaonni ei suosinut t�ll� kertaa etk� saanut yht��n alennusta...\n\n";
		}
		else if (discount == 0.1) {
			cout << "Hienoa sait 10% alennusta.\n\n";
		}
		else if (discount == 0.2) {
			cout << "Wau sait huiman 20% alennusta.\n\n";
		}
	}

	// Perform automatic reservation based on user input
	int automaticReservation(hotelReservation& hotel, bool& roomReserved) {
		int roomType, nights;

		cout << "Haluatko yhden vai kahden hengen huoneen? (1 = yhden hengen huone ja 2 = kahden hengen huone)\nSy�te: ";
		roomType = getInput(1, 2);

		if (roomType == 1 or roomType == 2) {
			cout << "Montako y�t� aiot viipy�?\nSy�te: ";
			nights = getPositiveInput();

			int availableRoomNumber = -1;
			for (const auto& room : hotel.rooms) {
				if (!room.reserved && ((roomType == 1 && !room.isDoubleRoom) or (roomType == 2 && room.isDoubleRoom))) {
					availableRoomNumber = room.roomNumber;
					break;
				}
			}
			if (availableRoomNumber != -1) {
				if (hotel.reserveRoom(availableRoomNumber, nights)) {
					cout << "\nHuone varattu onnistuneesti.\n\n";
					roomReserved = true;
				}
				else {
					cout << "\nValitettavasti huone on jo varattu tai ei ole saatavilla.\n\n";
				}
			}
			else {
				cout << "\nValitsemasi huonetyyppi ei ole t�ll� hetkell� saatavilla.\n\n";
			}
		}
		else {
			cout << "\nVirheellinen sy�te huonetyypille.\n\n";
		}
		return roomType;
	}

	// Perform manual reservation based on user input
	int manualReservation(hotelReservation& hotel, bool& roomReserved) {
		int roomNumber, nights;
		cout << "Sy�t� huoneen numero: ";
		roomNumber = getPositiveInput();
		cout << "Sy�t� �iden m��r�: ";
		nights = getPositiveInput();
		if (hotel.reserveRoom(roomNumber, nights)) {
			cout << "\nHuone varattu onnistuneesti.\n\n";
			roomReserved = true;
		}
		else {
			cout << "\nValittu huone on jo varattu tai ei ole saatavilla.\n\n";
		}
		return roomNumber;
	}

public:
	// Get positive user input
	int getPositiveInput() const {
		int value;
		while (true) {
			cin >> value;
			if (cin.fail() or value <= 0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Virheellinen sy�te yrit� uudelleen.";
			}
			else {
				break;
			}
		}
		return value;
	}

	// Get user input within a specific range
	int getInput(int min, int max) const {
		int value;
		while (true) {
			cin >> value;
			if (cin.fail() or value < min or value > max) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Virheellinen sy�te anna luku " << min << " ja " << max << " v�lilt�.";
			}
			else {
				break;
			}
		}
		return value;
	}
};

int main() {
	srand(time(0));
	
	hotelReservation hotel(0);
	
	int task;
	bool roomReserved = false;
	cout << "Tervetuloa t�mm�seen hienoon hotelliin!\n"
		<< "----------------------------\n\n";
	
	do {
		cout << "Lista toimminoista hotellihuoneen varaukseen (sy�t� numero v�lilt� 1-5):\n"
			<< "Sy�t� 1 jos haluat varata huoneita.\n"
			<< "Sy�t� 2 jos haluat ohjelman varaavan huoneen,\nilmoita vain haluatko yhden vai kahden hengen huoneen ja montako y�t� aiot viipy�.\n"
			<< "Sy�t� 3 jos haluat n�hd� vapaana olevat huoneet.\n"
			<< "Sy�t� 4 jos haluat n�hd� varatut huoneet.\n"
			<< "Sy�t� 5 jos haluat poistua ohjelmasta.\n"
			<< "----------\n"
			<< "Sy�te: ";
		task = hotel.getInput(1, 5);
		cout << "----------\n";
		switch (task)
		{
		case 1:
			hotel.manualReservation(hotel, roomReserved);
			break;
		case 2:
			hotel.automaticReservation(hotel, roomReserved);
			break;
		case 3:
			hotel.displayAvailableRooms();
			break;
		case 4:
			hotel.displayReservedRooms();
			break;
		case 5:
			if (roomReserved) {
				hotel.displayBill();
				cout << "\nToivottavasti viihdyt hotellissa ja n�emme viel� uudestaan.\n\n";
			}
			else {
				cout << "\nPahoittelut mik�li et l�yt�nyt huonetta joka kelpaisi sinulle.\n\n";
			}
			break;
		default:
			cout << "\nVirheellinen sy�te yrit� uudelleen.\n\n";
			break;
		}
	} while (task != 5);

	cout << "Paina jotain n�pp�int� poistuaksesi ohjelmasta...";
	cin.ignore();
	cin.get();

	return 0;
}