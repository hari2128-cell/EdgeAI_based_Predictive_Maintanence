#ifndef LABELS_H
#define LABELS_H

// Class label order MUST match the order used during model training.
constexpr const char* kClassLabels[3] = {"Healthy", "Warning", "Fault"};
constexpr int kNumClasses = 3;

#endif // LABELS_H
