#ifndef HANGAROO_H
#define HANGAROO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>

#define MAX_LIFE 5
#define MAX_WORD_LENGTH 20
#define NUM_WORDS 11


extern char word[MAX_WORD_LENGTH];
extern char displayWord[MAX_WORD_LENGTH];
extern int life;
extern int userInputThreadCompleted;
extern pthread_mutex_t mutex;

void generateWord(int difficulty_level);
void displayGameState();
void *getUserInput(void *arg);
void testHangaroo();

#endif
