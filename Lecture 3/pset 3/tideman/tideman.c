#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];


// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];                               // initialized all values to false in the main function.

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];                             // initialized and added candidates names in the main function
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;                                      // initialized in the main function, line 68
int candidate_count;                                // initialized in the main function, line 46

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool recurseGraph(int column);
int get_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage

    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");                     // check if sufficient candidates are there
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;                                         // inputed candidate number

    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);                // limit the maximum canditate size
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];                            // add names (strings) of candidate names to an array
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;                               // set default values for pairs
        }
    }

    pair_count = 0;                                             //initialized pair count

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

    add_pairs();
    sort_pairs();

    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {

        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }

    }

    return false;

}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{


    for (int i = 0; i < candidate_count; i++)
    {

            for (int l = i + 1; l < candidate_count; l++)
            {

                preferences[ranks[i]][ranks[l]] += 1;

            }

    }

    // for (int o = 0; o < candidate_count; o++)
    // {
    //     for (int al = 0; al < candidate_count; al++)
    //     {
    //         printf("Preferences %i to %i:   %i\n\n", o, al, preferences[o][al]);
    //     }
    // }

    return;

}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
        for (int i = 0; i < candidate_count; i++)
        {

            for (int l = i + 1; l < candidate_count; l++)
            {

                if (preferences[i][l] != preferences[l][i])
                {

                    if (preferences[i][l] > preferences[l][i])
                    {
                        pairs[pair_count].winner = i;
                        pairs[pair_count].loser = l;
                    }
                    else
                    {
                        pairs[pair_count].winner = l;
                        pairs[pair_count].loser = i;
                    }

                    pair_count++;

                }



        }

    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    if (pair_count > 0)
    {
        for (int i = 0; i < pair_count; i++)
        {
            for (int l = i + 1; l < pair_count; l++) // -2
            {
                if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[l].winner][pairs[l].loser])
                {
                    int temp_winner = pairs[i].winner, temp_loser = pairs[i].loser;

                    pairs[i].winner = pairs[l].winner;
                    pairs[i].loser = pairs[l].loser;

                    pairs[l].winner = temp_winner;
                    pairs[l].loser = temp_loser;

                }
            }

            //printf("%i -th winner is Pair: %i - %i \n With Winner's of number of total votes: %i\n Loser's of number of total votes: %i\n\n", i, pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser], preferences[pairs[i].loser][pairs[i].winner]);
        }
    }


    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{


    if (pair_count > 0)
    {

        for (int i = 0; i < pair_count; i++)
        {

            locked[pairs[i].winner][pairs[i].loser] = true;

        }


    }



    return;
}

// Print the winner of the election
void print_winner(void)
{
    int temp_winner = -1;
    int counter = 1;

    if (pair_count > 0)
    {
        temp_winner = get_winner();
        //if cycled
        while (temp_winner == -1)
        {
            locked[pairs[pair_count - counter].winner][pairs[pair_count - counter].loser] = false;
            temp_winner = get_winner();
            counter++;
        }
    }

    printf("%s\n", candidates[temp_winner]);

    return;
}


bool recurseGraph(int column)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][column] == true)
        {
            return false;
        }
    }

    return true;

}


int get_winner(void)
{
    int temp_winner = -1;

     for (int i = 0; i < candidate_count; i++)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                if (locked[i][j] == true && recurseGraph(i) == true)
                {
                    temp_winner = i;
                }
            }
        }
    return temp_winner;
}

