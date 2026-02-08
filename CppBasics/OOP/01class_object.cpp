#include <iostream>
using namespace std;

/*
class is user defined data type, which holds it's own data memebers 
and member functions, which can be accessed and used by creating object. 
It is blueprint for an object.

An Object is an instance of a Class. When a class is defined, 
no memory is allocated but when it is instantiated 
(i.e. an object is created) memory is allocated.
*/

class Student{
public:
    int id;
    Student(){
        id = -1;
    }

    void setRollNo(int _rollno){
        this->id = _rollno;
    }

    void printRollNo(); // define member function outside of the class
};

//using scope resolution operator
void Student::printRollNo(){
    cout << "Roll no is: " << this->id << endl;
}

int main(){
    Student obj;
    // obj.setRollNo(26);
    obj.printRollNo();
}