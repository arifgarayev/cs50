#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    int j = 0;

    // input to lowercase


    // while (name[j] != '\0')
    // {
    //     name[j] = tolower(name[j]);
    //     j++;
    // }

    for (int i = 0; i < candidate_count; i++)
    {
        // candidates to lowercase


        // int k = 0;
        // while (candidates[i].name[k] != '\0')
        // {
        //     candidates[i].name[k] = tolower(candidates[i].name[k]);
        //     k++;
        // }

        if (!strcmp(name, candidates[i].name))
        {
            candidates[i].votes += 1;
            // printf("%i\n", candidates[i].votes);
            // candidates[i].name[0] = toupper(candidates[i].name[0]);
            return true;
        }
        // candidates[i].name[0] = toupper(candidates[i].name[0]);
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int largest_vote_index = 0;

    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[largest_vote_index].votes < candidates[i].votes)
        {
            largest_vote_index = i;
        }
    }

    printf("%s\n", candidates[largest_vote_index].name);

    for (int i = 0; i < candidate_count; i++)
    {
        if (i != largest_vote_index)
        {
            if (candidates[largest_vote_index].votes == candidates[i].votes)
            {
                printf("%s\n", candidates[i].name);
            }
        }

    }
}