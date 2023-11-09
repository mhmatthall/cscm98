#include <iostream>
#include <thread>

#include "utils.h"

// In C++, const is used to declare a variable as unchanging, like here where
// we want to set up some configuration options for the game. We name them in
// all caps to indicate that they are constants.
const int NUMBER_OF_THREADS = 20;
const int STARTING_BALANCE = 10;
const int EXPECTED_END_BALANCE = NUMBER_OF_THREADS * STARTING_BALANCE;

// An array to store each player's bank balance
int bank_accounts[NUMBER_OF_THREADS];

// A set to track the players still in the game
SimpleSet players_in_game;

/*
    Print the current balance of all players' accounts
*/
void print_account_balances()
{
    // Sum the total balance
    int total_balance = 0;

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        printf("  Player %02d: $%d\n", i, bank_accounts[i]);
        total_balance += bank_accounts[i];
    }

    printf("Total bank balance: $%d\n", total_balance);
}

/*
    Transfer $1 from one player to another
    `from`: The player transferring money
    `to`: The player receiving money
*/
void transfer(int from, int to)
{
    // Guard: Can't transfer money to same account
    if (from == to)
    {
        // printf("Player %02d ($%3d) tried to transfer to themself\n", from, bank_accounts[from]);
        return;
    }

    // Guard: Can't transfer money from bust players
    if (bank_accounts[from] <= 0 || bank_accounts[to] <= 0)
    {
        printf("Error: Player %02d ($%3d) tried to transfer to bust Player %02d\n", from, bank_accounts[from], to);
        return;
    }

    // Make the transfer
    bank_accounts[from]--;
    bank_accounts[to]++;

    // printf("Player %02d ($%3d) transferred $1 to player %2d ($%3d)\n", from, bank_accounts[from], to, bank_accounts[to]);
}

/*
    The logic that each player in the game should follow
    `player_number`: The player's number
*/
void player(int player_number)
{
    // Keep playing while we have money and there are other players in the game
    while ((bank_accounts[player_number] > 0) && (players_in_game.size() > 1))
    {
        // Transfer $1 to a random player
        transfer(player_number, players_in_game.select_random());

        // Slow the program down by pausing the thread's execution for a few milliseconds
        // (our modern computers are a bit fast for this game to work properly otherwise)
        sleep_thread(4);
    }

    // If we have no money left, we're bust and we leave the game
    if (bank_accounts[player_number] <= 0)
    {
        printf("Player %d went bust!\n", player_number);
        players_in_game.remove(player_number);
    }
    // Otherwise, we won!
    else
    {
        printf("Player %d won!\n", player_number);
    }
}

int main(int argc, const char *argv[])
{
    // Create a thread for each player
    std::thread players[NUMBER_OF_THREADS];

    // Initialise bank account balances and the set of players in the game
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        bank_accounts[i] = STARTING_BALANCE;
        players_in_game.insert(i);
    }

    // Print the initial game state
    printf("Initial player set: %s\n", players_in_game.to_string().c_str());
    printf("Initial bank balances:\n");
    print_account_balances();

    // Start a timer
    Timer timer;

    // Start the game
    printf("-------- GAME START --------\n");

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        players[i] = std::thread(player, i);
    }

    // Wait for the players to finish
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        players[i].join();
    }

    printf("-------- GAME FINISH -------\n");

    // Print the time taken
    printf("Game finished in %.1f seconds\n", (timer.measure() / 1000));

    // Print the final game state
    printf("Final player set: %s\n", players_in_game.to_string().c_str());
    printf("Final bank balances:\n");
    print_account_balances();
    printf("Expected total bank balance: $%d\n", EXPECTED_END_BALANCE);

    return 0;
}
