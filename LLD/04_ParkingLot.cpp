/*
================================================================================
                    LOW-LEVEL DESIGN: PARKING LOT SYSTEM
================================================================================

PROBLEM:
  Design a parking lot system that can handle multiple floors, different
  vehicle types, and various parking spot sizes.

REQUIREMENTS:
  1. Multiple floors, each with multiple parking spots
  2. Different vehicle types: Bike, Car, Truck
  3. Different spot sizes: Small (bike), Medium (car), Large (truck)
  4. Vehicle can only park in a spot of matching or larger size
  5. Find nearest available spot for a vehicle
  6. Track entry/exit time, calculate parking fee
  7. Display available spots per floor and type

DESIGN PATTERNS:
  - Strategy Pattern: Different pricing strategies (hourly, daily, flat)
  - Enum Types: VehicleType, SpotSize, TicketStatus
  - Factory (optional): Create appropriate spot for vehicle type

CLASSES:
  Vehicle         - base class (type, license plate)
  ParkingSpot     - spot on a floor (size, availability, assigned vehicle)
  ParkingFloor    - collection of spots on one floor
  ParkingTicket   - entry time, exit time, fee
  ParkingLot      - main controller (floors, entry/exit, fee calculation)
  PricingStrategy - interface for fee calculation

================================================================================
                              TODO: IMPLEMENT
================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// ENUMS
// ═══════════════════════════════════════════════════════════════════════════

enum class VehicleType { BIKE, CAR, TRUCK };
enum class SpotSize { SMALL, MEDIUM, LARGE };
enum class TicketStatus { ACTIVE, PAID };

// ═══════════════════════════════════════════════════════════════════════════
// VEHICLE
// ═══════════════════════════════════════════════════════════════════════════

class Vehicle {
    string licensePlate;
    VehicleType type;

public:
    Vehicle(const string& plate, VehicleType type)
        : licensePlate(plate), type(type) {}

    string getLicensePlate() const { return licensePlate; }
    VehicleType getType() const { return type; }
};

// ═══════════════════════════════════════════════════════════════════════════
// PARKING SPOT
// ═══════════════════════════════════════════════════════════════════════════

class ParkingSpot {
    int spotId;
    SpotSize size;
    bool occupied;
    Vehicle* parkedVehicle;

public:
    ParkingSpot(int id, SpotSize size)
        : spotId(id), size(size), occupied(false), parkedVehicle(nullptr) {}

    bool isAvailable() const { return !occupied; }
    SpotSize getSize() const { return size; }
    int getId() const { return spotId; }

    bool canFit(VehicleType vType) const {
        // TODO: Implement — vehicle can park in same-size or larger spot
        return false;
    }

    void parkVehicle(Vehicle* vehicle) {
        // TODO: Implement
    }

    void removeVehicle() {
        // TODO: Implement
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// PARKING FLOOR
// ═══════════════════════════════════════════════════════════════════════════

class ParkingFloor {
    int floorNumber;
    vector<ParkingSpot> spots;

public:
    ParkingFloor(int floor, int numSmall, int numMedium, int numLarge) : floorNumber(floor) {
        // TODO: Initialize spots of each size
    }

    ParkingSpot* findAvailableSpot(VehicleType vType) {
        // TODO: Find first available spot that fits the vehicle
        return nullptr;
    }

    int getAvailableCount(SpotSize size) const {
        // TODO: Count available spots of given size
        return 0;
    }

    void displayStatus() const {
        // TODO: Print available/total for each spot size
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// PARKING TICKET
// ═══════════════════════════════════════════════════════════════════════════

class ParkingTicket {
    string ticketId;
    string licensePlate;
    int floorNumber;
    int spotId;
    time_t entryTime;
    time_t exitTime;
    TicketStatus status;

public:
    ParkingTicket(const string& id, const string& plate, int floor, int spot)
        : ticketId(id), licensePlate(plate), floorNumber(floor), spotId(spot),
          entryTime(time(nullptr)), exitTime(0), status(TicketStatus::ACTIVE) {}

    void markExit() {
        // TODO: Set exit time and calculate duration
    }

    double calculateFee(double ratePerHour) const {
        // TODO: Calculate fee based on duration
        return 0.0;
    }

    void display() const {
        // TODO: Print ticket details
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// PARKING LOT - MAIN CONTROLLER
// ═══════════════════════════════════════════════════════════════════════════

class ParkingLot {
    string name;
    vector<ParkingFloor> floors;
    unordered_map<string, ParkingTicket> activeTickets; // licensePlate -> ticket

public:
    ParkingLot(const string& name, int numFloors) : name(name) {
        // TODO: Initialize floors with default spot configuration
    }

    ParkingTicket* parkVehicle(Vehicle& vehicle) {
        // TODO: Find spot across floors, create ticket, park vehicle
        return nullptr;
    }

    double unparkVehicle(const string& licensePlate) {
        // TODO: Find ticket, calculate fee, free spot
        return 0.0;
    }

    void displayAvailability() const {
        // TODO: Show availability per floor
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN - DEMO
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // TODO: Create parking lot, park/unpark vehicles, display status

    cout << "===== PARKING LOT SYSTEM =====" << endl;
    cout << "(Stub — implement the TODOs above)" << endl;

    return 0;
}

/*
================================================================================
                         DESIGN NOTES
================================================================================

PRICING STRATEGIES (Strategy Pattern):
  - HourlyPricing: rate per hour (default)
  - FlatRatePricing: fixed rate regardless of duration
  - DailyPricing: rate per day with hourly overflow

EXTENSIBILITY:
  - EV charging spots (new SpotSize or subclass)
  - Handicap-accessible spots
  - Reservation system
  - Multiple entry/exit gates with concurrency

RELATED PROBLEMS:
  - LeetCode 1603: Design Parking System (simplified version)

================================================================================
*/
