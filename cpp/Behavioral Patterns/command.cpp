#include <fmt/core.h>

#include <memory>
#include <vector>

namespace {
// Receiver — knows how to perform the work.
class Drone {
public:
  void takeoff() { fmt::print("TakeOff\n"); }
  void arm() { fmt::print("Arm\n"); }
  void land() { fmt::print("Land\n"); }
  void disarm() { fmt::print("Disarm\n"); }
  void rtl() { fmt::print("RTL\n"); }
  void move_forward(int meters) { fmt::print("Moving forward {}m\n", meters); }
};

// Command — abstract request.
class Command {
public:
  virtual ~Command() = default;
  virtual void execute() = 0;
  virtual void undo() = 0;
};

// ConcreteCommands — each binds a receiver at construction.
class ArmCommand : public Command {
  Drone &drone;

public:
  explicit ArmCommand(Drone &drone) : drone(drone) {}
  void execute() override { drone.arm(); }
  void undo() override { drone.disarm(); }
};

class TakeOffCommand : public Command {
  Drone &drone;

public:
  explicit TakeOffCommand(Drone &drone) : drone(drone) {}
  void execute() override { drone.takeoff(); }
  void undo() override { drone.land(); }
};

class LandCommand : public Command {
  Drone &drone;

public:
  explicit LandCommand(Drone &drone) : drone(drone) {}
  void execute() override { drone.land(); }
  void undo() override { drone.takeoff(); }
};

class MoveForwardCommand : public Command {
  Drone &drone;
  int meters;

public:
  MoveForwardCommand(Drone &drone, int meters) : drone(drone), meters(meters) {}
  void execute() override { drone.move_forward(meters); }
  void undo() override { drone.move_forward(-meters); }
};

// Invoker — triggers commands and tracks history. Knows only Command.
class RemoteControl {
  std::vector<std::unique_ptr<Command>> history;

public:
  void submit(std::unique_ptr<Command> command) {
    command->execute();
    history.push_back(std::move(command));
  }

  void undo_last() {
    if (history.empty()) {
      return;
    }
    history.back()->undo();
    history.pop_back();
  }
};
} // namespace

int main() {
  Drone drone;
  RemoteControl remote;

  remote.submit(std::make_unique<ArmCommand>(drone));
  remote.submit(std::make_unique<TakeOffCommand>(drone));
  remote.submit(std::make_unique<MoveForwardCommand>(drone, 10));
  remote.submit(std::make_unique<LandCommand>(drone));

  remote.undo_last(); // undo Land -> takeoff again
}
