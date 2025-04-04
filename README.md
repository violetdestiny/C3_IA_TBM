# A Bug's Life - Bug Board Simulation 🐜

![C++](https://img.shields.io/badge/C++-17-blue.svg) 
![License](https://img.shields.io/badge/License-MIT-green.svg)  
*A 10x10 grid-based simulation of competitive bug movement and survival*

## 📜 Description
This C++ console application simulates the movement and interactions of "Crawler" bugs on a 10x10 grid. Bugs move according to directional rules, fight when colliding, and grow in size until only one survivor remains. Developed as part of a Semester 2 Continuous Assessment for B.Sc. Computing programs.

Key Features:
- 🎮 Console-based UI with 8 interactive menu options
- 📂 File I/O for bug initialization and life history logging
- ⚔️ Collision resolution with size-based dominance
- 🕹️ Real-time simulation mode (10 taps/second)
- 📊 Detailed tracking of bug paths and cell occupancy

## 🚀 Features
1. **Initialize Bug Board**: Load bug data from `crawler-bugs.txt`
2. **Display All Bugs**: Show ID, position, direction, size, and status
3. **Find Bug by ID**: Search and display individual bug details
4. **Tap Board**: Trigger movement and combat resolution
5. **Life History**: Display complete movement paths
6. **Cell Occupancy**: Show bugs in each grid cell
7. **Auto Simulation**: Run automated taps every 0.1s
8. **Exit & Save**: Write life history to timestamped file

## 🛠️ Installation
1. Clone repository:
   ```bash
   git clone https://github.com/yourusername/bugs-life-simulation.git
   
2. Compile with C++17 support:
`g++ -std=c++17 *.cpp -o bugs_simulation`

3. Run executable:
   `./bugs_simulation`

## 🎮 Usage
```MAIN MENU
1. Initialize Board
2. Display All Bugs
3. Find Bug by ID
4. Tap Board
5. Display Life History
6. Show Cell Occupancy
7. Run Simulation
8. Exit

（づ￣3￣）づ╭❤️～
