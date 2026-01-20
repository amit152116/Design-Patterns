#include <iostream>
#include <random>
#include <string>

using namespace std;

/* Strategy Pattern

    Definition: The Strategy Pattern defines a family of algorithms,
   encapsulates each one, and makes them interchangeable. Strategy lets the
   algorithm vary independently from clients that use it.

    Note:

*/

// --------------Payment Interface------------------------
class PaymentInterface {
public:
  virtual void transact() = 0;
  virtual ~PaymentInterface() { cout << "Payment Method Deleted" << endl; }
};

// ----------------------Payment Methods-----------------------
class CreditCard : public PaymentInterface {
public:
  void transact() override { cout << "Credit Card Payment" << endl; }
};

class PayPal : public PaymentInterface {
public:
  void transact() override { cout << "PayPal Payment" << endl; }
};
class UPI : public PaymentInterface {
public:
  void transact() override { cout << "UPI Payment" << endl; }
};

// ---------------------Customer Abstract Class-------------
class Customer {
protected:
  string customerId;
  string firstName;
  string lastName;
  string address;
  string phone;
  string email;
  PaymentInterface *paymentMethod;

public:
  Customer(string firstName, string lastName, string address, string phone,
           string email) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->address = address;
    this->phone = phone;
    this->email = email;
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> dis(100000, 999999);
    customerId = to_string(dis(gen));
    return;
  }

  string getCustomerId() { return this->customerId; }

  void setPaymentMethod(PaymentInterface *paymentMethod) {
    cout << "Payment Method Changed" << endl;
    this->paymentMethod = paymentMethod;
  }

  void makePayment() { this->paymentMethod->transact(); }

  virtual void display() {
    cout << "Customer Id: " << this->customerId << endl;
    cout << "First Name: " << this->firstName << endl;
    cout << "Last Name: " << this->lastName << endl;
    cout << "Address: " << this->address << endl;
    cout << "Phone: " << this->phone << endl;
    cout << "Email: " << this->email << endl;
  }
};

// ---------------------------------------------Customer Concrete
// Classes-------------------------------------
class KotakCustomer : public Customer {
public:
  KotakCustomer(string firstName, string lastName, string address, string phone,
                string email)
      : Customer(firstName, lastName, address, phone, email) {
    Customer::customerId = "KKBK" + this->customerId;
    Customer::paymentMethod = new CreditCard();
  }

  void display() override {
    cout << "Bank Name : Kotak Bank" << endl;
    Customer::display();
  }
};

class ICICICustomer : public Customer {
public:
  ICICICustomer(string firstName, string lastName, string address, string phone,
                string email)
      : Customer(firstName, lastName, address, phone, email) {
    Customer::customerId = "ICIC" + this->customerId;
    Customer::paymentMethod = new PayPal();
  }

  void display() override {
    cout << "Bank Name : ICICI Bank" << endl;
    Customer::display();
  }
};

class HDFCCustomer : public Customer {
public:
  HDFCCustomer(string firstName, string lastName, string address, string phone,
               string email)
      : Customer(firstName, lastName, address, phone, email) {
    Customer::customerId = "HDFC" + this->customerId;
    Customer::paymentMethod = new CreditCard();
  }
  void display() override {
    cout << "Bank Name : HDFC Bank" << endl;
    Customer::display();
  }
};

class SBICustomer : public Customer {
public:
  SBICustomer(string firstName, string lastName, string address, string phone,
              string email)
      : Customer(firstName, lastName, address, phone, email) {
    Customer::customerId = "SBIN" + this->customerId;
    Customer::paymentMethod = new UPI();
  }
  void display() override {
    cout << "Bank Name : SBI Bank" << endl;
    Customer::display();
  }
};

int main() {

  Customer *amit = new KotakCustomer("Amit", "Kumar", "Delhi", "1234567890",
                                     "amit152116@gmail.com");
  cout << amit->getCustomerId() << endl;
  amit->display();
  amit->makePayment();
  cout << endl;

  Customer *sumit = new ICICICustomer("Sumit", "Kumar", "Delhi", "1234567890",
                                      "sumit@gmail.com");
  cout << sumit->getCustomerId() << endl;
  sumit->display();
  sumit->makePayment();
  sumit->setPaymentMethod(new UPI());
  sumit->makePayment();
  cout << endl;

  Customer *ram = new HDFCCustomer("Ram", "Kumar", "Delhi", "1234567890",
                                   "asldkjfa@gmail.com");
  cout << ram->getCustomerId() << endl;
  ram->display();
  ram->makePayment();
  cout << endl;

  Customer *shyam =
      new SBICustomer("Shyam", "Kumar", "Delhi", "1234567890", "alsj@mail.com");
  cout << shyam->getCustomerId() << endl;
  shyam->display();
  shyam->makePayment();
  shyam->setPaymentMethod(new PayPal());
  shyam->makePayment();
  cout << endl;

  return 0;
}
