#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Factory Method Pattern
    Definition:
        Factory Method is a creational design pattern that provides an interface
   for creating objects in a superclass, but allows subclasses to alter the type
   of objects that will be created.

    Note:
        1. Factory Method is a good choice when you don't know ahead of time
   what class object you need.
        2. Factory Method is a good choice when you want to localize the
   knowledge of which class gets created.
        3. Factory Method is a good choice when you want to give users of the
   framework a way to extend or replace the framework's components.
        4. Factory Method is a good choice when you want to promote loose
   coupling.

*/

class Pizza {
public:
  virtual void prepare() = 0;
  virtual void bake() = 0;
  virtual void cut() = 0;
  virtual void box() = 0;
};

class VeggiePizza : public Pizza {
public:
  void prepare() { cout << "VeggiePizza prepare" << endl; }
  void bake() { cout << "VeggiePizza bake" << endl; }
  void cut() { cout << "VeggiePizza cut" << endl; }
  void box() { cout << "VeggiePizza box" << endl; }
};

class CheesePizza : public Pizza {
public:
  void prepare() { cout << "CheesePizza prepare" << endl; }
  void bake() { cout << "CheesePizza bake" << endl; }
  void cut() { cout << "CheesePizza cut" << endl; }
  void box() { cout << "CheesePizza box" << endl; }
};

class PizzaFactory {
public:
  Pizza *createPizza(string type) {
    if (type == "cheese") {
      return new CheesePizza();
    } else if (type == "veggie") {
      return new VeggiePizza();
    } else {
      return NULL;
    }
  }
  void orderPizza(string type) {
    Pizza *pizza = createPizza(type);
    if (pizza == NULL) {
      cout << "Sorry, we don't have " << type << " pizza" << endl;
      return;
    }
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
  }
};

int main() {
  PizzaFactory *pizzaFactory = new PizzaFactory();
  pizzaFactory->orderPizza("cheese");
  pizzaFactory->orderPizza("veggie");
  pizzaFactory->orderPizza("pepperoni");
  return 0;
}
