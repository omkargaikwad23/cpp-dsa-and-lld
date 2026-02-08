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

-------------------------------
v_id_001 SarjapurSocial Bengaluru 200

e_id_001 MaiSamayHoon v_id_001 StandUp 100 19:00 21:00 500

c_id_001 e_id_001

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