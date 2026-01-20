#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*  Observer Pattern
    Definition: The Observer Pattern defines a one-to-many dependency between
   objects so that when one object changes state, all of its dependents are
   notified and updated automatically.

    Note:

*/

// --------------------- Weather Dataclass ----------------------
typedef struct WeatherData {
  float tempertature;
  float humidity;
  float pressure;
  WeatherData(float temperature = 0, float humidity = 0, float pressure = 0) {
    this->tempertature = temperature;
    this->humidity = humidity;
    this->pressure = pressure;
  }
} WeatherData;

// ---------------------- Observer Interface -------------------
/*  Observer Interface
    This is the interface for all the observers
    All the observers must implement this interface
*/
class Observer {
public:
  ~Observer() {};
  virtual void update(WeatherData *data) = 0;
};

// ---------------------------------------------Subject
// Interface------------------------------------
/*  Subject Interface
    This is the interface for all the subjects
    All the subjects must implement this interface
*/
class Subject {
public:
  ~Subject() {};
  virtual void registerObserver(Observer *o) {};
  virtual void removeObserver(Observer *o) {};
  virtual void notifyObserver() const = 0;
};

// ------------------------------------------Weather Monitor
// class-----------------------------------
/* Weather Monitor
    This is the concrete subject class
    This class implements the Subject interface
    This class is responsible for registering,removing and notifying the
   observers
*/
class WeatherMointor : public Subject {
private:
  vector<Observer *> observers;
  WeatherData *data;

public:
  WeatherMointor() { data = new WeatherData(); }
  void registerObserver(Observer *o) override { observers.push_back(o); }
  void removeObserver(Observer *o) override {

    for (auto it = observers.begin(); it != observers.end(); it++) {
      if (*it == o) {
        observers.erase(it);
        break;
      }
    }
  }
  void notifyObserver() const override {
    for (auto it : observers) {
      it->update(data);
    }
  }
  void dataUpdated() { notifyObserver(); }
  void setData(float temperature, float humidity, float pressure) {
    data->humidity = humidity;
    data->pressure = pressure;
    data->tempertature = temperature;
    dataUpdated();
  }
};

// --------------------------------------------Concrete Observer
// Class---------------------------------
/* Current Weather Display
    This is the concrete observer class
    This class implements the Observer interface
    This class is responsible for displaying the current weather data
*/
class CurrentWeatherDisplay : public Observer {
private:
  WeatherData *data;

public:
  CurrentWeatherDisplay() {}

  void update(WeatherData *data) override {
    this->data = data;
    display();
  }

  void display() {
    cout << "Current Weather Data" << endl;
    cout << "Temperature: " << data->tempertature << endl;
    cout << "Humidity: " << data->humidity << endl;
    cout << "Pressure: " << data->pressure << endl;
  }
};

// --------------------------------------------Concrete Observer
// Class---------------------------------
class ForecastWeatherDisplay : public Observer {
private:
  WeatherData *data;

public:
  ForecastWeatherDisplay() {}

  void update(WeatherData *data) override {
    this->data = data;
    display();
  }

  void display() {
    cout << "Forecast Weather Data" << endl;
    cout << "Temperature: " << data->tempertature << endl;
    cout << "Humidity: " << data->humidity << endl;
    cout << "Pressure: " << data->pressure << endl;
  }
};

// --------------------------------------------Main
// Function-------------------------------------------
int main() {
  WeatherMointor *weatherReporter = new WeatherMointor();
  CurrentWeatherDisplay *currentWeatherDisplay = new CurrentWeatherDisplay();
  ForecastWeatherDisplay *forecastWeatherDisplay = new ForecastWeatherDisplay();

  // Register the observer
  weatherReporter->registerObserver(currentWeatherDisplay);

  weatherReporter->setData(10, 20, 30);
  weatherReporter->registerObserver(forecastWeatherDisplay);
  weatherReporter->setData(20, 30, 40);

  weatherReporter->removeObserver(currentWeatherDisplay);

  weatherReporter->setData(30, 40, 50);
  return 0;
}
