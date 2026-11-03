/*
 * ============================================================
 *   COLLEGE ADMISSION WAITING LIST MANAGEMENT SYSTEM
 *   Data Structure Used : Queue (Linked List based)
 *   Concept             : FIFO - First In, First Out
 *   Language            : C++
 * ============================================================
 *
 *  MENU OPTIONS:
 *   1. Add Applicant to Waiting List    -> Enqueue
 *   2. Process Next Applicant           -> Dequeue
 *   3. View Next Applicant (Peek)       -> Front of Queue
 *   4. Display Entire Waiting List      -> Traverse Queue
 *   5. Search Applicant by ID           -> Linear Search
 *   6. Check Waiting List Status        -> isEmpty / Size
 *   7. Clear Entire Waiting List        -> Empty Queue
 *   8. Display Admitted Students        -> Separate list
 *   0. Exit
 */

#include <iostream>
#include <string>
#include <iomanip>   // for setw() - formatting output
using namespace std;

// ─────────────────────────────────────────────
//  STEP 1: Define what data each applicant has
// ─────────────────────────────────────────────
struct Applicant {
    int    id;          // Unique applicant ID
    string name;        // Full name
    string course;      // Applied course (e.g., CS, ECE)
    float  score;       // Entrance exam score
    string status;      // "Waiting" or "Admitted"
    Applicant* next;    // Pointer to the next applicant in the queue

    // Constructor – fills data when a new applicant is created
    Applicant(int i, string n, string c, float s) {
        id     = i;
        name   = n;
        course = c;
        score  = s;
        status = "Waiting";
        next   = nullptr;  // No next node yet
    }
};

// ─────────────────────────────────────────────
//  STEP 2: Build the Queue class
//           front → first person to be processed
//           rear  → last person who joined
// ─────────────────────────────────────────────
class AdmissionQueue {
private:
    Applicant* front;      // Points to the first applicant (to be processed next)
    Applicant* rear;       // Points to the last applicant (most recently added)
    int        size;       // Tracks how many applicants are in the queue
    int        nextID;     // Auto-incrementing applicant ID

    // Separate list to store admitted students (simple array-style linked list)
    Applicant* admittedHead;

public:
    // Constructor – initializes an empty queue
    AdmissionQueue() {
        front       = nullptr;
        rear        = nullptr;
        admittedHead= nullptr;
        size        = 0;
        nextID      = 1001;   // IDs start from 1001
    }

    // Destructor – frees all memory when program ends
    ~AdmissionQueue() {
        clearQueue();
        // Also free admitted list
        while (admittedHead != nullptr) {
            Applicant* temp = admittedHead;
            admittedHead = admittedHead->next;
            delete temp;
        }
    }

    // ── Utility ──────────────────────────────
    bool isEmpty() { return front == nullptr; }
    int  getSize() { return size; }

    // ─────────────────────────────────────────
    //  ENQUEUE – Add a new applicant to the
    //  END of the waiting list
    // ─────────────────────────────────────────
    void addApplicant(string name, string course, float score) {
        // Create a new applicant node
        Applicant* newApplicant = new Applicant(nextID++, name, course, score);

        if (isEmpty()) {
            // Queue is empty → new node is both front and rear
            front = newApplicant;
            rear  = newApplicant;
        } else {
            // Attach new node after current rear, then update rear
            rear->next = newApplicant;
            rear       = newApplicant;
        }
        size++;

        cout << "\n  ✔ Applicant Added Successfully!\n";
        cout << "  ID     : " << newApplicant->id   << "\n";
        cout << "  Name   : " << newApplicant->name << "\n";
        cout << "  Course : " << newApplicant->course << "\n";
        cout << "  Score  : " << newApplicant->score  << "\n";
        cout << "  Position in queue: " << size << "\n";
    }

    // ─────────────────────────────────────────
    //  DEQUEUE – Process (remove) the applicant
    //  at the FRONT of the waiting list
    // ─────────────────────────────────────────
    void processNextApplicant() {
        if (isEmpty()) {
            cout << "\n  ✘ Waiting list is empty! No applicants to process.\n";
            return;
        }

        // Save the front applicant
        Applicant* processed = front;

        // Move front pointer to the next applicant
        front = front->next;

        // If queue becomes empty after removal, reset rear too
        if (front == nullptr) rear = nullptr;

        size--;

        // Mark this applicant as admitted and move to admitted list
        processed->status = "Admitted";
        processed->next   = admittedHead;   // Prepend to admitted list
        admittedHead      = processed;

        cout << "\n  ✔ Applicant Processed & ADMITTED!\n";
        cout << "  ─────────────────────────────\n";
        cout << "  ID     : " << processed->id     << "\n";
        cout << "  Name   : " << processed->name   << "\n";
        cout << "  Course : " << processed->course << "\n";
        cout << "  Score  : " << processed->score  << "\n";
        cout << "  Status : " << processed->status << " ✓\n";
        cout << "  Remaining in queue: " << size   << "\n";
    }

    // ─────────────────────────────────────────
    //  PEEK – View the FRONT applicant without
    //  removing them from the queue
    // ─────────────────────────────────────────
    void peekFront() {
        if (isEmpty()) {
            cout << "\n  ✘ Waiting list is empty!\n";
            return;
        }

        cout << "\n  Next Applicant to be Processed:\n";
        cout << "  ─────────────────────────────\n";
        cout << "  ID     : " << front->id     << "\n";
        cout << "  Name   : " << front->name   << "\n";
        cout << "  Course : " << front->course << "\n";
        cout << "  Score  : " << front->score  << "\n";
        cout << "  Status : " << front->status << "\n";
    }

    // ─────────────────────────────────────────
    //  DISPLAY – Show all applicants currently
    //  in the waiting list (front to rear)
    // ─────────────────────────────────────────
    void displayWaitingList() {
        if (isEmpty()) {
            cout << "\n  ✘ Waiting list is empty!\n";
            return;
        }

        cout << "\n  ╔══════════════════════════════════════════════════════════════╗\n";
        cout << "  ║               COLLEGE ADMISSION WAITING LIST                ║\n";
        cout << "  ╠══════════════════════════════════════════════════════════════╣\n";
        cout << "  ║  Pos │  ID  │ Name                │ Course    │ Score       ║\n";
        cout << "  ╠══════════════════════════════════════════════════════════════╣\n";

        Applicant* current = front;
        int position = 1;

        while (current != nullptr) {
            cout << "  ║  "
                 << setw(3)  << left << position           << " │ "
                 << setw(4)  << left << current->id        << " │ "
                 << setw(20) << left << current->name      << "│ "
                 << setw(9)  << left << current->course    << " │ "
                 << setw(5)  << left << current->score     << "       ║\n";
            current = current->next;
            position++;
        }

        cout << "  ╚══════════════════════════════════════════════════════════════╝\n";
        cout << "  Total applicants in queue: " << size << "\n";
    }

    // ─────────────────────────────────────────
    //  SEARCH – Find an applicant by their ID
    // ─────────────────────────────────────────
    void searchApplicant(int searchID) {
        // Search in waiting list first
        Applicant* current = front;
        int position = 1;

        while (current != nullptr) {
            if (current->id == searchID) {
                cout << "\n  ✔ Applicant Found in WAITING LIST:\n";
                cout << "  ─────────────────────────────\n";
                cout << "  ID       : " << current->id       << "\n";
                cout << "  Name     : " << current->name     << "\n";
                cout << "  Course   : " << current->course   << "\n";
                cout << "  Score    : " << current->score    << "\n";
                cout << "  Status   : " << current->status   << "\n";
                cout << "  Position : " << position << " in queue\n";
                return;
            }
            current = current->next;
            position++;
        }

        // Search in admitted list
        current = admittedHead;
        while (current != nullptr) {
            if (current->id == searchID) {
                cout << "\n  ✔ Applicant Found in ADMITTED LIST:\n";
                cout << "  ─────────────────────────────\n";
                cout << "  ID     : " << current->id     << "\n";
                cout << "  Name   : " << current->name   << "\n";
                cout << "  Course : " << current->course << "\n";
                cout << "  Score  : " << current->score  << "\n";
                cout << "  Status : " << current->status << " ✓\n";
                return;
            }
            current = current->next;
        }

        cout << "\n  ✘ Applicant with ID " << searchID << " not found.\n";
    }

    // ─────────────────────────────────────────
    //  STATUS – Show queue info
    // ─────────────────────────────────────────
    void checkStatus() {
        cout << "\n  ── Waiting List Status ──────────────\n";
        if (isEmpty()) {
            cout << "  Queue Status : EMPTY\n";
        } else {
            cout << "  Queue Status : ACTIVE\n";
            cout << "  Total Waiting: " << size << " applicants\n";
            cout << "  Front (Next) : [" << front->id << "] " << front->name << "\n";
            cout << "  Rear  (Last) : [" << rear->id  << "] " << rear->name  << "\n";
        }

        // Count admitted students
        int admittedCount = 0;
        Applicant* temp = admittedHead;
        while (temp != nullptr) { admittedCount++; temp = temp->next; }
        cout << "  Total Admitted: " << admittedCount << " students\n";
        cout << "  ────────────────────────────────────\n";
    }

    // ─────────────────────────────────────────
    //  CLEAR – Remove all applicants from queue
    // ─────────────────────────────────────────
    void clearQueue() {
        if (isEmpty()) {
            cout << "\n  ✘ Queue is already empty!\n";
            return;
        }

        int count = 0;
        while (front != nullptr) {
            Applicant* temp = front;
            front = front->next;
            delete temp;
            count++;
        }
        rear = nullptr;
        size = 0;

        cout << "\n  ✔ Waiting list cleared! " << count << " applicant(s) removed.\n";
    }

    // ─────────────────────────────────────────
    //  DISPLAY ADMITTED – Show all admitted
    // ─────────────────────────────────────────
    void displayAdmitted() {
        if (admittedHead == nullptr) {
            cout << "\n  ✘ No students have been admitted yet!\n";
            return;
        }

        cout << "\n  ╔══════════════════════════════════════════════════════════════╗\n";
        cout << "  ║                  ADMITTED STUDENTS LIST                     ║\n";
        cout << "  ╠══════════════════════════════════════════════════════════════╣\n";
        cout << "  ║   ID  │ Name                │ Course    │ Score │ Status    ║\n";
        cout << "  ╠══════════════════════════════════════════════════════════════╣\n";

        Applicant* current = admittedHead;
        while (current != nullptr) {
            cout << "  ║  "
                 << setw(4)  << left << current->id        << " │ "
                 << setw(20) << left << current->name      << "│ "
                 << setw(9)  << left << current->course    << " │ "
                 << setw(5)  << left << current->score     << " │ "
                 << setw(9)  << left << current->status    << " ║\n";
            current = current->next;
        }

        cout << "  ╚══════════════════════════════════════════════════════════════╝\n";
    }
};

// ─────────────────────────────────────────────
//  Helper: Print a separator line
// ─────────────────────────────────────────────
void printLine() {
    cout << "\n  ════════════════════════════════════\n";
}

// ─────────────────────────────────────────────
//  Helper: Print the main menu
// ─────────────────────────────────────────────
void printMenu() {
    cout << "\n";
    cout << "  ╔══════════════════════════════════════╗\n";
    cout << "  ║   COLLEGE ADMISSION WAITING LIST     ║\n";
    cout << "  ║        MANAGEMENT SYSTEM             ║\n";
    cout << "  ╠══════════════════════════════════════╣\n";
    cout << "  ║  1. Add Applicant to Waiting List    ║\n";
    cout << "  ║  2. Process Next Applicant           ║\n";
    cout << "  ║  3. View Next Applicant (Peek)       ║\n";
    cout << "  ║  4. Display Entire Waiting List      ║\n";
    cout << "  ║  5. Search Applicant by ID           ║\n";
    cout << "  ║  6. Check Waiting List Status        ║\n";
    cout << "  ║  7. Clear Entire Waiting List        ║\n";
    cout << "  ║  8. Display Admitted Students        ║\n";
    cout << "  ║  0. Exit                             ║\n";
    cout << "  ╚══════════════════════════════════════╝\n";
    cout << "  Enter your choice: ";
}

// ─────────────────────────────────────────────
//  MAIN FUNCTION
// ─────────────────────────────────────────────
int main() {
    AdmissionQueue waitingList;   // Our queue object
    int choice;

    cout << "\n  ══════════════════════════════════════\n";
    cout << "   Welcome to College Admission System  \n";
    cout << "  ══════════════════════════════════════\n";

    // Pre-load some demo applicants so you can see the system right away
    cout << "\n  [ Loading demo applicants... ]\n";
    waitingList.addApplicant("Aarav Sharma",   "Computer Science", 92.5);
    waitingList.addApplicant("Priya Patel",    "Electronics",      87.0);
    waitingList.addApplicant("Rahul Gupta",    "Mechanical",       78.5);
    waitingList.addApplicant("Sneha Verma",    "Civil Engg",       83.0);
    waitingList.addApplicant("Kiran Mehta",    "Computer Science", 95.0);

    do {
        printMenu();
        cin >> choice;
        cin.ignore();   // clear newline from buffer

        switch (choice) {

            // ── Option 1: Add Applicant ──────────
            case 1: {
                printLine();
                string name, course;
                float  score;

                cout << "  Enter Applicant Name   : ";
                getline(cin, name);

                cout << "  Enter Applied Course   : ";
                getline(cin, course);

                cout << "  Enter Entrance Score   : ";
                cin >> score;
                cin.ignore();

                // Validate score
                if (score < 0 || score > 100) {
                    cout << "\n  ✘ Invalid score! Must be between 0 and 100.\n";
                } else {
                    waitingList.addApplicant(name, course, score);
                }
                break;
            }

            // ── Option 2: Process Next ───────────
            case 2: {
                printLine();
                char confirm;
                cout << "  Process the next applicant? (y/n): ";
                cin >> confirm;
                cin.ignore();

                if (confirm == 'y' || confirm == 'Y') {
                    waitingList.processNextApplicant();
                } else {
                    cout << "  Action cancelled.\n";
                }
                break;
            }

            // ── Option 3: Peek Front ─────────────
            case 3: {
                printLine();
                waitingList.peekFront();
                break;
            }

            // ── Option 4: Display All ────────────
            case 4: {
                printLine();
                waitingList.displayWaitingList();
                break;
            }

            // ── Option 5: Search ─────────────────
            case 5: {
                printLine();
                int searchID;
                cout << "  Enter Applicant ID to search: ";
                cin >> searchID;
                cin.ignore();
                waitingList.searchApplicant(searchID);
                break;
            }

            // ── Option 6: Status ─────────────────
            case 6: {
                printLine();
                waitingList.checkStatus();
                break;
            }

            // ── Option 7: Clear ──────────────────
            case 7: {
                printLine();
                char confirm;
                cout << "  ⚠  This will remove ALL applicants from the waiting list!\n";
                cout << "  Are you sure? (y/n): ";
                cin >> confirm;
                cin.ignore();

                if (confirm == 'y' || confirm == 'Y') {
                    waitingList.clearQueue();
                } else {
                    cout << "  Action cancelled.\n";
                }
                break;
            }

            // ── Option 8: Admitted List ──────────
            case 8: {
                printLine();
                waitingList.displayAdmitted();
                break;
            }

            // ── Option 0: Exit ───────────────────
            case 0: {
                cout << "\n  Thank you for using the Admission System!\n";
                cout << "  Goodbye! 👋\n\n";
                break;
            }

            default: {
                cout << "\n  ✘ Invalid choice! Please enter 0-8.\n";
            }
        }

    } while (choice != 0);

    return 0;
}
