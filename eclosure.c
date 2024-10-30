#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 100

int closure[MAX_STATES][MAX_STATES]; // To store epsilon closures
int epsilon_transitions[MAX_STATES][MAX_STATES]; // To store epsilon transitions
int closure_size[MAX_STATES]; // To store size of each state's closure

// Function to recursively find epsilon closure for a given state
void find_closure(int state, int current_state) {
    for (int next_state = 0; next_state < MAX_STATES; next_state++) {
        if (epsilon_transitions[current_state][next_state] == 1 && !closure[state][next_state]) {
            closure[state][next_state] = 1;
            closure_size[state]++;
            find_closure(state, next_state); // Recursively find closure
        }
    }
}

// Function to calculate the epsilon closure for each state
void compute_closures(int num_states) {
    for (int state = 0; state < num_states; state++) {
        closure[state][state] = 1; // Each state includes itself
        closure_size[state] = 1;
        find_closure(state, state); // Find all reachable states via epsilon transitions
    }
}

// Function to display epsilon closures
void display_closures(int num_states) {
    for (int state = 0; state < num_states; state++) {
        printf("Epsilon closure of state %d: { ", state);
        for (int i = 0; i < MAX_STATES; i++) {
            if (closure[state][i]) {
                printf("%d ", i);
            }
        }
        printf("}\n");

    }
}

int main() {
    int num_states, num_transitions;

    // Initialize arrays
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_STATES; j++) {
            closure[i][j] = 0;
            epsilon_transitions[i][j] = 0;
        }
        closure_size[i] = 0;
    }

    // Input number of states and transitions
    printf("Enter the number of states in the NFA: ");
    scanf("%d", &num_states);

    printf("Enter the number of epsilon transitions: ");
    scanf("%d", &num_transitions);

    printf("Enter the epsilon transitions:\n");
    for (int i = 0; i < num_transitions; i++) {
        int from_state, to_state;
        scanf("%d %d", &from_state, &to_state);
        epsilon_transitions[from_state][to_state] = 1; // Mark epsilon transition
    }

    // Compute epsilon closures
    compute_closures(num_states);

    // Display epsilon closures for all states
    display_closures(num_states);

    return 0;
}

