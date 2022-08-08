// Simulate a Tideman election //
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

typedef struct {
  int winner;
  int loser;
}
pair;

char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int pair_count = 0;
int candidate_count = 0;

// Function prototypes
bool vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("ERROR: At least two candidates must run in election.\n");
    return 1;
  }

  candidate_count = argc - 1;
  if (candidate_count > MAX) {
    printf("ERROR: No more than %i candidates can run in election.", MAX);
    return 2;
  }
  for (int i = 0; i < candidate_count; i++) {
    candidates[i] = argv[i + 1];
  }

  // Clear graph of locked in pairs
  for (int i = 0; i < candidate_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      locked[i][j] = false;
    }
  }

  pair_count = 0;
  int voter_count = 0;

  printf("Number of voters: ");
  if (!scanf("%d", &voter_count)) {
    printf("ERROR: The number of voters must be an integer.\n");
    return 3;
  }

  // Tally every voter's preferences
  for (int i = 0; i < voter_count; i++) {
    // ranks[i] is voter's ith preference
    int ranks[candidate_count];
    printf("VOTER %d\n", i+1);
    for (int j = 0; j < candidate_count; j++) {
      char name[20];
      do {
        printf("Rank %d: ", j+1);
        scanf("%s", name);

        if (!vote(j, name, ranks)) {
          printf("This person is not running in the election.\n");
        }
      } while (!vote(j, name, ranks));
    }
    record_preferences(ranks);
    printf("\n");
  }
  add_pairs();
  sort_pairs();
  lock_pairs();
  print_winner();
  return 0;
}

// Records the name of a voter's preference in the ranks array for that voter
bool vote(int rank, char *name, int ranks[]) {
  for (int i = 0; i < candidate_count; i++) {
    if (strcmp(name, candidates[i]) == 0) {
      ranks[rank] = i;
      return true;
    }
  }
  return false;
}

// Uses each voter's ranks array to update the 
// overall candidate preferences array
void record_preferences(int ranks[]) {
  for (int i = 0; i < candidate_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      if (i < j) {
        preferences[ranks[i]][ranks[j]]++;
      }
    }
  }
  return;
}

// Record winner and loser of each candidate matchup
void add_pairs(void) {
  for (int i = 0; i < candidate_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      if (preferences[i][j] > preferences[j][i]) {
        pairs[pair_count].winner = i;
        pairs[pair_count].loser = j;
        pair_count++;
      }
    }
  }
  return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
  int counter = -1;
  pair s;

  while (counter != 0) {
    counter = 0;

    for (int i = 0; i < pair_count - 1; i++) {
      if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser]) {
        s = pairs[i];
        pairs[i] = pairs[i + 1];
        pairs[i + 1] = s;
        counter++;
      }
    }
  }
  return;
}


// Recursive function to check for cycles in graph
bool cycle_check(int end, int start) {
  // Base case to check that inputs do not create a cycle
  if (end == start) {
    return true;
  }
  // Recursive case that loops through each candidate
  for (int i = 0; i < candidate_count; i++) {
    if (locked[end][i] == true) {
      if (cycle_check(i, start) == true) {
        return true;
      }
    }
  }
  return false;
}

// Lock pairs into the candidate graph by strength of victory, without creating cycles
void lock_pairs(void) {
  for (int i = 0; i < candidate_count; i++) {
      if (!cycle_check(pairs[i].loser, pairs[i].winner)) {
        locked[pairs[i].winner][pairs[i].loser] = true;
      }
  }
  return;
}

void print_winner(void) {
  for (int i = 0; i < candidate_count; i++) {
    int false_count = 0;

    for (int j = 0; j < candidate_count; j++) {
      if (locked[j][i] == false) {
        false_count++;

        if (false_count == candidate_count)
        {
          printf("The election winner is %s!\n", candidates[i]);
        }
      }
    }
  }
  return;
}