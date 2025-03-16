/*
You are given:
1. Intern Class (internName, wantsRoommate - Boolean)
2. Apartment Class (apartmentId, numBedrooms)

Given lists of interns and apartments, design an algorithm to optimally assign interns to apartments while considering their roommate preferences and available bedrooms.
• “Optimal” is undefined, so you may define it logically.
• You can modify the Intern and Apartment classes.
• Apartments can have any number of bedrooms.
*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Intern class definition
class Intern {
public:
    string internName;
    bool wantsRoommate;

    Intern(string name, bool roommate) : internName(name), wantsRoommate(roommate) {}
};

// Apartment class definition
class Apartment {
public:
    string apartmentId;
    int numBedrooms;

    Apartment(string id, int bedrooms) : apartmentId(id), numBedrooms(bedrooms) {}
};

// Function to assign interns to apartments
vector<pair<string, vector<string>>> assignApartments(
    vector<Intern>& interns, 
    vector<Apartment>& apartments) {

    map<string, vector<string>> assignments; // apartmentID -> list of interns

    // Separate interns based on their roommate preferences
    vector<Intern> wantsRoommate;
    vector<Intern> noRoommate;
    
    for (const auto& intern : interns) {
        if (intern.wantsRoommate) {
            wantsRoommate.push_back(intern);
        } else {
            noRoommate.push_back(intern);
        }
    }
    
    // Sort apartments to prioritize multi-bedroom places first, then single-bedroom for those needing space alone
    sort(apartments.begin(), apartments.end(), [](const Apartment& a, const Apartment& b) {
        return a.numBedrooms < b.numBedrooms; // Ascending order, so single rooms can be filled last or by those that don't want roommates
    });

    // First, we assign interns who want roommates to larger apartments
    for (auto& apartment : apartments) {
        if (apartment.numBedrooms > 1) {
            int availableRooms = apartment.numBedrooms;
            for (auto it = wantsRoommate.begin(); it != wantsRoommate.end() && availableRooms > 0;) {
                assignments[apartment.apartmentId].push_back(it->internName);
                it = wantsRoommate.erase(it); // Assign and remove from the list
                availableRooms--;
            }
        }
    }

    // Now, assign interns who do not want roommates or still want roommates but have no one else to pair with 
    // to single-bedroom places, or remaining capacity in multi-bedroom places if needed
    for (auto& apartment : apartments) {
        if (apartment.numBedrooms == 1 || assignments[apartment.apartmentId].empty()) {
            int availableRooms = apartment.numBedrooms;
            for (auto it = noRoommate.begin(); it != noRoommate.end() && availableRooms > 0;) {
                assignments[apartment.apartmentId].push_back(it->internName);
                it = noRoommate.erase(it); // Assign and remove from the list
                availableRooms--;
            }
        }
    }

    // Collect the result for easy access
    vector<pair<string, vector<string>>> result;
    for (const auto& assignment : assignments) {
        result.emplace_back(assignment.first, assignment.second);
    }

    return result;
}

int main() {
    // Sample data
    vector<Intern> interns = {
        Intern("Alice", true),
        Intern("Bob", true),
        Intern("Charlie", false),
        Intern("David", false),
        Intern("Eva", true)
    };

    vector<Apartment> apartments = {
        Apartment("A1", 3),
        Apartment("A2", 2),
        Apartment("A3", 1)
    };

    vector<pair<string, vector<string>>> result = assignApartments(interns, apartments);
    
    // Print the assignments
    for (const auto& r : result) {
        cout << "Apartment " << r.first << ": ";
        for (const auto& intern : r.second) {
            cout << intern << " ";
        }
        cout << endl;
    }

    return 0;
}