/*
This code has been compiled in Code::Blocks 16.01 IDE on Windows 10
Author:- Mishal Shah
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<Windows.h>
#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WARNINGS
char player1_symbol, player2_symbol;
char board_symbol[9] = { '1','2','3','4','5','6','7','8','9' };
char player1_name[50], player2_name[50];
void showBoard(void);
void showRule(void);
void chooseSymbol(void);
int checkHorizontal(void);
int checkVertical(void);
int checkDiagonal(void);
int checkDraw(void);
 
int main(void)
{
	FILE *leaderboard;
	leaderboard = fopen("leaderboard.txt", "a+");
	fclose(leaderboard);
	system("color 09");
	int current_player = 1;
	char board_position[100];
	int game_state = -1;
	char symbol;
	int menu_option;
	
	const int someoneWin =1;
	const int keepGoing = 0;
	
	const int gotoGame =1;
	const int gotoLeaderBoard = 2;
	const int quitGame = 3;
	
	const int player1_turn =1;
	const int player2_turn =2;
	
	showRule();

	printf("\n\nType 1 to start the game:-\nType 2 to view leader board:-\n");
	scanf("%d", &menu_option);
	if (menu_option == gotoGame)
	{
	read:
		menu_option = gotoGame;
		leaderboard = fopen("leaderboard.txt", "a+");
		printf("\nEnter name of player1: ");
		scanf("%s", player1_name);
		fprintf(leaderboard, "\n%s", player1_name);
		printf("Enter name of player2: ");
		scanf("%s", player2_name);
		fprintf(leaderboard, "\t%s", player2_name);
		fclose(leaderboard);
		if (!strcmp(player1_name, player2_name))
		{
			printf("Enter names of different players!\n\n");
			goto read;
		}
		else
			chooseSymbol();
		system("color fc");
		showBoard();
		do
		{
			current_player = ((current_player % 2) ? player1_turn : player2_turn);
			if (current_player == player1_turn)
				printf("%s Type any digit from 1-9 to fill your response:- ", player1_name);
			else
				printf("%s Type any digit from 1-9 to fill your response:- ", player2_name);
			scanf("%s",board_position);
			symbol = ((current_player == player1_turn) ? player1_symbol : player2_symbol);
			if (strcmp(board_position, "1") == 0  && board_symbol[0] == '1')
				board_symbol[0] = symbol;
			else if (strcmp(board_position,"2")==0 && board_symbol[1] == '2')
				board_symbol[1] = symbol;
			else if (strcmp(board_position, "3") == 0 && board_symbol[2] == '3')
				board_symbol[2] = symbol;
			else if (strcmp(board_position, "4") == 0 && board_symbol[3] == '4')
				board_symbol[3] = symbol;
			else if (strcmp(board_position, "5") == 0 && board_symbol[4] == '5')
				board_symbol[4] = symbol;
			else if (strcmp(board_position, "6") == 0 && board_symbol[5] == '6')
				board_symbol[5] = symbol;
			else if (strcmp(board_position, "7") == 0 && board_symbol[6] == '7')
				board_symbol[6] = symbol;
			else if (strcmp(board_position, "8") == 0 && board_symbol[7] == '8')
				board_symbol[7] = symbol;
			else if (strcmp(board_position, "9") == 0 && board_symbol[8] == '9')
				board_symbol[8] = symbol;
			else
			{
				printf("Wrong Selection\n");
				Sleep(1000);
				current_player--;
			}
			game_state = checkVertical();
			if (game_state )
			{
				current_player++;
				showBoard();
				break;
			}
			game_state = checkHorizontal();
			if (game_state )
			{
				current_player++;
				showBoard();
				break;
			}
			game_state = checkDiagonal();
			if (game_state )
			{
				current_player++;
				showBoard();
				break;
			}
			game_state=checkDraw();
			current_player++;
			showBoard();
		} while (game_state == keepGoing);
 

		leaderboard = fopen("leaderboard.txt", "a+");
		if (game_state == someoneWin)
		{
			if (current_player == 2)
			{
				printf("\n\nPlayer1 %s Wins!\n\n", player1_name); fprintf(leaderboard, "\t%s", player1_name);
				getchar();
			}
			else
			{
				printf("\n\nPlayer2 %s Wins!\n\n", player2_name); fprintf(leaderboard, "\t%s", player2_name);
				getchar();
			}
			fclose(leaderboard);
		}
		else
		{
			printf("\n\nGame Draws!\n\n"); fprintf(leaderboard, "\t%s", "DRAW");
			getchar();
			fclose(leaderboard);
		}
	}
	else if (menu_option == gotoLeaderBoard)
	{
	menu2:
		system("cls");
		int cho;
		printf("\n\n");
		printf("\tLEADERBOARD\n\n");
		char c = '\0';
		leaderboard = fopen("leaderboard.txt", "r");
		while (c != EOF)
		{
			c = (char)(getc(leaderboard));
			printf("%c", c);
		}
		fclose(leaderboard);
		printf("\n\nPress 1 to start the game:- ");
		scanf("%d", &cho);
		if (cho == gotoGame)
			goto read;

		else
		{
			printf("\n\nShould have typed 1 to play the game!\nHope to see you back soon!\n\n");
			getchar();
		}
 
	}
	else {
	menu3:
		printf("잘못된 입력입니다!");
		printf("게임을 시작하려면 1을, 리더보드를 보려면 2를 입력하세요");
		scanf("%d", &menu_option);
		if (menu_option == gotoGame) {
			goto read;
		}
		else if (menu_option == gotoLeaderBoard) {
			goto menu2;
		}
		else {
			goto menu3;
		}
	}
}
int checkHorizontal(void)
{
	const int horizontal_complete =1;
	const int horizontal_fail = 0;
	
	if (board_symbol[0] == board_symbol[1] && board_symbol[1] == board_symbol[2])
		return horizontal_complete;
	else if (board_symbol[3] == board_symbol[4] && board_symbol[4] == board_symbol[5])
		return horizontal_complete;
	else if (board_symbol[6] == board_symbol[7] && board_symbol[7] == board_symbol[8])
		return horizontal_complete;
	else
		return horizontal_fail;
}

int checkVertical(void)
{
	const int vertical_complete =1;
	const int vertical_fail = 0;
	
	if (board_symbol[0] == board_symbol[3] && board_symbol[3] == board_symbol[6])
		return vertical_complete;
	else if (board_symbol[1] == board_symbol[4] && board_symbol[4] == board_symbol[7])
		return vertical_complete;
	else if (board_symbol[2] == board_symbol[5] && board_symbol[5] == board_symbol[8])
		return vertical_complete;
	else
		return vertical_fail;
}
int checkDiagonal(void)
{
	const int diagonal_complete =1;
	const int diagonal_fail = 0;
	
	if (board_symbol[0] == board_symbol[4] && board_symbol[4] == board_symbol[8])
		return diagonal_complete;
	else if (board_symbol[2] == board_symbol[4] && board_symbol[4] == board_symbol[6])
		return diagonal_complete;
	else
		return diagonal_fail;
}
int checkDraw(void)
{
	const int draw_complete = -1;
	const int draw_fail = 0;
	
	if (board_symbol[0] != '1' && board_symbol[1] != '2' && board_symbol[2] != '3' && board_symbol[3] != '4' && board_symbol[4] != '5' && board_symbol[5] != '6' && board_symbol[6] != '7' && board_symbol[7] != '8' && board_symbol[8] != '9')
		return draw_complete;
	else
		return draw_fail;
}

void showBoard(void)
{
	system("cls");
 	printf("\tTic-Tac-Toe\n\n");
	printf("\n\n");
	printf("%s:- (%c)\n%s:-  (%c)\n\n\n", player1_name, player1_symbol, player2_name, player2_symbol);
	printf("  %c |  %c | %c\n", board_symbol[0], board_symbol[1], board_symbol[2]);
	printf("    |    |    \n");
	printf("----|----|----\n");
	printf("    |    |    \n");
	printf("  %c |  %c | %c\n", board_symbol[3], board_symbol[4], board_symbol[5]);
	printf("    |    |    \n");
	printf("----|----|----\n");
	printf("  %c |  %c | %c\n", board_symbol[6], board_symbol[7], board_symbol[8]);
	printf("    |    |    \n");
}
void showRule(void)
{
	char link;
	printf("\tTic-Tac-Toe\n\n");
	printf("Welcome to the most played 2D game and a sort of fun using X and O\n\n");
	printf("Rules:-\n");
	printf("\n1:Each player will be entering the number to put respective X or O in the desired position");
	printf("\n2:Player who gets a combination of 3 same characters either diagonal or horizontally or \n  vertically will be declared as the winner");
	printf("\n\nEnjoy the game! Be a Winner!\n\n");
	printf("For more clarifications press Y else type any other character:- ");
	scanf("%c", &link);
	if (link == 'y' || link == 'Y')
	{
		system("start http://www.wikihow.com/Play-Tic-Tac-Toe");
	}
}
void chooseSymbol(void)
{
	char dec;
deci:
	printf("\n\nPlayer1 %s choose the X or 0:", player1_name);
	dec = getchar();
	scanf("%c", &dec);
	if (dec == 'X' || dec == 'x')
	{
		player1_symbol = 'X';
		player2_symbol = '0';
	}
	else if (dec == '0')
	{
		player1_symbol= '0';
		player2_symbol = 'X';

	}
	else
	{
		printf("Please enter either X or 0 only \n\n");
		goto deci;
	}

}
