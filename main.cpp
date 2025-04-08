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
                << "8. Last Bug Standing\n"
                << "9. Exit \n"
                << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                board.initializeBoard("crawler-bugs.txt");
                cout << "Board initialized!\n";
                break;
            case 2:
                board.displayAllBugs();
                break;
            case 3: {
                if (!board.isInitialized()) {
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
                if (!board.isInitialized()) {
                    cout << "Error: Initialize board first!\n";
                    break;
                }
                board.tapBoard();
                cout << "Board tapped!\n";
                break;
            case 5:
                if (!board.isInitialized()) {
                    cout << "Error: Initialize board first!\n";
                    break;
                }
                board.displayLifeHistory();
                break;
            case 6:
                board.displayAllCells();
                break;
            case 7: {
                if (!board.isInitialized()) {
                    cout << "Error: Initialize board first!\n";
                    break;
                }
                int taps;
                cout << "Enter number of taps: ";
                cin >> taps;
                cout << "Tapping....\n";

                board.runSimulation(taps);
                if (taps == 1) {
                    cout << "Board taped once!\n";
                } else
                    cout << "Board taped " << taps << " times\n";
                break;
            }
            case 8: {
                if (!board.isInitialized()) {
                    cout << "Error: Initialize board first!\n";
                    break;
                }
                cout << "Running Battle Royale (10 second limit) ...\n\n";
                cout<< "!!!!!To maintain CONFIDENTIALITY of the bug champions, their history shall not be disclosed!!!!!\n What happens at bug arena stays at bug arena ;)"<<endl;
                auto [taps, winners] = board.runBattleRoyale();

                cout << "\n=== BATTLE RESULTS ===\n";
                cout << "Taps: " << taps << "\n";

                if (winners.size() > 0) {
                    cout << "1st: Bug " << winners[0].id << " (" << winners[0].type
                         << ") Size: " << winners[0].size << " Kills: " << winners[0].kills << "\n";
                }
                if (winners.size() > 1) {
                    cout << "2nd: Bug " << winners[1].id << " (" << winners[1].type
                         << ") Size: " << winners[1].size << " Kills: " << winners[1].kills << "\n";
                }
                if (winners.size() > 2) {
                    cout << "3rd: Bug " << winners[2].id << " (" << winners[2].type
                         << ") Size: " << winners[2].size << " Kills: " << winners[2].kills << "\n";
                }

                if (winners.size() > 0 && winners[0].kills == 0) {
                    cout << "Note: Battle ended by time limit\n";
                }
                break;
            }
            case 9:
                if (board.isInitialized()) {
                    board.writeLifeHistoryToFile("bugs_life_history.out");
                }
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 9);

    return 0;
}
