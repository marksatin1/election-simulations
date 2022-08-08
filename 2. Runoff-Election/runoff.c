// Simulate a Runoff election //
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct {
  char *name;
  int votes;
  bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, char *name);
void tabulate_votes(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);

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

  // Populate candidates array
  for (int i = 0; i < candidate_count; i++) {
    candidates[i].name = argv[i+1];
    candidates[i].votes = 0;
    candidates[i].eliminated = false;
  }

  printf("Number of voters: ");
  if (!scanf("%d", &voter_count)) {
    printf("ERROR: The number of voters must be an integer.\n");
    return 3;
  }
  if (voter_count > MAX_VOTERS) {
    printf("ERROR: No more than %i voters can vote in election.\n", MAX_VOTERS);
    return 4;
  }

  // Tally every voter's preferences
  for (int i = 0; i < voter_count; i++) {
      printf("VOTER %d\n", i+1);
    for (int j = 0; j < candidate_count; j++) {
      char name[20];
      do {
        printf("Rank %d: ", j+1);
        scanf("%s", name);

        if (!vote(i, j, name)) {
          printf("ERROR: This person is not running in the election.\n");
        }
      } while (!vote(i, j, name));
    }
    printf("\n");
  }

  // Keep holding runoffs until winner exists
  while (true) {
    tabulate_votes();
    if (print_winner()) {
      break;
    }

    int min = find_min();
    bool tie = is_tie(min);
    if (tie) {
      printf("The election is tied.");
      break;
    }

    // Eliminate the candidate(s) with the lowest number of votes
    for (int i = 0; i < candidate_count; i++) {
      if (candidates[i].votes == min) {
        candidates[i].eliminated = true;
      }
    }

    // Reset candidate vote count to 0
    for (int i = 0; i < candidate_count; i++) {
      candidates[i].votes = 0;
    }
  }
  return 0;
}

bool vote(int voter, int rank, char *name) {
  for (int i = 0; i < candidate_count; i++) {
    if (strcmp(name, candidates[i].name) == 0) {
      preferences[voter][rank] = i;
      return true;
    }
  }
  return false;
}

void tabulate_votes(void)
{
  for (int i = 0; i < voter_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      if (!candidates[preferences[i][j]].eliminated) {
        candidates[preferences[i][j]].votes++;
        break;
      }
    }
  }
}

bool print_winner(void)
{
  float majority = (0.5 * voter_count) + 1;
  for (int i = 0; i < candidate_count; i++) {
    if (candidates[i].votes >= majority) {
      printf("%s is the election winner!\n", candidates[i].name);
      return true;
    }
  }
  return false;
}

int find_min(void)
{
  int min = voter_count;
  for (int i = 0; i < candidate_count; i++) {
    if (!candidates[i].eliminated) {
      if (candidates[i].votes < min) {
        min = candidates[i].votes;
      }
    }
  }
  return min;
}

bool is_tie(int min)
{
  for (int i = 0; i < candidate_count; i++) {
    if (!candidates[i].eliminated) {
      if (candidates[i].votes != min) {
        return false;
      }
    }
  }
  return true;
}
