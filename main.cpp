#include "Board.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;
int main() {
    Board board;
    int choice;

    do {
        cout << "\nBug Simulation Menu:\n"
             << "1. Initialize Board\n"
             << "2. Display All Bugs\n"
             << "3. Find Bug\n"
             << "4. Tap the Bug Board\n"
             << "5. Display Life History of all Bugs\n"
             << "6. Display all Cells listing their Bugs\n"
             << "7. Run simulation \n"
             << "8. Exit \n"
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
                if(!board.isInitialized()) {
                    cout << "Error: Initialize board first!\n";
                    break;
                }
                int id;
                cout << "Enter bug ID: ";
                cin >> id;
                board.findBug(id);
                break;
            }
            case 4:
                if(!board.isInitialized()) {
                    cout << "Error: Initialize board first!\n";
                    break;
                }
                board.tapBoard();
            break;
            case 5:
                if(!board.isInitialized()) {
                    cout << "Error: Initialize board first!\n";
                    break;
                }
                board.displayLifeHistory();
            break;
            case 6:
                board.displayAllCells();
            break;
            case 7: {
                if(!board.isInitialized()) {
                    cout << "Error: Initialize board first!\n";
                    break;
                }
                int taps;
                cout << "Enter number of taps: ";
                cin >> taps;
                board.runSimulation(taps);
                break;
            }
           case 8:
               if(board.isInitialized()) {
                   board.writeLifeHistoryToFile("bugs_life_history.out");
               }            cout << "Exiting...\n";
            break;

            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 8);

    return 0;
}