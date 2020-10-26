    // The developer of this program is Aditya Girish Pawate. Roll Number: 18MA20054
    // I have converted this probabilistic game into a deterministic set of logical games.
    // I haven't used any non-trivial functions. I hardcoded everything using my own strategy which I use to play with everyone
    // I have forced the other player to a move. which means that if the other player does not play the move which I intend him to do, then he will loose the game.
    // This programs NEVER looses for any input value from the user. The computer plays optimally for every position.
    // So first we divide the whole program into two functions one for playing the moves when computer plays first and second one for when the user to start first
    // We include header files required
    #include <iostream>
    // We create useful #define macros which will save our coding time.
    #define rep(i,n) for(int i=0;i<n;i++)
    #define f(i,a,b) for(int i=a;i<b;i++)
    using namespace std;
    //This is our global variable board which stores the position of the board

    // Sir has mentioned in the assignment that Player 1 is X and Player 2 is O.
    // This convention has been used exactly as stated. But in the comments for a better understanding
    // of the code I have drawn the board with the following convention
    // X= Computer, O - Opponent, _- Empty Place
    // This was solely done to enhance the readability of the code
    // I have used standard indentation of the code
    char board[9];
    /* Each position of the board is a character stored in board as follows
         * --------------
         * | 0 | 1 | 2 |
         * | 3 | 4 | 5 |
         * | 6 | 7 | 8 |
         * --------------
         * So now the player has 9 possible moves which we take as a switch case
         * DISCLAIMER: As mentioned in the assignment we had to take 1 based indexing. I have done exactly that while running the program.
         * But only in the comments for the sake of understanding and because array is 0-based indexing I have used 0,1,2,...,9
         */
    //So we create many utility functions to help us with the program
    // This is a function that takes in the current board position and prints the current position of the board
    void print_board(){
        //first we print the top line for graphics
        rep(i,15){
            cout<<"-";
        }
        cout<<endl;
        //we print the first line of the board
        f(i,0,3){
            cout<<" | "<<board[i];
        }
        //we print the second line of the board
        cout<<" | "<<endl;
        f(i,3,6){
            cout<<" | "<<board[i];
        }
        //we print the third line of the board
        cout<<" | "<<endl;
        f(i,6,9){
            cout<<" | "<<board[i];
        }
        cout<<" | "<<endl;
        //first we print the bottom line for graphics
        rep(i,15){
            cout<<"-";
        }
        cout<<endl;
    }

    //This function is displayed at the beginning and will tell the user how to play the game.
    void show_instructions(){
        rep(i,30){
            cout<<"-";
        }
        //here we give the instructions to play the game
        cout<<endl;
        cout<<"Welcome to the TICTACTOE GAME. "<<endl<<"These are the instructions to play the GAME.\n"
                                                       "The game is played on a grid that's 3 squares by 3 squares.\n"
                                                       "The computer is always X,  the you are always O. Players take turns putting their marks in empty squares.\n"
                                                       "The first player to get 3 of their marks in a row (up, down, across, or diagonally) is the winner.\n"
                                                       "When all 9 squares are full, the game is over.\nThese are the board position numbers.\nDuring your turn you must enter these numbers to play on that position."<<endl;
        char a[9];
        int i=0;
        //we display the numbers to enter for playing in each each position
        /*
        * --------------
        * | 1 | 2 | 3 |
        * | 4 | 5 | 6 |
        * | 7 | 8 | 9 |
        * --------------
        */
        char ch='1';
        while(i<9){
            a[i]=ch;
            board[i]=a[i];
            ch++,i++;
        }
        print_board();
    }

    //For every game this function will be called and the board will be reset and ready for the new game.
    void initialize_board(){
        rep(i,9){
            board[i]='-';
        }
    }

    // This function will display the board and ask where the player wants to play the move
    // This will not allow invalid moves and it return an integer which is the position played
    int take_move(){
        cout<<"The computer has played its move. This is the the current board position."<<endl;
        print_board();
        int move=-1;
        char ch;
        string s;
        //this block ensures no invalid moves
        while(move<0){
            cout<<"Where would you like to play?"<<endl;
            cin>>s;
            if(s.length()>1){
                cout<<"Invalid move. Please enter a single digit number. Play again!!!"<<endl;
                continue;
            }
            ch=s[0];
            move=ch-'0';
            if(board[move-1]!='-'){
                cout<<"Invalid move. Note that you cannot play in non-empty place. Play again!!!"<<endl;
                move=-1;
            }
        }
        board[move-1]='O';
        cout<<"You have played your move !! The current position of the board is shown."<<endl;
        print_board();
        return move-1;
    }

    //These are the set of moves the computer plays when it starts the game
    int get_move_1(){
        //Let the computer be X
        char x='X';
        // We play the first move as 6 because it has maximum chances of winning
        board[6]=x;
        /*
         * --------------
         * | _ | _ | _ |
         * | _ | _ | _ |
         * | X | _ | _ |
         * --------------
         * So now the player has 9 possible moves which we take as a switch case
         */
        switch(take_move()){ // As take move returns an integer representing the position we switch case on that
            case 0: board[2]=x;
                /* If the player plays 0 as their move then we play 2
                 * --------------
                 * | O | _ | X |
                 * | _ | _ | _ |
                 * | X | _ | _ |
                 * --------------
                */
                // As we see that we are forcing the player to play in the center otherwise computer wins
                // We use the same strategy in further positions of the board
                switch (take_move()) {
                    /*
                     * Again we switch cases between the moves now if the player plays in 4 then
                     * we play in 8 now we have a guaranteed win because if the player plays anyone of the move we
                     * will surely win by placing in 5 or 7
                     * --------------
                     * | O | _ | X |
                     * | _ | O | _ |
                     * | X | _ | X |
                     * --------------
                     */
                    case 4: board[8]=x;
                        switch (take_move()) {
                            //So we finish the game by plying 7 if the player plays 5
                            case 5: board[7]=x;
                                return 1; // We signal 1 because we have won the game
                                //And by default we shall play 5 to win the game
                            default: board[5]=x;
                                return 1; // We signal 1 because we have won the game
                        }
                        //This is the case when the player doesn't play 4
                        //then we just play 4 and win the game
                    default:board[4]='X';
                        return(1);
                }
            case 8: board[2]=x;
                /* If the player plays 8 as their move then we play 2
                 * --------------
                 * | _ | _ | X |
                 * | _ | _ | _ |
                 * | X | _ | O |
                 * --------------
                */
                // As we see that we are forcing the player to play in the center otherwise computer wins
                switch (take_move()) {
                    /*
                     * Again we switch cases between the moves now if the player plays in 4 then
                     * we play in 0 now we have a guarantee win because if the player plays anyone of the move we
                     * will surely win by placing in 1 or 3
                     * --------------
                     * | X | _ | X |
                     * | _ | O | _ |
                     * | X | _ | O |
                     * --------------
                     */
                    case 4: board[0]=x;
                        switch (take_move()) {
                            //So we finish the game by playing 1 if the player plays 3
                            case 3: board[1]=x;
                                return 1; // We signal 1 because we have won the game
                                //And by default we shall play 3 to win the game
                            default: board[3]=x;
                                return 1; // We signal 1 because we have won the game
                        }
                        //If the player doesn't play 4 then computer wins
                    default:board[4]='X';
                        return(1);
                }
            case 1:board[4]=x;
                /* If the player plays 1 as their first move then we play 4
                 * --------------
                 * | _ | O | _ |
                 * | _ | X | _ |
                 * | X | _ | _ |
                 * --------------
                */
                // As we see that we are forcing the player to play in position 2 otherwise computer wins
                switch (take_move()) {
                    /*
                     * Again we switch cases between the moves now if the player plays in 2 then
                     * we play in 0 now we have a guarantee win because if the player plays anyone of the move we
                     * will surely win by placing in 3 or 8
                    * --------------
                     * | X | O | O |
                     * | _ | X | _ |
                     * | X | _ | _ |
                     * --------------
                     */
                    case 2:board[0]=x;
                        switch (take_move()) {
                            //So we finish the game by playing 8 if the player plays 3
                            case 3: board[8]=x;
                                return 1; // We signal 1 because we have won the game
                                //And by default we shall play 3 to win the game
                            default: board[3]=x;
                                return 1; // We signal 1 because we have won the game
                        }
                        //If the player doesn't play 2 then computer wins
                    default:board[2]=x;
                        return 1;
                }
            case 2:board[8]=x;
                /* If the player plays 2 as their first move then we play 8
                     * --------------
                     * | _ | _ | O |
                     * | _ | _ | _ |
                     * | X | _ | X |
                     * --------------
                    */
                // As we see that we are forcing the player to play in position 7 otherwise computer wins
                switch (take_move()) {
                    /*
                     * Again we switch cases between the moves now if the player plays in 7 then
                     * we play in 0 now we have a guarantee win because if the player plays anyone of the move we
                     * will surely win by placing in 3 or 4
                     * --------------
                     * | X | _ | O |
                     * | _ | _ | _ |
                     * | X | O | X |
                     * --------------
                     */
                    case 7: board[0]=x;
                        switch (take_move()) {
                            //So we finish the game by playing 4 if the player plays 3
                            case 3:board[4]=x;
                                return 1;// We signal 1 because we have won the game
                                //And by default we shall play 3 to win the game
                            default:board[3]=x;// We signal 1 because we have won the game
                                return 1;
                        }
                        //If the player doesn't play 7 then computer wins
                    default:board[7]=x;
                        return 1;
                }
            case 4:board[3]=x;
                /* If the player plays 4 as their first move then we play 3
                 * --------------
                 * | _ | _ | _ |
                 * | X | O | _ |
                 * | X | _ | _ |
                 * --------------
                */
                // As we see that we are forcing the player to play in position 7 otherwise computer wins
                switch (take_move()) {
                    case 0:board[8]=x;
                        switch (take_move()) {
                            case 7:board[1]=x;
                                if(take_move()==2) board[5]=x;
                                else board[2]=x;
                                return 0;// We signal 0 because the game is tied
                            default:board[7]=x;
                                return 1;// We signal 1 because we have won the game
                        }
                    default:board[0]=x;
                        return 1; // We signal 1 because we have won the game
                }
            case 7:board[4]=x;
                /*
                 * This is when the player plays 7 this is what happens
                 * we play 4, player if forced to play 2, then we play 8 to get guaranteed move in position 7 or 0
                 * --------------  --------------    --------------
                 * | _ | _ | _ |    | X | _ | O |    | X | _ | O |
                 * | _ | X | _ | => | _ | X | _ | => | O | X | _ |
                 * | X | O | _ |    | X | O | _ |    | X | O | X |
                 * --------------  --------------    --------------
                */
                // As we see that we are forcing the player to play in position 7 otherwise computer wins
                switch (take_move()) {
                    case 2:board[0]=x;
                        switch (take_move()) {
                            case 3:board[8]=x;
                                return 1;// We signal 1 because we have won the game
                            default:board[3]=x;
                                return 1;// We signal 1 because we have won the game
                        }
                    default:board[2]=x;
                        return 1;// We signal 1 because we have won the game
                }
                //This is the default case which encorporates the following moves
                // if the player plays 3,5,7
            default:board[4]=x;
                /* If the player plays 3,5 or 7 as their first move then we play 4 as our second
                 * This is when the player plays 3 this is what happens
                 * we play 4, player if forced to play 2, then we play 8 to get guaranteed move in position 7 or 0
                 * --------------  --------------    --------------
                 * | _ | _ | _ |    | _ | _ | O |    | O | _ | O |
                 * | O | X | _ | => | O | X | _ | => | O | X | _ |
                 * | X | _ | _ |    | X | _ | X |    | X | X | X |
                 * --------------  --------------    --------------
                 * * This is when the player plays 5 this is what happens
                 * we play 4, player if forced to play 2, then we play 8 to get guaranteed move in position 7 or 0
                 * --------------  --------------    --------------
                 * | _ | _ | _ |    | _ | _ | O |    | O | _ | O |
                 * | _ | X | O | => | _ | X | O | => | _ | X | O |
                 * | X | _ | _ |    | X | _ | X |    | X | X | X |
                 * --------------  --------------    --------------
                 *
                */
                // As we see that we are forcing the player to play in a position otherwise computer wins
                switch (take_move()) {
                    case 2:board[8]=x;
                        switch (take_move()) {
                            case 0:board[7]=x;
                                return 1;
                            default: board[0]=x;
                                return 1;
                        }
                    default:board[2]=x;
                        return 1;
                }
        }
    }
    // This function will display the board and ask where the player wants to play the move
    // We create a seperate function for the case 2 when the player plays first and computer plays second
    int take_move_2(){
        cout<<"This is the the current board position."<<endl;
        print_board();
        int move=-1;
        char ch;
        string s;
        while(move<1){
            cout<<"Where would you like to play?"<<endl;
            cin>>s;
            if(s.length()>1){
                cout<<"Invalid move. Please enter a single digit number. Play again!!!"<<endl;
                continue;
            }
            ch=s[0];
            if(isdigit(ch)==false){
                cout<<"Invalid move. Please enter a number. Play again!!!"<<endl;
                continue;
            }
            move=ch-'0';
            if(board[move-1]!='-'){
                cout<<"Invalid move. Note that you cannot play in non-empty place. Play again!!!"<<endl;
                move=-1;
            }
        }
        board[move-1]='X';
        cout<<"You have played your move!! The current position of the board is shown."<<endl;
        print_board();
        return move-1;
    }

    // This function is used when the computer plays second.
    // This time we will have a lot of cases because we cannot directly force a move in this game.
    int get_move_2(){
        // Let the computer be O
        char x='O';
        // We switch cases on all possible first moves of the players. Hence we have 9 cases.
        // If the player plays a non-centeral move then the game is easy. But the code becomes really
        // long if the first player plays center. Hence we shall look at this case at last
        switch (take_move_2()) {
            //If the player plays the first move as 0 then we play 4
            case 0: board[4]=x;
                /*
                 * This is when the player plays 0 this is what happens
                 * we play 4, then we have 7 possible subcases
                 * --------------  --------------
                 * | O | _ | _ |    | O | 1 | 2 |
                 * | _ | X | _ | => | 3 | X | 5 |
                 * | _ | _ | _ |    | 6 | 7 | 8 |
                 * --------------  --------------
                 * These are the subcases it is divided into
                */
                switch (take_move_2()) {
                    /*
                 * This is when the player plays 1 this is what happens
                 * we play 2
                 * --------------  --------------    --------------
                 * | O | O | X |    | O | O | X |    | O | O | X |
                 * | _ | X | _ | => | X | X | O | => | X | X | O |
                 * | O | _ | _ |    | O | _ | _ |    | O | O | X |
                 * --------------  --------------    --------------
                */
                    case 1:board[2]=x;
                        switch (take_move_2()) {
                            case 6: board[3]=x;
                                switch (take_move_2()) {
                                    case 5: board[8]=x;
                                        take_move_2();
                                        return 0; // We signal O because  the game is a tie
                                    default: board[5]=x;
                                        return 1; // We signal 1 because we have won the game
                                }
                            default:board[6]=x;
                                return 1; // We signal 1 because we have won the game
                        }
                        /*
                 * This is when the player plays 2 this is what happens
                 * we play 1
                 * --------------  --------------    --------------
                 * | O | X | O |    | O | X | O |    | O | X | O |
                 * | _ | X | _ | => | _ | X | X | => | O | X | X |
                 * | _ | _ | _ |    | _ | O | _ |    | X | O | O |
                 * --------------  --------------    --------------
                */
                    case 2:board[1]=x;
                        switch (take_move_2()) {
                            case 7:board[5]=x;
                                switch (take_move_2()) {
                                    case 3: board[6]=x;
                                        take_move_2();
                                        return 0;
                                    default: board[3]=x;
                                        return 1;
                                }
                            default:board[7]=x;
                                return 1;
                        }
                        /*
                 * This is when the player plays 3 this is what happens
                 * we play 6
                 * --------------  --------------    --------------
                 * | O | _ | _ |    | O | X | O |    | O | X | O |
                 * | O | X | _ | => | O | X | _ | => | O | X | X |
                 * | X | _ | _ |    | X | _ | _ |    | X | O | O |
                 * --------------  --------------    --------------
                */
                    case 3:board[6]=x;
                        switch (take_move_2()) {
                            case 2:board[1]=x;
                                switch (take_move_2()) {
                                    case 7:board[8]=x;
                                        take_move_2();
                                        return 0;
                                    default:board[7]=x;
                                        return 1;
                                }
                            default:board[2]=x;
                                return 1;
                        }
                        /*
                 * This is when the player plays 5 this is what happens
                 * we play 1
                 * --------------  --------------    --------------
                 * | O | X | _ |    | O | X | _ |    | O | X | O |
                 * | _ | X | O | => | _ | X | O | => | O | X | O |
                 * | _ | O | _ |    | X | O | X |    | X | O | X |
                 * --------------  --------------    --------------
                */
                    case 5:board[1]=x;
                        switch (take_move_2()) {
                            case 7:board[6]=x;
                                switch (take_move_2()) {
                                    case 2:board[8]=x;
                                        take_move_2();
                                        return 0;
                                    default: board[2]=x;
                                        return 1;
                                }
                            default:board[7]=x;
                                return 1;
                        }
                        /*
                 * This is when the player plays 6 this is what happens
                 * we play 3
                 * --------------  --------------    --------------
                 * | O | _ | _ |    | O | X | _ |    | O | X | O |
                 * | X | X | _ | => | X | X | O | => | X | X | O |
                 * | O | _ | _ |    | O | O | _ |    | O | O | X |
                 * --------------  --------------    --------------
                */
                    case 6:board[3]=x;
                        switch (take_move_2()) {
                            case 5:board[1]=x;
                                switch (take_move_2()) {
                                    case 7:board[8]=x;
                                        take_move_2();
                                        return 0;
                                    default: board[7]=x;
                                        return 1;
                                }
                            default:board[5]=x;
                                return 1;
                        }
                        /*
                 * This is when the player plays 7 this is what happens
                 * we play 3
                 * --------------  --------------    --------------
                 * | O | _ | _ |    | O | _ | X |    | O | O | X |
                 * | X | X | _ | => | X | X | O | => | X | X | O |
                 * | _ | O | _ |    | _ | O | _ |    | O | O | X |
                 * --------------  --------------    --------------
                */
                    case 7:board[3]=x;
                        switch (take_move_2()) {
                            case 5:board[2]=x;
                                switch (take_move_2()) {
                                    case 6:board[8]=x;
                                        take_move_2();
                                        return 0;
                                    default: board[6]=x;
                                        return 1;
                                }
                            default:board[5]=x;
                                return 1;
                        }
                        /*
                * This is when the player plays 7 this is what happens
                 * we play 3
                 * --------------  --------------    --------------
                 * | O | _ | _ |    | O | O | X |    | O | O | X |
                 * | _ | X | _ | => | _ | X | _ | => | X | X | O |
                 * | _ | X | O |    | _ | X | O |    | O | X | O |
                 * --------------  --------------    --------------
                */
                    case 8:board[7]=x;
                        switch (take_move_2()) {
                            case 1:board[2]=x;
                                switch (take_move_2()) {
                                    case 6:board[3]=x;
                                        take_move_2();
                                        return 0;
                                    default: board[6]=x;
                                        return 1;
                                }
                            default:board[1]=x;
                                return 1;
                        }
                }
                //This is the case when the first move by the user is 1
            case 1:board[4]=x; //we play center
                /*
                     * This is when the player plays 1 this is what happens
                     * we play 4, then we have 7 possible subcases
                     * --------------  --------------
                     * | _ | O | _ |    | 0 | O | 2 |
                     * | _ | X | _ | => | 3 | X | 5 |
                     * | _ | _ | _ |    | 6 | 7 | 8 |
                     * --------------  --------------
                     * These are the subcases it is divided into
                    */
                switch (take_move_2()) {
                    /*
                        * This is when the player plays 0 this is what happens
                         * we play 2
                         * --------------  --------------    --------------
                         * | O | O | X |    | O | O | X |    | O | O | X |
                         * | _ | X | _ | => | X | X | _ | => | X | X | O |
                         * | _ | _ | _ |    | O | _ | _ |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                    case 0:board[2]=x;
                        switch (take_move_2()) {
                            case 6:
                                board[3] = x;
                                switch (take_move_2()) {
                                    case 5:
                                        board[8] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[5] = x;
                                        return 1;
                                }
                            default:
                                board[6] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 2 this is what happens
                         * we play 0
                         * --------------  --------------    --------------
                         * | X | O | O |    | X | O | O |    | X | O | O |
                         * | _ | X | _ | => | _ | X | X | => | O | X | X |
                         * | _ | _ | _ |    | _ | _ | O |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 2:board[0]=x;
                        switch (take_move_2()) {
                            case 8:
                                board[5] = x;
                                switch (take_move_2()) {
                                    case 3:
                                        board[7] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[3] = x;
                                        return 1;
                                }
                            default:
                                board[8] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 3 this is what happens
                         * we play 6
                         * --------------  --------------    --------------
                         * | _ | O | _ |    | X | O | O |    | X | O | O |
                         * | O | X | _ | => | O | X | _ | => | O | X | X |
                         * | X | _ | _ |    | X | _ | _ |    | X | O | O |
                         * --------------  --------------    --------------
                        */
                    case 3:board[6]=x;
                        switch (take_move_2()) {
                            case 2:
                                board[0] = x;
                                switch (take_move_2()) {
                                    case 8:
                                        board[5] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[8] = x;
                                        return 1;
                                }
                            default:
                                board[2] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 5 this is what happens
                         * we play 8
                         * --------------  --------------    --------------
                         * | _ | O | _ |    | O | O | X |    | O | O | X |
                         * | _ | X | O | => | _ | X | O | => | X | X | O |
                         * | _ | _ | X |    | _ | _ | X |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                    case 5:board[8]=x;
                        switch (take_move_2()) {
                            case 0:
                                board[2] = x;
                                switch (take_move_2()) {
                                    case 6:
                                        board[3] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[6] = x;
                                        return 1;
                                }
                            default:
                                board[0] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 6 this is what happens
                         * we play 3
                         * --------------  --------------    --------------
                         * | _ | O | _ |    | _ | O | _ |    | O | O | X |
                         * | X | X | _ | => | X | X | O | => | X | X | O |
                         * | O | _ | _ |    | O | _ | X |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                    case 6:board[3]=x;
                        switch (take_move_2()) {
                            case 5:
                                board[8] = x;
                                switch (take_move_2()) {
                                    case 0:
                                        board[2] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[0] = x;
                                        return 1;
                                }
                            default:
                                board[5] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 7 this is what happens
                         * we play 2
                         * --------------  --------------    --------------
                         * | _ | O | X |    | _ | O | X |    | O | O | X |
                         * | _ | X | _ | => | _ | X | _ | => | _ | X | X |
                         * | _ | O | _ |    | O | O | _ |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                    case 7:board[2]=x;
                        switch (take_move_2()) {
                            case 6:
                                board[8] = x;
                                switch (take_move_2()) {
                                    case 0:
                                        board[5] = x;
                                        return 1;
                                    default:
                                        board[0] = x;
                                        return 1;
                                }
                            default:
                                board[6] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 8 this is what happens
                         * we play 5
                         * --------------  --------------    --------------
                         * | _ | O | _ |    | _ | O | _ |    | X | O | O |
                         * | _ | X | X | => | O | X | X | => | O | X | X |
                         * | _ | _ | O |    | X | _ | O |    | X | O | O |
                         * --------------  --------------    --------------
                        */
                    case 8:board[5]=x;
                        switch (take_move_2()) {
                            case 3:
                                board[6] = x;
                                switch (take_move_2()) {
                                    case 2:
                                        board[0] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[2] = x;
                                        return 1;
                                }
                            default:
                                board[3] = x;
                                return 1;
                        }
                }
                //This is the case when the first move by the user is 1
            case 2:board[4]=x; //we play center
                /*
                     * This is when the player plays 2 this is what happens
                     * we play 4, then we have 7 possible subcases
                     * --------------  --------------
                     * | _ | _ | O |    | 0 | 1 | O |
                     * | _ | X | _ | => | 3 | X | 5 |
                     * | _ | _ | _ |    | 6 | 7 | 8 |
                     * --------------  --------------
                     * These are the subcases it is divided into
                    */
                switch (take_move_2()) {
                    /*
                        * This is when the player plays 0 this is what happens
                         * we play 1
                         * --------------  --------------    --------------
                         * | O | _ | O |    | O | X | O |    | O | X | O |
                         * | _ | X | _ | => | _ | X | X | => | O | X | X |
                         * | _ | _ | _ |    | _ | O | _ |    | X | O | O |
                         * --------------  --------------    --------------
                        */
                    case 0:board[1]=x;
                        switch (take_move_2()) {
                            case 7:
                                board[5] = x;
                                switch (take_move_2()) {
                                    case 3:
                                        board[6] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[3] = x;
                                        return 1;
                                }
                            default:
                                board[7] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 8 this is what happens
                         * we play 5
                         * --------------  --------------    --------------
                         * | X | O | O |    | X | O | O |    | X | O | O |
                         * | _ | X | _ | => | _ | X | X | => | O | X | X |
                         * | _ | _ | _ |    | _ | _ | O |    | X | O | O |
                         * --------------  --------------    --------------
                        */
                    case 1:board[0]=x;
                        switch (take_move_2()) {
                            case 8:
                                board[5] = x;
                                switch (take_move_2()) {
                                    case 3:
                                        board[6] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[3] = x;
                                        return 1;
                                }
                            default:
                                board[8] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 3 this is what happens
                         * we play 1
                         * --------------  --------------    --------------
                         * | _ | X | O |    | _ | X | O |    | O | X | O |
                         * | O | X | _ | => | O | X | _ | => | O | X | O |
                         * | _ | _ | _ |    | _ | O | X |    | X | O | X |
                         * --------------  --------------    --------------
                        */
                    case 3:board[1]=x;
                        switch (take_move_2()) {
                            case 7:
                                board[8] = x;
                                switch (take_move_2()) {
                                    case 0:
                                        board[6] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[0] = x;
                                        return 1;
                                }
                            default:
                                board[7] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 5 this is what happens
                         * we play 8
                         * --------------  --------------    --------------
                         * | _ | _ | O |    | O | X | O |    | O | X | O |
                         * | _ | X | O | => | _ | X | O | => | O | X | O |
                         * | _ | _ | X |    | _ | _ | X |    | X | O | X |
                         * --------------  --------------    --------------
                        */
                    case 5:board[8]=x;
                        switch (take_move_2()) {
                            case 0:
                                board[1] = x;
                                switch (take_move_2()) {
                                    case 7:
                                        board[6] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[7] = x;
                                        return 1;
                                }
                            default:
                                board[0] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 6 this is what happens
                         * we play 7
                         * --------------  --------------    --------------
                         * | _ | _ | O |    | X | O | O |    | X | O | O |
                         * | _ | X | _ | => | _ | X | _ | => | O | X | X |
                         * | O | _ | _ |    | O | X | _ |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 6:board[7]=x;
                        switch (take_move_2()) {
                            case 1:
                                board[0] = x;
                                switch (take_move_2()) {
                                    case 8:
                                        board[5] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[8] = x;
                                        return 1;
                                }
                            default:
                                board[1] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 6 this is what happens
                         * we play 7
                         * --------------  --------------    --------------
                         * | _ | _ | O |    | X | _ | O |    | X | O | O |
                         * | O | X | X | => | O | X | X | => | O | X | X |
                         * | _ | O | _ |    | _ | O | _ |    | X | O | O |
                         * --------------  --------------    --------------
                        */
                    case 7:board[5]=x;
                        switch (take_move_2()) {
                            case 3:
                                board[0] = x;
                                switch (take_move_2()) {
                                    case 8:
                                        board[6] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[8] = x;
                                        return 1;
                                }
                            default:
                                board[3] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 6 this is what happens
                         * we play 7
                         * --------------  --------------    --------------
                         * | _ | _ | O |    | _ | _ | O |    | X | O | O |
                         * | _ | X | X | => | O | X | X | => | O | X | X |
                         * | _ | _ | O |    | _ | _ | O |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 8:board[5]=x;
                        switch (take_move_2()) {
                            case 3:
                                board[1] = x;
                                switch (take_move_2()) {
                                    case 7:
                                        board[0] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[7] = x;
                                        return 1;
                                }
                            default:
                                board[3] = x;
                                return 1;
                        }
                }
            case 3:board[4]=x; //we play center
                /*
                     * This is when the player plays 3 this is what happens
                     * we play 4, then we have 7 possible subcases
                     * --------------  --------------
                     * | _ | _ | _ |    | 0 | 1 | 2 |
                     * | O | X | _ | => | O | X | 5 |
                     * | _ | _ | _ |    | 6 | 7 | 8 |
                     * --------------  --------------
                     * These are the subcases it is divided into
                    */
                switch (take_move_2()) {
                    /*
                        * This is when the player plays 0 this is what happens
                         * we play 1
                         * --------------  --------------    --------------
                         * | O | _ | _ |    | O | X | O |    | O | X | O |
                         * | O | X | _ | => | O | X | _ | => | O | X | O |
                         * | X | _ | _ |    | X | _ | _ |    | X | O | X |
                         * --------------  --------------    --------------
                        */
                    case 0:board[6]=x;
                        switch (take_move_2()) {
                            case 2:
                                board[1] = x;
                                switch (take_move_2()) {
                                    case 7:
                                        board[8] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[7] = x;
                                        return 1;
                                }
                            default:
                                board[2] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 1 this is what happens
                         * we play 0
                         * --------------  --------------    --------------
                         * | X | O | _ |    | X | O | X |    | X | O | X |
                         * | O | X | _ | => | O | X | _ | => | O | X | _ |
                         * | _ | _ | _ |    | _ | _ | O |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 1:board[0]=x;
                        switch (take_move_2()) {
                            case 8:
                                board[2] = x;
                                switch (take_move_2()) {
                                    case 6:
                                        board[7] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[6] = x;
                                        return 1;
                                }
                            default:
                                board[8] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 2 this is what happens
                         * we play 1
                         * --------------  --------------    --------------
                         * | _ | _ | O |    | X | O | O |    | X | O | O |
                         * | O | X | _ | => | O | X | _ | => | O | X | X |
                         * | _ | X | _ |    | _ | X | _ |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 2:board[7]=x;
                        switch (take_move_2()) {
                            case 1:
                                board[0] = x;
                                switch (take_move_2()) {
                                    case 8:
                                        board[5] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[8] = x;
                                        return 1;
                                }
                            default:
                                board[1] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 5 this is what happens
                         * we play 8
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | O | _ | _ |    | O | _ | O |
                         * | O | X | O | => | O | X | O | => | O | X | O |
                         * | _ | _ | X |    | X | _ | X |    | X | X | X |
                         * --------------  --------------    --------------
                        */
                    case 5:board[8]=x;
                        switch (take_move_2()) {
                            case 0:
                                board[6] = x;
                                switch (take_move_2()) {
                                    case 2:
                                        board[7] = x;
                                        return 1;
                                    default:
                                        board[2] = x;
                                        return 1;
                                }
                            default:
                                board[0] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 6 this is what happens
                         * we play 0
                         * --------------  --------------    --------------
                         * | X | _ | _ |    | X | _ | _ |    | X | O | O |
                         * | O | X | _ | => | O | X | _ | => | O | X | X |
                         * | O | _ | _ |    | O | X | O |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 6:board[0]=x;
                        switch (take_move_2()) {
                            case 8:
                                board[7] = x;
                                switch (take_move_2()) {
                                    case 1:
                                        board[5] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[1] = x;
                                        return 1;
                                }
                            default:
                                board[8] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 7 this is what happens
                         * we play 6
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | _ | O |    | O | X | O |
                         * | O | X | _ | => | O | X | _ | => | O | X | O |
                         * | X | O | _ |    | X | O | X |    | X | O | X |
                         * --------------  --------------    --------------
                        */
                    case 7:board[6]=x;
                        switch (take_move_2()) {
                            case 2:
                                board[8] = x;
                                switch (take_move_2()) {
                                    case 0:
                                        board[1] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[0] = x;
                                        return 1;
                                }
                            default:
                                board[2] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 6 this is what happens
                         * we play 7
                         * --------------  --------------    --------------
                         * | _ | O | _ |    | _ | O | X |    | X | O | X |
                         * | O | X | _ | => | O | X | _ | => | O | X | O |
                         * | _ | X | O |    | _ | X | O |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 8:board[7]=x;
                        switch (take_move_2()) {
                            case 1:
                                board[2] = x;
                                switch (take_move_2()) {
                                    case 6:
                                        board[0] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[6] = x;
                                        return 1;
                                }
                            default:
                                board[1] = x;
                                return 1;
                        }
                }
            case 5:board[4]=x; //we play center
                /*
                     * This is when the player plays 5 this is what happens
                     * we play 4, then we have 7 possible subcases
                     * --------------  --------------
                     * | _ | _ | _ |    | 0 | 1 | 2 |
                     * | _ | X | O | => | 3 | X | O |
                     * | _ | _ | _ |    | 6 | 7 | 8 |
                     * --------------  --------------
                     * These are the subcases it is divided into
                    */
                switch (take_move_2()) {
                    /*
                        * This is when the player plays 0 this is what happens
                         * we play 7
                         * --------------  --------------    --------------
                         * | O | _ | _ |    | O | O | X |    | O | O | X |
                         * | _ | X | O | => | _ | X | O | => | X | X | O |
                         * | _ | X | _ |    | _ | X | _ |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 0:board[7]=x;
                        switch (take_move_2()) {
                            case 1:
                                board[2] = x;
                                switch (take_move_2()) {
                                    case 6:
                                        board[3] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[6] = x;
                                        return 1;
                                }
                            default:
                                board[1] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 1 this is what happens
                         * we play 2
                         * --------------  --------------    --------------
                         * | _ | O | X |    | _ | O | X |    | O | O | X |
                         * | _ | X | O | => | _ | X | O | => | X | X | O |
                         * | _ | _ | _ |    | O | _ | X |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                    case 1:board[2]=x;
                        switch (take_move_2()) {
                            case 6:
                                board[8] = x;
                                switch (take_move_2()) {
                                    case 0:
                                        board[3] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[0] = x;
                                        return 1;
                                }
                            default:
                                board[6] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 2 this is what happens
                         * we play 8
                         * --------------  --------------    --------------
                         * | _ | _ | O |    | O | X | O |    | O | X | O |
                         * | _ | X | O | => | _ | X | O | => | O | X | O |
                         * | _ | _ | X |    | _ | _ | x |    | X | O | X |
                         * --------------  --------------    --------------
                        */
                    case 2:board[8]=x;
                        switch (take_move_2()) {
                            case 0:
                                board[1] = x;
                                switch (take_move_2()) {
                                    case 7:
                                        board[6] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[7] = x;
                                        return 1;
                                }
                            default:
                                board[0] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 3 this is what happens
                         * we play 6
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | _ | O |    | O | _ | O |
                         * | O | X | O | => | O | X | O | => | O | X | O |
                         * | X | _ | _ |    | X | _ | X |    | X | X | X |
                         * --------------  --------------    --------------
                        */
                    case 3:board[6]=x;
                        switch (take_move_2()) {
                            case 2:
                                board[8] = x;
                                switch (take_move_2()) {
                                    case 0:
                                        board[7] = x;
                                        return 1;
                                    default:
                                        board[0] = x;
                                        return 1;
                                }
                            default:
                                board[2] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 6 this is what happens
                         * we play 7
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | O | _ |    | X | O | X |
                         * | _ | X | O | => | _ | X | O | => | O | X | O |
                         * | O | X | _ |    | O | X | _ |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 6:board[7]=x;
                        switch (take_move_2()) {
                            case 1:
                                board[0] = x;
                                switch (take_move_2()) {
                                    case 8:
                                        board[2] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[8] = x;
                                        return 1;
                                }
                            default:
                                board[0] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 7 this is what happens
                         * we play 8
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | O | _ | X |    | O | O | X |
                         * | _ | X | O | => | _ | X | O | => | X | X | O |
                         * | _ | O | X |    | _ | O | x |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                    case 7:board[8]=x;
                        switch (take_move_2()) {
                            case 0:
                                board[2] = x;
                                switch (take_move_2()) {
                                    case 6:
                                        board[3] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[6] = x;
                                        return 1;
                                }
                            default:
                                board[0] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 6 this is what happens
                         * we play 7
                         * --------------  --------------    --------------
                         * | _ | _ | X |    | _ | _ | X |    | X | O | X |
                         * | _ | X | O | => | _ | X | O | => | O | X | O |
                         * | _ | _ | O |    | O | X | O |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 8:board[2]=x;
                        switch (take_move_2()) {
                            case 6:
                                board[7] = x;
                                switch (take_move_2()) {
                                    case 1:
                                        board[0] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[1] = x;
                                        return 1;
                                }
                            default:
                                board[6] = x;
                                return 1;
                        }
                }
            case 6:board[4]=x; //we play center
                /*
                     * This is when the player plays 6 this is what happens
                     * we play 4, then we have 7 possible subcases
                     * --------------  --------------
                     * | _ | _ | _ |    | 0 | 1 | 2 |
                     * | _ | X | _ | => | 3 | X | 5 |
                     * | O | _ | _ |    | O | 7 | 8 |
                     * --------------  --------------
                     * These are the subcases it is divided into
                    */
                switch (take_move_2()) {
                    /*
                        * This is when the player plays 0 this is what happens
                         * we play 3
                         * --------------  --------------    --------------
                         * | O | _ | _ |    | O | X | _ |    | O | X | O |
                         * | X | X | _ | => | X | X | O | => | X | X | O |
                         * | O | _ | _ |    | O | _ | _ |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                    case 0:board[3]=x;
                        switch (take_move_2()) {
                            case 5:
                                board[1] = x;
                                switch (take_move_2()) {
                                    case 7:
                                        board[8] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[7] = x;
                                        return 1;
                                }
                            default:
                                board[5] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 1 this is what happens
                         * we play 3
                         * --------------  --------------    --------------
                         * | _ | O | _ |    | _ | O | _ |    | O | O | X |
                         * | X | X | _ | => | X | X | O | => | X | X | O |
                         * | O | _ | _ |    | O | _ | X |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                    case 1:board[3]=x;
                        switch (take_move_2()) {
                            case 5:
                                board[8] = x;
                                switch (take_move_2()) {
                                    case 0:
                                        board[2] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[0] = x;
                                        return 1;
                                }
                            default:
                                board[5] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 2 this is what happens
                         * we play 5
                         * --------------  --------------    --------------
                         * | _ | _ | O |    | X | _ | O |    | X | O | O |
                         * | _ | X | X | => | O | X | X | => | O | X | X |
                         * | O | _ | _ |    | O | _ | _ |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 2:board[5]=x;
                        switch (take_move_2()) {
                            case 3:
                                board[0] = x;
                                switch (take_move_2()) {
                                    case 8:
                                        board[7] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[8] = x;
                                        return 1;
                                }
                            default:
                                board[3] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 3 this is what happens
                         * we play 0
                         * --------------  --------------    --------------
                         * | X | _ | _ |    | X | _ | _ |    | X | O | O |
                         * | O | X | _ | => | O | X | _ | => | O | X | X |
                         * | O | _ | _ |    | O | X | O |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 3:board[0]=x;
                        switch (take_move_2()) {
                            case 8:
                                board[7] = x;
                                switch (take_move_2()) {
                                    case 1:
                                        board[5] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[1] = x;
                                        return 1;
                                }
                            default:
                                board[8] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 5 this is what happens
                         * we play 7
                         * --------------  --------------    --------------
                         * | _ | O | _ |    | X | O | _ |    | X | O | X |
                         * | _ | X | O | => | _ | X | O | => | O | X | O |
                         * | O | X | _ |    | O | X | _ |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 5:board[7]=x;
                        switch (take_move_2()) {
                            case 1:
                                board[0] = x;
                                switch (take_move_2()) {
                                    case 8:
                                        board[2] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[8] = x;
                                        return 1;
                                }
                            default:
                                board[1] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 7 this is what happens
                         * we play 8
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | O | _ | _ |    | O | X | O |
                         * | _ | X | _ | => | X | X | _ | => | X | X | O |
                         * | O | O | X |    | O | O | X |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                    case 7:board[8]=x;
                        switch (take_move_2()) {
                            case 0:
                                board[3] = x;
                                switch (take_move_2()) {
                                    case 5:
                                        board[1] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[5] = x;
                                        return 1;
                                }
                            default:
                                board[0] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 8 this is what happens
                         * we play 7
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | O | _ |    | O | O | X |
                         * | _ | X | _ | => | X | X | _ | => | X | X | O |
                         * | O | X | O |    | O | X | O |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 8:board[7]=x;
                        switch (take_move_2()) {
                            case 1:
                                board[3] = x;
                                switch (take_move_2()) {
                                    case 5:
                                        board[2] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[5] = x;
                                        return 1;
                                }
                            default:
                                board[1] = x;
                                return 1;
                        }
                }
            case 7:board[4]=x; //we play center
                /*
                     * This is when the player plays 7 this is what happens
                     * we play 4, then we have 7 possible subcases
                     * --------------  --------------
                     * | _ | _ | _ |    | 0 | 1 | 2 |
                     * | _ | X | _ | => | 3 | X | 5 |
                     * | _ | O | _ |    | 6 | O | 8 |
                     * --------------  --------------
                     * These are the subcases it is divided into
                    */
                switch (take_move_2()) {
                    /*
                        * This is when the player plays 0 this is what happens
                         * we play 3
                         * --------------  --------------    --------------
                         * | O | _ | _ |    | O | _ | X |    | O | O | X |
                         * | X | X | _ | => | X | X | O | => | X | X | O |
                         * | _ | O | _ |    | _ | O | _ |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                    case 0:board[3]=x;
                        switch (take_move_2()) {
                            case 5:
                                board[2] = x;
                                switch (take_move_2()) {
                                    case 6:
                                        board[8] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[6] = x;
                                        return 1;
                                }
                            default:
                                board[5] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 1 this is what happens
                         * we play 0
                         * --------------  --------------    --------------
                         * | X | O | _ |    | X | O | _ |    | X | O | O |
                         * | _ | X | _ | => | _ | X | _ | => | X | X | _ |
                         * | _ | O | _ |    | X | O | O |    | X | O | O |
                         * --------------  --------------    --------------
                        */
                    case 1:board[0]=x;
                        switch (take_move_2()) {
                            case 8:
                                board[6] = x;
                                switch (take_move_2()) {
                                    case 2:
                                        board[3] = x;
                                        return 1;
                                    default:
                                        board[2] = x;
                                        return 1;
                                }
                            default:
                                board[8] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 2 this is what happens
                         * we play 5
                         * --------------  --------------    --------------
                         * | _ | _ | O |    | _ | _ | O |    | O | X | O |
                         * | X | X | _ | => | X | X | O | => | X | X | O |
                         * | _ | O | _ |    | _ | O | X |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                    case 2:board[3]=x;
                        switch (take_move_2()) {
                            case 5:
                                board[8] = x;
                                switch (take_move_2()) {
                                    case 0:
                                        board[1] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[0] = x;
                                        return 1;
                                }
                            default:
                                board[5] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 3 this is what happens
                         * we play 6
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | _ | O |    | O | X | O |
                         * | O | X | _ | => | O | X | _ | => | O | X | O |
                         * | X | O | _ |    | X | O | X |    | X | O | X |
                         * --------------  --------------    --------------
                        */
                    case 3:board[6]=x;
                        switch (take_move_2()) {
                            case 2:
                                board[8] = x;
                                switch (take_move_2()) {
                                    case 0:
                                        board[1] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[0] = x;
                                        return 1;
                                }
                            default:
                                board[2] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 5 this is what happens
                         * we play 8
                         * --------------  --------------    --------------
                         * | O | _ | _ |    | O | _ | _ |    | O | X | O |
                         * | _ | X | O | => | _ | X | O | => | O | X | O |
                         * | _ | O | X |    | X | O | X |    | X | O | X |
                         * --------------  --------------    --------------
                        */
                    case 5:board[8]=x;
                        switch (take_move_2()) {
                            case 0:
                                board[6] = x;
                                switch (take_move_2()) {
                                    case 2:
                                        board[1] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[2] = x;
                                        return 1;
                                }
                            default:
                                board[0] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 6 this is what happens
                         * we play 8
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | O | _ | _ |    | O | X | O |
                         * | _ | X | _ | => | X | X | _ | => | X | X | O |
                         * | O | O | X |    | O | O | X |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                    case 6:board[8]=x;
                        switch (take_move_2()) {
                            case 0:
                                board[3] = x;
                                switch (take_move_2()) {
                                    case 5:
                                        board[1] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[5] = x;
                                        return 1;
                                }
                            default:
                                board[0] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 8 this is what happens
                         * we play 6
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | _ | O |    | O | X | O |
                         * | _ | X | _ | => | _ | X | X | => | O | X | X |
                         * | X | O | O |    | X | O | O |    | X | O | O |
                         * --------------  --------------    --------------
                        */
                    case 8:board[6]=x;
                        switch (take_move_2()) {
                            case 2:
                                board[5] = x;
                                switch (take_move_2()) {
                                    case 3:
                                        board[1] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[3] = x;
                                        return 1;
                                }
                            default:
                                board[2] = x;
                                return 1;
                        }
                }
            case 8:board[4]=x; //we play center
                /*
                     * This is when the player plays 8 this is what happens
                     * we play 4, then we have 7 possible subcases
                     * --------------  --------------
                     * | _ | _ | _ |    | 0 | 1 | 2 |
                     * | _ | X | _ | => | 3 | X | 5 |
                     * | _ | _ | O |    | 6 | 7 | O |
                     * --------------  --------------
                     * These are the subcases it is divided into
                    */
                switch (take_move_2()) {
                    /*
                        * This is when the player plays 0 this is what happens
                         * we play 3
                         * --------------  --------------    --------------
                         * | O | X | _ |    | O | X | _ |    | O | X | O |
                         * | _ | X | _ | => | _ | X | _ | => | X | X | X |
                         * | _ | _ | O |    | X | O | O |    | X | O | O |
                         * --------------  --------------    --------------
                        */
                    case 0:board[1]=x;
                        switch (take_move_2()) {
                            case 7:
                                board[6] = x;
                                switch (take_move_2()) {
                                    case 2:
                                        board[5] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[2] = x;
                                        return 1;
                                }
                            default:
                                board[7] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 1 this is what happens
                         * we play 5
                          --------------  --------------    --------------
                         * | _ | O | _ |    | _ | O | _ |    | X | O | O |
                         * | _ | X | X | => | O | X | X | => | O | X | X |
                         * | _ | _ | O |    | X | _ | O |    | X | O | O |
                         * --------------  --------------    --------------
                        */
                    case 1:board[5]=x;
                        switch (take_move_2()) {
                            case 3:
                                board[6] = x;
                                switch (take_move_2()) {
                                    case 2:
                                        board[0] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[2] = x;
                                        return 1;
                                }
                            default:
                                board[3] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 2 this is what happens
                         * we play 5
                          --------------  --------------    --------------
                         * | _ | _ | O |    | _ | X | O |    | O | X | O |
                         * | _ | X | X | => | O | X | X | => | O | X | X |
                         * | _ | _ | O |    | _ | _ | O |    | X | O | O |
                         * --------------  --------------    --------------
                        */
                    case 2:board[5]=x;
                        switch (take_move_2()) {
                            case 3:
                                board[1] = x;
                                switch (take_move_2()) {
                                    case 7:
                                        board[6] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[7] = x;
                                        return 1;
                                }
                            default:
                                board[3] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 3 this is what happens
                         * we play 7
                          --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | O | X |    | X | O | X |
                         * | O | X | _ | => | O | X | _ | => | O | X | O |
                         * | _ | X | O |    | _ | X | O |    | O | x | O |
                         * --------------  --------------    --------------
                        */
                    case 3:board[7]=x;
                        switch (take_move_2()) {
                            case 1:
                                board[2] = x;
                                switch (take_move_2()) {
                                    case 6:
                                        board[0] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[6] = x;
                                        return 1;
                                }
                            default:
                                board[1] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 5 this is what happens
                         * we play 2
                          --------------  --------------    --------------
                         * | _ | _ | X |    | _ | _ | X |    | X | O | X |
                         * | _ | X | O | => | _ | X | O | => | O | X | O |
                         * | _ | _ | O |    | O | X | O |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 5:board[2]=x;
                        switch (take_move_2()) {
                            case 6:
                                board[7] = x;
                                switch (take_move_2()) {
                                    case 1:
                                        board[0] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[1] = x;
                                        return 1;
                                }
                            default:
                                board[6] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 6 this is what happens
                         * we play 7
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | O | _ |    | X | O | O |
                         * | _ | X | _ | => | _ | X | X | => | O | X | X |
                         * | O | X | O |    | O | X | O |    | O | X | O |
                         * --------------  --------------    --------------
                        */
                    case 6:board[7]=x;
                        switch (take_move_2()) {
                            case 1:
                                board[5] = x;
                                switch (take_move_2()) {
                                    case 3:
                                        board[0] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[3] = x;
                                        return 1;
                                }
                            default:
                                board[1] = x;
                                return 1;
                        }
                        /*
                        * This is when the player plays 7 this is what happens
                         * we play 6
                          --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | _ | O |    | X | X | O |
                         * | _ | X | _ | => | _ | X | X | => | O | X | X |
                         * | X | O | O |    | X | O | O |    | X | O | O |
                         * --------------  --------------    --------------
                        */
                    case 7:board[6]=x;
                        switch (take_move_2()) {
                            case 2:
                                board[5] = x;
                                switch (take_move_2()) {
                                    case 3:
                                        board[1] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[3] = x;
                                        return 1;
                                }
                            default:
                                board[5] = x;
                                return 1;
                        }
                }
            default:board[8]=x;
                /*
                     * This is when the player plays 4 this is what happens
                     * we play 8, then we have 7 possible subcases
                     * --------------  --------------
                     * | _ | _ | _ |    | 0 | 1 | 2 |
                     * | _ | O | _ | => | 3 | O | 5 |
                     * | _ | _ | X |    | 6 | 7 | X |
                     * --------------  --------------
                     * These are the subcases it is divided into
                    */

                switch (take_move_2()) {
                    case 0:                    /*
                        * This is when the player plays 0 this is what happens
                         * we play 2
                         * --------------  --------------    --------------
                         * | O | _ | X |    | O | _ | X |    | O | X | X |
                         * | _ | O | _ | => | X | O | O | => | X | O | O |
                         * | _ | _ | X |    | _ | _ | X |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                        board[2]=x;
                        switch (take_move_2()) {
                            case 5:
                                board[3] = x;
                                switch (take_move_2()) {
                                    case 1:
                                        board[7] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[1] = x;
                                        take_move_2();
                                        return 0;
                                }
                            default:
                                board[5] = x;
                                return 1;
                        }
                    case 1:/*
                        * This is when the player plays 0 this is what happens
                         * we play 2
                         * --------------  --------------    --------------
                         * | _ | O | _ |    | _ | O | X |    | O | O | X |
                         * | _ | O | _ | => | _ | O | _ | => | X | O | O |
                         * | _ | X | X |    | O | X | X |    | O | X | X |
                         * --------------  --------------    --------------
                        */
                        board[7]=x;
                        switch (take_move_2()) {
                            case 6:
                                board[2] = x;
                                switch (take_move_2()) {
                                    case 5:
                                        board[3] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[5] = x;
                                        return 1;
                                }
                            default:
                                board[6] = x;
                                return 1;
                        }
                    case 2:/*
                        * This is when the player plays 0 this is what happens
                         * we play 2
                         * --------------  --------------    --------------
                         * | _ | _ | O |    | _ | X | O |    | O | X | O |
                         * | _ | O | _ | => | _ | O | _ | => | O | O | X |
                         * | X | _ | X |    | X | O | X |    | X | O | X |
                         * --------------  --------------    --------------
                        */
                        board[6]=x;
                        switch (take_move_2()) {
                            case 7:
                                board[1] = x;
                                switch (take_move_2()) {
                                    case 5:
                                        board[3] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[5] = x;
                                        take_move_2();
                                        return 0;
                                }
                            default:
                                board[7] = x;
                                return 1;
                        }
                    case 3:
                        /*
                        * This is when the player plays 0 this is what happens
                         * we play 2
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | _ | O |    | O | X | O |
                         * | O | O | X | => | O | O | X | => | O | O | X |
                         * | _ | _ | X |    | X | _ | X |    | X | O | X |
                         * --------------  --------------    --------------
                        */
                        board[5]=x;
                        switch (take_move_2()) {
                            case 2:
                                board[6] = x;
                                switch (take_move_2()) {
                                    case 7:
                                        board[1] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[7] = x;
                                        return 1;
                                }
                            default:
                                board[6] = x;
                                return 1;
                        }

                    case 5:/*
                        * This is when the player plays 0 this is what happens
                         * we play 2
                         * subcase:0
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | O | _ | _ |    | O | O | X |
                         * | X | O | O | => | X | O | O | => | X | O | O |
                         * | _ | _ | X |    | _ | X | X |    | O | X | X |
                         * --------------  --------------    --------------
                         * subcase:1
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | O | _ |    | O | O | X |
                         * | X | O | O | => | X | O | O | => | X | O | O |
                         * | _ | _ | X |    | _ | X | X |    | O | X | X |
                         * --------------  --------------    --------------
                         * subcase:2
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | _ | O |    | X | _ | O |
                         * | X | O | O | => | X | O | O | => | X | O | O |
                         * | _ | _ | X |    | X | _ | X |    | X | O | X |
                         * --------------  --------------    --------------
                         * subcase:6
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | _ | X |    | O | X | X |
                         * | X | O | O | => | X | O | O | => | X | O | O |
                         * | _ | _ | X |    | O | _ | X |    | O | O | X |
                         * --------------  --------------    --------------
                         * subcase:7
                         * --------------  --------------    --------------
                         * | _ | _ | _ |    | _ | X | _ |    | O | X | O |
                         * | X | O | O | => | X | O | O | => | X | O | O |
                         * | _ | _ | X |    | _ | O | X |    | X | O | X |
                         * --------------  --------------    --------------
                        */
                        board[3]=x;
                        switch (take_move_2()) {
                            case 0:
                            case 1:board[7] = x;
                                switch (take_move_2()) {
                                    case 6:
                                        board[2] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[6] = x;
                                        return 1;
                                }
                            case 2:board[6] = x;
                                switch (take_move_2()) {
                                    case 7:
                                        board[0] = x;
                                        return 1;
                                    default:
                                        board[7] = x;
                                        return 1;
                                }
                            case 6:board[2] = x;
                                switch (take_move_2()) {
                                    case 7:
                                        board[1] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[7] = x;
                                        take_move_2();
                                        return 0;
                                }
                            default:board[1] = x;
                                switch (take_move_2()) {
                                    case 2:
                                        board[6] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[2] = x;
                                        take_move_2();
                                        return 0;
                                }
                        }
                    case 6:/*
                         * This is when the player plays 0 this is what happens
                         * we play 2
                         * --------------  --------------    --------------
                         * | _ | _ | X |    | _ | _ | X |    | O | X | X |
                         * | _ | O | _ | => | X | O | O | => | X | O | O |
                         * | O | _ | X |    | O | _ | X |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                        board[2]=x;
                        switch (take_move_2()) {
                            case 5:
                                board[3] = x;
                                switch (take_move_2()) {
                                    case 7:
                                        board[1] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[7] = x;
                                        take_move_2();
                                        return 0;
                                }
                            default:
                                board[5] = x;
                                return 1;
                        }
                    default:/*
                        * This is when the player plays 0 this is what happens
                         * we play 2
                         * subcase:0
                         * --------------  --------------    --------------
                         * | _ | X | _ |    | O | X | _ |    | O | X | O |
                         * | _ | O | _ | => | _ | O | X | => | O | O | X |
                         * | _ | O | X |    | _ | O | X |    | X | O | X |
                         * --------------  --------------    --------------
                         * subcase:2
                         * --------------  --------------    --------------
                         * | _ | X | _ |    | _ | X | O |    | O | X | O |
                         * | _ | O | _ | => | _ | O | _ | => | X | O | O |
                         * | _ | O | X |    | X | O | X |    | X | O | X |
                         * --------------  --------------    --------------
                         * subcase:3
                         * --------------  --------------    --------------
                         * | _ | X | _ |    | _ | X | _ |    | O | X | O |
                         * | _ | O | _ | => | O | O | X | => | O | O | X |
                         * | _ | O | X |    | _ | O | X |    | X | O | X |
                         * --------------  --------------    --------------
                         * subcase:5
                         * --------------  --------------    --------------
                         * | _ | X | _ |    | _ | X | _ |    | O | X | X |
                         * | _ | O | _ | => | X | O | O | => | X | O | O |
                         * | _ | O | X |    | _ | O | X |    | O | O | X |
                         * --------------  --------------    --------------
                         * subcase:6
                         * --------------  --------------    --------------
                         * | _ | X | _ |    | _ | X | X |    | O | X | X |
                         * | _ | O | _ | => | _ | O | _ | => | _ | O | x |
                         * | _ | O | X |    | O | O | X |    | O | O | X |
                         * --------------  --------------    --------------
                        */
                        board[1]=x;
                        switch (take_move_2()) {
                            case 3:
                            case 0:board[5] = x;
                                switch (take_move_2()) {
                                    case 2:
                                        board[6] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[2] = x;
                                        return 1;
                                }
                            case 2:board[6] = x;
                                switch (take_move_2()) {
                                    case 5:
                                        board[3] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[5] = x;
                                        take_move_2();
                                        return 0;
                                }
                            case 5:board[3] = x;
                                switch (take_move_2()) {
                                    case 2:
                                        board[6] = x;
                                        take_move_2();
                                        return 0;
                                    default:
                                        board[2] = x;
                                        take_move_2();
                                        return 0;
                                }
                            default:board[2] = x;
                                switch (take_move_2()) {
                                    case 5:
                                        board[0] = x;
                                        return 1;
                                    default:
                                        board[5] = x;
                                        return 1;
                                }
                        }
                }
        }
    }

    int main() //This is the starting of main function
    {
        // We call show instructions function to show the instructions
        show_instructions();
        // We create a variable to indicate that we need to end the program
        bool quit=false;

        //create a while loop till the user quits.
        while(!quit){
            //Now we create a variable to indicate who plays first
            int first=-1;
            char ch;
            string s;
            while(first!=0 && first!=1){
                cout<<"If you want to be Player 1 press '1' otherwise if you want to be Player 2 then press '0'"<<endl;
                cin>>s;
                if(s.length()>1){
                    cout<<"Invalid move. Please enter a single digit number. Play again!!!"<<endl;
                    continue;
                }
                ch=s[0];
                if(isdigit(ch)==false){
                    cout<<"Invalid move. Please enter a number. Play again!!!"<<endl;
                    continue;
                }
                first=ch-'0';
                if(first!=0 && first!=1) {
                    cout<<"Invalid Input!! press 0 or 1"<<endl;
                    first=-1;
                }
            }
            //we initialize the board to empty characters to start a new game
            initialize_board();

            //we switch when the computer plays first then the following code is run
            if(first==0){
                //if the computer plays first then the following code is run
                //the function get_move_1 plays the entire game and returns 1 if computer wins else returns 0 if the match is a tie.
                // The computer never looses
                if(get_move_1()){
                    print_board();
                    cout<<"Computer wins the game"<<endl;
                }
                    //this is when the get_move_1 function returns 0 and it is a tie
                else{
                    cout<<"Game is a tie"<<endl;
                }
            }
                // If the computer plays second then the following code is run
            else{
                cout<<"You are the first to play."<<endl;
                //the function get_move_2 plays the entire game and returns 1 if computer wins else returns 0 if the match is a tie.
                // The computer never looses
                if(get_move_2()){
                    print_board();
                    cout<<"Computer wins the game"<<endl;
                }
                    //this is when the get_move_2 function returns 0 and it is a tie
                else{
                    cout<<"Game is a tie"<<endl;
                }
            }
            cout<<"Do you want to play one more game? Press 1 for yes and 0 for no"<<endl;
            int no=-1;
            cin>>no;
            // This asks whether the plays wants to continue
            while(no!=1 && no!=0){
                cout<<"Invalid input!!"<<endl;
                cout<<"Do you want to play one more game? Press 1 for yes and 0 for no"<<endl;
                cin>>s;
                if(s.length()>1){
                    cout<<"Invalid move. Please enter a single digit number. Play again!!!"<<endl;
                    continue;
                }
                ch=s[0];
                if(isdigit(ch)==false){
                    cout<<"Invalid move. Please enter a number. Play again!!!"<<endl;
                    continue;
                }
                no=ch-'0';
            }
            // If the player doesn't want to play the game then quit the program
            if(no==0) {
                cout<<"Thank you for playing the game. Have a good day."<<endl;
                quit = true;
            }
        }
        return 0;

    }