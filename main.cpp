#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// ---------------- Passenger ----------------

struct Passenger
{
    int id;
    string name;
    int age;
};

// ---------------- Train ----------------

struct Train
{
    int trainNo;
    string trainName;
    int totalSeats;

    vector<Passenger> confirmedPassengers;
    queue<Passenger> waitingPassengers;
};

// Stores all trains
vector<Train> trains;
int nextPassengerID = 1001;

// =============================
// Find Train
// =============================

int findTrain(int trainNo)
{
    for(int i = 0; i < trains.size(); i++)
    {
        if(trains[i].trainNo == trainNo)
            return i;
    }

    return -1;
}



// =============================
// Add Train
// =============================

void addTrain()
{
    Train t;

    cout << "\nEnter Train Number : ";
    cin >> t.trainNo;

    if(findTrain(t.trainNo) != -1)
    {
        cout << "Train already exists.\n";
        return;
    }

    cin.ignore();

    cout << "Enter Train Name : ";
    getline(cin, t.trainName);

    cout << "Enter Total Seats : ";
    cin >> t.totalSeats;

    trains.push_back(t);

    cout << "\nTrain Added Successfully.\n";
}



// =============================
// Display All Trains
// =============================

void displayTrains()
{
    if(trains.empty())
    {
        cout << "\nNo Trains Available.\n";
        return;
    }

    cout << "\n========== TRAINS ==========\n";

    for(int i = 0; i < trains.size(); i++)
    {
        Train &t = trains[i];

        cout << "\nTrain Number : " << t.trainNo;
        cout << "\nTrain Name   : " << t.trainName;
        cout << "\nTotal Seats  : " << t.totalSeats;

        cout << "\nBooked Seats : "
             << t.confirmedPassengers.size();

        cout << "\nAvailable    : "
             << t.totalSeats - t.confirmedPassengers.size();

        cout << "\nWaiting      : "
             << t.waitingPassengers.size();

        cout << "\n-----------------------------\n";
    }
}

// =============================
// Book Ticket
// =============================

void bookTicket()
{
    int trainNo;

    cout << "\nEnter Train Number : ";
    cin >> trainNo;

    int index = findTrain(trainNo);

    if(index == -1)
    {
        cout << "Train not found.\n";
        return;
    }

    Passenger p;

   p.id = nextPassengerID++;

cout << "\nPassenger ID Generated : " << p.id << endl;

cin.ignore();

    cout << "Enter Passenger Name : ";
    getline(cin, p.name);

    cout << "Enter Age : ";
    cin >> p.age;

    Train &t = trains[index];

    if(t.confirmedPassengers.size() < t.totalSeats)
    {
        t.confirmedPassengers.push_back(p);

        cout << "\nTicket Confirmed!\n";
    }
    else
    {
        t.waitingPassengers.push(p);

        cout << "\nNo Seats Available.\n";
        cout << "Added to Waiting List.\n";
        cout << "Waiting Number : "
             << t.waitingPassengers.size()
             << endl;
    }
}

// =============================
// Menu
// =============================

void menu()
{
    cout << "\n";
    cout << "=========================================\n";
    cout << " SMART RAILWAY RESERVATION SYSTEM\n";
    cout << "=========================================\n";

    cout << "1. Add Train\n";
    cout << "2. Display Trains\n";
    cout << "3. Book Ticket\n";
    cout << "4. Cancel Ticket\n";
    cout << "5. View Confirmed Passengers\n";
    cout << "6. View Waiting List\n";
    cout << "7. Search Passenger\n";
    cout << "8. Sort Passengers\n";
    cout << "9. Train Statistics\n";
    cout << "10. Exit\n";

    cout << "\nEnter Choice : ";
}

// =============================
// View Confirmed Passengers
// =============================

void viewConfirmedPassengers()
{
    int trainNo;

    cout << "\nEnter Train Number : ";
    cin >> trainNo;

    int index = findTrain(trainNo);

    if(index == -1)
    {
        cout << "Train not found.\n";
        return;
    }

    Train &t = trains[index];

    if(t.confirmedPassengers.empty())
    {
        cout << "\nNo Confirmed Passengers.\n";
        return;
    }

    cout << "\n====== CONFIRMED PASSENGERS ======\n";

    for(int i=0;i<t.confirmedPassengers.size();i++)
    {
        Passenger p = t.confirmedPassengers[i];

        cout << "\nPassenger ID : "
             << p.id;

        cout << "\nName : "
             << p.name;

        cout << "\nAge : "
             << p.age;

        cout << "\n-------------------------\n";
    }
}

// =============================
// View Waiting List
// =============================

void viewWaitingList()
{
    int trainNo;

    cout << "\nEnter Train Number : ";
    cin >> trainNo;

    int index = findTrain(trainNo);

    if(index == -1)
    {
        cout << "Train not found.\n";
        return;
    }

    Train &t = trains[index];

    if(t.waitingPassengers.empty())
    {
        cout << "\nWaiting List Empty.\n";
        return;
    }

    queue<Passenger> temp = t.waitingPassengers;

    cout << "\n====== WAITING LIST ======\n";

    int position = 1;

    while(!temp.empty())
    {
        Passenger p = temp.front();

        cout << "\nPosition : "
             << position++;

        cout << "\nPassenger ID : "
             << p.id;

        cout << "\nName : "
             << p.name;

        cout << "\nAge : "
             << p.age;

        cout << "\n-------------------------\n";

        temp.pop();
    }
}

// =============================
// Cancel Ticket
// =============================

void cancelTicket()
{
    int trainNo;

    cout << "\nEnter Train Number : ";
    cin >> trainNo;

    int index = findTrain(trainNo);

    if(index == -1)
    {
        cout << "Train not found.\n";
        return;
    }

    Train &t = trains[index];

    int passengerID;

    cout << "Enter Passenger ID : ";
    cin >> passengerID;

    bool found = false;

    for(int i=0;i<t.confirmedPassengers.size();i++)
    {
        if(t.confirmedPassengers[i].id == passengerID)
        {
            t.confirmedPassengers.erase(
                t.confirmedPassengers.begin()+i);

            found = true;

            cout << "\nTicket Cancelled Successfully.\n";

            break;
        }
    }

    if(!found)
    {
        cout << "\nPassenger Not Found.\n";
        return;
    }

    if(!t.waitingPassengers.empty())
    {
        Passenger p = t.waitingPassengers.front();

        t.waitingPassengers.pop();

        t.confirmedPassengers.push_back(p);

        cout << "Passenger "
             << p.name
             << " moved from Waiting List to Confirmed.\n";
    }
}

// =============================
// Search Passenger
// =============================

void searchPassenger()
{
    int passengerID;

    cout << "\nEnter Passenger ID : ";
    cin >> passengerID;

    bool found = false;

    for(int i=0;i<trains.size();i++)
    {
        Train &t = trains[i];

        // Search in confirmed passengers
        for(int j=0;j<t.confirmedPassengers.size();j++)
        {
            if(t.confirmedPassengers[j].id == passengerID)
            {
                cout << "\nPassenger Found\n";

                cout << "Train Number : "
                     << t.trainNo << endl;

                cout << "Train Name : "
                     << t.trainName << endl;

                cout << "Passenger Name : "
                     << t.confirmedPassengers[j].name << endl;

                cout << "Age : "
                     << t.confirmedPassengers[j].age << endl;

                cout << "Status : Confirmed\n";

                found = true;
                return;
            }
        }

        // Search in waiting list

        queue<Passenger> temp = t.waitingPassengers;

        while(!temp.empty())
        {
            Passenger p = temp.front();

            if(p.id == passengerID)
            {
                cout << "\nPassenger Found\n";

                cout << "Train Number : "
                     << t.trainNo << endl;

                cout << "Train Name : "
                     << t.trainName << endl;

                cout << "Passenger Name : "
                     << p.name << endl;

                cout << "Age : "
                     << p.age << endl;

                cout << "Status : Waiting\n";

                found = true;
                return;
            }

            temp.pop();
        }
    }

    if(!found)
    {
        cout << "\nPassenger Not Found.\n";
    }
}

// =============================
// Sort by Name
// =============================

bool compareName(Passenger a, Passenger b)
{
    return a.name < b.name;
}

// =============================
// Sort by Age
// =============================

bool compareAge(Passenger a, Passenger b)
{
    return a.age < b.age;
}

// =============================
// Sort Passengers
// =============================

void sortPassengers()
{
    int trainNo;

    cout << "\nEnter Train Number : ";
    cin >> trainNo;

    int index = findTrain(trainNo);

    if(index==-1)
    {
        cout << "Train Not Found.\n";
        return;
    }

    Train &t = trains[index];

    if(t.confirmedPassengers.empty())
    {
        cout << "No Confirmed Passengers.\n";
        return;
    }

    int choice;

    cout << "\n1. Sort by Name\n";
    cout << "2. Sort by Age\n";

    cout << "Enter Choice : ";
    cin >> choice;

    if(choice==1)
    {
        sort(t.confirmedPassengers.begin(),
             t.confirmedPassengers.end(),
             compareName);

        cout << "\nSorted by Name.\n";
    }

    else if(choice==2)
    {
        sort(t.confirmedPassengers.begin(),
             t.confirmedPassengers.end(),
             compareAge);

        cout << "\nSorted by Age.\n";
    }

    else
    {
        cout << "Invalid Choice.\n";
    }
}

// =============================
// Train Statistics
// =============================

void trainStatistics()
{
    int trainNo;

    cout << "\nEnter Train Number : ";
    cin >> trainNo;

    int index = findTrain(trainNo);

    if(index==-1)
    {
        cout << "Train Not Found.\n";
        return;
    }

    Train &t = trains[index];

    cout << "\n========== TRAIN STATISTICS ==========\n";

    cout << "Train Number : "
         << t.trainNo << endl;

    cout << "Train Name : "
         << t.trainName << endl;

    cout << "Total Seats : "
         << t.totalSeats << endl;

    cout << "Confirmed Tickets : "
         << t.confirmedPassengers.size() << endl;

    cout << "Available Seats : "
         << t.totalSeats - t.confirmedPassengers.size()
         << endl;

    cout << "Waiting List : "
         << t.waitingPassengers.size()
         << endl;
}

// =============================
// Main
// =============================

int main()
{
    int choice;

    do
    {
        menu();

        cin >> choice;

        switch(choice)
        {
            case 1:
                addTrain();
                break;

            case 2:
                displayTrains();
                break;

            case 3:
                 bookTicket();
                break;

            case 4:
                 cancelTicket();
                break;

            case 5:
              viewConfirmedPassengers();
                break;

            case 6:
                viewWaitingList();
                break;

            case 7:
                 searchPassenger();
                break;

            case 8:
                 sortPassengers();
                break;

            case 9:
                 trainStatistics();
                break;

            case 10:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice.\n";
        }

    }while(choice != 10);

    return 0;
}
