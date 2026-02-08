/*
================================================================================
                    LOW-LEVEL DESIGN: ELEVATOR SYSTEM
================================================================================

PROBLEM:
  Design an elevator system for a building with multiple elevators
  serving multiple floors.

REQUIREMENTS:
  1. Multiple elevators in a building
  2. Handle up/down requests from any floor (external buttons)
  3. Handle floor selection from inside an elevator (internal buttons)
  4. Efficient scheduling: minimize wait time and travel distance
  5. Display current status of all elevators
  6. Handle edge cases: door open/close, overweight, emergency

DESIGN PATTERNS:
  - State Pattern: Elevator states (IDLE, MOVING_UP, MOVING_DOWN, DOOR_OPEN)
  - Strategy Pattern: Different scheduling algorithms (FCFS, SCAN, LOOK)
  - Observer Pattern: Notify display panels when elevator state changes

CLASSES:
  Request          - floor number, direction (UP/DOWN)
  Elevator         - current floor, state, pending requests, move logic
  ElevatorController - scheduling, dispatching requests to elevators
  Building         - collection of elevators, external request handling

================================================================================
                              TODO: IMPLEMENT
================================================================================
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// ENUMS
// ═══════════════════════════════════════════════════════════════════════════

enum class Direction { UP, DOWN, IDLE };
enum class ElevatorState { IDLE, MOVING_UP, MOVING_DOWN, DOOR_OPEN };

// ═══════════════════════════════════════════════════════════════════════════
// REQUEST
// ═══════════════════════════════════════════════════════════════════════════

class Request {
    int floor;
    Direction direction;

public:
    Request(int floor, Direction dir) : floor(floor), direction(dir) {}

    int getFloor() const { return floor; }
    Direction getDirection() const { return direction; }
};

// ═══════════════════════════════════════════════════════════════════════════
// ELEVATOR
// ═══════════════════════════════════════════════════════════════════════════

class Elevator {
    int id;
    int currentFloor;
    ElevatorState state;
    set<int> upStops;    // Floors to stop at going up (sorted ascending)
    set<int> downStops;  // Floors to stop at going down (sorted descending)

public:
    Elevator(int id) : id(id), currentFloor(0), state(ElevatorState::IDLE) {}

    int getId() const { return id; }
    int getCurrentFloor() const { return currentFloor; }
    ElevatorState getState() const { return state; }

    void addStop(int floor) {
        // TODO: Add floor to appropriate stop set based on direction
    }

    void moveOneStep() {
        // TODO: Move one floor in current direction, check for stops
    }

    bool isIdle() const {
        // TODO: Return true if no pending stops
        return false;
    }

    int distanceTo(int floor) const {
        // TODO: Calculate distance considering current direction and stops
        return 0;
    }

    void displayStatus() const {
        string stateStr;
        switch (state) {
            case ElevatorState::IDLE: stateStr = "IDLE"; break;
            case ElevatorState::MOVING_UP: stateStr = "UP"; break;
            case ElevatorState::MOVING_DOWN: stateStr = "DOWN"; break;
            case ElevatorState::DOOR_OPEN: stateStr = "DOOR_OPEN"; break;
        }
        cout << "Elevator " << id << ": Floor " << currentFloor
             << " [" << stateStr << "]" << endl;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// ELEVATOR CONTROLLER - SCHEDULING & DISPATCH
// ═══════════════════════════════════════════════════════════════════════════

class ElevatorController {
    vector<Elevator> elevators;

public:
    ElevatorController(int numElevators) {
        for (int i = 0; i < numElevators; i++) {
            elevators.emplace_back(i);
        }
    }

    Elevator* findBestElevator(const Request& request) {
        // TODO: Implement LOOK/SCAN algorithm
        // Prefer: idle elevator on same floor > elevator moving toward request
        //       > nearest idle elevator
        return nullptr;
    }

    void handleExternalRequest(int floor, Direction dir) {
        // TODO: Find best elevator and assign the request
    }

    void handleInternalRequest(int elevatorId, int floor) {
        // TODO: Add stop to specific elevator
    }

    void step() {
        // TODO: Move all elevators one step (simulate time tick)
    }

    void displayStatus() const {
        cout << "\n--- Elevator Status ---" << endl;
        for (const auto& e : elevators) {
            e.displayStatus();
        }
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// BUILDING
// ═══════════════════════════════════════════════════════════════════════════

class Building {
    int numFloors;
    ElevatorController controller;

public:
    Building(int floors, int numElevators)
        : numFloors(floors), controller(numElevators) {}

    void pressUpButton(int floor) {
        // TODO: Create external request with Direction::UP
    }

    void pressDownButton(int floor) {
        // TODO: Create external request with Direction::DOWN
    }

    void pressFloorButton(int elevatorId, int floor) {
        // TODO: Create internal request
    }

    void simulate(int steps) {
        // TODO: Run simulation for N steps
    }

    void displayStatus() const {
        controller.displayStatus();
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN - DEMO
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // TODO: Create building, simulate elevator requests

    cout << "===== ELEVATOR SYSTEM =====" << endl;
    cout << "(Stub — implement the TODOs above)" << endl;

    return 0;
}

/*
================================================================================
                         DESIGN NOTES
================================================================================

SCHEDULING ALGORITHMS:
  - FCFS: First come first serve (simple but inefficient)
  - SCAN (Elevator Algorithm): Move in one direction, serve all requests,
    then reverse. Like a disk arm.
  - LOOK: Like SCAN but reverses when no more requests in current direction
    (no need to go to the end)

STATE TRANSITIONS:
  IDLE -> MOVING_UP/DOWN (on receiving request)
  MOVING_UP/DOWN -> DOOR_OPEN (on reaching a stop)
  DOOR_OPEN -> MOVING_UP/DOWN (after door timeout, if more stops)
  DOOR_OPEN -> IDLE (if no more stops)

EXTENSIBILITY:
  - VIP/Express elevator (skips certain floors)
  - Weight sensor (refuse if overloaded)
  - Emergency mode (all elevators go to ground floor)
  - Multiple scheduling strategies (swap via Strategy pattern)

================================================================================
*/
