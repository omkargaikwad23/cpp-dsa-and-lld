#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Entity class for Venue
class Venue {
public:
    string venueId;
    string name;
    string location;
    int maxCapacity;

    int startTime, endTime;

    Venue() {}

    Venue(string vid, string n, string loc, int cap) : venueId(vid), name(n), location(loc), maxCapacity(cap) {}
};

// Entity class for Event
class Event {
public:
    string eventId;
    string name;
    string venueId;
    string eventType;
    int maxParticipants;
    string startTime;
    string endTime;
    double ticketPrice;
    int currentBookings;

    Event() {}

    Event(string eid, string n, string vid, string etype, int maxPar, string start, string end, double price)
        : eventId(eid), name(n), venueId(vid), eventType(etype), maxParticipants(maxPar), 
          startTime(start), endTime(end), ticketPrice(price), currentBookings(0) {}
};


//
// services -> venueOperation, eventOperation, booking, trendingEvents
// utility -> searchById, displayEvent
// datatypes -> event, venue

// src -> 
// MVC

// OOP 
// Inhenritance

// Event (Superclass)
// ComedyEvent (SubClass)
// WeddingEvent ()

// SOLID 
// 
// curTime == startTime
// 


// Booking System
class BookingSystem {
    vector<Venue> venues;
    vector<Event> events;
    map<string, vector<string>> customerBookings; // Map from customerId to list of booked eventIds
    map<string, vector<string>> waitLists;        // Wait list for full events
    unordered_map<string, string> bookingToEvent; // Map bookingId to eventId

public:
    // Admin functions
    void addVenue(string id, string name, string location, int maxCapacity);
    void removeVenue(string id);
    void addEvent(string eId, string name, string vId, string eType, int maxParticipants, string start, string end, double price);
    void removeEvent(string eId);

    // Customer functions
    vector<Event> searchByEventType(string eType);
    vector<Event> searchByEventType(string eType, string sortType);
    vector<Event> getAllEvents(string venueId);
    string bookEvent(string customerId, string eventId);
    vector<string> getAllBookings(string customerId);
    bool cancelBooking(string bookingId);
    vector<Event> trendingEvents(int topN);

    // Utility functions
    Venue* findVenueById(string vId);
    Event* findEventById(string eId);
    void displayEvent(const Event& event);
    void displayBookings(const vector<string>& bookings);
    void cancelAllBookingsForEvent(string eId);
};

void BookingSystem::addVenue(string id, string name, string location, int maxCapacity) {
    if (findVenueById(id)) {
        cout << "Venue ID already exists!" << endl;
        return;
    }
    venues.emplace_back(id, name, location, maxCapacity);
    cout << "Venue " << name << " added to " << location << endl;
}

void BookingSystem::removeVenue(string id) {
    auto it = remove_if(venues.begin(), venues.end(), [&id](const Venue& v) {
        return v.venueId == id;
    });

    vector<string> eventsToRemove;

    if (it != venues.end()) {
        // Remove all events associated with this venue
        for (const auto& event : events) {
            if (event.venueId == id) {
                eventsToRemove.push_back(event.eventId);
            }
        }
        for (const auto& eventId : eventsToRemove) {
            removeEvent(eventId);
        }

        venues.erase(it, venues.end());
        cout << "Venue " << id << " removed." << endl;
    } else {
        cout << "Venue ID not found!" << endl;
    }
}

void BookingSystem::addEvent(string eId, string name, string vId, string eType, int maxParticipants, string start, string end, double price) {
    if (findEventById(eId)) {
        cout << "Event ID already exists!" << endl;
        return;
    }
    // v1 -> (vt1, vt2)
    // 
    

    // e -> startTime, endTime
    // basedParamter -> methodOverloading 

    Venue* venue = findVenueById(vId);
    if (!venue) {
        cout << "Venue ID not found!" << endl;
        return;
    }

    if (maxParticipants > venue->maxCapacity) {
        cout << "Event exceeds venue capacity!" << endl;
        return;
    }

    events.emplace_back(eId, name, vId, eType, maxParticipants, start, end, price);
    cout << "Created an event: " << eId << " at the venue: " << vId << endl;
}

void BookingSystem::removeEvent(string eId) {
    auto it = remove_if(events.begin(), events.end(), [&eId](const Event& e) {
        return e.eventId == eId;
    });

    if (it != events.end()) {
        events.erase(it, events.end());
        cancelAllBookingsForEvent(eId);
        waitLists.erase(eId);
        cout << "Event " << eId << " removed." << endl;
    } else {
        cout << "Event ID not found!" << endl;
    }
}

vector<Event> BookingSystem::searchByEventType(string eType) {
    vector<Event> result;
    for (const auto& e : events) {
        if (e.eventType == eType) {
            result.push_back(e);
        }
    }
    for (const auto& e : result) {
        displayEvent(e);
    }
    return result;
}

vector<Event> BookingSystem::searchByEventType(string eType, string sortType) {
    vector<Event> result = searchByEventType(eType);

    if (sortType == "earliest") {
        sort(result.begin(), result.end(), [](const Event& e1, const Event& e2) {
            return e1.startTime < e2.startTime;
        });
    } else if (sortType == "price") {
        sort(result.begin(), result.end(), [](const Event& e1, const Event& e2) {
            return e1.ticketPrice < e2.ticketPrice;
        });
    }

    for (const auto& e : result) {
        displayEvent(e);
    }
    return result;
}

vector<Event> BookingSystem::getAllEvents(string venueId) {
    vector<Event> result;
    for (const auto& e : events) {
        if (e.venueId == venueId) {
            displayEvent(e);
            result.push_back(e);
        }
    }
    return result;
}


/*
Sharding

*/

string BookingSystem::bookEvent(string customerId, string eventId) {
    Event* event = findEventById(eventId);

    // get venuename using eventId
    // get their blocked timeslots for this venue
    // if user wants to book a ticket in the same timeslot, 

    // not allow to create event during that timeslot
    // 1. move event to another timeslot 
    // 2. cancel event due to time constaint 

    if (!event) {
        cout << "Event ID not found!" << endl;
        return "";
    }

    if (event->currentBookings >= event->maxParticipants) {
        cout << "Event is fully booked." << endl;
        waitLists[eventId].push_back(customerId);
        cout << "Added to wait list." << endl;
        return "";
    }

    event->currentBookings++;
    string bookingId = customerId + "_" + eventId + "_" + to_string(event->currentBookings);
    customerBookings[customerId].push_back(bookingId);
    bookingToEvent[bookingId] = eventId;
    cout << "Booking Success with Booking ID: " << bookingId << endl;
    return bookingId;
}

vector<string> BookingSystem::getAllBookings(string customerId) {
    const auto& bookings = customerBookings[customerId];
    displayBookings(bookings);
    return bookings;
}

bool BookingSystem::cancelBooking(string bookingId) {
    auto it = bookingToEvent.find(bookingId);
    if (it == bookingToEvent.end()) {
        cout << "Booking ID not found!" << endl;
        return false;
    }

    string eventId = it->second;
    Event* event = findEventById(eventId);
    if(event) {
        event->currentBookings--;
        if (!waitLists[eventId].empty()) {
            string firstInLine = waitLists[eventId].front();
            waitLists[eventId].erase(waitLists[eventId].begin());
            bookEvent(firstInLine, eventId);
            cout << "Booking moved from waitlist." << endl;
        }
    }

    bookingToEvent.erase(it);

    for (auto& pair : customerBookings) {
        auto& bookings = pair.second;
        bookings.erase(remove(bookings.begin(), bookings.end(), bookingId), bookings.end());
    }
    cout << "Cancelled booking: " << bookingId << endl;
    return true;
}


vector<Event> BookingSystem::trendingEvents(int topN) {
    vector<Event> copy = events; // Work on a copy for sorting

    sort(copy.begin(), copy.end(), [](const Event& e1, const Event& e2) {
        return (e1.currentBookings / (double)e1.maxParticipants) > (e2.currentBookings / (double)e2.maxParticipants);
    });

    copy.resize(min(topN, static_cast<int>(copy.size())));
    for (const auto& e : copy) {
        displayEvent(e);
    }
    return copy; 
}


Venue* BookingSystem::findVenueById(string vId) {
    for (auto& venue : venues) {
        if (venue.venueId == vId) {
            return &venue;
        }
    }
    return nullptr;
}

// O(n) time complexity for finding event by id, can be improved to O(1) using unordered_map
Event* BookingSystem::findEventById(string eId) {
    for (auto& event : events) {
        if (event.eventId == eId) {
            return &event;
        }
    }
    return nullptr;
}

void BookingSystem::displayEvent(const Event& event) {
    cout << "Event ID: " << event.eventId 
         << ", Name: " << event.name 
         << ", Type: " << event.eventType 
         << ", Venue: " << event.venueId 
         << ", Start: " << event.startTime 
         << ", End: " << event.endTime 
         << ", Price: " << event.ticketPrice 
         << ", Bookings: " << event.currentBookings << "/" << event.maxParticipants << endl;
}

void BookingSystem::displayBookings(const vector<string>& bookings) {
    for (const auto& bookingId : bookings) {
        auto it = bookingToEvent.find(bookingId);
        if (it != bookingToEvent.end()) {
            Event* event = findEventById(it->second);
            if (event) {
                cout << "Booking ID: " << bookingId << ", Venue: " << event->venueId 
                     << ", Event: " << event->name 
                     << ", Time: " << event->startTime << " - " << event->endTime << endl;
            }
        }
    }
}

void BookingSystem::cancelAllBookingsForEvent(string eId) {
    for (auto it = bookingToEvent.begin(); it != bookingToEvent.end(); ) {
        if (it->second == eId) {
            it = bookingToEvent.erase(it);
        } else {
            ++it;
        }
    }
    for (auto& pair : customerBookings) {
        auto& bookings = pair.second;
        bookings.erase(remove_if(bookings.begin(), bookings.end(), [&](const string& bookingId) {
            return bookingToEvent.find(bookingId) == bookingToEvent.end();
        }), bookings.end());
    }
    waitLists.erase(eId);
}

void adminFlow(BookingSystem& system) {
    int choice;
    do {
        cout << "\nAdmin Menu:\n1. Add Venue\n2. Remove Venue\n3. Add Event\n4. Remove Event\n5. Exit Admin\n>>Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid choice. Try again." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                string id, name, location;
                int maxCapacity;
                cout << "Enter Venue ID, Name, Location, Max Capacity: ";
                cin >> id >> name >> location >> maxCapacity;
                system.addVenue(id, name, location, maxCapacity);
                break;
            }
            case 2: {
                string id;
                cout << "Enter Venue ID: ";
                cin >> id;
                system.removeVenue(id);
                break;
            }
            case 3: {
                string eId, name, vId, eType, start, end;
                int maxParticipants;
                double price;
                cout << "Enter Event ID, Name, Venue ID, Type, Max Participants, Start Time, End Time, Ticket Price: ";
                cin >> eId >> name >> vId >> eType >> maxParticipants >> start >> end >> price;
                system.addEvent(eId, name, vId, eType, maxParticipants, start, end, price);
                break;
            }
            case 4: {
                string eId;
                cout << "Enter Event ID: ";
                cin >> eId;
                system.removeEvent(eId);
                break;
            }
            case 5:
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);
}

void customerFlow(BookingSystem& system) {
    int choice;
    do {
        cout << "\nCustomer Menu:\n1. Search Events by Type\n2. View All Events\n3. Book Event\n4. View My Bookings\n5. Cancel Booking\n6. Trending Events\n7. Exit Customer\n>>Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid choice. Try again." << endl;
            continue;
        }


        switch (choice) {
            case 1: {
                string eType;
                cout << "Enter Event Type: ";
                cin >> eType;
                system.searchByEventType(eType);
                break;
            }
            case 2: {
                string vId;
                cout << "Enter Venue ID: ";
                cin >> vId;
                system.getAllEvents(vId);
                break;
            }
            case 3: {
                string cId, eId;
                cout << "Enter Customer ID and Event ID: ";
                cin >> cId >> eId;
                system.bookEvent(cId, eId);
                break;
            }
            case 4: {
                string cId;
                cout << "Enter Customer ID: ";
                cin >> cId;
                system.getAllBookings(cId);
                break;
            }
            case 5: {
                string bId;
                cout << "Enter Booking ID: ";
                cin >> bId;
                system.cancelBooking(bId);
                break;
            }
            case 6: {
                int topN;
                cout << "Enter number of top events: ";
                cin >> topN;
                system.trendingEvents(topN);
                break;
            }
            case 7:
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
    } while (choice != 7);
}

int main() {
    BookingSystem system;
    int userType;

    cout << "\nWelcome to Event Booking System!\n" << endl;

    do {
        cout << "\nSelect User Type:\n1. Admin\n2. Customer\n3. Exit\n>>Enter choice: ";
        cin >> userType;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (userType) {
            case 1:
                adminFlow(system);
                break;
            case 2:
                customerFlow(system);
                break;
            case 3:
                cout << "Exiting the system." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
    } while (userType != 3);

    return 0;
}


/*
RACE

Semaphore, mutex

API: 

trendingEvents -> redis
searchEvents -> recom

100 -> 1 million





To run:

omkar@L1819 System-Design-DSA % g++ -std=c++11 event_booking_system.cpp -o event_booking_system  
omkar@L1819 System-Design-DSA % ./event_booking_system   

-------------------------------
>> Enter Venue ID, Name, Location, Max Capacity:
vid_1 SarjapurSocial Bengaluru 2


>> Enter Event ID, Name, Venue ID, Type, Max Participants, Start Time, End Time, Ticket Price
eid_1 MaiSamayHoon vid_1 StandUp 2 19:00 21:00 500
eid_2 KBC vid_1 StandUp 2 19:00 21:00 150

cid_1 eid_1 -> Booking Success with Booking ID: cid_1_eid_1_1
cid_1 eid_1 -> Booking Success with Booking ID: cid_1_eid_1_2
cid_2 eid_1 -> added to waitlist

cancel booking -> cid_1_eid_1_1 -> added cid_2 eid_1 from waitlist (cid_2_eid_1_2)

Booking ID: cid_1_eid_2_1, Venue: vid_1, Event: KBC, Time: 19:00 - 21:00
Booking ID: cid_1_eid_2_2, Venue: vid_1, Event: KBC, Time: 19:00 - 21:00
-------------------------------

Event Venue Booking System
We have a chain of event venues in a city that need to move from offline to online management. The online portal will allow admins to manage venues and events, while customers can browse and book event spaces.

Admin Flows:
addVenue(venue_id, name, location, max_capacity): The admin can add a venue to the system. The max_capacity represents the maximum number of people allowed in the venue at any time. A venue can host multiple events at any time during the day.
removeVenue(venue_id): Admin can remove a venue from the system, which will also cancel all events scheduled at that venue.
addEvent(event_id, name, venue_id, event_type, max_participants, start_time, end_time, ticket_price): Admin can add events to a venue. Each event is associated with an event_type (e.g., wedding, conference, standup) and has a max_participants limit. The event will occur at a specific start_time and end_time, and the total capacity of the venue should not be exceeded by the total participants of all events at any given time.
removeEvent(event_id): Admin can remove an event, canceling all reservations for that event.

Customer Flows:
searchByEventType(event_type): Customers can search for venues hosting a particular event_type.
getAllEvents(venue_id): Customers can view all the events scheduled at a particular venue.
bookEvent(customer_id, event_id): Customers can book a spot at an event. If the event is full, the booking should not be allowed.
trendingEvents(top_N): Shows top N events, sorted by % of total booked
getAllBookings(customer_id): Customers can view all events they’ve booked.
cancelBooking(customer_id, booking_id): Customers can cancel an event booking.

Bonus features:
Waiting List for Full Events: If an event is fully booked, customers can be added to a waiting list. If someone cancels, the first person in the waiting list is automatically booked for the event.
searchByEventType(event_type, sortType): The sortType parameter allows sorting results by various criteria (earliest event, price).

Sample Test Case:
>addVenue(v_id_001, SarjapurSocial, Bengaluru, 200)
>> Venue SarjapurSocial added to Bengaluru
> addEvent(e_id_001, MaiSamayHoon, v_id_001, StandUp, 100, 19:00, 21:00, 500)
>> Created an event: e_id_001 at the venue: v_id_001
> bookEvent(c_id_001, e_id_001)
>> Booking Success
> getAllBookings(c_id_001)
>> c_id_001: booking at venue SarjapurSocial, Bengaluru for the event MaiSamayHoon from 19:00 to 21:00

Guidelines:
No user/admin authentication.
Input/Output should be handled through files or STDIN/STDOUT.
Use in-memory storage for all data.
Ensure error handling and edge cases are managed appropriately.
Object-Oriented Design: Use classes and encapsulation to manage entities. Make the system modular, extensible, and easily testable.
No databases should be used.
Ensure the system is extensible enough to add or remove functionality without major rewrites.
Expectations:
The code should be demo-able and easy to follow.
The code should be functionally correct.
Proper exception handling should be in place to deal with invalid operations.
The design should be modular, testable, and extensible.
Class and method names should be intuitive and readable.



Missing:
1. when venue is removed by admin, all the events should be deleted and all the bookings must be cancelled. 
2. Haven't considered booking id
3. can't cancel the booking currently.
*/


