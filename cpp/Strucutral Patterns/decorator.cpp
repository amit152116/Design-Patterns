#include <iostream>
#include <string>

using namespace std;

// Design Principle : Classes should be open for extension but closed for
// modification.

/* Decorator Pattern
    Definition: The Decorator Pattern attaches additional responsibilities to an
   object dynamically. Decorators provide a flexible alternative to subclassing
   for extending functionality.

    Note: If you have code that relies on the concrete component's type,
   decorator will break that code. As long as you only write code againt the
   abstract component type, the use of decorators will remain transparent to the
   client. How ever once you start writing code against the concrete component
   type, you'll want to rethink your application's design.
*/

// --------------------Coffee Abstract Class--------------------------
class Coffee {
protected:
  string description;
  double cost;

public:
  Coffee(string description, double cost) {
    this->description = description;
    this->cost = cost;
  };

  virtual string getDescription() const { return description; }
  virtual double getCost() const { return cost; }
  virtual ~Coffee() {};
};

// -------------------Coffee Concrete Classes----------------------------

// Espresso
class Espresso : public Coffee {
public:
  Espresso() : Coffee("Espresso", 1.99) {};
};

// HouseBlend
class HouseBlend : public Coffee {
public:
  HouseBlend() : Coffee("House Blend Coffee", 0.89) {};
};
// Dark Roast
class DarkRoast : public Coffee {
public:
  DarkRoast() : Coffee("Dark Roast Coffee", 0.99) {};
};

// ------------------Coffee Decorator Abstract Class-------------------
class CoffeeDecorator : public Coffee {
protected:
  Coffee *coffee;

public:
  CoffeeDecorator(Coffee *coffee, string description, double cost)
      : Coffee(description, cost) {
    this->coffee = coffee;
  }
  string getDescription() const override {
    return coffee->getDescription() + " " + description;
  }
  double getCost() const override { return coffee->getCost() + cost; }
};

// ------------------Coffee Decorator Concrete Classes-------------------
class Mocha : public CoffeeDecorator {
public:
  Mocha(Coffee *coffee) : CoffeeDecorator(coffee, "Mocha", 0.20) {};
};

class Whip : public CoffeeDecorator {
public:
  Whip(Coffee *coffee) : CoffeeDecorator(coffee, "Whip", 0.10) {};
};

class Soy : public CoffeeDecorator {
public:
  Soy(Coffee *coffee) : CoffeeDecorator(coffee, "Soy", 0.15) {};
};

class SteamedMilk : public CoffeeDecorator {
public:
  SteamedMilk(Coffee *coffee)
      : CoffeeDecorator(coffee, "Steamed Milk", 0.10) {};
};

int main() {
  Coffee *coffee = new Espresso();
  cout << coffee->getDescription() << " = $" << coffee->getCost() << endl;
  coffee = new Mocha(coffee);
  cout << coffee->getDescription() << " = $" << coffee->getCost() << endl;
  coffee = new Whip(coffee);
  cout << coffee->getDescription() << " = $" << coffee->getCost() << endl;
  coffee = new Soy(coffee);
  cout << coffee->getDescription() << " = $" << coffee->getCost() << endl;
  coffee = new SteamedMilk(coffee);
  cout << coffee->getDescription() << " = $" << coffee->getCost() << endl;

  Coffee *coffee2 = new DarkRoast();
  cout << coffee2->getDescription() << " = $" << coffee2->getCost() << endl;
  coffee2 = new Mocha(coffee2);
  cout << coffee2->getDescription() << " = $" << coffee2->getCost() << endl;
  return 0;
}
