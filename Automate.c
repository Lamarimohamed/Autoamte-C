#include <stdio.h>
#include <stdlib.h>

typedef struct Liste {
    int val;
    struct Liste *suivant;
} Liste;

typedef struct Automate {
    int q0;
    int **delta; // 2D array to store transitions
    Liste *finaux;
} Automate;

void afficherListe(const Liste *liste) {
    for (const Liste *ptr = liste; ptr != NULL; ptr = ptr->suivant) {
        printf("%d ", ptr->val);
    }
    printf("\n");
}

void afficherAutomate(const Automate *automate) {
    printf("Etat initial: %d\n", automate->q0); // Display initial state

    printf("Transitions :\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            if (automate->delta[i][j] != -1) {
                printf("State %d on input %d: %d\n", i, j, automate->delta[i][j]);
            }
        }
    }

    printf("\n");
    printf("Etats finaux :\n");
    afficherListe(automate->finaux);
}

int reconnaitre(const Automate *automate, const int *word, int length) {
    int currentState = automate->q0;
    for (int i = 0; i < length; i++) {
        int inputSymbol = word[i];
        currentState = automate->delta[currentState][inputSymbol];
        if (currentState == -1) {
            return 0; // Not recognized
        }
    }
    // Check if the final state is reached
    for (const Liste *ptr = automate->finaux; ptr != NULL; ptr = ptr->suivant) {
        if (ptr->val == currentState) {
            return 1; // Recognized
        }
    }
    return 0; // Not recognized
}

int main() {
    Automate automate = {0, (int **)malloc(3 * sizeof(int *)), NULL};
    for (int i = 0; i < 3; i++) {
        automate.delta[i] = (int *)malloc(2 * sizeof(int));
    }

    automate.delta[0][0] = 0;
    automate.delta[0][1] = 1;
    automate.delta[1][0] = 2;
    automate.delta[1][1] = 1;
    automate.delta[2][0] = -1; // Not a valid transition
    automate.delta[2][1] = -1; // Not a valid transition

    automate.finaux = malloc(sizeof(Liste));
    if (automate.finaux == NULL) {
        return 1; // Error in memory allocation
    }
    automate.finaux->val = 2; // Set final state (replace with your actual final states)
    automate.finaux->suivant = NULL;

    afficherAutomate(&automate);

    // Take input from the user for the word
    printf("\nEnter the length of the word: ");
    int length;
    scanf("%d", &length);

    int *word = (int *)malloc(length * sizeof(int));
    if (word == NULL) {
        return 1; // Error in memory allocation
    }

    printf("Enter the word (sequence of 0s and 1s separated by spaces): ");
    for (int i = 0; i < length; i++) {
        scanf("%d", &word[i]);
    }

    // Test the recognition function with the user's word
    printf("Recognition result: %s\n", reconnaitre(&automate, word, length) ? "Recognized" : "Not recognized");

    // Free allocated memory
    for (int i = 0; i < 3; i++) {
        free(automate.delta[i]);
    }
    free(automate.delta);
    free(automate.finaux);
    free(word);

    return 0;
}
