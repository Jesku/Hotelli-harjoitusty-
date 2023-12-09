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
			cout << "Arpaonni ei suosinut tällä kertaa etkä saanut yhtään alennusta...\n\n";
		}
		else if (discount == 0.1) {
			cout << "Hienoa sait 10% alennusta.\n\n";
		}
		else if (discount == 0.2) {
			cout << "Wau sait huiman 20% alennusta.\n\n";
		}
	}
};

int main() {
	srand(time(0));
	
	hotelReservation hotel(0);
	
	int task;
	cout << "Tervetuloa (nimi) hotelliin!\n"
		<< "----------------------------\n\n";
	
	do {
		cout << "Lista toimminoista hotellihuoneen varaukseen (syötä numero väliltä 1-4):\n"
			<< "Syötä 1 jos haluat varata huoneita.\n"
			<< "Syötä 2 jos haluat nähdä vapaana olevat huoneet.\n"
			<< "Syötä 3 jos haluat nähdä varatut huoneet.\n"
			<< "Syötä 4 jos haluat poistua ohjelmasta.\n"
			<< "----------\n"
			<< "Syöte: ";
		cin >> task;
		cout << "----------\n";
		switch (task)
		{
		case 1:
			int roomNumber, nights;
			cout << "Syötä huoneen numero: ";
			cin >> roomNumber;
			cout << "Syötä öiden määrä: ";
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
			hotel.displayReservedRooms();
			//cout << "\ntoiminto 3\n\n";
			break;
		case 4:
			hotel.displayBill();
			cout << "\nHyvästi ja hyvää loppuelämää...\n\n";
			break;
		default:
			cout << "\nKatoppa uuestaa!\n\n";
			break;
		}
	} while (task != 4);
		return 0;
}