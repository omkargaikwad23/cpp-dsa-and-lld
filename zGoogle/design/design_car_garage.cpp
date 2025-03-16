#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

/*

Designing a garage system involves several components beyond just tracking the number of cars. We need to consider the following elements in our design:

Garage Capacity : Ensuring no more cars are parked than the capacity allows.
Day Checks : Handling the transition between days and possibly different rates or rules based on the day of the week.
Parking Fee Calculation : Calculating the fees based on the duration of parking and potentially other factors.
Design Components
1. Data Structures
Car Event : Maintain arrival and departure times, and optionally car ID.
Garage State : Holds the current state of the garage (e.g., number of parked cars).
Event Queue : For sorting and processing events by time.
2. Functional Components
Event Handling : Process arrival and departure events:
Arrival : Check capacity, mark car as parked.
Departure : Mark car as departed, calculate parking fee.
Capacity Management : Ensure that the garage doesn't exceed its capacity at any point.
Fee Calculation : Based on parking time. Could use:
A fixed hourly rate.
Different rates for different times/days.
Day Management : Check if events span across different days, which might involve different fees or rules.
Implementation Guide
Define Data Structures :
struct Event for arrival and departure.
struct Car to store details and fee calculations.
Garage Class : Manages state and operations.
Event Processing :
Sort events by time ('D' should come before 'A' if times are the same to handle edge cases).
Fee Calculation Logic : Could involve checking total hours, days, or specific rules.
*/

struct Event {
    int time;
    char type; // 'A' for arrival, 'D' for departure
    int carID;
};

class Garage {
public:
    Garage(int capacity) : capacity(capacity), currentCars(0) {}

    void processEvents(const vector<Event>& events) {
        for (const auto& event : events) {
            if (event.type == 'A') {
                handleArrival(event);
            } else if (event.type == 'D') {
                handleDeparture(event);
            }
        }
    }

    void handleArrival(const Event& event) {
        if (currentCars < capacity) {
            currentCars++;
            parkedCars[event.carID] = event.time; // Store arrival time
            cout << "Car " << event.carID << " parked at time " << event.time << endl;
        } else {
            cout << "Car " << event.carID << " denied entry. Garage full." << endl;
        }
    }

    void handleDeparture(const Event& event) {
        if (parkedCars.find(event.carID) != parkedCars.end()) {
            currentCars--;
            int arrivalTime = parkedCars[event.carID];
            parkedCars.erase(event.carID);
            int fee = calculateFee(arrivalTime, event.time);
            cout << "Car " << event.carID << " departed at time " << event.time << ". Fee: $" << fee << endl;
        }
    }

    int calculateFee(int startTime, int endTime) {
        int duration = endTime - startTime;
        int fee = (duration / 60) * hourlyRate; // example calculation per hour
        return fee;
    }

private:
    int capacity;
    int currentCars;
    map<int, int> parkedCars; // carID -> arrivalTime
    const int hourlyRate = 10; // Example rate
};

int main() {
    vector<Event> events = {
        {10, 'A', 1},
        {50, 'A', 2},
        {70, 'D', 1},
        {100, 'A', 3}
    };

    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        if (a.time == b.time) return a.type < b.type; // Departures before Arrivals
        return a.time < b.time;
    });

    Garage garage(2);
    garage.processEvents(events);

    return 0;
}