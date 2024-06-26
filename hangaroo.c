#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>
#include "hangaroo.h"

#define MAX_LIFE 5
#define MAX_WORD_LENGTH 20
#define NUM_WORDS_EASY 5
#define NUM_WORDS_MEDIUM 8
#define NUM_WORDS_HARD 11

// Global variables for Hangaroo game
char word[MAX_WORD_LENGTH];
char displayWord[MAX_WORD_LENGTH];
int life = MAX_LIFE;
int wordLength;
char* words_easy[NUM_WORDS_EASY] = {"process", "hangaroo", "memory", "linux", "mutex"};
char* words_medium[NUM_WORDS_MEDIUM] = {"semaphores", "deadlock", "race", "condition", "thread", "kernel", "system", "algorithm"};
char* words_hard[NUM_WORDS_HARD] = {"operating", "networking", "synchronization", "concurrency", "programming", "multithreading", "management", "scheduler", "filesystem", "virtual", "journaling"};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int userInputThreadCompleted = 0;

int alreadyGuessed[26] = {0}; // Array to track already guessed letters

void generateWord(int difficulty_level) {
    // Select a random word based on the difficulty level
    int index;
    switch (difficulty_level) {
        case 1:
            index = rand() % NUM_WORDS_EASY;
            strcpy(word, words_easy[index]);
            break;
        case 2:
            index = rand() % NUM_WORDS_MEDIUM;
            strcpy(word, words_medium[index]);
            break;
        case 3:
            index = rand() % NUM_WORDS_HARD;
            strcpy(word, words_hard[index]);
            break;
        default:
            printf("Invalid difficulty level.\n");
            exit(EXIT_FAILURE);
    }

    wordLength = strlen(word);

    // Initialize display word
    for (int i = 0; i < wordLength; ++i) {
        displayWord[i] = '_';
    }
    displayWord[wordLength] = '\0';
}

void displayGameState() {
    printf("Word: %s\n", displayWord);
    printf("Life: %d\n", life);
}

void *processUserInput(void *arg) {
    char input = *((char*) arg);

    pthread_mutex_lock(&mutex);
    int revealed = 0;
    if (alreadyGuessed[tolower(input) - 'a'] == 1) {
        printf("You have already guessed this letter. Please try another one.\n");
    } else {
        alreadyGuessed[tolower(input) - 'a'] = 1; // Mark the letter as already guessed
        for (int i = 0; i < wordLength; ++i) {
            if (tolower(word[i]) == tolower(input)) {
                displayWord[i] = word[i];
                revealed = 1;
            }
        }

        if (revealed) {
            printf("Correct guess!\n");
        } else {
            life--;
            printf("Incorrect guess. Life remaining: %d\n", life);
        }

        displayGameState(); // Display updated word after each guess

        if (strcmp(displayWord, word) == 0) {
            printf("Congratulations! You guessed the word correctly: %s\n", word);
            userInputThreadCompleted = 1;
        } else if (life == 0) {
            printf("Oops! You have ran out of lives. The correct word was: %s\n", word);
            userInputThreadCompleted = 1;
        }
    }
    pthread_mutex_unlock(&mutex);

    if (userInputThreadCompleted) {
        exit(EXIT_SUCCESS);
    }

    return NULL;
}

// Implementation of testHangaroo function
void testHangaroo() {
    // Test generateWord()
    printf("Generated word: %s\n", word);

    // Test displayGameState()
    printf("Initial game state:\n");
    displayGameState();
}

int main() {
    srand(time(NULL));

    testHangaroo();

    int difficulty_level;
    printf("\nChoose difficulty level (1: Easy, 2: Medium, 3: Hard): ");
    scanf("%d", &difficulty_level);

    // Generate random word based on the chosen difficulty level
    generateWord(difficulty_level);

    // Main game loop
    while (!userInputThreadCompleted) {
        // Read input character
        char input;
        printf("Enter a letter: ");
        scanf(" %c", &input);

        // Check if the input is a letter
        if (!isalpha(input)) {
            printf("Invalid input. Please enter a letter.\n");
            continue; // Skip processing invalid input
        }

        // Start a new thread to process the user input
        pthread_t inputThread;
        pthread_create(&inputThread, NULL, processUserInput, (void*) &input);
        pthread_detach(inputThread); // Detach the thread so it can run independently
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
