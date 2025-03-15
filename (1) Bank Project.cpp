#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
#include <iostream>
using namespace std;

const string ClientsFileName = "Clients_Data.text";

enum enClientMood{Show_Client_List=1,Add_New_Client=2,Delete_Client=3,Update_Client_Info=4,Find_Client=5,Transactions_Mood=6,Logout=7};
enum enTransactions{Deposit=1,Withdraw=2,Total_Balances=3,Back_Main_Menue};

struct stClientInfo
{
    string Name, Account_Number, Phone, Pin_Code;
    double Account_Balance;
    bool MarkForDelet = false;
};

string ReadClientAccountNumber()
{
    string AccNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccNumber;
    cout << endl;
    return AccNumber;
}
//                                  Delete the Seperator
vector <string> SplitString(string& S1, string Delim)
{
    vector<string> vString;
    string sword;
    short pos = 0;
    string s1_copy = S1;

    while ((pos = s1_copy.find(Delim)) != string::npos)
    {
        sword = s1_copy.substr(0, pos);
        if (!sword.empty())
        {
            vString.push_back(sword);
        }
        s1_copy.erase(0, pos + Delim.length());
    }
    if (!s1_copy.empty())
    {
        vString.push_back(s1_copy);
    }

    return vString;
}
//                                 Give Information to each Client
stClientInfo ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    vector<string> vClientData = SplitString(Line, Seperator);

    stClientInfo Client;
    Client.Account_Number = vClientData[0];
    Client.Pin_Code = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.Account_Balance = stod(vClientData[4]);

    return Client;
}
//                                  Vector Of Stuctures 
vector<stClientInfo> LoadCleintsDataFromFile(string FileName)
{
    vector<stClientInfo> vClientRecords;
    fstream MyFile1;

    MyFile1.open(FileName, ios::in);
    if (MyFile1.is_open())
    {
        string line;
        while (getline(MyFile1, line))
        {
            stClientInfo Client = ConvertLinetoRecord(line);
            vClientRecords.push_back(Client);
        }
    }
    else {
        cerr << "Error: Could not open file " << FileName << endl; //print error  immediately sent to the output destination (usually the console) without waiting. This is in contrast to cout, which is buffered, meaning it may wait before actually displaying the output until the buffer is full or flushed.


    }
    MyFile1.close();
    return vClientRecords;
}            
//  Print All Clients Information
void PrintClientRecords(stClientInfo Client)
{
    cout << "\nThe following is  Client details :\n";
    cout << "------------------------------------------------\n";
    cout << "\nAccout Number: " << Client.Account_Number;
    cout << "\nPin Code     : " << Client.Pin_Code;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.Account_Balance;
    cout << "\n------------------------------------------------\n";
}
void PrintClientRecord(stClientInfo Client)
{
    cout << "| " << setw(15) << left << Client.Account_Number;
    cout << "| " << setw(12) << left << Client.Pin_Code;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.Account_Balance;
}
void PrintAllClientsData(vector<stClientInfo> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(12) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stClientInfo& Client_Data : vClients)
    {
        PrintClientRecord(Client_Data);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void PrintAllClients()
{
    vector<stClientInfo> vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintAllClientsData(vClients);
}
// Add Clients
bool CheckIfAccountExictBefore(string AccNumber)
{
    vector<stClientInfo> vClients;
    vClients = LoadCleintsDataFromFile(ClientsFileName);

    for (stClientInfo& Client_Data : vClients)
    {
        if (AccNumber==  Client_Data.Account_Number)
        {
            return true;
        }
    }
    return false;


}
stClientInfo AddNewClientInfo()
{
    stClientInfo Client;
    // ignore(0, "\n");
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.Account_Number);
    if (CheckIfAccountExictBefore(Client.Account_Number))
    {
        cout << "\n Client With Account Number [" << Client.Account_Number << "] already exists, ";
        cout << "Enter another Account Number? ";
        cin >> Client.Account_Number;
    }
    cout << "Enter PinCode? ";
    getline(cin>> ws, Client.Pin_Code);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.Account_Balance;
    return Client;
}
string ConvertRecordToLine(stClientInfo Client, string Delim = "#//#")
{
    string ClintInfo = "";

    ClintInfo += Client.Account_Number + Delim;
    ClintInfo += Client.Pin_Code + Delim;
    ClintInfo += Client.Name + Delim;
    ClintInfo += Client.Phone + Delim;
    ClintInfo += to_string(Client.Account_Balance);

    return ClintInfo;
}
void AddDataLineToFile(string FileName, string DataLine)
{
    fstream My_File;
    My_File.open(FileName, ios::out | ios::app);
    if (My_File.is_open())
    {
        My_File << DataLine << endl;
    }
    else {
        cerr << "Error: Could not open file " << FileName << endl;
    }

    My_File.close();

}
void AddNewClient()
{
    stClientInfo Client;
    Client = AddNewClientInfo();

    string Dataline;
    Dataline = ConvertRecordToLine(Client);

        AddDataLineToFile(ClientsFileName, Dataline);
}
void AddMoreClientsScreen()
{
    char Add_More = 'Y';
    do
    {
        cout << "\n\n====================================================\n";
        cout << "\t\tAdd New Client Screen\n";
        cout << "====================================================\n";

        cout << "Adding New Client:\n\n";
        AddNewClient();

        cout << "\n Client Added Successfully, do you want to add more clients? {Y or N}:  ";
        cin >> Add_More;

    } while (Add_More == 'Y' || Add_More == 'y');

}
//Delete Clients
bool IsAccountNumberExist(string Account_Number, vector<stClientInfo> vClients, stClientInfo& Client)
{
    vClients = LoadCleintsDataFromFile(ClientsFileName);
    for (stClientInfo& Client_Data : vClients)
    {
        if (Client_Data.Account_Number == Account_Number)
        {
            Client = Client_Data;
            return true;
        }
    }
    return false;

}
bool MarkClientForDeleteByAccountNumber(string AccNumber, vector<stClientInfo>& vClients)
{
    for (stClientInfo& Client : vClients)
    {
        if (Client.Account_Number == AccNumber)
        {
            Client.MarkForDelet = true;
            return true;
        }
    }
    return false;
}
vector <stClientInfo> SaveCleintsDataToFile(string FileName, vector<stClientInfo> vClients)
{
    fstream My_File;
    string DataLine;
    My_File.open(FileName, ios::out);
    if (My_File.is_open())
    {
        for (stClientInfo& C : vClients)
        {
            if (!(C.MarkForDelet))
            {
                DataLine = ConvertRecordToLine(C);
                AddDataLineToFile(FileName, DataLine);
            }
        }
        My_File.close();
    }
    return vClients;
}
bool DeleteClientByAccountNumber(string Account_Number, vector<stClientInfo> vClientRecords)
{
    char Answer;
    stClientInfo Client;
    if (IsAccountNumberExist(Account_Number, vClientRecords, Client))
    {
        PrintClientRecords(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(Account_Number, vClientRecords);
            SaveCleintsDataToFile(ClientsFileName, vClientRecords);
            vClientRecords = LoadCleintsDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else {
        cout << "\nClient with Account Number (" << Account_Number << ") is Not Found!";
        return false;
    }
}
void DeleteAccountScreen()
{
    cout << "\n\n====================================================\n";
    cout << "\t\tDelete Client Screen\n";
    cout << "====================================================\n\n";

    vector<stClientInfo> vClientRecords;
    vClientRecords = LoadCleintsDataFromFile(ClientsFileName);
    string AccNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccNumber, vClientRecords);

}
//Update Clients Information
stClientInfo ChangeClientRecord(string AccountNumber)
{
    stClientInfo Client;
    Client.Account_Number = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.Pin_Code);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.Account_Balance;
    return Client;
}
bool UpdateClientAccount(string AccNumber, vector<stClientInfo> vClients)
{
    stClientInfo Client;
    char Update;
    if (IsAccountNumberExist(AccNumber, vClients, Client)) {
        PrintClientRecords(Client);
        cout << "\n\nAre you sure you want to Update this Client? {y or N}: ";
        cin >> Update;
        if (Update == 'y' || Update == 'Y') {
            for (stClientInfo& C : vClients) {
                if (C.Account_Number == AccNumber) {
                    C = ChangeClientRecord(AccNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.\n";
            return true;
        }
    }
    else {
        cout << "\nClient with Account Number (" << AccNumber << ") is Not Found!\n";
        return false;
    }
}
void UpdateClientAccountScreen()
{
    cout << "\n\n====================================================\n";
    cout << "\t\tUpdate Client Screen\n";
    cout << "====================================================\n\n";

    vector<stClientInfo> vClientRecords;
    vClientRecords = LoadCleintsDataFromFile(ClientsFileName);
    string AccNumber = ReadClientAccountNumber();
    UpdateClientAccount(AccNumber, vClientRecords);
}
// Find Client
bool FindAccount(string AccNumber, vector<stClientInfo> vClients, stClientInfo& Clients)
{
    if (IsAccountNumberExist(AccNumber, vClients, Clients))
    {
        PrintClientRecords(Clients);
        return true;
    }
    else
    {
        cout << "Client with Account Number (" << AccNumber << ") Not Found!";
        return false;
    }

}
void FindAccountScreen()
{
    system("cls");
    cout << "\n\n====================================================\n";
    cout << "\tFind Client Screen\n";
    cout << "====================================================\n\n";
    string AccNumber;
    stClientInfo Clients;
    vector <stClientInfo> vClients;
    vClients = LoadCleintsDataFromFile(ClientsFileName);

     AccNumber = ReadClientAccountNumber();
     FindAccount(AccNumber, vClients, Clients);
}
  
//                                                   Transactions
// Deposit
bool DepositTransaction(string AccNumber, vector<stClientInfo>& vClients)
{
    stClientInfo Client;
    double Deposit_Amount;
    char ensure;

    // Loop until a valid account number is entered
    while (true)
    {
        // Check if account number exists
        if (IsAccountNumberExist(AccNumber, vClients, Client))
        {
            PrintClientRecords(Client);

            // Iterate over the list of clients to find the correct account
            for (stClientInfo& C : vClients)
            {
                if (C.Account_Number == AccNumber)
                {
                    cout << "\nPlease Enter Deposit Amount: ";
                    cin >> Deposit_Amount;

                    cout << "\n\nAre you sure you want to perform this transaction (Y or N)? ";
                    cin >> ensure;

                    if (ensure == 'y' || ensure == 'Y')
                    {
                        C.Account_Balance += Deposit_Amount;
                        SaveCleintsDataToFile(ClientsFileName, vClients);
                        return true;
                    }
                    else
                    {
                        cout << "Transaction cancelled.\n";
                        return false;
                    }
                }
            }
        }
        else
        {
            cout << "\nClient with Account Number (" << AccNumber << ") is not found!\n";
            cout << "Please enter a valid account number: ";
            cin >> AccNumber;
        }
    }
}
void DepositTrancactionScreen()
{
    system("cls");
    cout << "\n\n====================================================\n";
    cout << "\tDeposit Screen\n";
    cout << "====================================================\n\n";

    vector<stClientInfo> vClients;
    vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccNumber;
    AccNumber = ReadClientAccountNumber();
    DepositTransaction(AccNumber, vClients);
}
//  WithDraw
bool WithDrawTransaction(string AccNumber, vector<stClientInfo>& vClients)
{
    stClientInfo Client;
    double WithDraw_Amount;
    char ensure;
    while (true)
    {
        if (IsAccountNumberExist(AccNumber, vClients, Client))
        {
            PrintClientRecords(Client);

            // Iterate over the list of clients to find the correct account
            for (stClientInfo& C : vClients)
            {
                if (C.Account_Number == AccNumber)
                {
                    while (true)
                    {
                        cout << "\nPlease Enter Withdraw Amount: ";
                        cin >> WithDraw_Amount;

                        // Check if the withdrawal amount is less than or equal to the account balance
                        if (WithDraw_Amount <= C.Account_Balance)
                        {
                            C.Account_Balance -= WithDraw_Amount;

                            cout << "\n\nAre you sure you want to perform this transaction (Y or N)? ";
                            cin >> ensure;

                            if (ensure == 'y' || ensure == 'Y')
                            {
                                SaveCleintsDataToFile(ClientsFileName, vClients);
                                return true;
                            }
                            else
                            {
                                cout << "Transaction cancelled.\n";
                                return false;
                            }
                        }
                        else
                        {
                            cout << "\nAmount exceeds the balance, you can withdraw up to: " << C.Account_Balance << endl;
                            cout << "Please enter a valid amount.\n";
                        }
                    }
                }
            }
        }
        else
        {
            cout << "\nClient with Account Number (" << AccNumber << ") is not found!\n";
            cout << "Please enter a valid account number: ";
            cin >> AccNumber;
        }

    }
}
void WithDrawTrancactionScreen()
{
    system("cls");
    cout << "\n\n====================================================\n";
    cout << "\tWithdraw Screen\n";
    cout << "====================================================\n\n";

    vector<stClientInfo> vClients;
    vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccNumber;
    AccNumber = ReadClientAccountNumber();
    WithDrawTransaction(AccNumber, vClients);
}
// Accounts Balances
void PrintClient_Balance_Record(stClientInfo Client)
{
    cout << "| " << setw(15) << left << Client.Account_Number;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Account_Balance;
}
void PrintAllClients_Balance_Data(vector<stClientInfo> vClients)
{
    double Total_Balance=0;
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stClientInfo& Client_Data : vClients)
    {
        PrintClientRecord(Client_Data);
        cout << endl;
        Total_Balance += Client_Data.Account_Balance;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\tTotal Balances = " << Total_Balance << endl;
}
void PrintAll_Balance_Clients()
{
    vector<stClientInfo> vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintAllClients_Balance_Data(vClients);
}
// Show Transactions Menue
void ShowTransactionsMenue()
{
    system("cls");
    cout << "====================================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "====================================================\n";
    cout << "\t[1] Deposit. \n";
    cout << "\t[2] Withdraw. \n";
    cout << "\t[3] Total Balances. \n";
    cout << "\t[4] Main Menue. \n";
    cout << "====================================================\n";

}

// Ask user for Transaction Mood
enTransactions AskFor_Transaction_Mood()
{
    int MoodNum;

    do
    {
        cout << "\nChoose What do you want to do -> [1 to 4]? ";
        cin >> MoodNum;

    } while (MoodNum < 1 || MoodNum>4);
    return (enTransactions)MoodNum;
}

// ChooseTransaction Mood to do
void GoToMainMenueDirectly();
void GoBackToTransactionMenue();
void DoChoosen_Transactions_Mood(enTransactions TMood)
{
    switch (TMood)
    {
    case enTransactions:: Deposit:
        system("cls");
        DepositTrancactionScreen();
        GoBackToTransactionMenue();
        break;
    case enTransactions:: Withdraw:
        system("cls");
        WithDrawTrancactionScreen();
        GoBackToTransactionMenue();
        break;
    case enTransactions:: Total_Balances:
        system("cls");
        PrintAll_Balance_Clients();
        GoBackToTransactionMenue();
        break;
    case enTransactions:: Back_Main_Menue:
        system("cls");
        GoToMainMenueDirectly();
        break;
    }
}

// Go Back to Trnsaction menu
enClientMood AskForMood();
void DoChoosenMood(enClientMood);
void ShowMainMenue();
void GoToMainMenueDirectly()
{
    ShowMainMenue();
    DoChoosenMood(AskForMood());
}
void GoBackToTransactionMenue()
{
    cout << "\n\nBress any key to go back to Transaction Menue...";
    system("pause>0");
    ShowTransactionsMenue();
    DoChoosen_Transactions_Mood(AskFor_Transaction_Mood());
}
void GoToTransactionsMenueScreen()
{
    system("cls");
    ShowTransactionsMenue();
    DoChoosen_Transactions_Mood(AskFor_Transaction_Mood());

}



// Exit Screen
void ShowEndScreen()
{
    cout << "\n\n====================================================\n";
    cout << "\t\tProgram Ends :-) \n";
    cout << "====================================================\n\n";
    system("pause>0");
}
// Go Back to main menu
    enClientMood AskForMood();
    void DoChoosenMood(enClientMood);
    void ShowMainMenue();
void GoBackToMainMenue()
{
    cout << "\n\nBress any key to go back to Mean Menue...";
    system("pause>0");
    ShowMainMenue();
    DoChoosenMood(AskForMood());

}
// Ask user for Mood
enClientMood AskForMood()
{
    int MoodNum;

    do
    {
        cout << "\nChoose What do you want to do -> [1 to 7]? ";
        cin >> MoodNum;

    } while (MoodNum<1||MoodNum>7);
    return (enClientMood)MoodNum;
}
// Choose Mood to do
void DoChoosenMood(enClientMood Mood)
{
    switch (Mood)
    {
    case enClientMood:: Show_Client_List:
        system("cls");
        PrintAllClients();
        GoBackToMainMenue();
        break;
    case enClientMood:: Add_New_Client:
        system("cls");
        AddMoreClientsScreen();
        GoBackToMainMenue();
        break;
    case enClientMood:: Delete_Client:
        system("cls");
        DeleteAccountScreen();
        GoBackToMainMenue();
        break;
    case enClientMood:: Update_Client_Info:
        system("cls");
        UpdateClientAccountScreen();
        GoBackToMainMenue();
        break;
    case enClientMood:: Find_Client:
        system("cls");
        FindAccountScreen();
        GoBackToMainMenue();
        break;
    case enClientMood::Transactions_Mood:
        system("cls");
        GoToTransactionsMenueScreen();
        break;
    case enClientMood:: Logout:
        system("cls");
        ShowEndScreen();
        break;
    }
}
// Show Start Menue
void ShowMainMenue()
{
    system("cls");
    cout << "====================================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "====================================================\n";
    cout << "\t[1] Show Client List. \n";
    cout << "\t[2] Add New Client. \n";
    cout << "\t[3] Delete Client. \n";
    cout << "\t[4] Update Client Information. \n";
    cout << "\t[5] Find Client. \n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "====================================================\n";

}
// Start Program
void StartProgram()
{
    ShowMainMenue();
    DoChoosenMood(AskForMood());
}





int main()
{
    StartProgram();
}

/*


A100#//#9654#//#Mohamed EL-Kenany#//#0505684369#//#500000.000000
A101#//#1234#//#Ahmed Khaled#//#0501234567#//#450000.000000
A102#//#5678#//#Mona Hussein#//#0502345678#//#600000.000000
A103#//#4321#//#Ali Hassan#//#0503456789#//#700000.000000
A104#//#8765#//#Sara Ahmed#//#0504567890#//#800000.000000
A105#//#6543#//#Omar Mahmoud#//#0505678901#//#900000.000000
A106#//#7890#//#Laila Youssef#//#0506789012#//#1000000.000000
A107#//#0987#//#Khaled Farid#//#0507890123#//#1100000.000000
A108#//#3456#//#Nour Ali#//#0508901234#//#1200000.000000
A109#//#5678#//#Yasmin Omar#//#0509012345#//#1300000.000000
A110#//#1234#//#Hassan Youssef#//#0500123456#//#1400000.000000
A111#//#3456#//#Rania Farid#//#0501234567#//#1500000.000000
A112#//#7890#//#Mustafa Ahmed#//#0502345678#//#1600000.000000
A113#//#6543#//#Farida Khaled#//#0503456789#//#1700000.000000
A114#//#0987#//#Youssef Mohamed#//#0504567890#//#1800000.000000
A115#//#4321#//#Zeinab Ali#//#0505678901#//#1900000.000000
A116#//#8765#//#Ayman Hassan#//#0506789012#//#2000000.000000
A117#//#5678#//#Fatima Omar#//#0507890123#//#2100000.000000
A118#//#0987#//#Mahmoud Youssef#//#0508901234#//#2200000.000000
A119#//#3456#//#Amira Khaled#//#0509012345#//#2300000.000000
A120#//#1234#//#Hani Farid#//#0500123456#//#2400000.000000
A121#//#5678#//#Salma Ahmed#//#0501234567#//#2500000.000000
A122#//#4321#//#Nader Hassan#//#0502345678#//#2600000.000000
A123#//#8765#//#Aya Youssef#//#0503456789#//#2700000.000000
A124#//#0987#//#Ola Ali#//#0504567890#//#2800000.000000
A125#//#7890#//#Mariam Omar#//#0505678901#//#2900000.000000
A126#//#6543#//#Ahmed Mahmoud#//#0506789012#//#3000000.000000
A127#//#3456#//#Nahla Farid#//#0507890123#//#3100000.000000
A128#//#1234#//#Sherif Khaled#//#0508901234#//#3200000.000000
A129#//#5678#//#Dina Youssef#//#0509012345#//#3300000.000000
A130#//#0987#//#Heba Ahmed#//#0500123456#//#3400000.000000
A131#//#4321#//#Tamer Ali#//#0501234567#//#3500000.000000
A132#//#8765#//#Huda Hassan#//#0502345678#//#3600000.000000
A133#//#7890#//#Khaled Omar#//#0503456789#//#3700000.000000
A134#//#6543#//#Sami Youssef#//#0504567890#//#3800000.000000
A135#//#0987#//#Lina Farid#//#0505678901#//#3900000.000000
A136#//#3456#//#Nabil Khaled#//#0506789012#//#4000000.000000
A137#//#1234#//#Manal Ahmed#//#0507890123#//#4100000.000000
A138#//#5678#//#Alaa Hassan#//#0508901234#//#4200000.000000
A139#//#4321#//#Sahar Ali#//#0509012345#//#4300000.000000
A140#//#8765#//#Maher Youssef#//#0500123456#//#4400000.000000
A141#//#7890#//#Farah Khaled#//#0501234567#//#4500000.000000
A142#//#6543#//#Waleed Omar#//#0502345678#//#4600000.000000
A143#//#0987#//#Nisreen Youssef#//#0503456789#//#4700000.000000
A144#//#3456#//#Hisham Ahmed#//#0504567890#//#4800000.000000
A145#//#1234#//#Aisha Ali#//#0505678901#//#4900000.000000
A146#//#5678#//#Rami Hassan#//#0506789012#//#5000000.000000
A147#//#4321#//#Amal Youssef#//#0507890123#//#5100000.000000
A148#//#8765#//#Basem Khaled#//#0508901234#//#5200000.000000
A149#//#0987#//#Maha Omar#//#0509012345#//#5300000.000000
A150#//#7890#//#Sameh Youssef#//#0500123456#//#5400000.000000
A151#//#6543#//#Nadia Ahmed#//#0501234567#//#5500000.000000
A152#//#3456#//#Hussein Ali#//#0502345678#//#5600000.000000
A153#//#1234#//#Samiha Hassan#//#0503456789#//#5700000.000000
A154#//#5678#//#Adel Youssef#//#0504567890#//#5800000.000000
A155#//#4321#//#Noha Khaled#//#0505678901#//#5900000.000000
A156#//#8765#//#Tarek Omar#//#0506789012#//#6000000.000000
A157#//#0987#//#Lamis Youssef#//#0507890123#//#6100000.000000
A158#//#3456#//#Hala Ahmed#//#0508901234#//#6200000.000000
A159#//#1234#//#Rashid Ali#//#0509012345#//#6300000.000000
A160#//#5678#//#Nada Hassan#//#0500123456#//#6400000.000000
A161#//#4321#//#Karim Youssef#//#0501234567#//#6500000.000000
A162#//#8765#//#Yasmeen Khaled#//#0502345678#//#6600000.000000
A163#//#0987#//#Ahmed Omar#//#0503456789#//#6700000.000000
A164#//#7890#//#Lina Youssef#//#0504567890#//#6800000.000000
A165#//#6543#//#Salem Ahmed#//#0505678901#//#6900000.000000
A166#//#3456#//#Shereen Ali#//#0506789012#//#7000000.000000
A167#//#1234#//#Mohsen Hassan#//#0507890123#//#7100000.000000
A168#//#5678#//#Walaa Youssef#//#0508901234#//#7200000.000000
A169#//#4321#//#Mamdouh Khaled#//#0509012345#//#7300000.000000
A170#//#8765#//#Asmaa Omar#//#0500123456#//#7400000.000000
A171#//#0987#//#Sherif Youssef#//#0501234567#//#7500000.000000
A172#//#7890#//#Ghada Ahmed#//#0502345678#//#7600000.000000
A173#//#6543#//#Salah Ali#//#0503456789#//#7700000.000000
A174#//#3456#//#Rami Hassan#//#0504567890#//#7800000.000000
A175#//#1234#//#Nahla Youssef#//#0505678901#//#7900000.000000


*/