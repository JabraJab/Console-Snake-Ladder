#include<iostream>
using namespace std;
#include<random>

int roll() {                                                            //generate random nuber for dice
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 6);
    return distribution(gen);
}

void board(int Player[], int nPlayers) {                               //shows player positions in board
    for (int row = 9; row >= 0; row--) {
        for (int col = 0; col < 10; col++) {
            int position = row * 10 + col + 1;
            bool occupied = false;
            for (int i = 0; i < nPlayers; i++) {
                if (Player[i] == position) {
                    cout << "\tP" <<  (i + 1);
                    occupied = true;
                    break;
                }
            }
            if (!occupied) {
                cout << "\t" << position;
            }
        }
        cout << endl;
    }
}

    int main() {
        int nPlayer;
        cout << "enter no of players: ";
        cin >> nPlayer;                                             // no of players
        int Player[nPlayer];                                        // will store positions
        for(int i = 0; i < nPlayer; i++) {                          //initialize to 0
            Player[i] = 1;
        }
        int winner;

        int snakes_start[] = {30, 47, 56, 73, 82, 92, 98};          //position of snakes
        int snakes_end[] = {7, 15, 19, 51, 42, 75, 55};
        
        int ladders_start[] = {4, 21, 29, 43, 63, 71};              //position of ladders
        int ladders_end[] = {25, 39, 74, 76, 80, 89};
        
        int game = true;                                           //status of game
        while(game == true) {
            int turn;
            for(turn = 0; turn < nPlayer; turn++) {
                int dice = roll();
                cout << "Player[" << turn+1 << "] rolled a " << dice << " : "<< Player[turn] << " -> " << Player[turn] + dice << endl;
                Player[turn] = Player[turn] + dice;                 //player position change

                if (Player[turn] > 100) {
                    cout << "cant move outside board, returning to : " << Player[turn] << " -> " << Player[turn] - dice << endl;
                    Player[turn] = Player[turn] - dice;
                }
                
                for(int i = 0; i <= 7; i++) {                        //Snake Check
                    if(Player[turn] == snakes_start[i]) {
                        cout << "Player[" << turn+1 << "] stepped on a snake: " << Player[turn] << " -> " << snakes_end[i] << endl;
                        Player[turn] = snakes_end[i];
                    }
                    else
                        continue;
                }

                for(int i = 0; i <= 6; i++) {                        //Ladder Check
                    if(Player[turn] == ladders_start[i]) {
                        cout << "Player[" << turn+1 << " stepped on a ladder: " << Player[turn] << " -> " << ladders_end[i] << endl;
                        Player[turn] = ladders_end[i];
                    }
                }
            }

            board(Player, nPlayer);                            //Players' Positions
            for(int i = 0; i < nPlayer; i++) {                  //Victory Check
                if(Player[i] == 100) {
                    winner = i+1;
                    game = false;
                    goto lol;
                }
            }
        }
        lol:
            cout << "\n\n!! !! !! !! !! !! !! !! !! !! !! \nPlayer [" << winner << "] wins\n";
            game = false;
        return 0;
}
