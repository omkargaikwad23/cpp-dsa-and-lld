/*
================================================================================
                    LOW-LEVEL DESIGN: EVENT VENUE BOOKING SYSTEM
================================================================================

PROBLEM:
  Design an online event venue booking system for a chain of event venues.
  Admins manage venues and events; customers browse, book, and cancel.

REQUIREMENTS:
  Admin Flows:
    - addVenue(id, name, location, max_capacity)
    - removeVenue(id) — cancels all events and bookings at that venue
    - addEvent(id, name, venue_id, type, max_participants, start, end, price)
    - removeEvent(id) — cancels all bookings for that event

  Customer Flows:
    - searchByEventType(type) — find events by type
    - searchByEventType(type, sortType) — sort by "earliest" or "price"
    - getAllEvents(venue_id) — list all events at a venue
    - bookEvent(customer_id, event_id) — book a spot (waitlist if full)
    - getAllBookings(customer_id) — view all bookings
    - cancelBooking(booking_id) — cancel and auto-promote from waitlist
    - trendingEvents(topN) — top N events by booking fill percentage

DESIGN DECISIONS:
  - In-memory storage using vectors and maps
  - Waitlist auto-promotes first-in-line on cancellation
  - Booking ID format: customerId_eventId_sequenceNumber
  - Method overloading for searchByEventType with optional sort

CLASSES:
  Venue          - venue entity (id, name, location, capacity)
  Event          - event entity (id, name, venue, type, timing, price, bookings)
  BookingSystem  - core service handling all admin and customer operations

================================================================================
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <limits>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// VENUE ENTITY
// ═══════════════════════════════════════════════════════════════════════════

class Venue {
public:
    string venueId;
    string name;
    string location;
    int maxCapacity;

    Venue() : maxCapacity(0) {}

    Venue(string vid, string n, string loc, int cap)
        : venueId(vid), name(n), location(loc), maxCapacity(cap) {}
};

// ═══════════════════════════════════════════════════════════════════════════
// EVENT ENTITY
// ═══════════════════════════════════════════════════════════════════════════

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

    Event() : maxParticipants(0), ticketPrice(0), currentBookings(0) {}

    Event(string eid, string n, string vid, string etype,
          int maxPar, string start, string end, double price)
        : eventId(eid), name(n), venueId(vid), eventType(etype),
          maxParticipants(maxPar), startTime(start), endTime(end),
          ticketPrice(price), currentBookings(0) {}
};

// ═══════════════════════════════════════════════════════════════════════════
// BOOKING SYSTEM - CORE SERVICE
// ═══════════════════════════════════════════════════════════════════════════

class BookingSystem {
    vector<Venue> venues;
    vector<Event> events;
    map<string, vector<string>> customerBookings; // customerId -> bookingIds
    map<string, vector<string>> waitLists;        // eventId -> customerIds
    unordered_map<string, string> bookingToEvent; // bookingId -> eventId

public:
    // ── Admin Functions ──────────────────────────────────────────────────

    void addVenue(string id, string name, string location, int maxCapacity) {
        if (findVenueById(id)) {
            cout << "Venue ID already exists!" << endl;
            return;
        }
        venues.emplace_back(id, name, location, maxCapacity);
        cout << "Venue " << name << " added to " << location << endl;
    }

    void removeVenue(string id) {
        auto it = remove_if(venues.begin(), venues.end(),
            [&id](const Venue& v) { return v.venueId == id; });

        if (it != venues.end()) {
            // Remove all events associated with this venue
            vector<string> eventsToRemove;
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

    void addEvent(string eId, string name, string vId, string eType,
                  int maxParticipants, string start, string end, double price) {
        if (findEventById(eId)) {
            cout << "Event ID already exists!" << endl;
            return;
        }

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

    void removeEvent(string eId) {
        auto it = remove_if(events.begin(), events.end(),
            [&eId](const Event& e) { return e.eventId == eId; });

        if (it != events.end()) {
            events.erase(it, events.end());
            cancelAllBookingsForEvent(eId);
            waitLists.erase(eId);
            cout << "Event " << eId << " removed." << endl;
        } else {
            cout << "Event ID not found!" << endl;
        }
    }

    // ── Customer Functions ───────────────────────────────────────────────

    vector<Event> searchByEventType(string eType) {
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

    vector<Event> searchByEventType(string eType, string sortType) {
        vector<Event> result = searchByEventType(eType);

        if (sortType == "earliest") {
            sort(result.begin(), result.end(),
                [](const Event& a, const Event& b) { return a.startTime < b.startTime; });
        } else if (sortType == "price") {
            sort(result.begin(), result.end(),
                [](const Event& a, const Event& b) { return a.ticketPrice < b.ticketPrice; });
        }

        for (const auto& e : result) {
            displayEvent(e);
        }
        return result;
    }

    vector<Event> getAllEvents(string venueId) {
        vector<Event> result;
        for (const auto& e : events) {
            if (e.venueId == venueId) {
                displayEvent(e);
                result.push_back(e);
            }
        }
        return result;
    }

    string bookEvent(string customerId, string eventId) {
        Event* event = findEventById(eventId);
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

    vector<string> getAllBookings(string customerId) {
        const auto& bookings = customerBookings[customerId];
        displayBookings(bookings);
        return bookings;
    }

    bool cancelBooking(string bookingId) {
        auto it = bookingToEvent.find(bookingId);
        if (it == bookingToEvent.end()) {
            cout << "Booking ID not found!" << endl;
            return false;
        }

        string eventId = it->second;
        Event* event = findEventById(eventId);
        if (event) {
            event->currentBookings--;

            // Auto-promote from waitlist
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

    vector<Event> trendingEvents(int topN) {
        vector<Event> sorted = events;
        sort(sorted.begin(), sorted.end(), [](const Event& a, const Event& b) {
            return (a.currentBookings / (double)a.maxParticipants)
                 > (b.currentBookings / (double)b.maxParticipants);
        });

        sorted.resize(min(topN, static_cast<int>(sorted.size())));
        for (const auto& e : sorted) {
            displayEvent(e);
        }
        return sorted;
    }

private:
    // ── Utility Functions ────────────────────────────────────────────────

    Venue* findVenueById(string vId) {
        for (auto& venue : venues) {
            if (venue.venueId == vId) return &venue;
        }
        return nullptr;
    }

    Event* findEventById(string eId) {
        for (auto& event : events) {
            if (event.eventId == eId) return &event;
        }
        return nullptr;
    }

    void displayEvent(const Event& event) {
        cout << "Event ID: " << event.eventId
             << ", Name: " << event.name
             << ", Type: " << event.eventType
             << ", Venue: " << event.venueId
             << ", Time: " << event.startTime << "-" << event.endTime
             << ", Price: " << event.ticketPrice
             << ", Bookings: " << event.currentBookings
             << "/" << event.maxParticipants << endl;
    }

    void displayBookings(const vector<string>& bookings) {
        for (const auto& bookingId : bookings) {
            auto it = bookingToEvent.find(bookingId);
            if (it != bookingToEvent.end()) {
                Event* event = findEventById(it->second);
                if (event) {
                    cout << "Booking ID: " << bookingId
                         << ", Venue: " << event->venueId
                         << ", Event: " << event->name
                         << ", Time: " << event->startTime
                         << " - " << event->endTime << endl;
                }
            }
        }
    }

    void cancelAllBookingsForEvent(string eId) {
        for (auto it = bookingToEvent.begin(); it != bookingToEvent.end(); ) {
            if (it->second == eId) {
                it = bookingToEvent.erase(it);
            } else {
                ++it;
            }
        }
        for (auto& pair : customerBookings) {
            auto& bookings = pair.second;
            bookings.erase(remove_if(bookings.begin(), bookings.end(),
                [&](const string& bid) {
                    return bookingToEvent.find(bid) == bookingToEvent.end();
                }), bookings.end());
        }
        waitLists.erase(eId);
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// CLI FLOWS
// ═══════════════════════════════════════════════════════════════════════════

void adminFlow(BookingSystem& system) {
    int choice;
    do {
        cout << "\nAdmin Menu:\n"
             << "  1. Add Venue\n"
             << "  2. Remove Venue\n"
             << "  3. Add Event\n"
             << "  4. Remove Event\n"
             << "  5. Exit Admin\n"
             << ">> Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                cout << "Enter Event ID, Name, Venue ID, Type, Max Participants, "
                     << "Start Time, End Time, Ticket Price: ";
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
            case 5: break;
            default: cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);
}

void customerFlow(BookingSystem& system) {
    int choice;
    do {
        cout << "\nCustomer Menu:\n"
             << "  1. Search Events by Type\n"
             << "  2. View All Events at Venue\n"
             << "  3. Book Event\n"
             << "  4. View My Bookings\n"
             << "  5. Cancel Booking\n"
             << "  6. Trending Events\n"
             << "  7. Exit Customer\n"
             << ">> Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            case 7: break;
            default: cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 7);
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    BookingSystem system;
    int userType;

    cout << "\n===== EVENT VENUE BOOKING SYSTEM =====\n" << endl;

    do {
        cout << "\nSelect User Type:\n"
             << "  1. Admin\n"
             << "  2. Customer\n"
             << "  3. Exit\n"
             << ">> Enter choice: ";
        cin >> userType;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (userType) {
            case 1: adminFlow(system); break;
            case 2: customerFlow(system); break;
            case 3: cout << "Exiting the system." << endl; break;
            default: cout << "Invalid choice. Try again." << endl;
        }
    } while (userType != 3);

    return 0;
}

/*
================================================================================
                         DESIGN NOTES
================================================================================

SAMPLE TEST FLOW:
  Admin:
    addVenue(vid_1, SarjapurSocial, Bengaluru, 200)
    addEvent(eid_1, MaiSamayHoon, vid_1, StandUp, 2, 19:00, 21:00, 500)

  Customer:
    bookEvent(cid_1, eid_1) -> Booking ID: cid_1_eid_1_1
    bookEvent(cid_2, eid_1) -> Booking ID: cid_2_eid_1_2
    bookEvent(cid_3, eid_1) -> Added to waitlist (event full)
    cancelBooking(cid_1_eid_1_1) -> cid_3 auto-promoted from waitlist

KEY OOP PRINCIPLES:
  - Encapsulation: BookingSystem hides internal data structures
  - Single Responsibility: Venue/Event are pure data, BookingSystem is logic
  - Method Overloading: searchByEventType with optional sort parameter

EXTENSIBILITY:
  - Event subclasses (ComedyEvent, WeddingEvent) via inheritance
  - Time slot conflict detection for venue scheduling
  - Notification system (Observer pattern) for waitlist promotions
  - Database/Redis backing for production scale

================================================================================
*/
