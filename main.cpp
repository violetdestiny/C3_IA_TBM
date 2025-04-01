#include "Board.h"
#include <iostream>
using namespace std;

int main() {
    Board board;
    int choice;

    do {
        cout << "\nBug Simulation Menu:\n"
                  << "1. Initialize Board\n"
                  << "2. Display All Bugs\n"
                  << "3. Find Bug\n"
                  << "4. Exit\n"
                  << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                board.initializeBoard("crawler-bugs.txt");
            cout << "Board initialized!\n";
            break;
            case 2:
                board.displayAllBugs();
            break;
            case 3: {
                int id;
                cout << "Enter bug ID: ";
                cin >> id;
                board.findBug(id);
                break;
            }
            case 4:
                cout << "Exiting...\n";
            break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 4);

    return 0;
}