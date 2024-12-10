# ADS-Project-2023
Milan Technical University's Algorithms and Data Structures project. 

# Highway Car Sharing API
This project, developed in 2023, is a C application that simulates a car-sharing system along a highway. The highway features multiple service areas, each with a fleet of electric cars with varying ranges. The system provides robust functionality for managing service stations and vehicles, with a core algorithm to find the most efficient travel routes, while respecting the memory usage and calculation time requirements.

## Key Features

### Service Station Management  
- **Add a service station:** Insert a new station at a specific point on the highway.  
- **Remove a service station:** Delete an existing station and update the system accordingly.  

### Electric Vehicle Management  
- **Add a vehicle:** Add a new electric car to a specified service station with its range.  
- **Remove a vehicle:** Remove a vehicle from a designated service station.  

### Optimal Route Search: `route_planner`  
The primary function of the system. It finds the best route between two stations, considering their positions along the highway.  
- Supports searching from a closer station to a farther one and vice versa.
- Optimizes the path with the least number of service stations passed.  
- Optimizes the path to pass through stations nearest to the highway's starting point (distance 0). This functionality is also applied when transversing from a farther station to a closer one.

### Used data structures:
- Service areas: modified binary tree.
- Cars in each service area: linked list.  


## Ranks Table
The project was a success as it respects the memory usage and the time requirements, and by a large margin.
| Rank | Memory | Time | Mark |  
|------|--------|------|------|  
| 18   | 128 Mib| 19 s |      |  
| 21   | 118 Mib| 15 s |      |
| 24   | 108 Mib| 10 s |      |
| 27   | 98 Mib | 6 s  |      |
| 30   | 88 Mib | 4 s  |      |
| 30L  | 78 Mib | 1 s  |  ✓   |
  
### How to run the project:
You can use the "project_tests_checker", copy all and paste in terminal what's inside "all_commands". The folder contains different .txt files:
| File name        | Description                                                       |
|------------------|-------------------------------------------------------------------|
|open_1.txt        |Contains all the official input commands for the program to run    |
|open_1.output.txt |Contains all the official outputs the program is supposed to print |
|open_1.testing.txt|Contains all the outputs the program currently prints when runs    |

In alternative follow these steps to try the program:

To get this repository:
```bash
git clone https://github.com/polimiJHuang/ADS-Project-2023.git
```
To compile the code:
```bash
gcc ADS_project.c -o ADS_project
```
To run the compiled code:
```bash
./ADS_project
```
