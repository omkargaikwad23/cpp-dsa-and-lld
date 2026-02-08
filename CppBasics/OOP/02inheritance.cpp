#include <iostream>
using namespace std;

/*
The capability of a class to derive properties and characteristics from another class is called Inheritance.
*/

class Person{
    string name;
    int age;
public:
    void setNameAge(){
        cout << "Enter name and age:";
        cin >> name >> age;
    }

    void printNameAge(){
        cout << "Name:" << this->name << "\nAge:" << this->age << endl;
    }
};

// class  <derived_class_name> : <access-specifier> <base_class_name>
// {
//     //body
// }
class Student : private Person{
    int rollNo;
public:
    void setInfo(){
        setNameAge();
        cout << "Enter rollNo:"; 
        cin >> rollNo;
    }

    void printInfo(){
        printNameAge();
        cout << "Roll no: " << this->rollNo << endl;
    }
};

int main(){
    Student obj;
    obj.setInfo();
    obj.printInfo();
}