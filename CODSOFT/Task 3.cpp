#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure to represent a task
struct Task {
    string description;
    bool completed;

    Task(const string& desc) : description(desc), completed(false) {}
};

class TodoList {
private:
    vector<Task> tasks;

public:
    // Add a new task to the list
    void addTask(const string& description) {
        tasks.push_back(Task(description));
        cout << "Task added successfully!" << endl;
    }

    // Mark a task as completed
    void markTaskCompleted(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].completed = true;
            cout << "Task marked as completed!" << endl;
        }
        else {
            cout << "Invalid task index!" << endl;
        }
    }

    // Remove a task from the list
    void removeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
            cout << "Task removed successfully!" << endl;
        }
        else {
            cout << "Invalid task index!" << endl;
        }
    }

    // Display all tasks with their status
    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks to display." << endl;
        }
        else {
            cout << "Tasks:" << endl;
            for (size_t i = 0; i < tasks.size(); ++i) {
                cout << i + 1 << ". ";
                cout << (tasks[i].completed ? "[X] " : "[ ] ");
                cout << tasks[i].description << endl;
            }
        }
    }
};

int main() {
    TodoList todoList;

    char choice;
    do {
        cout << "\nMENU:\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            string description;
            cout << "Enter task description: ";
            cin.ignore();
            getline(cin, description);
            todoList.addTask(description);
            break;
        }
        case '2':
            todoList.viewTasks();
            break;
        case '3': {
            int index;
            cout << "Enter index of task to mark as completed: ";
            cin >> index;
            todoList.markTaskCompleted(index - 1); // Subtract 1 since index is 1-based
            break;
        }
        case '4': {
            int index;
            cout << "Enter index of task to remove: ";
            cin >> index;
            todoList.removeTask(index - 1); // Subtract 1 since index is 1-based
            break;
        }
        case '5':
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != '5');

    return 0;
}
