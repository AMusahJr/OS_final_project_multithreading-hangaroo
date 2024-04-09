#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>

#define MAX_LIFE 5
#define MAX_WORD_LENGTH 20
#define NUM_WORDS 5

// Global variables for Hangaroo game
char sentence[MAX_WORD_LENGTH];
char displaySentence[MAX_WORD_LENGTH];
int life = MAX_LIFE;
int sentenceLength;
char* words[NUM_WORDS] = {"programming", "hangaroo", "multithreading", "linux"};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int userInputThreadCompleted = 0;

void generateSentence() {
    // Select a random word
    int index = rand() % NUM_WORDS;
    strcpy(sentence, words[index]);
    sentenceLength = strlen(sentence);

    // Initialize display sentence
    for (int i = 0; i < sentenceLength; ++i) {
        displaySentence[i] = '_';
    }
    displaySentence[sentenceLength] = '\0';
}

void displayGameState() {
    printf("Sentence: %s\n", displaySentence);
    printf("Life: %d\n", life);
}

void *getUserInput(void *arg) {
    char input;

    // Display user prompt outside the loop for better visibility
    printf("Enter a letter (repeated entries won't affect the game):\n");

    while (life > 0) {
        scanf(" %c", &input);

        pthread_mutex_lock(&mutex);
        int revealed = 0;
        for (int i = 0; i < sentenceLength; ++i) {
            if (tolower(sentence[i]) == tolower(input)) {
                displaySentence[i] = sentence[i];
                revealed = 1;
            }
        }

        if (revealed) {
            printf("Correct guess!\n");
        } else {
            life--;
            printf("Incorrect guess. Life remaining: %d\n", life);
        }

        displayGameState(); // Display updated sentence after each guess

        if (strcmp(displaySentence, sentence) == 0 || life == 0) {
            userInputThreadCompleted = 1;
            pthread_mutex_unlock(&mutex);
            break;
        }

        pthread_mutex_unlock(&mutex);
    }

    // Display the word after lives are finished
    if (life == 0) {
        printf("Oops! You ran out of lives. The word was: %s\n", sentence);
    }

    return NULL;
}

int main() {
    srand(time(NULL));

    // Generate random sentence
    generateSentence();

    pthread_t userInputThread;
    pthread_create(&userInputThread, NULL, getUserInput, NULL);

    // Main game loop
    while (!userInputThreadCompleted) {
        // No changes needed in the main loop
    }

    pthread_join(userInputThread, NULL); // Wait for user input thread to finish
    pthread_mutex_destroy(&mutex);

    return 0;
}
