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
const string UsersFileName = "Users.txt";

void Login();
void ShowMangeUsersScreenMenu();
string ConvertUserRecordToLine(string, string);
void ShowMainMenuScreen();


struct stClient {
	string accountNum;
	string pinCode;
	string name;
	string phoneNum;
	double accountBalance;
	bool markForDelete = false;
};

struct stUsers {
	string userName;
	string password;
	int permissions;
	bool markForDelete = false;
};


string ReadAccountNumber() {
	string accountNum;
	cout << "Please enter Account Number: ";
	cin >> accountNum;

	return accountNum;
}

void GoBackToMainMenu() {
	cout << "\n\nPress any key to go back to Main Menu...";
	system("pause > 0");
}

void GoBackToManageMenuScreen() {
	cout << "\n\nPress any key to go back to Manage Users Menu Screen...";
	system("pause > 0");
}

void GoBackToTransactionsMenuScreen() {
	cout << "\nPress any key to go back to Transactions Menu...\n";
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

	GoBackToMainMenu();
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

	GoBackToMainMenu();
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
			GoBackToMainMenu();
			return true;
		}
		else {
			GoBackToMainMenu();
			return false;
		}

	}
	else {
		cout << "\nClient with Account Number [" << accountNumber << "] is Not Found! \n";
		GoBackToMainMenu();
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
			GoBackToMainMenu();
			return false;
		}

		SaveClientsDataToFile(ClientsFileName, vClients);


		cout << "\n\nClient Updated Successfully. \n";
		GoBackToMainMenu();
		return true;
	}
	else {
		cout << "\nClient with Account Number [" << accountNumber << "] is Not Found! \n";
		GoBackToMainMenu();
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

	GoBackToMainMenu();
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

		GoBackToTransactionsMenuScreen();
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

		GoBackToTransactionsMenuScreen();
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

	GoBackToTransactionsMenuScreen();
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
		ShowMainMenuScreen();
		break;
	}
}

void ShowAccessDeniedScreen() {
	system("cls");
	cout << "\n------------------------------------------\n";
	cout << "Access Denied,\n";
	cout << "You don't Have Permission To Do this,\n";
	cout << "Please Contact Your Admin.\n";
	cout << "------------------------------------------\n\n\n";

	GoBackToMainMenu();
}

string ConvertUserRecordToLine(stUsers User, string separator = "#//#") {
	string stUserDataRecord = "";

	stUserDataRecord += User.userName + separator;
	stUserDataRecord += User.password + separator;
	stUserDataRecord += to_string(User.permissions);

	return stUserDataRecord;
}

stUsers ConvertLineToUserRecord(string line, string separator = "#//#") {
	stUsers User;
	vector<string> vUsersData;

	vUsersData = SplitString(line, separator);

	User.userName = vUsersData[0];
	User.password = vUsersData[1];
	User.permissions = stoi(vUsersData[2]);

	return User;
}

vector<stUsers> LoadUsersDataFromFile(string FileName) {
	vector<stUsers> vUsers;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string line;
		stUsers User;

		while (getline(MyFile, line)) {
			User = ConvertLineToUserRecord(line);
			vUsers.push_back(User);
		}
		MyFile.close();
	}

	return vUsers;
}

vector<stUsers> SaveUsersDataToFile(string FileName, vector<stUsers> vUsers) {
	fstream MyFile;
	MyFile.open(FileName, ios::out); // overwrite

	string DataLine;

	if (MyFile.is_open()) {
		for (stUsers& User : vUsers) {
			if (User.markForDelete == false) {
				DataLine = ConvertUserRecordToLine(User);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}

	return vUsers;
}

stUsers ReadUserInfo() {
	stUsers User;

	cout << "Enter Username: ";
	getline(cin >> ws, User.userName);

	cout << "Enter Password: ";
	getline(cin >> ws, User.password);

	return User;
}

bool FindUserByUsernameAndPassword(string Username, string Password) {
	vector<stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);

	for (stUsers& U : vUsers) {
		if (U.userName == Username && U.password == Password) {
			return true;
		}
	}

	return false;
}

stUsers LoggedInUser;

enum enPermissions {
	Show_Permission = 1, Add_Permission = 2, Delete_Permission = 4,
	Update_Permission = 8, Find_Permission = 16, Transactions_Permission = 32,
	Manage_Permissions = 64
};

void MainMenuScreen() {
	stClient Client;
	vector<stClient> vClients;
	vClients = LoadClientsDataFromFile(ClientsFileName);
	vector <stUsers> vUsers;
	vUsers = LoadUsersDataFromFile(UsersFileName);
	stUsers User;

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
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "============================================\n";

	for (stUsers& U : vUsers) {
		if (U.userName == LoggedInUser.userName) {
			LoggedInUser.permissions = U.permissions;
		}
	}

	int num;
	cout << "Choose what you want to do? [1 to 8]? ";
	cin >> num;

	switch (num) {
	case 1:
		if (LoggedInUser.userName == "Admin" || (LoggedInUser.permissions & enPermissions::Show_Permission) == enPermissions::Show_Permission)
			PrintAllClientsData(vClients);
		else
			ShowAccessDeniedScreen();
		ShowMainMenuScreen();
		break;
	case 2:
		if (LoggedInUser.userName == "Admin" || (LoggedInUser.permissions & enPermissions::Add_Permission) == enPermissions::Add_Permission)
			AddClients(vClients);
		else
			ShowAccessDeniedScreen();
		ShowMainMenuScreen();
		break;
	case 3:
		if (LoggedInUser.userName == "Admin" || (LoggedInUser.permissions & enPermissions::Delete_Permission) == enPermissions::Delete_Permission)
			DeleteClientByAccountNumber(vClients);
		else
			ShowAccessDeniedScreen();
		ShowMainMenuScreen();
		break;
	case 4:
		if (LoggedInUser.userName == "Admin"  || (LoggedInUser.permissions & enPermissions::Update_Permission) == enPermissions::Update_Permission)
			UpdateClientByAccountNumber(vClients);
		else
			ShowAccessDeniedScreen();
		ShowMainMenuScreen();
		break;
	case 5:
		if (LoggedInUser.userName == "Admin" || (LoggedInUser.permissions & enPermissions::Find_Permission) == enPermissions::Find_Permission)
			FindClientScreen(Client);
		else
			ShowAccessDeniedScreen();
		ShowMainMenuScreen();
		break;
	case 6:
		if (LoggedInUser.userName == "Admin" || (LoggedInUser.permissions & enPermissions::Transactions_Permission) == enPermissions::Transactions_Permission)
			TransactionsScreen();
		else
			ShowAccessDeniedScreen();
		ShowMainMenuScreen();
		break;
	case 7:
		if (LoggedInUser.userName == "Admin" || (LoggedInUser.permissions & enPermissions::Manage_Permissions) == enPermissions::Manage_Permissions)
			ShowMangeUsersScreenMenu();
		else
			ShowAccessDeniedScreen();
		ShowMainMenuScreen();
		break;
	case 8:
		Login();
		break;
	}

}

void ShowMainMenuScreen() {
	MainMenuScreen();
}

// Bank Extension 2 Part //

void ManageUsersMenuScreen() {
	system("cls");
	cout << "============================================\n";
	cout << "\t\tManage Users Menu Screen\n";
	cout << "============================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu.\n";
	cout << "============================================\n";
}

void PrintUserList(stUsers User) {
	cout << "| " << left << setw(19) << User.userName;
	cout << "| " << left << setw(10) << User.password;
	cout << "| " << left << setw(15) << User.permissions;
}

void PrintUserRecord(stUsers User) {
	cout << "\nThe following are the clients details: \n";
	cout << "-----------------------------------\n";
	cout << "Username    : " << User.userName;
	cout << "\nPassword    : " << User.password;
	cout << "\nPermissions : " << User.permissions;
	cout << "\n-----------------------------------\n";
}

void ShowListUsersScreen() {
	system("cls");
	vector<stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
	cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
	cout << "\n_______________________________________________________";
	cout << "_____________________________________________________\n\n";
	cout << "| " << setw(19) << left << "User Name";
	cout << "| " << setw(10) << left << "Password";
	cout << "| " << setw(15) << left << "Permissions";
	cout << "\n_______________________________________________________";
	cout << "_____________________________________________________\n\n";

	if (vUsers.size() == 0) {
		cout << "\t\t\t\t\tNo Users available in the System! \n";
	}
	else {
		for (stUsers User : vUsers) {
			PrintUserList(User);
			cout << endl;
		}
	}

	cout << "\n_______________________________________________________";
	cout << "_____________________________________________________\n\n";

	GoBackToManageMenuScreen();
}

void AddUserDataLineToFile(string FileName, string stDataLine) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}

bool UserExistsByUserName(string Username) {
	vector<stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
	for (stUsers U : vUsers) {
		if (Username == U.userName)
			return true;
	}
	return false;
}

int ReadPermissionsToSet() {
	vector<stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
	int permissions = 0;
	char answer = 'y';

	cout << "\nDo you want to give full access? y/n? ";
	cin >> answer;

	if (answer == 'y' || answer == 'Y') {
		return permissions = 127;
	}

	cout << "\nDo you want to give access to: \n";

	cout << "\nShow Client List? y/n? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y') {
		permissions = enPermissions::Show_Permission | permissions;
	}

	cout << "\nAdd New Client? y/n? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y') {
		permissions = (enPermissions::Add_Permission | permissions);
	}

	cout << "\nDelete Client? y/n? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y') {
		permissions = (enPermissions::Delete_Permission | permissions);
	}

	cout << "\nUpdate Client? y/n? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y') {
		permissions = (enPermissions::Update_Permission | permissions);
	}

	cout << "\nFind Client? y/n? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y') {
		permissions = (enPermissions::Find_Permission | permissions);
	}

	cout << "\nTransactions? y/n? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y') {
		permissions = (enPermissions::Transactions_Permission | permissions);
	}

	cout << "\nManage Users? y/n? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y') {
		permissions = (enPermissions::Manage_Permissions | permissions);
	}

	return permissions;
}

stUsers ReadNewUser() {
	stUsers User;

	cout << "Enter Username: ";
	getline(cin >> ws, User.userName);

	while(UserExistsByUserName(User.userName)) {
		cout << "\n\nUser with [" << User.userName << "] already exists, Enter another username: ";
		getline(cin >> ws, User.userName);
	}

	cout << "Enter Password: ";
	getline(cin >> ws, User.password);

	User.permissions = ReadPermissionsToSet();

	AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));

	return User;
}

void AddUserScreen(stUsers &User) {
	char answer = 'n';
	do {
		cout << "Adding New User: \n\n";
		User = ReadNewUser();
		cout << "\n\nUser Added Successfully, do you want to add more Users? Y/N? ";
		cin >> answer;
	} while (answer == 'y' || answer == 'Y');
}

void ShowAddNewUserScreen() {
	system("cls");
	cout << "-------------------------------------------\n";
	cout << "\tAdd New User Screen \n";
	cout << "-------------------------------------------\n";
	stUsers User;
	AddUserScreen(User);

	GoBackToManageMenuScreen();
}

bool MarkUserForDelete(string Username, vector<stUsers>& vUsers) {

	for (stUsers &U : vUsers) {
		if (U.userName == Username) {
			U.markForDelete = true;
			return true;
		}
	}

	return false;
}

void DeleteUserScreen(string Username, vector<stUsers> vUsers) {
	cout << "Please enter Username: ";
	getline(cin >> ws, Username);

	for (stUsers U : vUsers) {
		if (U.userName == Username) {
			PrintUserRecord(U);
		}
	}

	if (!UserExistsByUserName(Username)) {
		cout << "\nUser with Username [" << Username << "] does not exist!\n";
		GoBackToManageMenuScreen();
		return;
	}


	char answer = 'n';
	cout << "\nAre you sure you want to delete this User? y/n? ";
	cin >> answer;

	if (answer == 'y' || answer == 'Y') {
		if (Username != "Admin") {
		    MarkUserForDelete(Username, vUsers);
		}
		else {
			cout << "\nYou cannot Delete This User.";
			GoBackToManageMenuScreen();
			return;
		}
		SaveUsersDataToFile(UsersFileName, vUsers);

		vUsers = LoadUsersDataFromFile(UsersFileName);
		cout << "\n\nUser Deleted Successfully. \n";
	}

}

void ShowDeleteUserScreen() {
	system("cls");
	stUsers User;
	string Username;
	vector<stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
	cout << "-------------------------------------------\n";
	cout << "\tDelete User Screen \n";
	cout << "-------------------------------------------\n";
	DeleteUserScreen(Username, vUsers);

	GoBackToManageMenuScreen();
}

void UpdateUserScreen(string Username, vector<stUsers> vUsers) {
	stUsers User;
	cout << "\nPlease Enter Username: ";
	getline(cin >> ws, Username);

	for (stUsers U : vUsers) {
		if (U.userName == Username) {
			PrintUserRecord(U);
		}
	}

	if (!UserExistsByUserName(Username)) {
		cout << "\nUser with Username [" << Username << "] does not exist!\n";
		GoBackToManageMenuScreen();
		return;
	}

	char answer = 'n';
	cout << "\n\nAre you sure you want to update this User? y/n? ";
	cin >> answer;

	if (answer == 'y' || answer == 'Y') {
		cout << "\n\nEnter Password: ";
		getline(cin >> ws, User.password);
		User.permissions = ReadPermissionsToSet();

		for (stUsers& U : vUsers) {
			if (U.userName == Username) {
				U.password = User.password;
				U.permissions = User.permissions;
			}
		}

		SaveUsersDataToFile(UsersFileName, vUsers);
		vUsers = LoadUsersDataFromFile(UsersFileName);

		cout << "\n\nUser Updated Successfully.";
		GoBackToManageMenuScreen();
	}
	else {
		GoBackToManageMenuScreen();
	}
}

void ShowUpdateUserScreen() {
	system("cls");
	string Username;
	vector<stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
	cout << "-------------------------------------------\n";
	cout << "\tDelete User Screen \n";
	cout << "-------------------------------------------\n";
	UpdateUserScreen(Username, vUsers);
}

void FindUserScreen(string Username, vector<stUsers> vUsers) {
	cout << "Please enter Username: ";
	getline(cin >> ws, Username);

	for (stUsers U : vUsers) {
		if (U.userName == Username) {
			PrintUserRecord(U);
		}
	}

	if (!UserExistsByUserName(Username))
		cout << "\nUser with Username [" << Username << "] does not exist!\n";
}

void ShowFindUserScreen() {
	system("cls");
	stUsers User;
	string Username;
	vector<stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
	cout << "-------------------------------------------\n";
	cout << "\tFind User Screen \n";
	cout << "-------------------------------------------\n";
	FindUserScreen(Username, vUsers);

	GoBackToManageMenuScreen();
}

void ShowMangeUsersScreenMenu() {

	ManageUsersMenuScreen();
	
	int choice = 0;
	cout << "Choose what you want to do? ";
	cin >> choice;

	switch (choice) {
	case 1:
		ShowListUsersScreen();
		ShowMangeUsersScreenMenu();
		break;
	case 2:
		ShowAddNewUserScreen();
		ShowMangeUsersScreenMenu();
		break;
	case 3:
		ShowDeleteUserScreen();
		ShowMangeUsersScreenMenu();
		break;
	case 4:
		ShowUpdateUserScreen();
		ShowMangeUsersScreenMenu();
		break;
	case 5:
		ShowFindUserScreen();
		ShowMangeUsersScreenMenu();
		break;
	case 6:
		ShowMainMenuScreen();
		break;
	}
}


void ShowLoginScreen() {
	cout << "-------------------------------------------\n";
	cout << "\tLogin Screen \n";
	cout << "-------------------------------------------\n";
}

void Login() {
	system("cls");
	ShowLoginScreen();
	stUsers User;
	User = ReadUserInfo();
	LoggedInUser = User;
	if (FindUserByUsernameAndPassword(User.userName, User.password)) {
		ShowMainMenuScreen();
	}
	do {
		system("cls");
		ShowLoginScreen();
		cout << "Invalid Username/Password!\n";
		User = ReadUserInfo();
		LoggedInUser = User;
		if (FindUserByUsernameAndPassword(User.userName, User.password)) {
			ShowMainMenuScreen();
		}
	} while (!FindUserByUsernameAndPassword(User.userName, User.password));
}

int main() {

	Login();

	return 0;
}