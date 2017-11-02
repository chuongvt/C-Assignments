#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
void playGame(int numberOfPlayers);
int rollDie(int howManyTimes, int amountOfPlayers, int playerIndex, int thePlayerBalance[], const char *thePlayers[]);
bool checkForWinner(const char *pickedPlayers[], int playerBalances[], int numberOfPlayers, int *thePot);

int main(){
    int seed;
    int numOfPlayers;

    printf("Random seed: ");
    scanf("%d", &seed);
    srand(seed);

    printf("How many players? ");
    scanf("%d", &numOfPlayers);

    playGame(numOfPlayers);

    return 0;
}

void playGame(int numberOfPlayers) {
    int i;
    int j = 0;
    int pot = 0;
    int playerBalances[numberOfPlayers];
    bool running = true;
    const char *names[] = {"Whoopi",
                           "Dale",
                           "Rosie",
                           "Jimmie",
                           "Barbara",
                           "Kyle",
                           "Raven",
                           "Tony",
                           "Jenny",
                           "Clint"};

    const char *pickedPlayers[numberOfPlayers];

    for (i=0; i<numberOfPlayers; i++) {
        pickedPlayers[i] = names[i];
        playerBalances[i] = 3;
    }

    while (running) {
        running = checkForWinner(pickedPlayers, playerBalances, numberOfPlayers, &pot);
        if (running == false) {
            break;
        }
        if (j < numberOfPlayers) {
            if (playerBalances[j] >= 3) {
                printf("%s rolls... ", pickedPlayers[j]);
                pot += rollDie(3, numberOfPlayers, j, playerBalances, pickedPlayers);
                printf("\n");
            }
            else if (playerBalances[j] == 2) {
                printf("%s rolls... ", pickedPlayers[j]);
                pot += rollDie(2, numberOfPlayers, j, playerBalances, pickedPlayers);
                printf("\n");
            }
            else if (playerBalances[j] == 1) {
                printf("%s rolls... ", pickedPlayers[j]);
                pot += rollDie(1, numberOfPlayers, j, playerBalances, pickedPlayers);
                printf("\n");
            }
            j++;
        }
        if (j == numberOfPlayers) {
            j = 0;
        }
    }
    return;
}

int rollDie(int howManyTimes, int amountOfPlayers, int playerIndex, int thePlayerBalance[], const char *thePlayers[]) {
    int addedToPot = 0;
    int i;
    int roll;
    typedef enum faciem{LEFT, RIGHT, CENTER, PASS} faces;
    faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};

    for (i=0; i<howManyTimes; i++){
        roll = rand() % 6;
        if (die[roll] == LEFT) {
            thePlayerBalance[playerIndex]--;
            if (playerIndex == 0) {
                thePlayerBalance[amountOfPlayers-1]++;
                printf("gives $1 to %s ", thePlayers[amountOfPlayers-1]);
            }
            else{
                thePlayerBalance[playerIndex-1]++;
                printf("gives $1 to %s ", thePlayers[playerIndex-1]);
            }
        }
        if (die[roll] == RIGHT) {
            thePlayerBalance[playerIndex]--;
            if (playerIndex == (amountOfPlayers-1)) {
                thePlayerBalance[0]++;
                printf("gives $1 to %s ", thePlayers[0]);
            }
            else{
                thePlayerBalance[playerIndex+1]++;
                printf("gives $1 to %s ", thePlayers[playerIndex+1]);
            }
        }
        if (die[roll] == CENTER) {
            thePlayerBalance[playerIndex]--;
            addedToPot++;
            printf("puts $1 in the pot ");
        }
        if (die[roll] == PASS) {
            printf("gets a pass ");
        }
    }
    return addedToPot;
}

bool checkForWinner(const char *pickedPlayers[], int playerBalances[], int numberOfPlayers, int *thePot) {
    int i, j;
    int counter = 0;
    int out = (numberOfPlayers - 1);
    int winningPlayerBalance;
    bool gameRunning = true;
    const char *winningPlayer;

    for (i=0; i<numberOfPlayers; i++) {
        if (playerBalances[i]==0) {
            counter++;
        }
    }

    if (counter == out) {
        for (j=0; j<numberOfPlayers; j++) {
            if (playerBalances[j] != 0) {
                winningPlayer = pickedPlayers[j];
                winningPlayerBalance = playerBalances[j];
            }
        }
        gameRunning = false;
        printf("%s wins the $%d pot with $%d left in the bank\n", winningPlayer, *thePot, winningPlayerBalance);
    }
    counter = 0;
    return gameRunning;
}
