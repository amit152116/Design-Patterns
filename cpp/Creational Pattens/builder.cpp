#include <fmt/format.h>

/*

Say you have a constructor with ten optional parameters. Calling such a beast is
very inconvenient; therefore, you overload the constructor and create several
shorter versions with fewer parameters. These constructors still refer to the
main one, passing some default values into any omitted parameters.

*/
class Computer {
public:
  // Computer(std::string cpu, std::string ram, std::string storage)
  //     : cpu_(cpu), ram_(ram), storage_(storage) {}

  void setCpu(std::string cpu) { cpu_ = cpu; }

  void setRam(std::string ram) { ram_ = ram; }

  void setStorage(std::string storage) { storage_ = storage; }

  void displayInfo() const {
    fmt::print("Computer Config: \nCPU: {}\nRAM:{}\nSTORAGE:{}\n\n", cpu_, ram_,
               storage_);
  }

private:
  std::string cpu_;
  std::string ram_;
  std::string storage_;
};

class Builder {
public:
  virtual void buildCpu() = 0;
  virtual void buildRam() = 0;
  virtual void buildStorage() = 0;
  virtual Computer getResult() = 0;
};

class GamingComputerBuilder : public Builder {
private:
  Computer computer_;

public:
  GamingComputerBuilder() {}
  void buildCpu() override { computer_.setCpu("Intel i7 14th gen"); }
  void buildRam() override { computer_.setRam("16 GB DDR5"); };
  void buildStorage() override { computer_.setStorage("2TB SSD Nvme"); };
  Computer getResult() override { return computer_; }
};
class ProfessionalComputerBuilder : public Builder {
private:
  Computer computer_;

public:
  ProfessionalComputerBuilder() {}
  void buildCpu() override { computer_.setCpu("Intel i9 11th gen"); }
  void buildRam() override { computer_.setRam("32 GB DDR5"); };
  void buildStorage() override { computer_.setStorage("1TB SSD Nvme"); };
  Computer getResult() override { return computer_; }
};

class Director {
public:
  void construct(Builder &builder) {
    builder.buildCpu();
    builder.buildRam();
    builder.buildStorage();
  }
};

int main(int argc, char *argv[]) {

  GamingComputerBuilder gamingBuilder;
  Director director;

  director.construct(gamingBuilder);
  auto computer = gamingBuilder.getResult();
  computer.displayInfo();

  ProfessionalComputerBuilder proBuilder;
  director.construct(proBuilder);
  auto proComputer = proBuilder.getResult();
  proComputer.displayInfo();

  return 0;
}
