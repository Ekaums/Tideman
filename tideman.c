#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int pair, int start_num);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs(); // Now, NOT for every voter. For overall preferences
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0) // Look at all candidates, check to see if given name is a match
        {
            ranks[rank] = i; // If it is, rank that candidate's index at that position
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++) // For every candidate:
    {
        for (int j = 0; j < candidate_count; j++) // Compare to every other candidate
        {
            if ((j - i) > 0) // If the current candidate is higher ranked than the other candidate (j > i)
            {
                preferences[ranks[i]][ranks[j]] += 1; // Candidate i is preferred over j
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i]) // If any candidates are preferred over each other, add them to the pairs array
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO

    // Strength = preferences[pairs[a].winner][pairs[a].loser]

    pair temp; // Temporarily store value

    for (int i = 0; i < pair_count; i++) // For every position in pairs array
    {
        int strongest = 0; // Strongest edge

        for (int j = i; j < pair_count; j++) // Look for strongest edge
        {
            if (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner]  > strongest)
            {
                strongest = j;
            }
        }

        temp = pairs[i];
        pairs[i] = pairs[strongest]; // Swap current position with strongest pair
        pairs[strongest] = temp;


    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO

    for (int i = 0; i < 2; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true; // 1st and second pair will always be locked in (cycle can't be created yet with 2)
    }


    for (int i = 2; i < pair_count; i++) // For every other pair
    {
        if (check_cycle(i, pairs[i].winner) == false) // If it doesn't create a cycle
        {
            locked[pairs[i].winner][pairs[i].loser] = true; // Lock in pair
        }
    }


    return;
}



bool check_cycle(int pair, int start_num)
{



    int num = pairs[pair].loser;

    if (num == start_num) // If the current number we're looking at is the starting number:
    {
        return true; // A cycle has been created
    }

    for (int i = 0; i <= pair_count; i++) // Otherwise, check all pairs
    {

        if (locked[pairs[i].winner][pairs[i].loser] == true
            && pairs[i].winner == num) // There may be an edge that we can follow, that may create a cycle
        {

            if (check_cycle(i, start_num) == true) // If there is, follow that edge.
            {
                return true;
                break;
            }
        }

    }

    return false; // If the for loop is completed, there is no cycle


}





// Print the winner of the election
void print_winner(void)
{
    // TODO


    for (int i = 0; i < candidate_count; i++) // For every candidate
    {

        int lose = 0; // Initialize loss counter

        for (int j = 0; j < candidate_count; j++) // Compare to every other candidate
        {
            if (locked[j][i] == true)
            {
                lose++;
            }
        }

        if (lose == 0) // If that candidate doesn't lose anywhere, they are the winner
        {
            printf("%s\n", candidates[i]);
            break;
        }

    }


    return;
}