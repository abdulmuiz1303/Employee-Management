#include <iostream>
#include <cstring>   
using namespace std;

class Employee {
private:
    char* name;
    int id;
    double salary;

    static int empCount;
    static const string companyName;

public:
    // Constructor with initializer list
    Employee(const char* n, int id, double salary) : id(id), salary(salary) {
        this->name = new char[strlen(n) + 1];
        strcpy_s(this->name, strlen(n) + 1, n);   
        empCount++;
    }

    // Copy Constructor (Deep Copy)
    Employee(const Employee& other) : id(other.id), salary(other.salary) {
        this->name = new char[strlen(other.name) + 1];
        strcpy_s(this->name, strlen(other.name) + 1, other.name);  
        empCount++;
    }

    // Destructor
    ~Employee() {
        delete[] name;
        empCount--;
    }

    // Display employee details
    void display() const {
        cout << "Company: " << companyName << endl;
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Salary: " << salary << endl;
        cout << "-----------------------------" << endl;
    }

    // Static function to show total employees
    static void showCount() {
        cout << "Total Employees: " << empCount << endl;
    }

    // Update salary using 'this' pointer
    void updateSalary(double newSalary) {
        this->salary = newSalary;
    }

    // Update name using 'this' pointer
    void updateName(const char* newName) {
        delete[] this->name;
        this->name = new char[strlen(newName) + 1];
        strcpy_s(this->name, strlen(newName) + 1, newName);  
    }

    // Function that returns a new Employee object with bonus added
    Employee giveBonus(double bonusPercent) const {
        Employee temp(this->name, this->id, this->salary);
        temp.salary += temp.salary * bonusPercent / 100;
        return temp; 
    }

    // Static function - Pass object by value
    static void showEmployeeByValue(Employee e) {
        cout << "[Passed by Value]" << endl;
        e.display();
    }

    // Static function - Pass object by reference
    static void showEmployeeByReference(const Employee& e) {
        cout << "[Passed by Reference]" << endl;
        e.display();
    }
};

// Static member initialization
int Employee::empCount = 0;
const string Employee::companyName = "TechSolutions";

// Main function
int main() {
    cout << "=== Employee Management System ===\n" << endl;

    Employee* e1 = new Employee("Atir", 10, 500000);
    e1->display();
    Employee::showCount();

    // Creating a deep copy
    Employee e2 = *e1;
    cout << "\n[Deep Copy Created as e2]" << endl;
    e2.display();

    // Modify original
    e1->updateName("Ahmed");
    e1->updateSalary(400000);

    cout << "\nAfter modifying original (e1):" << endl;
    cout << "Original Object (e1):" << endl;
    e1->display();

    cout << "Copied Object (e2):" << endl;
    e2.display();

    Employee::showEmployeeByValue(*e1);
    Employee::showEmployeeByReference(e2);

    Employee e3 = e2.giveBonus(10);
    cout << "\n[After Bonus Returned Object]" << endl;
    e3.display();
    Employee::showCount();

    delete e1;
    cout << "\nAfter deleting e1:\n" << endl;
    Employee::showCount();

    cout << "\nProgram Ended Successfully." << endl;
    return 0;
}
