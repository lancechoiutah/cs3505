#include <iostream>


using std::cout;
using std::endl;

class Student{
    public:
        int id;

        int operator+(const Student& other) const {
            return this->id + other.id;
        }
        Student operator+(int value) const {
            return Student{this->id + value};
        }
        friend std::ostream& operator<<(std::ostream& os, const Student& s);
};
std::ostream& operator<<(std::ostream& os, const Student& s) {
    // 위에서 친구 허락을 받아놨기 때문에, 밖에서도 private id를 건드릴 수 있습니다.
    os << "Student ID: " << s.id; 
    return os;
}
class Teacher{
    public:
        int id;

        bool operator==(const Student& s) const {
            return this->id == s.id;
        }
        int operator+(const Student& s) const {
            return this->id + s.id;
        }
};
int main() {
    Student s1;
    s1.id = 10;
    Student s2 = s1 + 100;
    cout << "Student ID: " << s1.id << endl;
    Teacher t1;
    t1.id = 20;
    cout << "Teacher ID: " << t1.id << endl;
    if (t1 == s1) {
        cout << "IDs are equal." << endl;
    } else {
        cout << "IDs are not equal." << endl;
    }
    int sum = t1 + s1;
    int sum2 = s1 + s1;
    cout << "Sum of Teacher and Student IDs: " << sum << endl;
    cout << "Sum of IDs: " << sum << endl;
    cout<<s2.id<<endl;
    cout << s2 << endl;
    return 0;
}