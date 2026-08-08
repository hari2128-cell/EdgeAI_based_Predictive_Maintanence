#include "app_state_machine.h"

AppStateMachine::AppStateMachine()
    : state_(MachineState::BOOT), lastPrediction_(-1), consistentCount_(0) {}

void AppStateMachine::begin() {
  state_ = MachineState::INITIALIZING;
  lastPrediction_ = -1;
  consistentCount_ = 0;
}

MachineState AppStateMachine::classIndexToState(int classIndex) const {
  switch (classIndex) {
    case 0: return MachineState::HEALTHY;
    case 1: return MachineState::WARNING;
    case 2: return MachineState::FAULT;
    default: return state_;
  }
}

bool AppStateMachine::update(int predictedClassIndex) {
  if (predictedClassIndex == lastPrediction_) {
    consistentCount_++;
  } else {
    lastPrediction_ = predictedClassIndex;
    consistentCount_ = 1;
  }

  if (consistentCount_ >= kDebounceThreshold) {
    MachineState newState = classIndexToState(predictedClassIndex);
    if (newState != state_) {
      state_ = newState;
      return true;
    }
  }
  return false;
}

const char* AppStateMachine::currentStateName() const {
  switch (state_) {
    case MachineState::BOOT:          return "Boot";
    case MachineState::INITIALIZING:  return "Initializing";
    case MachineState::HEALTHY:       return "Healthy";
    case MachineState::WARNING:       return "Warning";
    case MachineState::FAULT:         return "Fault";
    default:                          return "Unknown";
  }
}
