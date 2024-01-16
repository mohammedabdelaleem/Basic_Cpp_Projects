#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include <windows.h> // Sleep
#include <cstdlib>  // cls

using namespace std;

const string ClientsFileName = "ClientsInfo.txt";
const string UsersFileName = "UserssInfo.txt";

static short ClientId = 0; //it damaged after finish the main() , and returns to 0


enum enMainMenuOption {
	eListClients = 1, eAddNewClient = 2,
	eDeleteClent = 3, eUpdateClient = 4, eFindClient = 5, eTransactions = 6, eMangeUsers = 7, eExit = 8
};

enum enManageUsersMenuOption {
	eListUsers = 1, eAddNewUser = 2,
	eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenuOption = 6
};

enum enTransactionMenuOption {
	eDeposite = 1, eWithDraw = 2, eTotalBalances = 3, eMainMenu = 4
};

enum enMainMenuePermissions {
	eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClients = 8,
	pFindClient = 16, pTranactions = 32, pManageUsers = 64
};

struct stClient {
	short Id = 0;
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0.0;
	bool MarkForDelete = false;  ///////

};

struct  stUser
{
	string UserName;
	string Password;
	short Premissions;
	bool MarkForDelete = false;  ///////

};

stUser CurrentUser;

void ShowMainMenu();
void ShowTransactionMenu();
void GoBackToTransactionScreen();
void Login();
void ShowManageUsersMenu();

//Load And Move Cursor
void moveCursor(int row, int col) {/////////////
	cout << "\033[" << row << ";" << col << "H"; //33 Escape character
}

inline void load(short time)
{
	moveCursor(25, 48);
	cout << "\t--->Loading";
	for (int i = 0; i < time; i++)
	{
		if ((i + 1) != time)
		{
			Sleep(250);//250*10^3sec
			cout << ".";
		}
		else
		{
			Sleep(250);
			cout << ":-)";
			Sleep(350);
		}
	}
	system("cls");
}

//Function I Will Need I My Project
vector<string> SpiltString(string str, string delim = " ")
{
	short Pos = 0;
	string sWord;
	vector<string>vWords;

	while ((Pos = str.find(delim)) != std::string::npos)
	{
		sWord = str.substr(0, Pos); //store The Word

		if (sWord != "") //To Handle Spaces"Ali     Mohammed"
			vWords.push_back(sWord);

		str.erase(0, Pos + delim.length());
	}

	//Print The Last Word
	if (str != "")
		vWords.push_back(str);

	return vWords;
}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#") {

	string stClientRecord = "";

	stClientRecord += to_string(Client.Id) + Seperator;
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}

stClient ConvertLinetoRecord(string sClientRecord, string Seperator = "#//#")
{

	vector<string>vClientRecord = SpiltString(sClientRecord, Seperator);
	stClient Client;

	Client.Id = stoi(vClientRecord[0]);
	Client.AccountNumber = vClientRecord[1];
	Client.PinCode = vClientRecord[2];
	Client.Name = vClientRecord[3];
	Client.Phone = vClientRecord[4];
	Client.AccountBalance = stod(vClientRecord[5]);

	return Client;
}

//Super Funcotion from Eng
vector <stClient> LoadCleintsDataFromFile(string ClientsFileName)
{

	ClientId = 0; //i Made A constructor to increase static=>id , but some thing wrong , so i need to always update it
	vector <stClient> vClients;
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::in);//read Mode

	if (MyFile.is_open())
	{
		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);

			ClientId++;
		}
		MyFile.close();

	}
	return vClients;
}


string ConvertUserRecordToLine(stUser User, string Seperator = "#//#") {

	string sUserRecord = "";

	sUserRecord += User.UserName + Seperator;
	sUserRecord += User.Password + Seperator;
	sUserRecord += to_string(User.Premissions);

	return sUserRecord;
}

stUser ConvertUserLinetoRecord(string sUserRecord, string Seperator = "#//#")
{

	vector<string>vUserRecord = SpiltString(sUserRecord, Seperator);
	stUser User;

	User.UserName = vUserRecord[0];
	User.Password = vUserRecord[1];
	User.Premissions = stoi(vUserRecord[2]);

	return User;
}

vector <stUser> LoadUsersDataFromFile(string UsersFileName)
{
	vector <stUser> vUsers;
	fstream MyFile;
	MyFile.open(UsersFileName, ios::in);//read Mode

	if (MyFile.is_open())
	{
		string Line;
		stUser User;

		while (getline(MyFile, Line))
		{
			User = ConvertUserLinetoRecord(Line);
			vUsers.push_back(User);

			ClientId++;
		}
		MyFile.close();

	}
	return vUsers;
}


short ReadOption(short From, short To)
{
	short Number = 1;
	bool validInput = true;
	do
	{
		cout << "What Do You Want To Do [" << From << "-" << To << "] ? ";
		cin >> Number;

	} while (Number<From || Number>To);

	return Number;
}

void GoBackToMainMenu()
{
	cout << "\n\nPress Any Key To Back To Main Menu......";
	system("Pause>0");
	ShowMainMenu();
}

void ShowAccessDeniedMessage()
{
	cout << "-----------------------------------------------------------\n";
	cout << "Access Denied,\nYou Dao't Have Permissions To Do This ,\nPlease Contact Your Admin\n";
	cout << "-----------------------------------------------------------\n";

}
//////////////////////حلوييين/////////////////////////
bool CheckAccessPermission(enMainMenuePermissions Permission)
{
	if (CurrentUser.Premissions == enMainMenuePermissions::eAll)
		return true;

	if ((Permission & CurrentUser.Premissions) == Permission)
		return true;
	return false;
}


//1-Perform Print Clients
string GetN_char(short Number = 100, char ch = '-')
{
	string NumberOfChars = "";
	for (short i = 0; i < Number; i++)
		NumberOfChars += ch;

	return NumberOfChars;
}

void PrintClientsHeader(short NumberOfClients)
{

	//	cout << "\t\t\t\tClient List(" << stClient::Id << ") Clients\n";
	cout << "\t\t\t\tClient List(" << NumberOfClients << ") Clients\n";

	cout << GetN_char(107, '-') << endl;
	cout << "| Id |  Account Number |    PinCode    |         Client Name           |     Phone        |   Balance      |\n";
	cout << GetN_char(107, '-');

	cout << endl;
}

void PrintClient(stClient& Client)
{
	cout << "| " << left << setw(3) << Client.Id << "| " << left << setw(16) << Client.AccountNumber <<
		"| " << left << setw(14) << Client.PinCode << "| " << left << setw(30) << Client.Name <<
		"| " << left << setw(17) << Client.Phone << "| " << left << setw(15) << Client.AccountBalance << "|\n";

	cout << GetN_char(107, '-') << endl;
}

void ShowAllClientsScreen()
{

	if (!CheckAccessPermission(enMainMenuePermissions::pListClients))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}

	vector<stClient>vClients = LoadCleintsDataFromFile(ClientsFileName);

	system("cls");

	//Header Of Procces
	cout << "---------------------------------\n";
	cout << "\tPrint List\n";
	cout << "---------------------------------\n\n";


	if (vClients.size())
	{

		PrintClientsHeader(vClients.size());
		for (stClient& Client : vClients)
		{
			PrintClient(Client);
		}
	}
	else
	{
		cout << "\n\nNot Clients Available In The System!! \n";
	}
}


//2- Show Add New Client Screen

bool ClientExistsByAccounNumber(string AccountNumber, string ClientsFileName)
{
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close(); //Don't Forget
				return true;
			}
		}

		MyFile.close();
	}

	return false;
}

stClient ReadNewClient() {

	stClient Client;

	//Usage of ws will all the whitespace character from buffer , because of [cin+getline]
	cout << "Enter An Account Number? ";//We Assume Account Number Uniqness
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccounNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient With [" << Client.AccountBalance << "] Already Exist ,Enter Another Account Number: ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter PinCode? ";
	cin >> Client.PinCode;

	cout << "Enter Phone? ";
	cin >> Client.Phone;

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	Client.Id = ++ClientId;

	return Client;
}

void AddClientToFile(string ClientsFileName, string sClientRecord)
{
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << sClientRecord << endl;

	}
	MyFile.close();

}

void AddNewClient()
{
	stClient Client = ReadNewClient();
	AddClientToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
	char AddMore = 'Y';

	do
	{

		cout << "Adding New Client\n\n";

		AddNewClient();

		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}

void ShowAddNewClientsScreen()
{

	if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}

	//Header Of Procces
	cout << "---------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "---------------------------------\n\n";

	AddNewClients();
}


//3-Delete Client
bool FindClientByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient& Client);

string ReadString(string Message)
{
	string Str = "";

	cout << "\n" << Message;
	getline(cin >> ws, Str);

	return Str;
}


bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}

	return false;
}

vector <stClient> SaveCleintsDataToFile(string ClientsFileName, vector<stClient>& vClients)
{

	short StartId = 1;

	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out);//overwrite

	string DataLine;

	if (MyFile.is_open())
	{
		for (stClient& C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				C.Id = StartId++;
				//we only write records that are not marked for delete.
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;

}

void PrintClientCard(const stClient& Client, short index = 0)
{
	(index != 0) ?
		cout << "Following Are The Client " << index << " Details:\n\n" :
		cout << "Following Are The Client  Details:\n\n";


	cout << "Name              :" << Client.Name << endl
		<< "Id                :" << Client.Id << endl
		<< "Account Number    :" << Client.AccountNumber << endl
		<< "PinCode           :" << Client.PinCode << endl
		<< "Phone             :" << Client.Phone << endl
		<< "Balance           :" << Client.AccountBalance << endl;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClients) {

	stClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);

			//Refresh Clients
			vClients = LoadCleintsDataFromFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!"; return false;
	}
}

void ShowDeleteClientScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}

	//Header Of Procces
	cout << "---------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "---------------------------------\n\n";

	vector<stClient>vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadString("Please Enter An Account Number: ");
	DeleteClientByAccountNumber(AccountNumber, vClients);
}


//4-Update Client

stClient ChangeClientRecord(string AccountNumber, short Id)
{
	stClient Client;

	Client.AccountNumber = AccountNumber;
	Client.Id = Id;

	cout << "Enter A New PinCode: ";
	cin >> Client.PinCode;

	cout << "Enter A New Name: ";
	getline(cin >> ws, Client.Name);

	cout << "Enter A New Phone: ";
	cin >> Client.Phone;

	cout << "Enter A New Balance: ";
	cin >> Client.AccountBalance;

	return Client;

}

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{

	stClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

		PrintClientCard(Client);

		cout << "\n\nAre you sure you want Update this client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			for (stClient& Client : vClients)
			{
				if (Client.AccountNumber == AccountNumber)
				{
					Client = ChangeClientRecord(AccountNumber, Client.Id);
					break;
				}
			}

			SaveCleintsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

void ShowUpdateClientScreen()
{

	if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClients))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}

	cout << "---------------------------------\n";
	cout << "\tUpdate Client Screen\n";
	cout << "---------------------------------\n\n";

	vector<stClient>vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadString("Please Enter An Account Number: ");
	UpdateClientByAccountNumber(AccountNumber, vClients);
}


//5-Find Procces

bool FindClientByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient& Client)
{

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	} return false;
}

void ShowFindClientScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}

	cout << "---------------------------------\n";
	cout << "\tFind Client Screen\n";
	cout << "---------------------------------\n\n";

	vector<stClient>vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadString("Please Enter An Account Number: ");
	stClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintClientCard(Client);
	else
		cout << "Client With Account [" << AccountNumber << "] Not Found\n\n";

}

//6-Transactions [Deposite + , WithDraw - , Total Balances ,Main Menu

// 6/1 Deposite

void DepositeBalanceToClientByAccountNumber(string AccountNumber, vector<stClient>& vClients, double Amount)
{
	for (stClient& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			Client.AccountBalance += Amount;
		}
	}
}

void ShowDepositeScreen()
{
	cout << "----------------------------------\n";
	cout << "Deposite Screen\n";
	cout << "----------------------------------\n\n";

	vector<stClient>vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadString("Please Enter An Account Number: ");
	stClient Client;
	double Amount = 0;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nPlease Enter A Deposite Number: ";
		cin >> Amount;

		cout << "Are You Sure You Want Perform This Transaction[Y/N]? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			DepositeBalanceToClientByAccountNumber(AccountNumber, vClients, Amount);
			SaveCleintsDataToFile(ClientsFileName, vClients);

			cout << "\nDeposite Proccess Completed Successfully, New Balance Is : " << Client.AccountBalance << endl;
		}
		else
		{
			cout << "No Problem....\n";
		}


	}
	else
	{
		cout << "Client With Account Number [" << AccountNumber << "] Not Found In The System!!!\n";
	}
}

//// 6/2 WithDraw

void WithDrawAndUpdateClients(string AccountNumber, vector<stClient>& vClients, double Amount)
{
	for (stClient& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			Client.AccountBalance -= Amount;
		}
	}
}

void ShowWithDrawScreen()
{
	cout << "----------------------------------\n";
	cout << "WithDraw Screen\n";
	cout << "----------------------------------\n\n";

	vector<stClient>vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadString("Please Enter An Account Number: ");
	stClient Client;
	double Amount = 0;

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nPlease Enter A WithDraw Number: ";
		cin >> Amount;

		while (Amount > Client.AccountBalance)
		{
			cout << "\n\nAmount Exceeds The Balance ,You Can WithDraw Up To " << Client.AccountBalance << "\n Please Enter Anoter WithDraw Number : ";
			cin >> Amount;
		}

		WithDrawAndUpdateClients(AccountNumber, vClients, Amount);
		SaveCleintsDataToFile(ClientsFileName, vClients);

		cout << "\nWithDraw Proccess Completed Successfully...\n";
	}
	else
	{
		cout << "Client With Account Number [" << AccountNumber << "] Not Found In The System!!!\n";
	}
}


//// 6/3 Print Total Balances
void ShowAllBalancesScreen()
{
	vector<stClient>vClients = LoadCleintsDataFromFile(ClientsFileName);
	double TotalBalances = 0;

	cout << "\t\t\tBalances List (" << vClients.size() << ") Client(s)\n\n";

	cout << GetN_char(87, '-') << endl;
	cout << "|" << left << setw(3) << "Id" << "|" << left << setw(15) << "Account Number" << "|" << left << setw(50) << "Client Name" << "|" << left << setw(15) << "Balance " << "|\n";
	cout << GetN_char(87, '-') << endl;

	for (short i = 0; i < vClients.size(); i++)
	{
		TotalBalances += vClients[i].AccountBalance;

		cout << "|" << left << setw(3) << vClients[i].Id << "|" << left << setw(15) << vClients[i].AccountNumber << "|" << left << setw(50) << vClients[i].Name << "|" << left << setw(15) << vClients[i].AccountBalance << "|\n";
		cout << GetN_char(87, '-') << endl;
	}
	cout << "\t\t\t\t\t\t\tTotal Balances = " << TotalBalances << endl;
}


void PerformTransactionMenu(enTransactionMenuOption  TransactionOption)
{
	switch (TransactionOption)
	{
	case enTransactionMenuOption::eDeposite:
		load(5);
		ShowDepositeScreen();
		GoBackToTransactionScreen();
		break;

	case enTransactionMenuOption::eWithDraw:
		load(5);
		ShowWithDrawScreen();
		GoBackToTransactionScreen();
		break;

	case enTransactionMenuOption::eTotalBalances:
		load(5);
		ShowAllBalancesScreen();
		GoBackToTransactionScreen();
		break;

	case enTransactionMenuOption::eMainMenu:
		load(5);
		GoBackToMainMenu();
		break;

	}
}

void ShowTransactionMenu()
{
	system("cls");
	cout << "====================================================\n";
	cout << "\t\tTransaction Menu Screen\n";
	cout << "====================================================\n";

	cout << "\t[1] Deposite.\n" <<
		"\t[2] WithDraw.\n" <<
		"\t[3] Total Balances.\n" <<
		"\t[4] Main Menu.\n";
	cout << "====================================================\n";

	PerformTransactionMenu((enTransactionMenuOption)ReadOption(1, 4));

}

void GoBackToTransactionScreen()
{
	cout << "\n\nPress Any Key To Back To Transaction Menu......";
	system("Pause>0");
	ShowTransactionMenu();
}

////End Screen
//void ShowEndScreen()
//{
//	cout << "\n-----------------------------------\n";
//	cout << "\tProgram Ends :-)";
//	cout << "\n-----------------------------------\n";
//}

//Performe Main Menu Option
void PerformMainMenuOption(enMainMenuOption MainMenuOption)
{
	switch (MainMenuOption)
	{
	case enMainMenuOption::eListClients:
		//system("cls");
		load(5);
		ShowAllClientsScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eAddNewClient:
		//system("cls");
		load(5);
		ShowAddNewClientsScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eDeleteClent:
		//system("cls");
		load(5);
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eUpdateClient:
		//system("cls");
		load(5);
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eFindClient:
		//system("cls");
		load(5);
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOption::eTransactions:
		//system("cls");
		load(5);
		ShowTransactionMenu();
		//GoBackToMainMenu();
		break;

	case enMainMenuOption::eMangeUsers:
		//system("cls");
		load(5);
		ShowManageUsersMenu();
		break;

	case enMainMenuOption::eExit:
		load(5);
		Login();
		break;

	}


}


void ShowMainMenu()
{

	system("cls");
	cout << "=====================================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "======================================================\n";

	cout << "\t[1] Show Clients List.\n" <<
		"\t[2] Add New Client.\n" <<
		"\t[3] Delete Client.\n" <<
		"\t[4] Update Client.\n" <<
		"\t[5] Find Client.\n" <<
		"\t[6] Transactions.\n" <<
		"\t[7] Manage Users.\n" <<
		"\t[8] Logout\n";
	cout << "======================================================\n";

	PerformMainMenuOption((enMainMenuOption)ReadOption(1, 8));
}



//////////////////////Second Extention///////////////////////////////////////
//User Extention

bool FindUserByUserName(string UserName, vector<stUser> vUsers, stUser& User)
{

	for (stUser& U : vUsers)
	{
		if (U.UserName == UserName)
		{
			User = U;
			return true;
		}
	} return false;
}

bool FindUserByUserNameAndPassword(string UserName, string Password, stUser& User)
{

	vector<stUser>vUsers = LoadUsersDataFromFile(UsersFileName);

	for (stUser& U : vUsers)
	{
		if (U.UserName == UserName && U.Password == Password)
		{
			User = U;
			return true;
		}
	} return false;
}



//1-Show All Users
void PrintUserListHeader(short UsersNumber)
{
	cout << "\t\tUsers List(" << UsersNumber << ") Users\n";
	cout << GetN_char(44) << endl;
	cout << setw(15) << left << "UserName" << "|" << setw(15) << left << "Password" << "|" << setw(11) << left << "Permissions" << "|\n";
	cout << GetN_char(44) << endl;

}

void PrintUser(stUser& User)
{
	cout << setw(15) << left << User.UserName << "|" << setw(15) << left << User.Password << "|" << setw(11) << left << User.Premissions << "|\n";
	cout << GetN_char(44) << endl;

}

void ShowAllUsers()
{
	vector<stUser>vUsers = LoadUsersDataFromFile(UsersFileName);

	system("cls");

	//Header Of Procces
	cout << "---------------------------------\n";
	cout << "\tPrint User List\n";
	cout << "---------------------------------\n\n";


	if (vUsers.size())
	{

		PrintUserListHeader(vUsers.size());
		for (stUser& User : vUsers)
		{
			PrintUser(User);
		}
	}
	else
	{
		cout << "\n\nNot Users Available In The System!! \n";
	}
}
///////////////////////////////////

//2-Add New User
bool FindUserByUserName(string UserName, string UsersFileName)
{
	fstream MyFile;
	MyFile.open(UsersFileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stUser User;
		while (getline(MyFile, Line))
		{
			User = ConvertUserLinetoRecord(Line);
			if (User.UserName == UserName)
			{
				MyFile.close(); //Don't Forget
				return true;
			}
		}

		MyFile.close();
	}

	return false;
}

short ReadPermossionToSet() {

	char Choice = 'n';
	short Permission = 0;

	cout << "\n\nDo You Want To Give Full Access? ";
	cin >> Choice;

	if (toupper(Choice) == 'Y')
	{
		return (short)enMainMenuePermissions::eAll;
	}
	else
	{
		cout << "\nDo You Want To Give Access To : \n";

		cout << "Show Clients List [Y/N]?";
		cin >> Choice;
		if (toupper(Choice) == 'Y')
			Permission += enMainMenuePermissions::pListClients;


		cout << "\nAdd New Client [Y/N]?";
		cin >> Choice;
		if (toupper(Choice) == 'Y')
			Permission += enMainMenuePermissions::pAddNewClient;


		cout << "\nDelete Client [Y/N]?";
		cin >> Choice;
		if (toupper(Choice) == 'Y')
			Permission += enMainMenuePermissions::pDeleteClient;

		cout << "\nUpdate Client [Y/N]?";
		cin >> Choice;
		if (toupper(Choice) == 'Y')
			Permission += enMainMenuePermissions::pUpdateClients;

		cout << "\nFind Client [Y/N]?";
		cin >> Choice;
		if (toupper(Choice) == 'Y')
			Permission += enMainMenuePermissions::pFindClient;

		cout << "\nTransactions [Y/N]?";
		cin >> Choice;
		if (toupper(Choice) == 'Y')
			Permission += enMainMenuePermissions::pTranactions;

		cout << "\nManage Users [Y/N]?";
		cin >> Choice;
		if (toupper(Choice) == 'Y')
			Permission += enMainMenuePermissions::pManageUsers;
	}

	return Permission;
}

stUser ReadNewUser() {

	stUser User;

	cout << "\nEnter UserName? ";//We Assume Account Number Uniqness
	getline(cin >> ws, User.UserName);

	while (FindUserByUserName(User.UserName, UsersFileName))
	{
		cout << "\nUser With [" << User.UserName << "] Already Exist ,Enter Another UserName: ";
		getline(cin >> ws, User.UserName);
	}

	cout << "Enter A Password? ";
	getline(cin, User.Password);


	User.Premissions = ReadPermossionToSet(); ////Important

	return User;
}

void AddUserToFile(string UsersFileName, string sUserRecord)
{
	fstream MyFile;
	MyFile.open(UsersFileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << sUserRecord << endl;

	}
	MyFile.close();

}

void AddNewUser()
{
	stUser User = ReadNewUser();
	AddUserToFile(UsersFileName, ConvertUserRecordToLine(User));
}

void AddNewUsers()
{
	char AddMore = 'Y';

	do
	{

		cout << "\nAdding New User\n\n";

		AddNewUser();

		cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}

void ShowAddNewUserScreen()
{
	system("cls");

	//Header Of Procces
	cout << "---------------------------------\n";
	cout << "\tAdd New Users Screen\n";
	cout << "---------------------------------\n\n";

	AddNewUsers();


}

////////**

//3-Delete User


bool MarkUserForDeleteByUserName(string UserName, vector <stUser>& vUsers)
{
	for (stUser& U : vUsers)
	{
		if (U.UserName == UserName)
		{
			U.MarkForDelete = true;
			return true;
		}
	}

	return false;
}

vector <stUser> SaveUsersDataToFile(string FileName, vector<stUser>& vUsers)
{

	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite

	string DataLine;

	if (MyFile.is_open())
	{
		for (stUser& U : vUsers)
		{
			if (U.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.
				DataLine = ConvertUserRecordToLine(U);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vUsers;

}

void PrintUserCard(const stUser& User, short index = 0)
{
	(index != 0) ?
		cout << "Following Are The User " << index << " Details:\n\n" :
		cout << "Following Are The User  Details:\n\n";


	cout << "UserName          :" << User.UserName << endl
		<< "Password          :" << User.Password << endl
		<< "Permission        :" << User.Premissions << endl;
}

bool DeleteUserByUserName(string UserName, vector<stUser>& vUsers) {

	if (UserName == "Admin")
	{
		cout << "\n\nYou cannot Delete This User.";
		return false;
	}

	stUser User;
	char Answer = 'n';

	if (FindUserByUserName(UserName, vUsers, User)) {

		PrintUserCard(User);

		cout << "\n\nAre you sure you want delete this user? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			MarkUserForDeleteByUserName(UserName, vUsers);
			SaveUsersDataToFile(UsersFileName, vUsers);

			//Refresh Clients
			vUsers = LoadUsersDataFromFile(UsersFileName);

			cout << "\n\nUser Deleted Successfully.";
			return true;
		}
		else
		{
			cout << "User Dosen't Remove\n";
		}
	}
	else
	{
		cout << "\nUser with UserName (" << UserName << ") is Not Found!";
		return false;
	}
}

void ShowDeleteUserScreen()
{
	//Header Of Procces
	cout << "---------------------------------\n";
	cout << "\tDelete User Screen\n";
	cout << "---------------------------------\n\n";

	vector<stUser>vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadString("Please Enter A UserName: ");
	DeleteUserByUserName(UserName, vUsers);
}

//////////////////////////////////////

//4-Update User

stUser ChangeUserRecord(string UserName)
{
	stUser User;

	User.UserName = UserName;

	cout << "Enter A New Password: ";
	cin >> User.Password;

	User.Premissions = ReadPermossionToSet();

	return User;
}

bool UpdateUserByUserName(string UserName, vector<stUser>& vUsers)
{

	stUser User;
	char Answer = 'n';

	if (FindUserByUserName(UserName, vUsers, User)) {

		PrintUserCard(User);

		cout << "\n\nAre you sure you want Update this user? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			for (stUser& User : vUsers)
			{
				if (User.UserName == UserName)
				{
					User = ChangeUserRecord(UserName);
					break;
				}
			}

			SaveUsersDataToFile(UsersFileName, vUsers);

			cout << "\n\nUser Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << UserName << ") is Not Found!";
		return false;
	}
}

void ShowUpdateUserScreen()
{
	cout << "---------------------------------\n";
	cout << "\tUpdate User Screen\n";
	cout << "---------------------------------\n\n";

	vector<stUser>vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadString("Please Enter A UserName To Update Info: ");
	UpdateUserByUserName(UserName, vUsers);
}

/////////////
// 
//5-Find User
void ShowFindUserScreen()
{
	system("cls");
	cout << "----------------------------------\n";
	cout << "\tFind User Screen\n";
	cout << "----------------------------------\n";

	stUser User;
	vector<stUser>vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadString("Please Enter A UserName: ");
	if (FindUserByUserName(UserName, vUsers, User))
	{
		PrintUserCard(User);
	}
	else
	{
		cout << "User With UserName (" << UserName << ") Not Found In The System\n\a";
	}

}

void GoBackToManageUsersMenu()
{
	cout << "Press Any Key To Go Back To Manage Users Screen......";
	system("Pause>0");
	ShowManageUsersMenu();
}

void PerformManageUsersMenuOption(enManageUsersMenuOption ManageUsersMenuOption)
{

	switch (ManageUsersMenuOption)
	{
	case enManageUsersMenuOption::eListUsers:
	{
		load(5);
		ShowAllUsers();
		GoBackToManageUsersMenu();
		break;
	}

	case enManageUsersMenuOption::eAddNewUser:
	{
		load(5);
		ShowAddNewUserScreen();
		GoBackToManageUsersMenu();
		break;
	}
	case enManageUsersMenuOption::eDeleteUser:
	{
		load(5);
		ShowDeleteUserScreen();
		GoBackToManageUsersMenu();
		break;
	}
	case enManageUsersMenuOption::eUpdateUser:
	{
		load(5);
		ShowUpdateUserScreen();
		GoBackToManageUsersMenu();
		break;
	}
	case enManageUsersMenuOption::eFindUser:
	{
		load(5);
		ShowFindUserScreen();
		GoBackToManageUsersMenu();
		break;
	}
	case enManageUsersMenuOption::eMainMenuOption:
	{
		load(5);
		GoBackToMainMenu();
		break;
	}
	}
}


void ShowManageUsersMenu()
{

	if (!CheckAccessPermission(enMainMenuePermissions::pManageUsers))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenu();
		return;
	}

	system("cls");
	cout << "===========================================================\n";
	cout << "\t\tManage User Menu Screen\n";
	cout << "===========================================================\n";

	cout << "\t[1] Show Users List.\n" <<
		"\t[2] Add New User.\n" <<
		"\t[3] Delete User.\n" <<
		"\t[4] Update User.\n" <<
		"\t[5] Find User.\n" <<
		"\t[6] Main Menu.\n";
	cout << "======================================================\n";

	PerformManageUsersMenuOption((enManageUsersMenuOption)ReadOption(1, 6));

}

bool LoadUserInfo(string UserName, string Password)
{
	return (FindUserByUserNameAndPassword(UserName, Password, CurrentUser));

}

void Login()
{
	/*cout << "IF YOU NEED TO EXIT FILL UP USERNAME WITH : XXX\n";
	load(5);*/

	bool LoginFaild = false;
	string UserName, Password;

	do
	{
		system("cls");
		cout << "----------------------------\n";
		cout << "\tLogin Screen\n";
		cout << "----------------------------\n";



		if (LoginFaild)
		{
			cout << "Invalid UserName/Password!\n";
		}

		cout << "Enter UserName : ";
		getline(cin >> ws, UserName);

		cout << "Enter Password : ";
		cin >> Password;

		LoginFaild = !LoadUserInfo(UserName, Password);

	} while (LoginFaild);

	ShowMainMenu();
}

int main()
{

	Login();

	cout << "Press Any Key......";
	system("pause>0");
	return 0;
}