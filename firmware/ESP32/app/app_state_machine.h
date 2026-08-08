#ifndef APP_STATE_MACHINE_H
#define APP_STATE_MACHINE_H

// Machine health finite-state machine.
// States: BOOT -> INITIALIZING -> HEALTHY <-> WARNING <-> FAULT -> HEALTHY
// Transitions are driven by TinyML predictions and debounced (require N
// consecutive consistent predictions) to avoid unstable rapid switching.

enum class MachineState {
  BOOT,
  INITIALIZING,
  HEALTHY,
  WARNING,
  FAULT
};

class AppStateMachine {
 public:
  AppStateMachine();

  void begin();

  // Feed the latest TinyML prediction (0=Healthy, 1=Warning, 2=Fault).
  // Returns true if the machine state changed this call.
  bool update(int predictedClassIndex);

  MachineState currentState() const { return state_; }
  const char*  currentStateName() const;

 private:
  MachineState state_;
  int lastPrediction_;
  int consistentCount_;

  static constexpr int kDebounceThreshold = 3;

  MachineState classIndexToState(int classIndex) const;
};

#endif // APP_STATE_MACHINE_H
