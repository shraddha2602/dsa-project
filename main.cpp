#include <iostream>

using namespace std;

// Structure for a gate
struct Gate {
    int* queue; // Queue of attendees
    int capacity; // Maximum capacity of the gate
    int currentSize; // Current size of the queue

    Gate(int cap) : capacity(cap), currentSize(0) {
        queue = new int[capacity];
    }

    ~Gate() {
        delete[] queue;
    }
};

// Class for managing the entry queue
class entryqueue {
private:
    Gate* gates; // Array of pointers to gates
    int total; // Total number of attendees
    int max_gates; // Total number of entry gates
    int time; // Time taken for one person to enter the gate (in minutes)

public:
    entryqueue(int n, int m, int p) : max_gates(n), total(m), time(p) {
        gates = new Gate*[max_gates];
        for (int i = 0; i < max_gates; ++i) {
            gates[i] = new Gate(m / (2 * max_gates)); // Equal capacity for each gate
        }
    }

    ~entryqueue() {
        for (int i = 0; i < max_gates; ++i) {
            delete gates[i];
        }
        delete[] gates;
    }

    // Function to display the initial assignment of attendees to gates
    void displayInitialAssignment() {
        cout << "Initial assignment of attendees to gates:\n";
        for (int i = 0; i < max_gates; ++i) {
            cout << "Gate " << i + 1 << " (" << gates[i]->currentSize << " attendees): ";
            for (int j = 0; j < gates[i]->currentSize; ++j) {
                cout << gates[i]->queue[j] << " ";
            }
            cout << endl;
        }
    }

    // Function to enqueue attendees to the gates
    void enqueue(int gatei, int ticket_no) {
        if (gatei >= 0 && gatei < max_gates) {
            Gate* gate = gates[gatei];
            if (gate->currentSize < gate->capacity) {
                gate->queue[gate->currentSize++] = ticket_no;
                cout << "Attendee " << ticket_no << " enqueued to Gate " << gatei + 1 << endl;
            } else {
                cout << "Gate " << gatei + 1 << " is full. Cannot enqueue attendee " << ticket_no << endl;
            }
        } else {
            cout << "Invalid gate index" << endl;
        }
    }

    // Function to dequeue attendees from the gates
    int dequeue(int gatei) {
        if (gatei >= 0 && gatei < max_gates) {
            Gate* gate = gates[gatei];
            if (gate->currentSize > 0) {
                int dequeuedAttendee = gate->queue[0];
                for (int i = 0; i < gate->currentSize - 1; ++i) {
                    gate->queue[i] = gate->queue[i + 1]; // Shift the queue to the left
                }
                --gate->currentSize;
                cout << "Attendee " << dequeuedAttendee << " dequeued from Gate " << gatei + 1 << endl;
                return dequeuedAttendee;
            } else {
                cout << "Gate " << gatei + 1 << " is empty" << endl;
                return -1;
            }
        } else {
            cout << "Invalid gate index" << endl;
            return -1;
        }
    }

    // Function to switch attendees from one gate to another if the latter is empty
    void switchAttendees(int fromGateIndex, int toGateIndex) {
        if (fromGateIndex >= 0 && fromGateIndex < max_gates && toGateIndex >= 0 && toGateIndex < max_gates) {
            Gate* fromGate = gates[fromGateIndex];
            Gate* toGate = gates[toGateIndex];
            if (toGate->currentSize == 0 && fromGate->currentSize > 0) {
                int ticket_no = dequeue(fromGateIndex);
                if (ticket_no != -1) {
                    enqueue(toGateIndex, ticket_no);
                    cout << "Attendee " << ticket_no << " switched from Gate " << fromGateIndex + 1 << " to Gate " << toGateIndex + 1 << endl;
                }
            } else {
                cout << "Switching not possible. Either the source gate is empty or the destination gate is not empty." << endl;
            }
        } else {
            cout << "Invalid gate index" << endl;
        }
    }

    // Function to calculate estimated time for each person to enter through the gate
    int calculateEstimatedTime(int gatei) {
        if (gatei >= 0 && gatei < max_gates) {
            return gates[gatei]->currentSize * time;
        } else {
            cout << "Invalid gate index" << endl;
            return -1;
        }
    }
};

int main() {
    int numGates, total, time;
    cout << "Enter the number of entry gates: ";
    cin >> numGates;
    cout << "Enter the total number of attendees: ";
    cin >> total;
    cout << "Enter the time taken for one person to enter the gate (in minutes): ";
    cin >> time;

    entryqueue qu(numGates, total, time);

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Display Initial Assignment\n";
        cout << "2. Enqueue Attendee\n";
        cout << "3. Dequeue Attendee\n";
        cout << "4. Switch Attendee\n";
        cout << "5. Calculate Estimated Time\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                qu.displayInitialAssignment();
                break;
            case 2: {
                int gatei, ticket_no;
                cout << "Enter gate index: ";
                cin >> gatei;
                cout << "Enter attendee number: ";
                cin >> ticket_no;
                qu.enqueue(gatei - 1, ticket_no);
                break;
            }
            case 3: {
                int gatei;
                cout << "Enter gate index: ";
                cin >> gatei;
                qu.dequeue(gatei - 1);
                break;
            }
            case 4: {
                int fromGateIndex, toGateIndex;
                cout << "Enter source gate index: ";
                cin >> fromGateIndex;
                cout << "Enter destination gate index: ";
                cin >> toGateIndex;
                qu.switchAttendees(fromGateIndex - 1, toGateIndex - 1);
                break;
            }
            case 5: {
                int gatei;
                cout << "Enter gate index: ";
                cin >> gatei;
                int estimatedTime = qu.calculateEstimatedTime(gatei - 1);
                if (estimatedTime != -1) {
                    cout << "Estimated time for each person to enter through Gate " << gatei << ": " << estimatedTime << " minutes" << endl;
                }
                break;
            }
            case 6:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    }
}
