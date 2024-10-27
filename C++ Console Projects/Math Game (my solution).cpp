#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
using namespace std;

enum enQuestionsLvl {Easy = 1, Med = 2, Hard = 3, mix = 4};
enum enOperationType {Addition = 1, Subtraction = 2, Multiplication = 3, Division = 4, Mix = 5};

int RandomNumber(int from, int to) {
	int randomNum = rand() % (to - from + 1) + from;
	return randomNum;
}

void ResetScreen() {
	system("cls");
	system("color 0f");
}

int ReadQuestions() {
	short questions = 1;
	do {
		cout << "How Many Questions do you want to answer ? ";
		cin >> questions;
	} while (questions <= 0);

	return questions;
}

int ReadChoice() {
	int choice = 1;
	do {
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> choice;
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);

	return (enQuestionsLvl)choice;
}

int ReadOpType() {
	int opType = 1;
	do {
		cout << "Enter Operation Type [1] Add, [2] Subtract, [3] Multiply, [4] Divide, [5] Mix ? ";
		cin >> opType;
	} while (opType != 1 && opType != 2 && opType != 3 && opType != 4 && opType != 5);
	return opType;
}

int AskForQuestionsLvl(int choice) {
	switch (choice) {
	case enQuestionsLvl::Easy:
		return RandomNumber(1, 10);
	case enQuestionsLvl::Med:
		return RandomNumber(10, 20);
	case enQuestionsLvl::Hard:
		return RandomNumber(50, 100);
	default: 
		return RandomNumber(1, 100);
	}
}

string QuestionLvlName(int choice) {
	if (enQuestionsLvl::Easy == choice)
		return "Easy";
	if (enQuestionsLvl::Med == choice)
		return "Med";
	if (enQuestionsLvl::Hard == choice)
		return "Hard";
	if (enQuestionsLvl::mix == choice)
		return "Mix";
}

string OpTypeSymbol(int opType) {
	if (enOperationType::Addition == opType)
		return "+";
	if (enOperationType::Subtraction == opType)
		return "-";
	if (enOperationType::Multiplication == opType)
		return "x";
	if (enOperationType::Division == opType)
		return "/";
	if (enOperationType::Mix == opType)
		return "+, -, x, /";
}

enOperationType AskForOperationType(int opType) {

	switch (opType) {
	case 1:
		return enOperationType::Addition;
	case 2:
		return enOperationType::Subtraction;
	case 3:
		return enOperationType::Multiplication;
	case 4:
		return enOperationType::Division;
	case 5:
		return enOperationType::Mix;
	}
}



void QuestionList(int &choice, int &opType, int &rightAnswers, int &wrongAnswers) {
	int answer = 0, correctAnswer = 0, number1 = 0, number2 = 0, operation = rand() % 4;
	if (AskForOperationType(opType) == enOperationType::Addition) {
		number1 = AskForQuestionsLvl(choice);
		cout << number1;
		cout << endl;
		number2 = AskForQuestionsLvl(choice);
		cout << number2;
		cout << " +\n\n";
		cout << "________________\n";
		cin >> answer;
		correctAnswer = number1 + number2;
		if (answer != correctAnswer) {
			system("color 4f");
			cout << "\a";
			cout << "Wrong Answer :-( " << endl;
			cout << "The right answer is: " << correctAnswer << endl;
		}
		else {
			system("color 2f");
			cout << "Right Answer :-) " << endl;
		}
	}
	else if (AskForOperationType(opType) == enOperationType::Subtraction) {
		number1 = AskForQuestionsLvl(choice);
		cout << number1;
		cout << endl;
		number2 = AskForQuestionsLvl(choice);
		cout << number2;
		cout << " -\n\n";
		cout << "________________\n";
		cin >> answer;
		correctAnswer = number1 - number2;
		if (answer != correctAnswer) {
			system("color 4f");
			cout << "\a";
			cout << "Wrong Answer :-( " << endl;
			cout << "The right answer is: " << correctAnswer << endl;
		}
		else {
			system("color 2f");
			cout << "Right Answer :-) " << endl;
		}
	}
	else if (AskForOperationType(opType) == enOperationType::Multiplication) {
		number1 = AskForQuestionsLvl(choice);
		cout << number1;
		cout << endl;
		number2 = AskForQuestionsLvl(choice);
		cout << number2;
		cout << " x\n\n";
		cout << "________________\n";
		cin >> answer;
		correctAnswer = number1 * number2;
		if (answer != correctAnswer) {
			system("color 4f");
			cout << "\a";
			cout << "Wrong Answer :-( " << endl;
			cout << "The right answer is: " << correctAnswer << endl;
		}
		else {
			system("color 2f");
			cout << "Right Answer :-) " << endl;
		}
	}
	else if (AskForOperationType(opType) == enOperationType::Division) {
		number1 = AskForQuestionsLvl(choice);
		cout << number1;
		cout << endl;
		number2 = AskForQuestionsLvl(choice);
		cout << number2;
		cout << " /\n\n";
		cout << "________________\n";
		cin >> answer;
		correctAnswer = number1 / number2;
		if (answer != correctAnswer) {
			system("color 4f");
			cout << "\a";
			cout << "Wrong Answer :-( " << endl;
			cout << "The right answer is: " << correctAnswer << endl;
		}
		else {
			system("color 2f");
			cout << "Right Answer :-) " << endl;
		}
	}
	else if (AskForOperationType(opType) == enOperationType::Mix) {
		number1 = AskForQuestionsLvl(choice);
		cout << number1;
		cout << endl;
		number2 = AskForQuestionsLvl(choice);
		cout << number2;
		
		switch (operation) {
		case 0:
			cout << " +\n\n";
			cout << "________________\n";
			correctAnswer = number1 + number2;
			break;
		case 1:
			cout << " -\n\n";
			cout << "________________\n";
			correctAnswer = number1 - number2;
			break;
		case 2:
			cout << " x\n\n";
			cout << "________________\n";
			correctAnswer = number1 * number2;
			break;
		case 3:
			// Check for division by zero
			if (number2 != 0) {
				cout << " /\n\n";
				cout << "________________\n";
				correctAnswer = number1 / number2;
			}
			else
				cout << "Undefined(division by zero)" << endl;
			break;
		}
		cin >> answer;
		if (answer != correctAnswer) {
			system("color 4f");
			cout << "\a";
			cout << "Wrong Answer :-( " << endl;
			cout << "The right answer is: " << correctAnswer << endl;
		}
		else {
			system("color 2f");
			cout << "Right Answer :-) " << endl;
		}
	}

	if (correctAnswer == answer) {
		rightAnswers++;
	}
	else {
		wrongAnswers++;
	}	
}

string PassOrFail(int rightAnswers, int wrongAnswers) {
	if (rightAnswers >= wrongAnswers)
		return "PASS :-)";
	
    return "FAIL :-(";
}

void ShowGameOverScreen(int rightAnswers, int wrongAnswers) {
	cout << "\n\n_____________________________\n\n";
	cout << "  Final Results is " << PassOrFail(rightAnswers, wrongAnswers) << endl;
	cout << "_____________________________\n\n";
}

void ShowGameOverScreenStats(int &questions, int &choice, int &opType, int rightAnswers, int wrongAnswers) {
	cout << "Number of Questions: " << questions << endl;
	cout << "Questions Level    : " << QuestionLvlName(choice) << endl;
	cout << "OpType             : " << OpTypeSymbol(opType) << endl;
	cout << "Number of Right Answers: "<< rightAnswers << endl;
	cout << "Number of Wrong Answers: "<< wrongAnswers << endl;
	cout << "_____________________________\n";
}


void PlayGame() {
	int questions = ReadQuestions(), choice = ReadChoice(), opType = ReadOpType();
	int rightAnswers = 0, wrongAnswers = 0;
	for (int i = 1; i <= questions; i++) {
		cout << "\n\nQuestion [" << i << "/" << questions << "]\n\n";
		QuestionList(choice, opType, rightAnswers, wrongAnswers);
	}
	ShowGameOverScreen(rightAnswers, wrongAnswers);
	ShowGameOverScreenStats(questions, choice, opType, rightAnswers, wrongAnswers);
}

void StartGame() {
	char PlayAgain = 'y';
	do {
		ResetScreen();
		PlayGame();
		cout << "\nDo you want to play again? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}


int main() {
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}