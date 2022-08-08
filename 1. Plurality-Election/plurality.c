// Simulate a Plurality election //
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CANDIDATES 9

typedef struct {
  char *name;
  int votes;
}
candidate;

candidate candidates[MAX_CANDIDATES];
int candidate_count = 0;

// Function prototypes
bool vote(char *name);
void print_winner(int voter_count);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("ERROR: At least two candidates must run in election.\n");
    return 1;
  }

  candidate_count = argc - 1;
  if (candidate_count > MAX_CANDIDATES) {
    printf("ERROR: No more than %i candidates can run in election.\n", MAX_CANDIDATES);
    return 2;
  }

  for (int i = 0; i < candidate_count; i++) {
    candidates[i].name = argv[i + 1];
    candidates[i].votes = 0;
  }

  int voter_count = 0;
  printf("Number of voters: ");

  if (!scanf("%d", &voter_count)) {
    printf("ERROR: The number of voters must be an integer.\n");
    return 3;
  }

  for (int i = 0; i < voter_count; i++) {
    char name[20];
    do {
      printf("Vote: ");
      scanf("%s", name);

      if (!vote(name)) {
        printf("ERROR: This person is not running in the election.\n");
      }
    }
    while (!vote(name));
  }
  print_winner(voter_count);
}

bool vote(char *name) {
  for (int i = 0; i < candidate_count; i++) {
    if (strcmp(candidates[i].name, name) == 0) {
      candidates[i].votes++;
      return true;
    }
  }
  return false;
}

void print_winner(int voter_count) {
  int percent_won = 0;
  float win_vote = 0.0;

  for (int i = 0; i < candidate_count; i++) {
    if (candidates[i].votes > win_vote) {
      win_vote = candidates[i].votes;
    }
  }

  for (int i = 0; i < candidate_count; i++) {
    if (candidates[i].votes == win_vote) {
      percent_won = ((win_vote/2) / voter_count) * 100;
      printf("%s is the winner with %d percent of the vote.\n", candidates[i].name, percent_won);
    }
  }
}
