#include <iostream>
using namespace std;

int main() {
	int task;
	cout << "Tervetuloa (nimi) hotelliin!\n"
		<< "----------------------------\n\n";
	
	do {
		cout << "Lista toimminoista hotellihuoneen varaukseen (sy�t� numero v�lilt� 1-4):\n"
			<< "Toiminto 1\n"
			<< "Toiminto 2\n"
			<< "Toiminto 3\n"
			<< "Toiminto 4\n"
			<< "----------\n"
			<< "Sy�te: ";
		cin >> task;
		cout << "----------\n";
		switch (task)
		{
		case 1:
			cout << "\ntoiminto 1\n\n";
			break;
		case 2:
			cout << "\ntoiminto 2\n\n";
			break;
		case 3:
			cout << "\ntoiminto 3\n\n";
			break;
		case 4:
			cout << "\ntoiminto 4\n\n";
			break;
		default:
			cout << "\nKatoppa uuestaa!\n\n";
			break;
		}
	} while (task != 4);
		return 0;
}