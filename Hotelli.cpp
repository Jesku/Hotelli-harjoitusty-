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

public:
	/*hotelReservation(int singleRooms, int doubleRooms) {
		for (int i = 1; i <= singleRooms; i++) {
			rooms.push_back(hotelRooms(i, false));
		}
		for (int i = singleRooms + 1; i <= singleRooms + doubleRooms; i++) {
			rooms.push_back(hotelRooms(i, true));
		}
	}*/

	hotelReservation(int totalRooms) {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> distTotalRooms(40, 300);
		
		int actualTotalRooms = distTotalRooms(gen);
		int singleRooms = actualTotalRooms / 2;
		int doubleRooms = actualTotalRooms - singleRooms;

		for (int i = 1; i <= actualTotalRooms; i++) {
			bool isDouble = i > singleRooms;
			rooms.push_back(hotelRooms(i, isDouble));
		}

		/*// Generoidaan ensin yhden hengen huoneet
		for (int i = 0; i < totalRooms / 2; ++i) {
			int roomNumber;
			do {
				roomNumber = distSingle(gen);
			} while (roomNumber % 2 != 0); // Tarkistetaan, ett‰ numero on parillinen

			rooms.push_back(hotelRooms(roomNumber, false)); // Yhden hengen huone
		}

		// Generoidaan kahden hengen huoneet
		for (int i = totalRooms / 2 + 1; i <= totalRooms; ++i) {
			int roomNumber;
			do {
				roomNumber = distSingle(gen);
			} while (roomNumber % 2 != 0); // Tarkistetaan, ett‰ numero on parillinen

			rooms.push_back(hotelRooms(roomNumber, true)); // Kahden hengen huone
		}*/
	}

	void displayAvailableRooms() const {
		cout << "Vapaana olevat huoneet: ";
		for (const auto &room : rooms) {
			if (!room.reserved) {
				cout << room.roomNumber << " ";
			}
		}
		cout << endl;
	}

	void displayReservedRooms() const {
		cout << "Varatut huoneet: ";
		for (const auto &room : rooms) {
			if (room.reserved) {
				cout << room.roomNumber << " ";
			}
		}
		cout << endl;
	}

	bool reserveRoom(int roomNumber, int nights) {
		for (auto& room : rooms) {
			if (room.roomNumber == roomNumber && !room.reserved) {
				room.reserved = true;
				room.nights = nights;
				return true;
			}
		}
		return false;
	}

	void displayBill() const {
		double totalAmount = 0.0;
		double discount = 0.0;
		for (const auto& room : rooms) {
			if (room.reserved) {
				discount = (rand() % 3) * 0.1; // Alennus 0%, 10% tai 20%
				double roomCost = room.isDoubleRoom ? 150.0 : 100.0;
				double discountedAmount = roomCost * room.nights * (1.0 - discount);
				totalAmount += discountedAmount;
			}
		}
		cout << "Loppusumma: " << totalAmount << " euroa.\n";
		if (discount == 0.0) {
			cout << "Arpaonni ei suosinut t‰ll‰ kertaa etk‰ saanut yht‰‰n alennusta...\n\n";
		}
		else if (discount == 0.1) {
			cout << "Hienoa sait 10% alennusta.\n\n";
		}
		else if (discount == 0.2) {
			cout << "Wau sait huiman 20% alennusta.\n\n";
		}
	}
};

/*int generateRandomNum(int min, int max) {
	return rand() % (max - min + 1) + min;
}*/

int main() {
	srand(time(0));
	
	hotelReservation hotel(0);

	//int totalRooms = generateRandomNum(40, 300);
	

	/*int singlePrice = 100;
	int doublePrice = 150;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distTotalRooms(40, 300);

	int totalRooms;
	do {
		totalRooms = distTotalRooms(gen);
	} while (totalRooms % 2 != 0); // Varmistetaan, ett‰ huoneiden m‰‰r‰ on parillinen

	hotelReservation hotel(totalRooms);
	
	int singleRooms = totalRooms / 2;
	int doubleRooms = totalRooms - singleRooms;*/
	
	//hotelReservation hotel(singleRooms, doubleRooms);
	
	int task;
	cout << "Tervetuloa (nimi) hotelliin!\n"
		<< "----------------------------\n\n";
	
	do {
		cout << "Lista toimminoista hotellihuoneen varaukseen (syˆt‰ numero v‰lilt‰ 1-4):\n"
			<< "Syˆt‰ 1 jos haluat varata huoneita.\n"
			<< "Syˆt‰ 2 jos haluat n‰hd‰ vapaana olevat huoneet.\n"
			<< "Syˆt‰ 3 jos haluat n‰hd‰ varatut huoneet.\n"
			<< "Syˆt‰ 4 jos haluat poistua ohjelmasta.\n"
			<< "----------\n"
			<< "Syˆte: ";
		cin >> task;
		cout << "----------\n";
		switch (task)
		{
		case 1:
			int roomNumber, nights;
			cout << "Syˆt‰ huoneen numero: ";
			cin >> roomNumber;
			cout << "Syˆt‰ ˆiden m‰‰r‰: ";
			cin >> nights;
			if (hotel.reserveRoom(roomNumber, nights)) {
				cout << "\nHuone varattu onnistuneesti.\n\n";
			}
			else {
				cout << "\nValittu huone on jo varattu tai ei ole saatavilla.\n\n";
			}
			break;
		case 2:
			/*cout << "Total rooms: " << totalRooms << endl;
			cout << "Single rooms: " << singleRooms << endl;
			cout << "Double rooms: " << doubleRooms << endl;*/
			hotel.displayAvailableRooms();
			//cout << "\ntoiminto 2\n\n";
			break;
		case 3:
			//hotel.displayBill();
			hotel.displayReservedRooms();
			//cout << "\ntoiminto 3\n\n";
			break;
		case 4:
			hotel.displayBill();
			cout << "\nHyv‰sti ja hyv‰‰ loppuel‰m‰‰...\n\n";
			break;
		default:
			cout << "\nKatoppa uuestaa!\n\n";
			break;
		}
	} while (task != 4);
		return 0;
}