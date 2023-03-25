#include<stdio.h>                
#include<conio.h>                // FOR getch()
#include<time.h>             
#include<stdlib.h>              // for exit(0)
int menu();                   // menu driven function
void display_board(char *, char *);    // this function is displaying the game board
void reset_board();                   // if user want to play again it resets the board
void with_player();                  // to play with friend
void with_smart_computer();           // to play with a smart computer   
void with_evil_computer();             // to play with a cheater computer
void computer_smart_move(int);        // it intelligently pick the location to put the mark
void fill_choice(int,char);           // to fill the mark
int select_player();                  // which player is taking turn now             
int player_symbol(int);               // which symbol is associated with that player
int choice_number(int,char *);        // it ask the user to pick the location where to mark
int is_place_empty(int,int);          // is the picked location is available
int is_winner();                     // checks the winner and the state of game : returns 1 if winner, -1 if draw, 0 when game needs to continue.
int is_choice_left(int,int);         // is any vacant location is left in board
void game_result(int,char *);        // display the result and asked user to play again or not
# define RED "\033[1;31m"                           // DEFINING MACROS FOR COLORS
# define NORMAL_RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[1;34m"
# define GREEN "\033[0;32m"
# define CIAN "\033[1;36m"
# define PURPLE "\33[1;35m "
# define WHITE "\033[1;37m "
#define RESET "\033[0m"

char game_board[3][3]={                             // GLOBAL 2d char array for displaying game
                            {'1','2','3'},
                            {'4','5','6'},
                            {'7','8','9'}
                       };
int smart_board[3][3]={                           // Global 2d int array meant for computer intelligence move! 
                            { 2, 2, 2},
                            { 2, 2, 2},
                            { 2, 2, 2}
                       };
int flag=0;
int main()
{

     switch(menu())                                  //  select one of the variation of the game for play
    {
        case 1:
                with_smart_computer();            // it's a smart computer , you can win but u need to wisely.
                break;
        case 2:
                with_evil_computer();       // you can not win with this, because it will do cheating . at max u can draw but can't win
                break;
        case 3:
                with_player();                 // to play with a friend
                break;
        case 4:
                exit(0);                     // to exit the game
        default:
                printf("Invalid choice");     // invalid choice selected
    }

}
int menu()
{
    int choice;
    system("cls");                      // clear the screen
    for(int i=0;i<5;i++)
        printf("\n");
    printf(RED"\t\tT I C   -   T A C   -   T O E  \n"RESET);
    printf(RED"\t_____________________________________________"RESET);
     for(int i=0;i<5;i++)
        printf("\n");
    printf(YELLOW);
    printf("\n\n\t1. Want To Play With Smart Computer");
    printf("\n\n\t2. Want To Play With Evil Computer");
    printf("\n\n\t3. Want To Play With Player");
    printf("\n\n\t4. EXIT");
    printf(RESET);
    printf(CIAN"\n\n\n\t Enter your choice : "RESET);
    printf(GREEN);
    scanf("%d",&choice);
    printf(RESET);
    return choice;
}
void display_board(char *player1, char *player2)    // display the game board
{
    system("cls");  // to clear screen
    printf(PURPLE"------------T I C  -  T A C  -  T O E---------------\n\n\n"RESET);
    printf(CIAN);
    printf("\n\n %s: X\n",player1);
    printf(RESET);
    printf(YELLOW);
    printf("\n\n %s: 0\n",player2);
    printf(RESET);
    printf("\n\n\n");
    for(int row=0;row<3;row++)
    {
        printf(WHITE);
        printf("\t\t       |       |          ");
        printf("\n\t\t");
        for(int col=0;col<3;col++)
        {
            if(game_board[row][col]=='X')
             {
                  printf(CIAN);
                  printf("   %c  ",game_board[row][col]) ;
             }
            else if(game_board[row][col]=='0')
             {
                   printf(YELLOW);
                   printf("   %c  ",game_board[row][col]) ;
             }
            else
             {
                  printf(WHITE);
                  printf("  %c  ",game_board[row][col]) ;
             }
            printf(RESET);
            if(col!=2)
            {
                    printf(WHITE"|");
                    printf(RESET);
            }

        }
        printf("\n\t\t");
        if(row!=2)
         {
              printf(WHITE);
               printf("______|_______|________");
               printf("\n");
               printf(RESET);
         }
         else
         {
            
              printf(WHITE);
              printf("      |       |          ");
              printf("\n");
              printf(RESET);
         }
    }
    printf("\n\n\n\n\n");

    printf(PURPLE"------------T I C  -  T A C  -  T O E ---------------\n\n\n"RESET);
}

void reset_board()        // resets the board once you end the game and looking to play again
{
    int row,col;
    char a='1';
    flag=0;
    for(row=0;row<3;row++)
    {
        for(col=0;col<3;col++)
        {
            game_board[row][col]=a++;
            smart_board[row][col]=2;
        }
    }
}

void with_player()                   // to play with a friend
{
    int player=0;
    char symbol;
    int choice;
    int flag;
    // player info
    char player1_name[50];         // taking names of the player
    char player2_name[50];
    printf(GREEN"\n\n\nP L A Y E R  1 - N A M E : "RESET);
    fflush(stdin);
    printf(CIAN);
    gets(player1_name);
    printf(RESET);
    printf(GREEN"\n\n\nP L A Y E R  2 - N A M E : "RESET);
    printf(YELLOW);
    fflush(stdin);
    gets(player2_name);
     printf(RESET);

    // flow of game:
    while(1)
    {
          display_board( player1_name,player2_name);      // display the game
          player=select_player();               // select the player turn
          symbol=player_symbol(player);         // selects it's mark symbol
          if(player==0)
             choice=choice_number(player,player1_name);   // returns the choice selected by the particular player
          else                                            // to create specific display of a user we create 2 cariations of it.
            choice=choice_number(player,player2_name);
          fill_choice(choice,symbol);                   //  to fill the choice selected by the player and mark it's symbol
          flag=is_winner();                              // to check is player is  winner or not and check the state of game
          if(flag==1 || flag==-1)                         // 1 indicated win and -1 indicates draw and 0 indicates game continues.
          {
                if(player==0)
                    game_result(flag,player1_name);
                else
                    game_result(flag,player2_name);
                break;
          }                                               

    }

}
void with_smart_computer()            // to play with a smart computer
{
    int player,choice,flag;
    char player1_name[50],symbol;
    printf(GREEN"\nP L A Y E R  -  N A M E  : "RESET);
    fflush(stdin);
    printf(CIAN);
    gets(player1_name);
    printf(RESET);
    while(1)
    {
          display_board(player1_name,"Computer");       // display board
          player=select_player();                    // it selects the player
          if(player==1)                   // computer turn
              computer_smart_move(0) ;
          else                  // user turn
          {
            symbol=player_symbol(player);           // select symbol for a player
            choice=choice_number(player,player1_name); // mark the choice
            fill_choice(choice,symbol);               // fill the choice
          }
         flag=is_winner();                  // check for the winner
         if(flag==1 || flag==-1)             // 1 if win, -1 if draw and 0 game continues
          {
                if(player==0)
                    game_result(flag,player1_name);
                else
                    game_result(flag,"Computer");
                break;
          }

    }
}

void with_evil_computer()                  // it will do cheating , it will block all the possible location where opponent player is going to win in it's next try.
{
    int player,choice,flag;                    
    char player1_name[50],symbol;
    printf(GREEN"\nP L A Y E R   -   N A M E : "RESET);
    fflush(stdin);
    printf(CIAN);
    gets(player1_name);     // takes the player name
    printf(RESET);
    while(1)
    {
          display_board(player1_name,"Computer");
          player=select_player();
          if(player==1)                   // computer turn
              computer_smart_move(1) ;
          else                  // user turn
          {
            symbol=player_symbol(player);   // pick the symbol of user
            choice=choice_number(player,player1_name); // ask the choice looking to fill
            fill_choice(choice,symbol);            // fill the choice 
          }
         flag=is_winner();                 // check the winner 
         if(flag==1 || flag==-1)             // 1 for win , -1 for draw and 0 means game continues
          {
               if(player==0)
                    game_result(flag,player1_name);
               else
                    game_result(flag,"Computer");
                break;                              // it will terminate the loop if either win or draw.
          }

    }

}

void computer_smart_move(int is_evil)            // based on Artifical Intelligence 
{
    int row, col,mul, max_multi=1, selected_row,selected_col,i,j,res, evil_move=0,marked=0;
    if(flag==0)           // for the very first time we select the position randomly like a normally player do
    {
        srand(time(NULL));     // time is the quantity which changes every second  
        while(1)
        {
            int loc=rand()%10; // to get the random number
            if(loc==0)
                continue;        // there is no 0 position in our board 
            if(loc%3!=0)       // if loc is 3,6,9
            {
                 i= loc/3;             
                 j=(loc%3)-1;
            }
            else               // if location u=is 1,2,4,5,7,8
            {
                i=(loc/3)-1;
                j=2;
            }
            res=is_choice_left(i, j);   // check that location is vacant or not
            if(res==0)          // o means not vacant
                continue;
            else
            {                              // we put the mark there
                smart_board[i][j]=3;       // on smart_board we put 3
                game_board[i][j]='0';     // on game_board we put 0 mark of  a computer
                flag=1;                    // for the first and last time this function runs for a random selection
                return;
            }
        }

    }
/* now computer is smart it will wisely choose location like as player do 
    1. seeks if computer is winning or not
    2. if no, blocks the opponent to win
    3. if opponent is not winning, then mark the most appropiate location to win.

    AS , IT UNDERSTAND  ALL THE  CONDITION FIRST THEN MARK, THAT'S WHY IT'S AI BASED COMPUTER.

*/
/*
    SMART BOARD IS FOR COMPUTER: IT have 3 possible values.
    1> if opponent user marked at that location
    2> if that location is empty
    3> if computer marks there what will happen then.

    if sum is 27 then computer is winning at that location
    if sum is 3 means opponent is winning at that location
    maximum the sum is at that location is most appropiate to mark the symbol.

*/
// try to win
    for(row=0;row<3;row++)                        
    {
         for(col=0;col<3;col++)
        {
            if(smart_board[row][col]==2)
            {
                smart_board[row][col]=3;     // puts temporarily 3 at that vacant location   
                mul=smart_board[row][0]*smart_board[row][1]*smart_board[row][2];  //checks the row multiplication
                if(mul==27)        
                {
                    game_board[row][col]='0';   // computer will win
                    return;
                }
                else if(max_multi < mul)     // checking the max value for most appropiate location
                {
                    max_multi=mul;
                    selected_row=row;
                    selected_col=col;

                }
                mul=smart_board[0][col]*smart_board[1][col]*smart_board[2][col];  // checks vertically
                if(mul==27)
                {
                    game_board[row][col]='0';
                    return;
                }
                else if(max_multi < mul)
                {
                    max_multi=mul;
                    selected_row=row;
                    selected_col=col;

                }
                if(row==col)        // checking the left diagnoal
                {
                    mul=smart_board[0][0]*smart_board[1][1]*smart_board[2][2];  
                        if(mul==27)
                    {
                        game_board[row][col]='0';
                        return;
                    }
                        else if(max_multi < mul)
                    {
                        max_multi=mul;
                        selected_row=row;
                        selected_col=col;
                    }

                }
                if(row==0 && col==2 || row==2 && col==0 || row==1 && col==1)    // checking the right diagonal
                {
                    mul=smart_board[0][2]*smart_board[1][1]*smart_board[2][0];
                        if(mul==27)
                    {
                        game_board[row][col]='0';
                        return;
                    }
                    else if(max_multi <mul)
                    {
                        max_multi=mul;
                        selected_row=row;
                        selected_col=col;

                    }

                }
                smart_board[row][col]=2;     // make it to it's orignal form after checking
            }


            }
        }

        // block another player to win

    for(row=0;row<3;row++)
    {
        for(col=0;col<3;col++)
        {
            if(smart_board[row][col]==2)
            {
               smart_board[row][col]=3;         // mark 3 in smart_board at that location
               mul=smart_board[row][0]*smart_board[row][1]*smart_board[row][2]; // horizontally
               if(mul==3)
               {
                    marked=1;                               
                    game_board[row][col]='0';   // mark computer symbol there in game_board
                    if(is_evil==0)            // if computer is not evil we simply return after blocking  one location
                          return;
                      else
                        evil_move=1;          // for evil it need to block all the possible cases where opponent can will so it holds and look for another possible locations.
               }
              mul=smart_board[0][col]*smart_board[1][col]*smart_board[2][col]; // checks vertically
              if(mul==3)
              {
                    marked=1;
                    game_board[row][col]='0';
                    if(is_evil==0)
                          return;
                      else
                        evil_move=1;
              }
              if(row==col)          // checks left diagonal
              {
                mul=smart_board[0][0]*smart_board[1][1]*smart_board[2][2];
                if(mul==3)
                {
                    marked=1;
                    game_board[row][col]='0';
                    if(is_evil==0)
                          return;
                      else
                        evil_move=1;
                }

               }
               if(row==0 && col==2 || row==2 && col==0 || row==1 && col==1)  // check right diagonal
               {
                      mul=smart_board[0][2]*smart_board[1][1]*smart_board[2][0];
                     if(mul==3)
                     {
                         marked=1;
                         game_board[row][col]='0';
                         if(is_evil==0)   // if it's a smart computer only then return
                              return;
                         else
                              evil_move=1;    
                     }

                }
                if(evil_move==0)        //  if at that that location opponent is not winnig then we simply make it to it's orignal state
                     smart_board[row][col]=2;
                else
                    evil_move=0;        // if opponent is winning that location then we remain mark 3 at there in smart_board and in game_board it's '0' marked.
             }                          // evil_move=0 means for checking  next location we reset it's value.
    }
    }

   //  fill appropiate location
    if(marked==0)                               // if it's a smart computer or evil computer doesn't find any location where user is winning
    {                                           // then it mark most appropiate location 
       smart_board[selected_row][selected_col]=3;   // to take a track of game_board marking       
       game_board[selected_row][selected_col]='0';  // marks in the game_board.
    }

}


int select_player()          // selects the player 
{
    static int player=1;    // by static it's state remains saved. And it changes the player when called
    player=!player;          // 
    return player;
}
int player_symbol(int player)      // symbol for a player
{
     if(player==1)
         return('0');                 // for player 1
     else
          return('X');               // for player 0
}
int choice_number(int player,char *player1)      // returns the choice chossed by the player
{
    int choice;
    if(player==0)
    {  
        printf(CIAN"%s ,",player1);
        printf(RESET);
    }
    else
    {
        printf(YELLOW"%s ,",player1);
        printf(RESET);
    }
    printf(RED" M a r k   y o u r   c h o i c e  :"RESET);
    printf(RESET);
    scanf("%d",&choice);
    return choice;
}
void fill_choice(int choice,char symbol)        // fill the choice on the game_board
{
    int i,j,place;
    int flag=0;
   for(i=0;i<3;i++)
   {
        for(j=0;j<3;j++)
        {
            place = (3*i)+(j+1);
            if(choice==place && is_place_empty(i,j))
            {
                game_board[i][j]= symbol;
                smart_board[i][j]=1;  // to make a track of smart_board as well.
                flag=1;
                return ;
            }
        }
   }
   if(flag==0)
   {
        printf(RED"\n\nInvalid choice or that choice is already taken!\n"RESET);
        printf(GREEN"\n\nHit Enter to to fill choice again \n"RESET);
        getch();
        fflush(stdin);
        select_player();
   }

}
int is_place_empty(int i,int j)            // is that choosen place is vacant or not
{
    if(game_board[i][j]=='0'||game_board[i][j]=='X')
        return 0;
    else
        return 1;
}

int is_winner()                     // is the player is winner or not
{
    int row, col, placefilled=1;
    // Checking the Horizontal Match
    for(row=0;row<3;row++)
    {
        if(game_board[row][0]==game_board[row][1]&& game_board[row][1]==game_board[row][2])
            return 1;
    }
    // Checking the Vertical Match
    for(col=0;col<3;col++)
    {
        if(game_board[0][col]==game_board[1][col]&& game_board[1][col]==game_board[2][col])
            return 1;
    }
    // Checking the Diagonal Match
    if(game_board[0][0]==game_board[1][1] && game_board[1][1]==game_board[2][2])
        return 1;
    if(game_board[0][2]==game_board[1][1] && game_board[1][1]==game_board[2][0])
        return 1;

    for(row=0;row<3;row++)             // it checks if there is no winner than game_board have vacant location or not
    {
        for(col=0;col<3;col++)
        {
            if(placefilled==0)
                break;     // come out of loop if found
              if(is_choice_left(row,col)==1)
              {
                    placefilled=0;         // found vacant location on game_board
                    break;             // come out of loop
              }
        }
    }
    if(placefilled==1)        // means no vacant location is present now.
        return -1;
    else
        return 0;          // means vacant location is present on a game_board yet and game can continue.
}

int is_choice_left(int i,int j)
{
    if(game_board[i][j]=='0' ||game_board[i][j]=='X')   // returns 0 if that location is not vacant and 1 if it is vacant
        return 0;
    else
        return 1;                                        
}

void game_result(int flag,char *player)           // generates the result of the game and ask the user to play again or not
{
    int choice;
     if(flag==1)         // player has won the game
     {
        
        printf(PURPLE"\n\n\n############################################################\n\n"RESET);
        printf(GREEN"\n\n\t\t   %s   W O N  \n\n\n\n",player);
        printf(RESET);
        printf(PURPLE"############################################################\n\n"RESET);

     }
     else if(flag==-1)    // game is drawn 
     {
        printf(PURPLE"############################################################\n\n"RESET);
        printf(YELLOW"\n\n\t\tG A M E   D R A W N \n\n\n\n");
        printf(RESET);
        printf(PURPLE"############################################################\n\n"RESET);

     }
    for(int i=0;i<5;i++)
        printf("\n");
    printf(GREEN"DO YOU WANT TO PLAY AGAIN?"RESET);               // ask user to play again or not
    printf(YELLOW"\n\nPRESS 'Y' OR 'y' TO PLAY AGAIN"RESET);        
    printf(RED"\n\nEnter any other key to EXIT  "RED);
    choice=_getch();                                 // takes the ascii value of a inserted key by user              
    if(choice==89 || choice==121)    // ascii value of 'Y' and 'y'
       {
            reset_board();           // resets both boards i.e smart_board and game_board and global variabel flag
             main();             // go to main() function again by which user can  play again
       }
    else
        return;                // just return and there is break, in function body after this function call, which terminate the loop and program ends.

}
