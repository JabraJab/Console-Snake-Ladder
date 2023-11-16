import java.util.*;

public class saap{

    public static int roll() {
        Random random = new Random();
        return random.nextInt(6) + 1;
    }

    public static void board(int[] players, int nPlayers) {
        for (int row = 9; row >= 0; row--) {
            for (int col = 0; col < 10; col++) {
                int position = row * 10 + col + 1;
                boolean occupied = false;
                for (int i = 0; i < nPlayers; i++) {
                    if (players[i] == position) {
                        System.out.print("\tP" + (i + 1));
                        occupied = true;
                        break;
                    }
                }
                if (!occupied) {
                    System.out.print("\t" + position);
                }
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int nPlayers;
        System.out.print("Enter the number of players: ");
        Scanner scanner = new Scanner(System.in);
        nPlayers = scanner.nextInt();
        int[] players = new int[nPlayers];
        for (int i = 0; i < nPlayers; i++) {
            players[i] = 0;
        }
        int winner = -1;

        int[] snakesStart = {30, 47, 56, 73, 82, 92, 98};
        int[] snakesEnd = {7, 15, 19, 51, 42, 75, 55};

        int[] laddersStart = {4, 21, 29, 43, 63, 71};
        int[] laddersEnd = {25, 39, 74, 76, 80, 89};

        boolean game = true;
        System.out.print("\npress enter to continue...\n");
        while (game) {
            int turn;
            for (turn = 0; turn < nPlayers; turn++) {
            scanner.nextLine();

                int dice = roll();
                System.out.println("Player[" + (turn + 1) + "] rolled a " + dice + " : " + players[turn] + " -> " + (players[turn] + dice));
                players[turn] = players[turn] + dice;

                if (players[turn] > 100) {
                    System.out.println("Can't move outside the board, returning to : " + players[turn] + " -> " + (players[turn] - dice));
                    players[turn] = players[turn] - dice;
                }

                for (int i = 0; i < 7; i++) {
                    if (players[turn] == snakesStart[i]) {
                        System.out.println("Player[" + (turn + 1) + "] stepped on a snake: " + players[turn] + " -> " + snakesEnd[i]);
                        players[turn] = snakesEnd[i];
                    }
                }

                for (int i = 0; i < 6; i++) {
                    if (players[turn] == laddersStart[i]) {
                        System.out.println("Player[" + (turn + 1) + "] stepped on a ladder: " + players[turn] + " -> " + laddersEnd[i]);
                        players[turn] = laddersEnd[i];
                    }
                }
            }



            board(players, nPlayers);

            for (int i = 0; i < nPlayers; i++) {
                if (players[i] == 100) {
                    winner = i + 1;
                    game = false;
                    break;
                }
            }
        }

        System.out.println("\n\n\t\t\t!! !! !! !! !! !! !! !! !! !! !! \n\t\t\t\tPlayer [" + winner + "] wins");
    }
}
