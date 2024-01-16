#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include <windows.h> // Sleep
#include <cstdlib>  // cls

using namespace std;

const string FileName = "ClientsInfo.txt";
static short ClientId = 0; //it damaged after finish the main() , and returns to 0


enum enMainMenuOption {
	eListClients = 1, eAddNewClient = 2,
	eDeleteClent = 3, eUpdateClient = 4, eFindClient = 5, eExit = 6
};


struct stClient {
	short Id=0;
	string AccountNumber="";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance=0.0;
	bool MarkForDelete = false;  ///////

};

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




void ShowMainMenu();

short ReadMainMenuOption(short From, short To)
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
	vector<stClient>vClients = LoadCleintsDataFromFile(FileName);

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

bool ClientExistsByAccounNumber(string AccountNumber, string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line; 
		stClient Client;

		while (getline(MyFile,Line))
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

	while (ClientExistsByAccounNumber(Client.AccountNumber,FileName))
	{
		cout << "\nClient With [" << Client.AccountBalance << "] Already Exist ,Enter Another Account Number: ";	
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter Name? ";
	getline(cin , Client.Name);

	cout << "Enter PinCode? ";
	cin >> Client.PinCode;

	cout << "Enter Phone? ";
	cin >> Client.Phone;

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	Client.Id = ++ClientId;

	return Client;
}

void AddClientToFile(string FileName, string sClientRecord)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << sClientRecord << endl;

	}
	MyFile.close();

}

void AddNewClient()
{
	stClient Client = ReadNewClient();
	AddClientToFile(FileName, ConvertRecordToLine(Client));
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
	//Header Of Procces
	cout << "---------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "---------------------------------\n\n";

	AddNewClients();
}


//3-Delete Client
bool FindClientByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient& Client);

string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
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

vector <stClient> SaveCleintsDataToFile(string FileName, vector<stClient>& vClients) {

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
	return vClients;

}

void PrintClientCard(const stClient& Client, short index = 0)
{
	(index!=0)?
	cout << "Following Are The Client " << index << " Details:\n\n":
		cout << "Following Are The Client  Details:\n\n";


	cout <<"Name              :" << Client.Name << endl
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
			SaveCleintsDataToFile(FileName, vClients);

			//Refresh Clients
			vClients = LoadCleintsDataFromFile(FileName);

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
	//Header Of Procces
	cout << "---------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "---------------------------------\n\n";

	vector<stClient>vClients = LoadCleintsDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}


//4-Update Client

stClient ChangeClientRecord(string AccountNumber , short Id)
{
	stClient Client;

	Client.AccountNumber = AccountNumber;
	Client.Id = Id;

	cout << "Enter A New PinCode: ";
	cin >> Client.PinCode;

	cout << "Enter A New Name: ";
	getline(cin >>ws , Client.Name);

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
					Client = ChangeClientRecord(AccountNumber,Client.Id);	
					break;
				}
			}

			SaveCleintsDataToFile(FileName, vClients);

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
	cout << "---------------------------------\n";
	cout << "\tUpdate Client Screen\n";
	cout << "---------------------------------\n\n";

	vector<stClient>vClients = LoadCleintsDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
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
	cout << "---------------------------------\n";
	cout << "\tFind Client Screen\n";
	cout << "---------------------------------\n\n";

	vector<stClient>vClients = LoadCleintsDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
	stClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintClientCard(Client);
	else
		cout << "Client With Account [" << AccountNumber << "] Not Found\n\n";

}


//End Screen
void ShowEndScreen() 
{
	cout << "\n-----------------------------------\n";  
	cout << "\tProgram Ends :-)"; 
	cout << "\n-----------------------------------\n";
}

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

	case enMainMenuOption::eExit:
		//system("cls");
		load(5);
		ShowEndScreen();
		return;
		
	}


}


//Print Main Menu List To User
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
		"\t[6] Exit.\n";
	cout << "======================================================\n";

	PerformMainMenuOption((enMainMenuOption)ReadMainMenuOption(1, 6));
}


int main()
{
	ShowMainMenu();

	system("pause>0");
	return 0;
}