#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct Employee {
    int id;
    string name;
    string department;
    float salary;
};

void addEmployee(vector<Employee>& employees);
void displayEmployees(const vector<Employee>& employees);
void updateEmployee(vector<Employee>& employees);
void deleteEmployee(vector<Employee>& employees);
void saveToFile(const vector<Employee>& employees);
void loadFromFile(vector<Employee>& employees);


int main() {
    vector<Employee> employees;
    loadFromFile(employees); 
    
    int choice;
    do {
        cout << "\n--- Employee Management System ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employees\n";
        cout << "3. Update Employee\n";
        cout << "4. Delete Employee\n";
        cout << "5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(employees); break;
            case 2: displayEmployees(employees); break;
            case 3: updateEmployee(employees); break;
            case 4: deleteEmployee(employees); break;
            case 5: saveToFile(employees); break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}


void addEmployee(vector<Employee>& employees) {
    Employee emp;
    cout << "Enter Employee ID: ";
    cin >> emp.id;
    cin.ignore(); 
    cout << "Enter Name: ";
    getline(cin, emp.name);
    cout << "Enter Department: ";
    getline(cin, emp.department);
    cout << "Enter Salary: ";
    cin >> emp.salary;

    employees.push_back(emp);
    cout << "Employee added successfully.\n";
}


void displayEmployees(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "No employee records found.\n";
        return;
    }
    cout << "\n--- Employee Records ---\n";
    for (const auto& emp : employees) {
        cout << "ID: " << emp.id << ", Name: " << emp.name
             << ", Department: " << emp.department
             << ", Salary: $" << emp.salary << "\n";
    }
}


void updateEmployee(vector<Employee>& employees) {
    int id;
    cout << "Enter Employee ID to update: ";
    cin >> id;

    for (auto& emp : employees) {
        if (emp.id == id) {
            cin.ignore(); 
            cout << "Enter new Name: ";
            getline(cin, emp.name);
            cout << "Enter new Department: ";
            getline(cin, emp.department);
            cout << "Enter new Salary: ";
            cin >> emp.salary;

            cout << "Employee updated successfully.\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}


void deleteEmployee(vector<Employee>& employees) {
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (it->id == id) {
            employees.erase(it);
            cout << "Employee deleted successfully.\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}


void saveToFile(const vector<Employee>& employees) {
    ofstream file("employees.txt");
    if (!file) {
        cerr << "Error saving to file.\n";
        return;
    }
    for (const auto& emp : employees) {
        file << emp.id << "," << emp.name << "," << emp.department << "," << emp.salary << "\n";
    }
    file.close();
    cout << "Data saved successfully.\n";
}


void loadFromFile(vector<Employee>& employees) {
    ifstream file("employees.txt");
    if (!file) {
        cout << "No existing data found.\n";
        return;
    }
    Employee emp;
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        emp.id = stoi(line.substr(0, pos1));
        emp.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        emp.department = line.substr(pos2 + 1, pos3 - pos2 - 1);
        emp.salary = stof(line.substr(pos3 + 1));

        employees.push_back(emp);
    }
    file.close();
    cout << "Data loaded successfully.\n";
}
