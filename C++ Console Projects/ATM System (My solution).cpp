#pragma warning(disable: 4996)
#include <iostream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const string ClientsFileName = "Clients3.txt";

struct stClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

stClient CurrentClient;

void Login();
void GoBackToMainMenu();
void ShowATMMainMenu();
void MessageExceedsAmount();
void ShowQuickWithdrawScreen();

enum enATMMainMenuOptions {
	qWithdraw = 1, nWithdraw = 2, Deposit = 3, CheckBalance = 4,
	ChangePassword = 5, DisplayInformation = 6, LogOut = 7
};

enum enQuickWithdrawOptions {
	Twenty = 1, Fifty = 2, OneHundred = 3, TwoHundred = 4, FourHundred = 5,
	SixHundred = 6, EightHundred = 7, OneThousand = 8, Exit = 9
};

enum enQuickWithdrawValues {
	vTwenty = 20, vFifty = 50, vOneHundred = 100, vTwoHundred = 200, vFourHundred = 400,
	vSixHundred = 600, vEightHundred = 800, vOneThousand = 1000,
};

vector<string> SplitString(string str, string delim) {
	vector<string> vString;
	short pos = 0;
	string sWord;

	while ((pos = str.find(delim)) != std::string::npos) {
		sWord = str.substr(0, pos);
		if (sWord != "") {
			vString.push_back(sWord);
		}

		str.erase(0, pos + delim.length());
	}

	if (str != "") {
		vString.push_back(str);
	}

	return vString;
}

stClient ConvertLineToRecord(string Line, string Seperator = "#//#") {
	stClient Client;
	vector<string> vClientsData;

	vClientsData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientsData[0];
	Client.PinCode = vClientsData[1];
	Client.Name = vClientsData[2];
	Client.Phone = vClientsData[3];
	Client.AccountBalance = stod(vClientsData[4]);

	return Client;
}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#") {
	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}

vector<stClient> LoadClientsDataFromFile(string FileName) {
	vector<stClient> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		stClient Client;

		while (getline(MyFile, Line)) {
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

vector<stClient> SaveClientsDataToFile(string FileName, vector<stClient> vClients) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string DataLine;

	if (MyFile.is_open()) {
		for (stClient C : vClients) {
			if (C.MarkForDelete == false) {
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}

	return vClients;
}

bool FindClientByUsernameAndPassword(string AccountNumber, string Password, stClient& CurrentClient) {
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	for (stClient& C : vClients) {
		if (C.AccountNumber == AccountNumber && C.PinCode == Password) {
			CurrentClient = C;
			return true;
		}
	}

	return false;
}

bool LoadClientInfo(string AccountNumber, string Password) {
	if (FindClientByUsernameAndPassword(AccountNumber, Password, CurrentClient))
		return true;
	else
		return false;
}

short ReadATMMainMenuOption() {
	cout << "Choose what you want to do? [1 to 6]? ";
	short choice = 0;
	cin >> choice;

	return choice;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double amount, vector<stClient>& vClients) {
	char answer = 'n';
	cout << "\n\nAre you sure you want to perform this transaction? y/n ? ";
	cin >> answer;

	if (tolower(answer) == 'y') {
		for (stClient& C : vClients) {
			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += amount;
				CurrentClient.AccountBalance = C.AccountBalance;
				SaveClientsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
				return true;
			}
		}

		return false;
	}


}

short ReadQuickWithdrawOption() {
	cout << "Choose what you want to do? [1 to 9]? ";
	short choice = 0;
	cin >> choice;

	return choice;
}

enQuickWithdrawValues AssignWithdrawValueToWithdrawOption(enQuickWithdrawOptions WithdrawOption) {
	switch (WithdrawOption) {
	case enQuickWithdrawOptions::Twenty:
		return enQuickWithdrawValues::vTwenty;
	case enQuickWithdrawOptions::Fifty:
		return enQuickWithdrawValues::vFifty;
	case enQuickWithdrawOptions::OneHundred:
		return enQuickWithdrawValues::vOneHundred;
	case enQuickWithdrawOptions::TwoHundred:
		return enQuickWithdrawValues::vTwoHundred;
	case enQuickWithdrawOptions::FourHundred:
		return enQuickWithdrawValues::vFourHundred;
	case enQuickWithdrawOptions::SixHundred:
		return enQuickWithdrawValues::vSixHundred;
	case enQuickWithdrawOptions::EightHundred:
		return enQuickWithdrawValues::vEightHundred;
	case enQuickWithdrawOptions::OneThousand:
		return enQuickWithdrawValues::vOneThousand;
	}
}

void PerformQuickWithdrawOptions(enQuickWithdrawOptions QuickWithdrawOption) {
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	while (CurrentClient.AccountBalance < AssignWithdrawValueToWithdrawOption(QuickWithdrawOption)) {
		MessageExceedsAmount();
		system("cls");
		ShowQuickWithdrawScreen();
	}

	switch (QuickWithdrawOption) {
	case enQuickWithdrawOptions::Twenty:
		DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, 20 * -1, vClients);
		GoBackToMainMenu();
		break;
	case enQuickWithdrawOptions::Fifty:
		DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, 50 * -1, vClients);
		GoBackToMainMenu();
		break;
	case enQuickWithdrawOptions::OneHundred:
		DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, 100 * -1, vClients);
		GoBackToMainMenu();
		break;
	case enQuickWithdrawOptions::TwoHundred:
		DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, 200 * -1, vClients);
		GoBackToMainMenu();
		break;
	case enQuickWithdrawOptions::FourHundred:
		DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, 400 * -1, vClients);
		GoBackToMainMenu();
		break;
	case enQuickWithdrawOptions::SixHundred:
		DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, 600 * -1, vClients);
		GoBackToMainMenu();
		break;
	case enQuickWithdrawOptions::EightHundred:
		DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, 800 * -1, vClients);
		GoBackToMainMenu();
		break;
	case enQuickWithdrawOptions::OneThousand:
		DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, 1000 * -1, vClients);
		GoBackToMainMenu();
		break;
	case enQuickWithdrawOptions::Exit:
		ShowATMMainMenu();
	}

}

void ShowQuickWithdrawScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tQuick Withdraw Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] 20\t\t[2] 50\n";
	cout << "\t[3] 100\t\t[4] 200\n";
	cout << "\t[5] 400\t\t[6] 600\n";
	cout << "\t[7] 800\t\t[8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "===========================================\n";
	cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
	PerformQuickWithdrawOptions((enQuickWithdrawOptions)ReadQuickWithdrawOption());

	GoBackToMainMenu();
}


void ShowNormalWithdrawScreen() {
	system("cls");
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	double amount = 0;

	do {
		system("cls");
		cout << "===========================================\n";
		cout << "\t\tNormal Withdraw Screen\n";
		cout << "===========================================\n";
		cout << "\nEnter an amount multiple of 5's : ";
		cin >> amount;
		if (amount > CurrentClient.AccountBalance) {
			MessageExceedsAmount();
		}

	} while ((int)amount % 5 != 0 || amount > CurrentClient.AccountBalance);


	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, amount * -1, vClients);

	GoBackToMainMenu();
}

void ShowDepositScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tDeposit Screen\n";
	cout << "===========================================\n";
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	int amount = 0;

	do {
		cout << "\nEnter a positive Deposit Amount: ";
		cin >> amount;
	} while (amount < 0);


	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, amount, vClients);

	GoBackToMainMenu();
}

void ShowBalanceScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tCheck Balance Screen\n";
	cout << "===========================================\n";
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
	GoBackToMainMenu();
}

bool IsPinCodeTheSame(string PinCode) {
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	if (CurrentClient.PinCode == PinCode)
		return true;

	return false;
}

void ShowChangePinCodeScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tChange Password Screen\n";
	cout << "===========================================\n";
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string PinCode;
	cout << "Enter your current PinCode: ";
	cin >> PinCode;

	while (IsPinCodeTheSame(PinCode)) {
		cout << "\nYou entered the same PinCode, Choose a new one: ";
		cin >> PinCode;
	}

	char answer = 'n';
	cout << "\n\nAre you sure you want to change your PinCode? y/n? ";
	cin >> answer;
	if (tolower(answer) == 'y') {
		for (stClient& C : vClients) {
			if (C.AccountNumber == CurrentClient.AccountNumber) {
				CurrentClient.PinCode = PinCode;
				C.PinCode = CurrentClient.PinCode;
			}
		}
		SaveClientsDataToFile(ClientsFileName, vClients);
		cout << "\n\nDone, PinCode Changed Successfully.\n";
	}
	GoBackToMainMenu();
}

void PrintClientRecordLine(stClient CurrentClient) {
	cout << "| " << setw(15) << left << CurrentClient.AccountNumber;
	cout << "| " << setw(10) << left << CurrentClient.PinCode;
	cout << "| " << setw(35) << left << CurrentClient.Name;
	cout << "| " << setw(20) << left << CurrentClient.Phone;
	cout << "| " << setw(30) << left << CurrentClient.AccountBalance;
}

void ShowInformationScreen() {
	system("cls");
	cout << "\n\t\t\t\t\t\tYour Account Information\n";
	cout << "_______________________________________________________";
	cout << "_____________________________________________________\n" << endl;
	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(10) << left << "PinCode";
	cout << "| " << setw(35) << left << "Name";
	cout << "| " << setw(20) << left << "Phone Number";
	cout << "| " << setw(30) << left << "Account Balance";
	cout << "\n_______________________________________________________";
	cout << "_____________________________________________________\n" << endl;
	PrintClientRecordLine(CurrentClient);
	cout << "\n_______________________________________________________";
	cout << "_____________________________________________________\n" << endl;
	GoBackToMainMenu();
}

void PerformATMMainMenuOption(enATMMainMenuOptions ATMMainMenuOption) {
	switch (ATMMainMenuOption) {
	case enATMMainMenuOptions::qWithdraw:
		ShowQuickWithdrawScreen();
		ShowATMMainMenu();
		break;
	case enATMMainMenuOptions::nWithdraw:
		ShowNormalWithdrawScreen();
		ShowATMMainMenu();
		break;
	case enATMMainMenuOptions::Deposit:
		ShowDepositScreen();
		ShowATMMainMenu();
		break;
	case enATMMainMenuOptions::CheckBalance:
		ShowBalanceScreen();
		ShowATMMainMenu();
		break;
	case enATMMainMenuOptions::ChangePassword:
		ShowChangePinCodeScreen();
		ShowATMMainMenu();
		break;
	case enATMMainMenuOptions::DisplayInformation:
		ShowInformationScreen();
		ShowATMMainMenu();
		break;
	case enATMMainMenuOptions::LogOut:
		Login();
	}
}

void GoBackToMainMenu() {
	cout << "\n\nPress any key to go back to Main Menu...";
	system("pause>0");
	ShowATMMainMenu();
}

void PrintTodaysDate() {
	short year, month, day;
	time_t t = time(0);
	tm* now = localtime(&t);

	year = 1900 + now->tm_year;
	month = 1 + now ->tm_mon ;
	day = now->tm_mday;

	cout << day << "/" << month << "/" << year << endl;
}

void ShowATMMainMenu() {
	system("cls");
	cout << "      Welcome, " << CurrentClient.Name << "\t ";
	PrintTodaysDate();
	cout << "\n===========================================\n";
	cout << "\t\tATM Main Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Change PinCode.\n";
	cout << "\t[6] Show Account Information.\n";
	cout << "\t[7] Logout.\n";
	cout << "===========================================\n";
	PerformATMMainMenuOption((enATMMainMenuOptions)ReadATMMainMenuOption());
}

void MessageExceedsAmount() {
	cout << "\nThe amount exceeds your balance, make another choice.\n";
	cout << "Press AnyKey to continue...";
	system("pause>0");
}

void Login() {

	bool LoginFailed = false;

	string AccountNumber, Password;

	do {
		system("cls");
		cout << "---------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n---------------------------------\n";

		if (LoginFailed) {
			cout << "Invalid Account Number/Password!\n";
		}

		cout << "Enter AccountNumber: ";
		getline(cin >> ws, AccountNumber);

		cout << "Enter PinCode: ";
		getline(cin, Password);

		LoginFailed = !LoadClientInfo(AccountNumber, Password);

	} while (LoginFailed);

	ShowATMMainMenu();
}

int main() {

	Login();

	return 0;
}