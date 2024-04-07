/* TEAM NAME - BAD IDEA
Team ID - 202301059 (Leader ID)
PROJECT ID-P3
ID                                NAME 
202301059                         SHRADDHA RATHOD
202301001                         VED KOTADIYA
202301079                         KUSHAL BHUPTANI
202301012                         RASHA PARMAR

Title : Stadium Queue Management System 

PROJECT DESCRIPTION- This project about the entry queue manager is helpful in efficiently managing the entry of viewers in a stadium with 'N' number of entry gates.The main goal of this projet is to minimize the wait time and the crowding of viewers.
       -FEATURES:
        1.MULTIPLE GATES: stadium has 'N' number of gates,each gate will act as an entry queue.
        2.USAGE OF DYNAMIC QUEUE:Dynamic queue is used for switing the queue in order to get quick entry.
        3.QUEUE MONITORING: Length of each queue is monitored which helps in estimating the wait time of a person standing in the queue.
        4.GUIDANCE:We will inform the viewer if there is a change in queue and the timd estimated for their entry.
        5.SPECIAL ENTRY:We will provide special entry to VIP's and the disabled.
*/

#include <iostream>

using namespace std;

class Random {
private:
    unsigned long long s;

public:
    Random() {
        s = 123456789ULL;
    }

    int next(int x) {
        constexpr unsigned long long modulus = 0xFFFFFFFFFFFFFFFFULL;
        s = (6364136223846793005ULL * s + 1ULL) % modulus;
        return static_cast<int>((s >> 32) % (x + 1));
    }
};

struct Node {
    int data;
    Node* next;
};

class Queue {
private:
    Node* head;
    Node* rear;
public:
    Queue() {
        head = nullptr;
        rear = nullptr;
    }

    void enqueue(int val) {
        Node* newNode = new Node;
        newNode->data = val;
        newNode->next = nullptr;
        if (isEmpty()) {
            head = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return -1;
        }
        int val = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return val;
    }

    bool isEmpty() {
        return head == nullptr;
    }
//function to  get the number of elements in the queue
    int size() {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
    int Timetaken(int p) {
        return size() * p;
    }

    int LastPerson() {
        if (isEmpty()) {
            return -1;
        }   
        return rear->data;
    }

    void Switch_Person(Queue& otherQueue) {
        if (!isEmpty()) {
            int lastPerson = dequeue();
            otherQueue.enqueue(lastPerson);
        }
    }
};

bool allQueuesEqual(Queue* queues, int N) {
    int firstSize = queues[0].size();
    for (int i = 1; i < N; ++i) {
        if (queues[i].size() != firstSize) {
            return false;
        }
    }
    return true;
}

int main() {
    Random random;

    int M;
    cout << "Enter the total number of persons: ";
    cin >> M;

    int N;
    cout << "Enter the total number of queues: ";
    cin >> N;

    int p;
    cout << "Enter the time to pass through gate (in seconds): ";
    cin >> p;

    Queue* queues = new Queue[N];

    for (int i = 0; i < M / 2; ++i) {
        int person = i + 1;
        int queueNumber = random.next(N - 1);
        queues[queueNumber].enqueue(person);
    }

    cout << "Time for each queue to pass through gate:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << "Queue " << i + 1 << ": " << queues[i].Timetaken(p) << " seconds" << endl;
    }
    int switchCount = 0; 
    int maxIterations = 10000;
   while (!allQueuesEqual(queues, N) && switchCount < maxIterations) {
    int maxTime = queues[0].Timetaken(p);
    int maxQueueIndex = 0;
    for (int i = 1; i < N; ++i) {
        int queueTime = queues[i].Timetaken(p);
        if (queueTime > maxTime) {
            maxTime = queueTime;
            maxQueueIndex = i;
        }
    }

    int minTime = queues[0].Timetaken(p);
    int minQueueIndex = 0;
    for (int i = 1; i < N; ++i) {
        int queueTime = queues[i].Timetaken(p);
        if (queueTime < minTime) {
            minTime = queueTime;
            minQueueIndex = i;
        }
    }

    if (maxTime - minTime <= p) {
        break;
    }

    
    queues[maxQueueIndex].Switch_Person(queues[minQueueIndex]);
    switchCount++;
    cout << "Switch " << switchCount << ": Person from Queue " << maxQueueIndex + 1 << " moved to Queue " << minQueueIndex + 1 << endl;
}



    if (switchCount == maxIterations) {
        cout << "Maximum number of iterations reached. Convergence not achieved." << endl;
    } else {
        cout << "\nTime for each queue to pass through gate after switching:" << endl;
        for (int i = 0; i < N; ++i) {
            cout << "Queue " << i + 1 << ": " << queues[i].Timetaken(p) << " seconds" << endl;
        }

        cout << "\nTotal number of switches: " << switchCount << endl;
    }

    delete[] queues;

    return 0;
}
