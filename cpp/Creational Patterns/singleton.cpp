#include <iostream>
#include <vector>

using namespace std;

/* Singleton Pattern
    Definition: Ensure a class has only one instance, and provide a global point
   of access to it.
*/

class Singleton {
private:
  string name, address, phone;
  static Singleton *instance;
  Singleton() {};

public:
  static Singleton *getInstance() {
    if (instance == nullptr) {
      instance = new Singleton();
    }
    return instance;
  }

  void addInfo(string name, string address, string phone) {
    this->name = name;
    this->address = address;
    this->phone = phone;
  }
  void getInfo() {
    cout << "Name: " << name << endl;
    cout << "Address: " << address << endl;
    cout << "Phone: " << phone << endl;
  }
};

Singleton *Singleton::instance = nullptr;

int main() {

  Singleton *instance = Singleton::getInstance();
  instance->addInfo("John", "1234", "123456789");
  instance->getInfo();

  Singleton *instance2 = Singleton::getInstance();
  instance2->getInfo();
  return 0;
}
