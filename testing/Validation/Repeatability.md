# Repeatability Testing

## Objective
Verify that repeated runs of the same machine condition produce consistent classifications, and that the debounce logic (`kDebounceThreshold = 3` in `app_state_machine.cpp`) effectively prevents state flapping under noisy single-cycle predictions.

## Method
1. Run the system against the same machine condition (e.g., Healthy) for an extended period (e.g., 30+ minutes).
2. Log every state transition reported (LED changes, MQTT `machine_state` changes).
3. Count unexpected transitions (i.e., transitions away from and back to the expected state within a short window).

## Success Criterion
No unexpected state transitions during a sustained, unchanged machine condition.

**Status:** Method defined; results pending sustained hardware testing.
