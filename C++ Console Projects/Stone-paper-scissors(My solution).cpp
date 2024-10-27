/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
using namespace std;

int RandomNumber(int from, int to) {
	int randomNum = rand() % (to - from + 1) + from;
	return randomNum;
}

string PlayerChoice(int playerChoice) {
     if (playerChoice == 1)
     	return "Stone";
     else if (playerChoice == 2)
     	return "Paper";
     else if(playerChoice == 3)
     	return "Scissors"; 
	 return "Invalid Choice";
}

string ComputerChoice(int computerChoice) {
	if (computerChoice == 1)
		return "Stone";
	else if (computerChoice == 2)
		return "Paper";
	else if (computerChoice == 3)
		return "Scissors";
	return "Invalid Choice";
}

string WhoWon(int playerChoice, int computerChoice) {
	if (computerChoice == playerChoice) {
		system("color 6f");
		return "No Winner";
	}
	else if (computerChoice == 1 && playerChoice == 2) {
		system("color 2f");
		return "Player1";
	}
	else if (computerChoice == 1 && playerChoice == 3) {
		cout << "\a";
		system("color 4f");
		return "Computer";
	}
	else if (playerChoice == 1 && computerChoice == 2) {
		cout << "\a";
		system("color 4f");
		return "Computer";
	}
	else if (playerChoice == 1 && computerChoice == 3) {
		system("color 2f");
		return "Player1";
	}
	else if (computerChoice == 2 && playerChoice == 1) {
		cout << "\a";
		system("color 4f");
		return "Computer";
	}
	else if (computerChoice == 2 && playerChoice == 3) {
		system("color 2f");
		return "Player1";
	}
	else if (playerChoice == 2 && computerChoice == 1) {
		system("color 2f");
		return "Player1";
	}
	else if (playerChoice == 2 && computerChoice == 3) {
		cout << "\a";
		system("color 4f");
		return "Computer";
	}
	else if (computerChoice == 3 && playerChoice == 1) {
		system("color 2f");
		return "Player1";
	}
	else if (computerChoice == 3 && playerChoice == 2) {
		system("color 2f");
		return "Player1";
	}
	else if (playerChoice == 3 && computerChoice == 1) {
		cout << "\a";
		system("color 4f");
		return "Computer";
	}
	else if (playerChoice == 3 && computerChoice == 2) {
		system("color 2f");
		return "Player1";
	}
}

void TableResults(int round, int playerChoice, int computerChoice) {
		cout << "___________________" << " Round [" << round + 1 << "] " << "___________________\n\n";
		cout << "Player 1 choice: " << PlayerChoice(playerChoice) << endl;
		cout << "Computer choice: " << ComputerChoice(computerChoice) << endl;
	    cout << "Round Winner: " << "[" << WhoWon(playerChoice, computerChoice) << "]" << endl;
	    cout << "__________________________________________________\n";
}

int PlayerWonTimes(int rounds, int playerChoice, int computerChoice) {
	int counter = 0;
	for (int i = 0; i < rounds; i++) {
		if (WhoWon(playerChoice, computerChoice) == "Player1") {
			counter++;
		}
	}
	return counter;
}

int ComputerWonTimes(int rounds, int playerChoice, int computerChoice) {
	int counter = 0;
	for (int i = 0; i < rounds; i++) {
		if (WhoWon(playerChoice, computerChoice) == "Computer") {
			counter++;
		}
	}
	return counter;
}

int DrawTimes(int rounds, int playerChoice, int computerChoice) {
	int counter = 0;
	for (int i = 0; i < rounds; i++) {
		if (WhoWon(playerChoice, computerChoice) == "No Winner") {
			counter++;
		}
	}
	return counter;
}

string DecideWinner(int rounds, int playerChoice, int computerChoice) {
	if(ComputerWonTimes(rounds, playerChoice, computerChoice))
		return "Computer";
	if (PlayerWonTimes(rounds, playerChoice, computerChoice))
		return "Player1";
	if (DrawTimes(rounds, playerChoice, computerChoice))
		return "No Winner";
	
}

void GameOver(int rounds, int playerChoice, int computerChoice) {
	cout << "\t\t\t" << "____________________________________________\n\n";
	cout << "\t\t\t" << "\t\t+++ Game Over +++\t\t\n\n";
	cout << "\t\t\t" << "____________________________________________\n\n";
	cout << "\t\t\t" << "_____________ [Game Results] ________________\n\n";
	cout << "\t\t\t" << "Game Rounds: " << rounds << endl;
	cout << "\t\t\t" << "Player1 times won: " << PlayerWonTimes(rounds, playerChoice, computerChoice) << endl;
	cout << "\t\t\t" << "Computer times won: " << ComputerWonTimes(rounds, playerChoice, computerChoice) << endl;
	cout << "\t\t\t" << "Draw Times: " << DrawTimes(rounds, playerChoice, computerChoice) << endl;
	cout << "\t\t\t" << "Final Winner: " << DecideWinner(rounds, playerChoice, computerChoice) << endl;
	cout << "\t\t\t" << "____________________________________________\n";
}

void StartGame() {
	int playerChoice = 0; int computerChoice = 0, rounds;
	string winner;
	do {
		cout << "How many Rounds 1 to 10?" << endl;
		cin >> rounds;
	} while (rounds < 1 || rounds > 10);
	for (int i = 0; i < rounds; i++) {

		cout << "\n\nRound [" << i + 1 << "] begins: \n\n";
		
		cout << "Your Choice: [1]:Stone, [2]:Paper, [3]: Scissors ? ";
		cin >> playerChoice;
		cout << endl;
		
		computerChoice = RandomNumber(1, 3);

		TableResults(i, playerChoice, computerChoice);
	}

	DecideWinner(rounds, playerChoice, computerChoice);
	GameOver(rounds, playerChoice, computerChoice);

	char answer;
	cout << endl;
	cout << "\t\t\tDo you want to play again? Y/N?";
	cin >> answer;

	switch (answer) {
	   case 'y':
	       system("cls");
	       system("color 0f");
		   StartGame();
		   break;
	   case 'Y':
		   system("cls");
		   system("color 0f");
		   StartGame();
		   break;
	   case 'n':
		   break;
	   case 'N':
		   break;
	   default:
		   break;
	}
}




int main() {
	srand((unsigned)time(NULL));
	
	StartGame();

	return 0;
}