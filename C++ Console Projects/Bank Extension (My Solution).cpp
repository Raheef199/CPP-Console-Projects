#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

const string ClientsFileName = "Clients3.txt";

struct stClient {
	string accountNum;
	string pinCode;
	string name;
	string phoneNum;
	double accountBalance;
	bool markForDelete = false;
};

string ReadAccountNumber() {
	string accountNum;
	cout << "Please enter Account Number: ";
	cin >> accountNum;

	return accountNum;
}



stClient ChangeClientRecord(string AccountNumber) {
	stClient Client;

	Client.accountNum = AccountNumber;

	cout << "\nEnter PinCode: ";
	getline(cin >> ws, Client.pinCode);

	cout << "Enter Client Name: ";
	getline(cin, Client.name);

	cout << "Enter Phone Number: ";
	getline(cin, Client.phoneNum);

	cout << "Enter Account Balance: ";
	cin >> Client.accountBalance;

	return Client;
}


vector<string> SplitString(string str, string delim) {
	vector<string> vString;
	short pos = 0;
	string sWord;

	while ((pos = str.find(delim)) != string::npos) {
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

string ConvertRecordToLine(stClient Client, string separator = "#//#") {
	string stDataRecord = "";

	stDataRecord += Client.accountNum + separator;
	stDataRecord += Client.pinCode + separator;
	stDataRecord += Client.name + separator;
	stDataRecord += Client.phoneNum + separator;
	stDataRecord += to_string(Client.accountBalance);

	return stDataRecord;
}

stClient ConvertLineToRecord(string line, string separator = "#//#") {
	stClient Client;
	vector<string> vClientsData;

	vClientsData = SplitString(line, separator);

	Client.accountNum = vClientsData[0];
	Client.pinCode = vClientsData[1];
	Client.name = vClientsData[2];
	Client.phoneNum = vClientsData[3];
	Client.accountBalance = stod(vClientsData[4]);

	return Client;
}

vector<stClient> LoadClientsDataFromFile(string FileName) {
	vector<stClient> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);


	if (MyFile.is_open()) {
		string line;
		stClient Client;

		while (getline(MyFile, line)) {
			Client = ConvertLineToRecord(line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}

	return vClients;
}

bool FindClientByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient& Client) {
	for (stClient& C : vClients) {
		if (C.accountNum == AccountNumber) {
			Client = C;
			return true;
		}
	}

	return false;
}

stClient ReadClientData() {

	stClient Client;
	vector<stClient> vClients;
	vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "Adding New Client: ";

	cout << "\n\nEnter Account Number: ";
	getline(cin >> ws, Client.accountNum);

	for (stClient& C : vClients) {
		while (FindClientByAccountNumber(Client.accountNum, vClients, C)) {
			cout << "Client with [" << Client.accountNum << "] already exists, Enter another Account Number: ";
			getline(cin >> ws, Client.accountNum);
		}
	}

	cout << "\nEnter PinCode: ";
	getline(cin >> ws, Client.pinCode);

	cout << "Enter Name: ";
	getline(cin, Client.name);

	cout << "Enter Phone Number: ";
	getline(cin, Client.phoneNum);

	cout << "Enter Account Balance: ";
	cin >> Client.accountBalance;

	return Client;
}

vector<stClient> SaveClientsDataToFile(string FileName, vector<stClient> vClients) {
	fstream MyFile;
	MyFile.open(FileName, ios::out); // overwrite

	string DataLine;

	if (MyFile.is_open()) {
		for (stClient& Client : vClients) {
			if (Client.markForDelete == false) {
				DataLine = ConvertRecordToLine(Client);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}

	return vClients;
}

void AddDataLineToFile(string FileName, string stDataLine) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}

void AddNewClient() {
	stClient Client;
	Client = ReadClientData();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddClients(vector<stClient>& vClients) {
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "-----------------------------------\n\n";

	char answer = 'y';

	do {
		system("cls");
		AddNewClient();


		cout << "\n\nClient Added Successfully, do you want to add more clients? y/n? ";
		cin >> answer;
	} while (answer == 'y' || answer == 'Y');

	cout << "\n\nPress any key to go back to Main Menu...";
	system("pause > 0");
}

void PrintClientData(stClient Client) {
	cout << "| " << left << setw(15) << Client.accountNum;
	cout << "| " << left << setw(15) << Client.pinCode;
	cout << "| " << left << setw(40) << Client.name;
	cout << "| " << left << setw(15) << Client.phoneNum;
	cout << "| " << left << setw(20) << Client.accountBalance;
}

void PrintAllClientsData(vector<stClient> vClients) {
	system("cls");
	cout << "\n\t\t\t\t\t\tClient List (" << vClients.size() << ") Clients(s). \n";
	cout << "\n_______________________________________________________";
	cout << "_____________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Account Number ";
	cout << "| " << left << setw(15) << "Pin Code ";
	cout << "| " << left << setw(40) << "Client Name ";
	cout << "| " << left << setw(15) << "Phone ";
	cout << "| " << left << setw(20) << "Balance ";
	cout << "\n_______________________________________________________";
	cout << "_____________________________________________________\n\n";

	if (vClients.size() == 0) {
		cout << "\t\t\t\t\tNo Clients available in the System! \n";
	}
	else {
		for (stClient Client : vClients) {
			PrintClientData(Client);
			cout << endl;
		}
	}

	cout << "\n\n_______________________________________________________";
	cout << "_____________________________________________________\n\n";

	cout << "\n\nPress any key to go back to Main Menu...";
	system("pause > 0");
}


void PrintClientRecord(stClient Client) {
	cout << "\nThe following are the clients details: \n\n";
	cout << "-----------------------------------\n";
	cout << "Account Number : " << Client.accountNum;
	cout << "\nPin Code       : " << Client.pinCode;
	cout << "\nName           : " << Client.name;
	cout << "\nPhone          : " << Client.phoneNum;
	cout << "\nAccount Balance : " << Client.accountBalance;
	cout << "\n-----------------------------------\n";
}

bool MarkClientForDelete(string AccountNumber, vector<stClient>& vClients) {

	for (stClient& C : vClients) {
		if (C.accountNum == AccountNumber) {
			C.markForDelete = true;
			return true;
		}
	}

	return false;
}

bool DeleteClientByAccountNumber(vector<stClient>& vClients) {
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "-----------------------------------\n\n";
	string accountNumber = ReadAccountNumber();
	stClient Client;
	char answer = 'n';

	if (FindClientByAccountNumber(accountNumber, vClients, Client)) {
		PrintClientRecord(Client);
		cout << "\n\nAre you sure you want to delete this client? y/n? ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y') {
			MarkClientForDelete(accountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);

			vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully. \n";
			cout << "\n\nPress any key to go back to Main Menu...";
			system("pause > 0");
			return true;
		}
		else {
			cout << "\n\nPress any key to go back to Main Menu...";
			system("pause > 0");
			return false;
		}

	}
	else {
		cout << "\nClient with Account Number [" << accountNumber << "] is Not Found! \n";
		cout << "\n\nPress any key to go back to Main Menu...";
		system("pause > 0");
		return false;
	}
}

bool UpdateClientByAccountNumber(vector<stClient>& vClients) {
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen\n";
	cout << "-----------------------------------\n\n";
	stClient Client;
	string accountNumber = ReadAccountNumber();
	char answer = 'n';

	if (FindClientByAccountNumber(accountNumber, vClients, Client)) {
		PrintClientRecord(Client);
		cout << "\n\nAre you sure you want to update this client? y/n? ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y') {
			for (stClient& C : vClients) {
				if (C.accountNum == accountNumber) {
					C = ChangeClientRecord(accountNumber);
					break;
				}
			}
		}
		else {
			cout << "\n\nPress any key to go back to Main Menu...";
			system("pause > 0");
			return false;
		}

		SaveClientsDataToFile(ClientsFileName, vClients);


		cout << "\n\nClient Updated Successfully. \n";
		cout << "\n\nPress any key to go back to Main Menu...";
		system("pause > 0");
		return true;
	}
	else {
		cout << "\nClient with Account Number [" << accountNumber << "] is Not Found! \n";
		cout << "\n\nPress any key to go back to Main Menu...";
		system("pause > 0");
		return false;
	}

}


void FindClientScreen(stClient Client) {
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen\n";
	cout << "-----------------------------------\n\n";
	string accountNumber = ReadAccountNumber();
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	if (FindClientByAccountNumber(accountNumber, vClients, Client)) {
		PrintClientRecord(Client);
	}
	else {
		cout << "\nClient with Account Number [" << accountNumber << "] is Not Found! \n";
	}

	cout << "\n\nPress any key to go back to Main Menu...";
	system("pause > 0");
}



void Exit() {
	system("cls");
	cout << "-------------------------------------------\n";
	cout << "\tProgram Ends :-) \n";
	cout << "-------------------------------------------\n";
	system("pause > 0");
}

void MainMenuScreen() {
	system("cls");
	cout << "============================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "============================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "============================================\n";

}

bool MakeDeposit() {
	string accountNumber = ReadAccountNumber();
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	stClient Client;

	while (!FindClientByAccountNumber(accountNumber, vClients, Client)) {
	    cout << "\nClient with Account Number [" << accountNumber << "] does not exist. \n";
		cout << "\nPlease enter Account Number: ";
		getline(cin >> ws, accountNumber);
	}
	
	PrintClientRecord(Client);

	char answer = 'y';
	short deposit = 0;

	cout << "\n\nPlease enter deposit amount: ";
	cin >> deposit;

	cout << "\n\nAre you sure you want to perform this transaction? y/n? ";
	cin >> answer;

	if (tolower(answer) == 'y') {
		for (stClient& C : vClients) {
			if (C.accountNum == accountNumber) {
			    C.accountBalance += deposit;
		        cout << "\n\nAmount Deposited Successfully. New Balance is " << C.accountBalance << endl;
			}
		}

                cout << "\nPress any key to go back to Transactions Menu...\n";
		SaveClientsDataToFile(ClientsFileName, vClients);
		return true;
	}

	return false;
}

bool MakeWithdraw() {
	string accountNumber = ReadAccountNumber();
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	stClient Client;

	while (!FindClientByAccountNumber(accountNumber, vClients, Client)) {
		cout << "\nClient with Account Number [" << accountNumber << "] does not exist. \n";
		cout << "\nPlease enter Account Number: ";
		getline(cin >> ws, accountNumber);
	}

	PrintClientRecord(Client);

	char answer = 'y';
	short withdraw = 0;

	cout << "\n\nPlease enter withdraw amount: ";
	cin >> withdraw;

	while (withdraw > Client.accountBalance) {
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.accountBalance;
		cout << "\nPlease enter another amount: ";
		cin >> withdraw;
	}

	cout << "\n\nAre you sure you want to perform this transaction? y/n? ";
	cin >> answer;

	if (tolower(answer) == 'y') {
		for (stClient& C : vClients) {
			if (C.accountNum == accountNumber) {
				C.accountBalance -= withdraw;
				cout << "\n\nAmount Withdrawed Successfully. New Balance is " << C.accountBalance << endl;
			}
		}

                cout << "\nPress any key to go back to Transactions Menu...\n";
		SaveClientsDataToFile(ClientsFileName, vClients);
		return true;
	}

	return false;
}

void ShowWithdrawScreen() {
	cout << "-------------------------------------------\n";
	cout << "\tWithdraw Screen \n";
	cout << "-------------------------------------------\n";
	cout << endl;
	MakeWithdraw();
	system("pause > 0");
}

void ShowDepositScreen() {
	cout << "-------------------------------------------\n";
	cout << "\tDeposit Screen \n";
	cout << "-------------------------------------------\n";
	cout << endl;
	MakeDeposit();
	system("pause > 0");
}

enum enTransactionOptions {
	eDeposit = 1, eWithdraw = 2,
	eTotalBalances = 3, eMainMenu = 4
};

short ReadTransactionOption() {
	short num;
	cout << "Choose what you want to do? [1 to 4]? ";
	cin >> num;

	return num;
}

void PrintClientBalanceData(stClient Client) {
	cout << "| " << left << setw(19) << Client.accountNum;
	cout << "| " << left << setw(50) << Client.name;
	cout << "| " << left << setw(15) << Client.accountBalance;
}

void ShowTotalBalances() {
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s). ";
	cout << "\n_______________________________________________________";
	cout << "_____________________________________________________\n\n";
	cout << "| " << setw(19) << left << "Account Number";
	cout << "| " << setw(50) << left << "Client Name";
	cout << "| " << setw(15) << left << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_____________________________________________________\n\n";

	if (vClients.size() == 0) {
		cout << "\t\t\t\t\tNo Clients available in the System! \n";
	}
	else {
		for (stClient Client : vClients) {
			PrintClientBalanceData(Client);
			cout << endl;
		}
	}

	cout << "\n_______________________________________________________";
	cout << "_____________________________________________________\n\n";

	double counter = 0;

	for (stClient& Client : vClients) {
		counter += Client.accountBalance;
	}

	cout << "\t\t\t\t\tTotal Balances = " << counter << endl;

	cout << "\nPress any key to go back to Transactions Menu...\n";
	system("pause > 0");
}

void TransactionsScreen() {
	system("cls");
	cout << "=============================================\n";
	cout << "\t\tTransactions Menu Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] Deposit. \n";
	cout << "\t[2] Withdraw. \n";
	cout << "\t[3] Total Balances. \n";
	cout << "\t[4] Main Menu. \n";
	cout << "==========================================================\n";
	enTransactionOptions TransactionOption;
	TransactionOption = (enTransactionOptions)ReadTransactionOption();

	switch (TransactionOption) {
	case enTransactionOptions::eDeposit:
		system("cls");
		ShowDepositScreen();
		TransactionsScreen();
		break;
	case enTransactionOptions::eWithdraw:
		system("cls");
		ShowWithdrawScreen();
		TransactionsScreen();
		break;
	case enTransactionOptions::eTotalBalances:
		system("cls");
		ShowTotalBalances();
		TransactionsScreen();
		break;
	case enTransactionOptions::eMainMenu:
		system("cls");
		MainMenuScreen();
		break;
	}
}


void ShowMainMenuScreen() {
	stClient Client;
	vector<stClient> vClients;
	vClients = LoadClientsDataFromFile(ClientsFileName);

	MainMenuScreen();

	int num;
	cout << "Choose what you want to do? [1 to 7]? ";
	cin >> num;

	switch (num) {
	case 1:
		PrintAllClientsData(vClients);
		ShowMainMenuScreen();
		break;
	case 2:
		AddClients(vClients);
		ShowMainMenuScreen();
		break;
	case 3:
		DeleteClientByAccountNumber(vClients);
		ShowMainMenuScreen();
		break;
	case 4:
		UpdateClientByAccountNumber(vClients);
		ShowMainMenuScreen();
		break;
	case 5:
		FindClientScreen(Client);
		ShowMainMenuScreen();
		break;
	case 6:
		TransactionsScreen();
		ShowMainMenuScreen();
		break;
	case 7:
		Exit();
		break;
	}
}




int main() {

	ShowMainMenuScreen();

	return 0;
}