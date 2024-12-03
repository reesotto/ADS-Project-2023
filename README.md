# DSA-Project-2023
Milan Technical University's project

# Highway Car Sharing API
This project, developed in 2023, is a C application that simulates a car-sharing system along a highway. The highway features multiple service areas, each with a fleet of electric cars with varying ranges. The system provides robust functionality for managing service stations and vehicles, with a core algorithm to find the most efficient travel routes, while respecting the memory usage and calculation speed requirements.

## Key Features

### Service Station Management  
- **Add a service station:** Insert a new station at a specific point on the highway.  
- **Remove a service station:** Delete an existing station and update the system accordingly.  

### Electric Vehicle Management  
- **Add a vehicle:** Add a new electric car to a specified service station with its range.  
- **Remove a vehicle:** Remove a vehicle from a designated service station.  

### Optimal Route Search: `pathfinder`  
The primary function of the system. It finds the best route between two stations, considering their positions along the highway.  
- Supports searching from a closer station to a farther one and vice versa.
- Optimizes the path with the least number of service stations passed.  
- Optimizes the path to pass through stations nearest to the highway's starting point (distance 0).  

## Ranks Table

| Rank | Mark |  
|------|------|  
| 18   |      |  
| 21   |      |  
| 24   |      |  
| 27   |      |  
| 30   |      |  
| 30L  |  ✔   | 
  
##How to run the project:

To get this repository:
```bash
git clone https://github.com/polimiJHuang/DSA-Project-2023.git
```
To compile the code:
```bash
gcc DSA_project.c -o DSA_project
```
To run the compiled code:
```bash
./DSA_project
```
