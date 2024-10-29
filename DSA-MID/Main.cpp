#include <iostream>
#include <string>
#include <limits>

using namespace std;

typedef int Itemtype;

struct Node {
    Node* next;
    Node* previous;
    Itemtype score;
    Node(int s) : score(s), next(nullptr), previous(nullptr) {}
};

class doubly_linked_list {
private:
    Node* head;  // Pointer to the first node
    Node* tail;  // Pointer to the last node

public:
    doubly_linked_list();  // Constructor
    ~doubly_linked_list();  // Destructor
    void insert_at_beginning(int score);  // Insert at the beginning
    void insert_at_end(int score);  // Insert at the end
    void delete_node(Node* node);  // Delete a specific node
    void delete_all_occurrences(int score);  // Delete all occurrences of a score
    void display_forward();  // Display scores in forward order
    void display_reversed();  // Display scores in reverse order
    void find_highest();  // Find the highest score
    void find_lowest();  // Find the lowest score
    Node* find_node(int score);  // Find a node by score
};

doubly_linked_list::doubly_linked_list() {
    head = tail = nullptr;  // Initialize head and tail to null
}

doubly_linked_list::~doubly_linked_list() {
    Node* current = head;  // Start with the head
    while (current != nullptr) {
        Node* nextNode = current->next;  // Store the next node
        delete current;  // Delete the current node
        current = nextNode;  // Move to the next node
    }
}

void doubly_linked_list::insert_at_beginning(int score) {
    Node* newNode = new Node(score);
    if (head == nullptr) {
        head = tail = newNode;  // List is empty, new node is both head and tail
    }
    else {
        newNode->next = head;  // Link new node to the old head
        head->previous = newNode;  // Link old head back to new node
        head = newNode;  // Update head to new node
    }
    cout << "Successfully added Score " << score << " at the start." << endl;
}

void doubly_linked_list::insert_at_end(int score) {
    Node* newNode = new Node(score);
    if (tail == nullptr) {
        tail = head = newNode;  // List is empty, new node is both head and tail
    }
    else {
        tail->next = newNode;  // Link the old tail to the new node
        newNode->previous = tail;  // Link new node back to old tail
        tail = newNode;  // Update tail to new node
    }
    cout << "Successfully added score " << score << " at the end." << endl;
}

void doubly_linked_list::delete_node(Node* node) {
    if (node == nullptr) {
        cout << "Error: Cannot delete a null node." << endl;
        return;
    }

    if (node == head) {
        head = head->next;  // Update head if deleting the first node
        if (head != nullptr) head->previous = nullptr;
        else tail = nullptr;  // List is now empty
    }
    else if (node == tail) {
        tail = tail->previous;  // Update tail if deleting the last node
        if (tail != nullptr) tail->next = nullptr;
        else head = nullptr;  // List is now empty
    }
    else {
        node->previous->next = node->next;  // Bypass the node to delete
        node->next->previous = node->previous;
    }

    cout << "Successfully deleted score " << node->score << "." << endl;
    delete node;  // Free memory
}

void doubly_linked_list::delete_all_occurrences(int score) {
    if (head == nullptr) {
        cout << "No matches recorded yet." << endl;
        return;
    }

    Node* current = head;
    bool found = false;

    while (current != nullptr) {
        if (current->score == score) {
            Node* nodeToDelete = current;
            current = current->next;  // Move to the next node before deleting
            delete_node(nodeToDelete);  // Use existing delete_node method
            found = true;
        }
        else {
            current = current->next;  // Move to the next node
        }
    }

    if (found) {
        cout << "All occurrences of score " << score << " have been deleted." << endl;
    }
    else {
        cout << "Score " << score << " not found in any match." << endl;
    }
}

void doubly_linked_list::display_forward() {
    if (head == nullptr) {
        cout << "No scores recorded yet." << endl;
    }
    else {
        cout << "Scores in forward order: ";
        for (Node* current = head; current != nullptr; current = current->next) {
            cout << current->score << " ";
        }
        cout << endl;
    }
}

void doubly_linked_list::display_reversed() {
    if (tail == nullptr) {
        cout << "No scores recorded yet." << endl;
    }
    else {
        cout << "Scores in reverse order: ";
        for (Node* current = tail; current != nullptr; current = current->previous) {
            cout << current->score << " ";
        }
        cout << endl;
    }
}

void doubly_linked_list::find_highest() {
    if (head == nullptr) {
        cout << "No scores to evaluate." << endl;
        return;
    }

    int max = INT_MIN;
    Node* current = head;
    while (current != nullptr) {
        if (current->score > max) {
            max = current->score;  // Update max if current score is higher
        }
        current = current->next;  // Move to the next node
    }
    cout << "Highest Score: " << max << endl;
}

void doubly_linked_list::find_lowest() {
    if (head == nullptr) {
        cout << "No scores to evaluate." << endl;
        return;
    }

    int min = INT_MAX;
    Node* current = head;
    while (current != nullptr) {
        if (current->score < min) {
            min = current->score;  // Update min if current score is lower
        }
        current = current->next;  // Move to the next node
    }
    cout << "Lowest Score: " << min << endl;
}

Node* doubly_linked_list::find_node(int score) {
    Node* current = head;
    while (current != nullptr) {
        if (current->score == score) {
            return current;  // Node found
        }
        current = current->next;  // Move to the next node
    }
    return nullptr;  // Node not found
}

void displayMenu() {
    cout << "\n=== Cricket Team Performance Menu ===" << endl;
    cout << "1. Insert score at the start" << endl;
    cout << "2. Insert score at the end" << endl;
    cout << "3. Delete a score" << endl;
    cout << "4. Delete all occurrences of a score" << endl;
    cout << "5. Display scores in forward order" << endl;
    cout << "6. Display scores in reverse order" << endl;
    cout << "7. Find the highest score" << endl;
    cout << "8. Find the lowest score" << endl;
    cout << "9. Exit" << endl;
}

int main() {
    doubly_linked_list list;
    string choice;
    int score;

    do {
        displayMenu();
        cout << "Enter your choice (1-9): ";
        getline(cin, choice);  // Read the entire line for the choice

        if (choice == "1") {
            cout << "Enter the score (integer): ";
            if (!(cin >> score)) {
                cin.clear();  // Clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear invalid input
                cout << "Invalid input. Please enter an integer." << endl;
                continue;
            }
            cin.ignore();  // Clear the newline character left in the buffer
            list.insert_at_beginning(score);
        }
        else if (choice == "2") {
            cout << "Enter the score (integer): ";
            if (!(cin >> score)) {
                cin.clear();  // Clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear invalid input
                cout << "Invalid input. Please enter an integer." << endl;
                continue;
            }
            cin.ignore();  // Clear the newline character left in the buffer
            list.insert_at_end(score);
        }
        else if (choice == "3") {
            cout << "Enter the score to delete: ";
            if (!(cin >> score)) {
                cin.clear();  // Clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear invalid input
                cout << "Invalid input. Please enter an integer." << endl;
                continue;
            }
            cin.ignore();  // Clear the newline character left in the buffer
            Node* nodeToDelete = list.find_node(score);
            if (nodeToDelete) {
                list.delete_node(nodeToDelete);
            }
            else {
                cout << "Score " << score << " not found in the list." << endl;
            }
        }
        else if (choice == "4") {
            cout << "Enter the score to delete all occurrences: ";
            if (!(cin >> score)) {
                cin.clear();  // Clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear invalid input
                cout << "Invalid input. Please enter an integer." << endl;
                continue;
            }
            cin.ignore();  // Clear the newline character left in the buffer
            list.delete_all_occurrences(score);  // Call the function to delete all occurrences
        }
        else if (choice == "5") {
            list.display_forward();
        }
        else if (choice == "6") {
            list.display_reversed();
        }
        else if (choice == "7") {
            list.find_highest();
        }
        else if (choice == "8") {
            list.find_lowest();
        }
        else if (choice == "9") {
            char confirm;
            cout << "Are you sure you want to exit? (y/n): ";
            cin >> confirm;
            cin.ignore();  // Clear the newline character left in the buffer
            if (confirm == 'y' || confirm == 'Y') {
                cout << "Exiting the program!......." << endl;
                break;
            }
            else {
                cout << "Returning to the menu." << endl;
            }
        }
        else {
            cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
        }

    } while (true);

    return 0;
}
