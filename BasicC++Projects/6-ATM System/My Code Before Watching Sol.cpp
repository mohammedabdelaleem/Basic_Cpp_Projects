
//الحمد لله 

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include <windows.h> // Sleep
#include <cstdlib>  // cls

using namespace std;

const string ClientsFileName = "ClientsInfo.txt";
static short ClientId = 0; //it damaged after finish the main() , and returns to 0

struct stClient {
	short Id = 0;
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0.0;
	bool MarkForDelete = false;  ///////

};
stClient CurrentClient;

enum enMainMenuOption {
	eQuickWithDraw = 1, eNormalWithDraw = 2,
	eDeposite = 3, CheckBalance = 4, eExit = 5
};

enum enQuickWithDrawOption {
	eTwenty = 1, eFifty = 2, eOneHundred = 3, eTwoHundreds = 4, eFourHundreds = 5, eSixHundreds = 6, eEightHundreds = 7, eOneThousand = 8, eQuit
};

void ShowMainMenu();
void Login();
void PrintCurrentClientBalance();

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

string GetN_char(short Number = 100, char ch = '-')
{
	string NumberOfChars = "";
	for (short i = 0; i < Number; i++)
		NumberOfChars += ch;

	return NumberOfChars;
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

void SaveCleintsDataToFile(string FileName, vector<stClient>& vClients)
{

	short StartId = 1;

	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite

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

}

//Super Funcotion from Eng
vector <stClient> LoadCleintsDataFromFile(string FileName)
{

	ClientId = 0; //i Made A constructor to increase static=>id , but some thing wrong , so i need to always update it
	vector <stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

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

bool FindClientByAccountNumber(string AccountNumber, vector<stClient>& vClients, stClient& Client)
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

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string Pincode, vector<stClient>& vClients, stClient& Client)
{

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber && C.PinCode == Pincode)
		{
			Client = C;
			return true;
		}
	} return false;
}


void WithDrawAndUpdateClients(string AccountNumber, vector<stClient>& vClients, int Amount)
{
	for (stClient& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			Client.AccountBalance -= Amount;
			CurrentClient = Client;  //////////////////////////////
			return;
		}
	}
}

void DecreaseBalaceByAmoundAndUpdateClients(int Amount)
{
	vector<stClient>vClients = LoadCleintsDataFromFile(ClientsFileName);

	char Choice = 'n';

	while (Amount > CurrentClient.AccountBalance)
	{
		cout << "\n\nAmount Exceeds The Balance ,You Can WithDraw Up To " << CurrentClient.AccountBalance << "\n Please Enter Anoter WithDraw Number : ";
		cin >> Amount;
	}
	cout << "Are You Sure You Want To Perform This Transaction[Y/N]? ";
	cin >> Choice;

	if (toupper(Choice) == 'Y')
	{
		WithDrawAndUpdateClients(CurrentClient.AccountNumber, vClients, Amount);
		SaveCleintsDataToFile(ClientsFileName, vClients);

		cout << "Done Successfully , New Balance Is " << CurrentClient.AccountBalance << endl;
	}
	else
	{
		cout << "Don't Worry , Balance Dosen't Change\n";
	}

}

void PerformQuickWithDraw(enQuickWithDrawOption QuickWithDrawOption)
{
	switch (QuickWithDrawOption)
	{
	case enQuickWithDrawOption::eTwenty:
		DecreaseBalaceByAmoundAndUpdateClients(20);
		break;

	case enQuickWithDrawOption::eFifty:
		DecreaseBalaceByAmoundAndUpdateClients(50);
		break;

	case enQuickWithDrawOption::eOneHundred:
		DecreaseBalaceByAmoundAndUpdateClients(100);
		break;

	case enQuickWithDrawOption::eTwoHundreds:
		DecreaseBalaceByAmoundAndUpdateClients(200);
		break;

	case enQuickWithDrawOption::eFourHundreds:
		DecreaseBalaceByAmoundAndUpdateClients(400);
		break;

	case enQuickWithDrawOption::eSixHundreds:
		DecreaseBalaceByAmoundAndUpdateClients(600);
		break;

	case enQuickWithDrawOption::eEightHundreds:
		DecreaseBalaceByAmoundAndUpdateClients(800);
		break;

	case enQuickWithDrawOption::eOneThousand:
		DecreaseBalaceByAmoundAndUpdateClients(1000);
		break;

	case enQuickWithDrawOption::eQuit:
		GoBackToMainMenu();
		break;
	}

	vector<stClient>vClients = LoadCleintsDataFromFile(ClientsFileName);
	SaveCleintsDataToFile(ClientsFileName, vClients);
}


//1-Quick WithDraw
void ShowQuickWithDrawScreen()
{
	cout << "===================================\n";
	cout << "\tQuick WithDraw Screen\n";
	cout << "===================================\n";

	cout << "\t[1] 20 \t\t[2] 50" << endl;
	cout << "\t[3] 100\t\t[4] 200" << endl;
	cout << "\t[5] 400\t\t[6] 600" << endl;
	cout << "\t[7] 800\t\t[8] 1000" << endl;
	cout << "\t[9] Exit" << endl;
	cout << "===================================\n";

	PrintCurrentClientBalance();
	//cout << "Choose What To WithDraw From[1] To[8]";
	PerformQuickWithDraw((enQuickWithDrawOption)ReadOption(1, 9));
}

//2- Normal WithDraw

void ShowNormalWithDrawScreen()
{
	cout << "----------------------------------\n";
	cout << "\tNormal WithDraw Screen\n";
	cout << "----------------------------------\n\n";

	PrintCurrentClientBalance();

	int Amount = 0;

	cout << "\nPlease Enter A WithDraw Amount [Multiple Of 5's]: ";
	cin >> Amount;

	while (Amount > CurrentClient.AccountBalance)
	{
		cout << "\n\nAmount Exceeds The Balance ,You Can WithDraw Up To " << CurrentClient.AccountBalance << "\n Please Enter Anoter WithDraw Number : ";
		cin >> Amount;
	}

	while (Amount % 5 != 0)
	{
		cout << "\n\nPlease Enter A WithDraw Amount [Multiple Of 5's]: ";
		cin >> Amount;
	}

	DecreaseBalaceByAmoundAndUpdateClients(Amount);

	cout << "\nWithDraw Proccess Completed Successfully...\n";

}


//3-Deposite

void ShowDepositeScreen()
{
	cout << "----------------------------------\n";
	cout << "Deposite Screen\n";
	cout << "----------------------------------\n\n";

	PrintCurrentClientBalance();


	vector<stClient>vClients = LoadCleintsDataFromFile(ClientsFileName);

	int Amount = 0;
	char Answer = 'n';


	cout << "\n\nPlease Enter A Deposite Number: ";
	cin >> Amount;

	cout << "Are You Sure You Want Perform This Transaction[Y/N]? ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		WithDrawAndUpdateClients(CurrentClient.AccountNumber, vClients, -Amount); // - * - = +
		SaveCleintsDataToFile(ClientsFileName, vClients);

		cout << "\nDeposite Proccess Completed Successfully,  New Balance Is " << CurrentClient.AccountBalance << endl;
	}
	else
	{
		cout << "No Problem....\n";
	}

}

//4-

double GetClientBalance()
{
	return CurrentClient.AccountBalance;
}

void PrintCurrentClientBalance()
{
	cout << "Your Balance Is " << GetClientBalance() << endl;
}
void ShowCheckBalanceScreen()
{
	cout << "===================================\n";
	cout << "\tCheck Baalane Screen\n";
	cout << "===================================\n";

	PrintCurrentClientBalance();
}


void LoginOrNot()
{
	char Choice = 'n';
	cout << "Login [Y,N] ";
	cin >> Choice;

	if (toupper(Choice) == 'Y')
		Login();
	else
		exit(0);
}

void PerformMainMenuOpion(enMainMenuOption MainMenuOption)
{
	switch (MainMenuOption)
	{
	case enMainMenuOption::eQuickWithDraw:
	{
		load(4);
		ShowQuickWithDrawScreen();
		GoBackToMainMenu();
	}

	case enMainMenuOption::eNormalWithDraw:
	{
		load(4);
		ShowNormalWithDrawScreen();
		GoBackToMainMenu();
	}

	case enMainMenuOption::eDeposite:
	{
		load(4);
		ShowDepositeScreen();
		GoBackToMainMenu();
	}

	case enMainMenuOption::CheckBalance:
	{
		load(4);
		ShowCheckBalanceScreen();
		GoBackToMainMenu();
	}

	case enMainMenuOption::eExit:
	{
		load(2);
		LoginOrNot();
	}
	}
}

void ShowMainMenu()
{
	system("cls");
	cout << "======================================\n";
	cout << "\tATM Main Menu Screen\n";
	cout << "======================================\n";

	cout << "\t[1] Quick WithDraw\n" <<
		"\t[2] Normal WithDraw\n" <<
		"\t[3] Deposite\n" <<
		"\t[4] Check Balance\n" <<
		"\t[5] Logout\n";
	cout << "======================================\n";

	PerformMainMenuOpion((enMainMenuOption)ReadOption(1, 5));
}

bool LoadUserInfo(string AccountNumber, string PinCode)
{
	vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	return FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, vClients, CurrentClient);
}

void Login()
{
	bool LoginFaild = false;
	string AccountNumber, PinCode;

	do {

		system("cls");
		cout << "----------------------------\n";
		cout << "\tLogin Screen\n";
		cout << "----------------------------\n";


		if (LoginFaild)
			cout << "Invalid AccountNumber/PinCode\n";


		cout << "Enter An Account Number : ";
		getline(cin >> ws, AccountNumber);

		cout << "Enter A PinCode : ";
		cin >> PinCode;


		LoginFaild = !LoadUserInfo(AccountNumber, PinCode);

	} while (LoginFaild);

	ShowMainMenu();

}


int main()
{
	Login();

	return 0;
}