#include <iostream>
#include <string>

using namespace std;

/* Abstract Factory Pattern
    Definition:
        Provide an interface for creating families of related or dependent
   objects without specifying their concrete classes.

    Note:
        1. Abstract Factory Pattern is a factory of factories.
        2. Abstract Factory Pattern provides a way to encapsulate a group of
   individual factories that have a common theme without specifying their
   concrete classes.
        3. Abstract Factory Pattern is often implemented with Factory Method
   Pattern.
*/

class Pizza {
public:
  virtual void prepare() = 0;
  virtual void bake() = 0;
  virtual void cut() = 0;
  virtual void box() = 0;
};

class NYStyleCheesePizza : public Pizza {
public:
  void prepare() { cout << "NYStyleCheesePizza prepare" << endl; }
  void bake() { cout << "NYStyleCheesePizza bake" << endl; }
  void cut() { cout << "NYStyleCheesePizza cut" << endl; }
  void box() { cout << "NYStyleCheesePizza box" << endl; }
};

class NYStyleVeggiePizza : public Pizza {
public:
  void prepare() { cout << "NYStyleVeggiePizza prepare" << endl; }
  void bake() { cout << "NYStyleVeggiePizza bake" << endl; }
  void cut() { cout << "NYStyleVeggiePizza cut" << endl; }
  void box() { cout << "NYStyleVeggiePizza box" << endl; }
};

class ChicagoStyleCheesePizza : public Pizza {
public:
  void prepare() { cout << "ChicagoStyleCheesePizza prepare" << endl; }
  void bake() { cout << "ChicagoStyleCheesePizza bake" << endl; }
  void cut() { cout << "ChicagoStyleCheesePizza cut" << endl; }
  void box() { cout << "ChicagoStyleCheesePizza box" << endl; }
};

class ChicagoStyleVeggiePizza : public Pizza {
public:
  void prepare() { cout << "ChicagoStyleVeggiePizza prepare" << endl; }
  void bake() { cout << "ChicagoStyleVeggiePizza bake" << endl; }
  void cut() { cout << "ChicagoStyleVeggiePizza cut" << endl; }
  void box() { cout << "ChicagoStyleVeggiePizza box" << endl; }
};

class PizzaFactory {
public:
  virtual Pizza *createPizza(string type) = 0;
  virtual void orderPizza(string type) {
    Pizza *pizza = createPizza(type);
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
  }
};

class NYStylePizzaStore : public PizzaFactory {
public:
  Pizza *createPizza(string type) {
    Pizza *pizza;
    if (type == "cheese")
      pizza = new NYStyleCheesePizza();
    else if (type == "veggie")
      pizza = new NYStyleVeggiePizza();
    else
      cout << "error" << endl;
    return pizza;
  }
};

class ChicagoStylePizzaStore : public PizzaFactory {
public:
  Pizza *createPizza(string type) {
    Pizza *pizza;
    if (type == "cheese")
      pizza = new ChicagoStyleCheesePizza();
    else if (type == "veggie")
      pizza = new ChicagoStyleVeggiePizza();
    else
      cout << "error" << endl;
    return pizza;
  }
};

enum class Store { NY, Chicago };

class PizzaStore {
public:
  PizzaFactory *createPizzaStore(Store store) {
    PizzaFactory *pizzaStore;
    if (store == Store::NY)
      // Preprocessing for NYStylePizzaStore
      pizzaStore = new NYStylePizzaStore();
    else if (store == Store::Chicago)
      // Preprocessing for ChicagoStylePizzaStore
      pizzaStore = new ChicagoStylePizzaStore();
    else
      cout << "error" << endl;
    return pizzaStore;
  }
};

int main() {
  // Type 1
  PizzaStore *pizzaStore = new PizzaStore();
  PizzaFactory *nyStore = pizzaStore->createPizzaStore(Store::NY);
  PizzaFactory *chicagoStore = pizzaStore->createPizzaStore(Store::Chicago);
  nyStore->orderPizza("cheese");
  chicagoStore->orderPizza("veggie");

  // Type 2
  PizzaFactory *nyStore2 = new NYStylePizzaStore();
  PizzaFactory *chicagoStore2 = new ChicagoStylePizzaStore();
  nyStore2->orderPizza("cheese");
  chicagoStore2->orderPizza("veggie");
  return 0;
}
