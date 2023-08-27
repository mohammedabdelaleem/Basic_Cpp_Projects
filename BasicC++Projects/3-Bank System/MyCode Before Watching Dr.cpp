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

short ReadNumberInRange(short From, short To)
{
	short Number = 1;
	bool validInput = true;
	do
	{
		cout << "Enter Your Choice [" << From << "-" << To << "] ? ";
		cin >> Number;

	} while (Number<From || Number>To);

	return Number;
}


struct stClient {
	short Id;
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;  ///////

};


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



//Find Procces

void PrintClientCard(const stClient& Client, short index = 1)
{
	cout << "Following Are The Client " << index << " Details:\n\n";

	cout << "Name             :" << Client.Name << endl
		<< "Account Number    :" << Client.AccountNumber << endl
		<< "PinCode           :" << Client.PinCode << endl
		<< "Phone             :" << Client.Phone << endl
		<< "Balance           :" << Client.AccountBalance << endl;
}


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

bool FindClientByAccountNumberAndPrintItsCardOrNot(string AccountNumber, vector<stClient> vClients, bool Print = true)
{
	if (Print)
	{
		system("cls");
		//Header Of Procces
		cout << "---------------------------------\n";
		cout << "\Find Procces\n";
		cout << "---------------------------------\n\n";
	}

	stClient Client;
	bool Found = FindClientByAccountNumber(AccountNumber, vClients, Client);

	if (Found)
	{
		if (Print)
			PrintClientCard(Client);

		return true;
	}
	else
	{
		if (Print)
			cout << "Not Found!!!!!!!\n";

		return false;
	}
}



//Add Clients

string ReadUniqueAccountNumber()
{
	vector<stClient>vClients = LoadCleintsDataFromFile(FileName);
	string AccountNumber = "";


	do
	{
		//	system("cls");
		cout << "Enter Account Number: ";
		cin >> AccountNumber;

		bool FindAccountNumber = FindClientByAccountNumberAndPrintItsCardOrNot(AccountNumber, vClients, false);

		if (FindAccountNumber)
		{
			cout << "\nAccount Found Here,Please Enter Another...\n";
			system("Color 4f");//Red Bk Color
			cout << "\a";
		}

		else
		{
			system("Color 0f");
			return AccountNumber;
		}

	} while (FindClientByAccountNumber);


}

stClient ReadNewClient() {

	stClient Client;

	//Usage of ws will all the whitespace character from buffer , because of [cin+getline]
	cout << "Enter Name? ";
	getline(cin >> ws, Client.Name);

	Client.AccountNumber = ReadUniqueAccountNumber();


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

void AddClients()
{

	char AddMore = 'Y';

	do
	{
		system("cls");
		//Header Of Procces
		cout << "---------------------------------\n";
		cout << "\tAdd Clients \n";
		cout << "---------------------------------\n\n";

		cout << "Adding New Client\n\n";

		AddNewClient();

		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
}

//Print Clients

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

void PrintAllClients(vector<stClient>& vClients)
{
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
		cout << "Empty List!! \n";
	}
}




//Deletion Process

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

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClients) {

	system("cls");
	//Header Of Procces
	cout << "---------------------------------\n";
	cout << "\tDeletion Procces\n";
	cout << "---------------------------------\n\n";

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

string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}


//Updation Process

stClient ChangeClientRecord(string AccountNumber, short Id)
{
	stClient Client;
	Client.AccountNumber = AccountNumber;
	Client.Id = Id;

	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}


bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
	system("cls");
	//Header Of Procces
	cout << "---------------------------------\n";
	cout << "\tUpdation Procces\n";
	cout << "---------------------------------\n\n";

	stClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want update this client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber, C.Id);

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



void ShowMenuList()
{
	short Choice;

	do {
		system("cls");
		cout << "=====================================================\n";
		cout << "\t\tMain Menu Screen\n";
		cout << "======================================================\n";

		cout << "\t[1] Show Clients List.\n" <<
			"\t[2] Add New Client.\n" <<
			"\t[3] Delete Client.\n" <<
			"\t[4] Update Client.\n" <<
			"\t[5] Find Client.\n" <<
			"\t[0] Exit.\n";
		cout << "======================================================\n";

		Choice = ReadNumberInRange(0, 5);

		vector<stClient>vClients = LoadCleintsDataFromFile(FileName);

		switch (Choice)
		{
		case 1:
			PrintAllClients(vClients);
			break;

		case 2:
			AddClients();
			break;

		case 3:
			DeleteClientByAccountNumber(ReadClientAccountNumber(), vClients);
			break;

		case 4:
			UpdateClientByAccountNumber(ReadClientAccountNumber(), vClients);
			break;

		case 5:
			FindClientByAccountNumberAndPrintItsCardOrNot(ReadClientAccountNumber(), vClients);
			break;

		case 0:
			system("Color 0f");
			return;
		}

		cout << endl;
		system("Pause");
	} while (Choice != 0);

}

int main()
{
	ShowMenuList();
}