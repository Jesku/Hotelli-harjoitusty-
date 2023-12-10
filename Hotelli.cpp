#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class hotelRooms {
public:
	int roomNumber;
	int roomPrice;
	int nights;
	bool reserved;
	bool isDoubleRoom;

	hotelRooms(int number, bool isDouble) : roomNumber(number), roomPrice(0), nights(0), reserved(false), isDoubleRoom(isDouble){}
};

class hotelReservation {
private:
	vector<hotelRooms> rooms;

	int actualTotalRooms;
	int singleRooms;
	int doubleRooms;

public:

	hotelReservation(int totalRooms) {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> distTotalRooms(40, 300);

		int actualTotalRooms = distTotalRooms(gen);
		actualTotalRooms = max(actualTotalRooms - (actualTotalRooms % 2), 40);

		int singleRooms = actualTotalRooms / 2;
		int doubleRooms = actualTotalRooms - singleRooms;

		for (int i = 2; i <= actualTotalRooms * 2; i += 2) {
			bool isDouble = i > singleRooms * 2;
			rooms.push_back(hotelRooms(i, isDouble));
		}

		this->actualTotalRooms = actualTotalRooms;
		this->singleRooms = singleRooms;
		this->doubleRooms = doubleRooms;
	}

	void displayAvailableRooms() const {
		cout << "Vapaana olevat huoneet: ";

		for (const auto &room : rooms) {
			if (!room.reserved) {
				cout << room.roomNumber << " ";
			}
		}
		cout << "\nVapaana olevien huoneiden määrä: " << actualTotalRooms << endl;
		cout << "Vapaana olevien yhden hengen huoneiden määrä: " << singleRooms << endl;
		cout << "Vapaana olevien kahden hengen huoneiden määrä: " << doubleRooms << endl;
		cout << endl;
	}

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
		cout << "\nVarattujen huoneiden määrä: " << reservedTotalRooms << endl;
		cout << "Varattujen yhden hengen huoneiden määrä: " << reservedSingleRooms << endl;
		cout << "Varattujen kahden hengen huoneiden määrä: " << reservedDoubleRooms << endl;
		cout << endl;
	}

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
			cout << "Arpaonni ei suosinut tällä kertaa etkä saanut yhtään alennusta...\n\n";
		}
		else if (discount == 0.1) {
			cout << "Hienoa sait 10% alennusta.\n\n";
		}
		else if (discount == 0.2) {
			cout << "Wau sait huiman 20% alennusta.\n\n";
		}
	}

	int automaticReservation(hotelReservation& hotel, bool& roomReserved) {
		int roomType, nights;

		cout << "Haluatko yhden vai kahden hengen huoneen? (1 = yhden hengen huone ja 2 = kahden hengen huone)\nSyöte: ";
		cin >> roomType;

		if (roomType == 1 or roomType == 2) {
			cout << "Montako yötä aiot viipyä?\nSyöte: ";
			cin >> nights;

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
				cout << "\nValitsemasi huonetyyppi ei ole tällä hetkellä saatavilla.\n\n";
			}
		}
		else {
			cout << "\nVirheellinen syöte huonetyypille.\n\n";
		}
		return roomType;
	}

	int manualReservation(hotelReservation& hotel, bool& roomReserved) {
		int roomNumber, nights;
		cout << "Syötä huoneen numero: ";
		cin >> roomNumber;
		cout << "Syötä öiden määrä: ";
		cin >> nights;
		if (hotel.reserveRoom(roomNumber, nights)) {
			cout << "\nHuone varattu onnistuneesti.\n\n";
			roomReserved = true;
		}
		else {
			cout << "\nValittu huone on jo varattu tai ei ole saatavilla.\n\n";
		}
		return roomNumber;
	}
};

int main() {
	srand(time(0));
	
	hotelReservation hotel(0);
	
	int task;
	bool roomReserved = false;
	cout << "Tervetuloa (nimi) hotelliin!\n"
		<< "----------------------------\n\n";
	
	do {
		cout << "Lista toimminoista hotellihuoneen varaukseen (syötä numero väliltä 1-4):\n"
			<< "Syötä 1 jos haluat varata huoneita.\n"
			<< "Syötä 2 jos haluat ohjelman varaavan huoneen,\nilmoita vain haluatko yhden vai kahden hengen huoneen ja montako yötä aiot viipyä.\n"
			<< "Syötä 3 jos haluat nähdä vapaana olevat huoneet.\n"
			<< "Syötä 4 jos haluat nähdä varatut huoneet.\n"
			<< "Syötä 5 jos haluat poistua ohjelmasta.\n"
			<< "----------\n"
			<< "Syöte: ";
		cin >> task;
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
				cout << "\nHyvästi ja hyvää loppuelämää...\n\n";
			}
			else {
				cout << "\nPahoittelut mikäli et ollut tyytyväinen hotellimme tarjontaan.\n\n";
			}
			break;
		default:
			cout << "\nKatoppa uuestaa!\n\n";
			break;
		}
	} while (task != 5);

	cout << "Paina jotain näppäintä sulkeaksesi ohjelman...";
	cin.ignore();
	cin.get();

	return 0;
}