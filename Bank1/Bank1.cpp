// Bank1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

// nom du fichier contenant les données des clients
string ClientsFileName = "ClientsData.text";

// options du menu principal
enum eMainMenuOptions {eClientsList = 1, eAddNewClient = 2, eDeleteClient = 3,
                        eUpdateClient = 4, eFindClient = 5, eExit = 6};


void MainMenuScreen();

// fonction pour retourner au menu principal
void GoBackToMainMenu()
{
    cout << "\npress any key to go back to main menu";
    system("pause>0");
    MainMenuScreen(); 
}

// Structure pour stocker les données des clients
struct stClientData
{
    int AccountNumber = 0;
    int PinCode = 0;
    string Name;
    string Phone;
    float AccountBalance = 0;
    bool MarkForDelete = false;
    bool MarkForUpdate = false;
};

// Fonction pour lire une chaîne de caractères depuis l'entrée standard
string ReadString(string Message)
{
    string Words;
    cout << Message;
    getline(cin, Words);
    return Words;
}

// Fonction pour lire un caractère depuis l'entrée standard
char ReadChar(string Message)
{
    char C;
    cout << Message;
    cin >> C;
    return C;
}

// Fonction pour lire un nombre entier depuis l'entrée standard
int ReadNumber(string Message)
{
    int Number;
    cout << Message << endl;
    cin >> Number;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "invalid Number please enter valid Number ?" << endl;
        cin >> Number;
    }
    return Number;
}

// Fonction pour lire un nombre flottant depuis l'entrée standard
float ReadFloatNumber(string Message)
{
    float Number;
    cout << Message << endl;
    cin >> Number;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "invalid Number please enter valid Number ?" << endl;
        cin >> Number;
    }
    return Number;
}

// Fonction pour lire les données d'un fichier et les stocker dans un vecteur
void SaveFileToVector(string FileName, vector<string>& vFileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            vFileName.push_back(Line);
        }
        MyFile.close();
    }
}

// Fonction pour écrire les données d'un vecteur dans un fichier
void SaveVectorToFile(vector<string> vFileName, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (const string& Line : vFileName)
        {
            if (Line != "") {
                MyFile << Line << endl;
            }
        }
        MyFile.close();
    }
}

// Fonction pour afficher chaque mot d'une chaîne de caractères
void Print_Each_Word(string Words, string Delim)
{
    short pos = 0;
    string Temp;
    while ((pos = Words.find(Delim)) != Words.npos)
    {
        Temp = Words.substr(0, pos);
        if (Temp != "")
        {
            cout << Temp << endl;
        }
        Words.erase(0, pos + Delim.length());
    }
    if (Words != "")
    {
        cout << Words << endl;
    }
}

// Fonction pour diviser une chaîne de caractères en un vecteur de sous-chaînes
vector<string> SplitString(string Words, string Delim)
{
    vector<string> vToken;
    short pos = 0;
    string Token;
    while ((pos = Words.find(Delim)) != Words.npos)
    {
        Token = Words.substr(0, pos);
        if (Token != "")
        {
            vToken.push_back(Token);
        }
        Words.erase(0, pos + Delim.length());
    }
    if (Words != "")
    {
        vToken.push_back(Words);
    }
    return vToken;
}

// Fonction pour joindre les éléments d'un vecteur de chaînes de caractères en une seule chaîne
string JoinString(vector<string> vString, string Delim)
{
    string S;
    for (string& s : vString)
    {
        S += s + Delim;
    }
    return S.substr(0, S.length() - Delim.length());
}

// Fonction pour joindre les éléments d'un tableau de chaînes de caractères en une seule chaîne
string JoinString(string Arr[], short ArrLength, string Delim)
{
    string S;
    for (short i = 0; i < ArrLength; i++)
    {
        S += Arr[i] + Delim;
    }
    return S.substr(0, S.length() - Delim.length());
}

// Fonction pour inverser l'ordre des mots dans une chaîne de caractères
string ReverseString(string Words)
{
    string ReverseWords = "";
    vector <string> vString;
    vString = SplitString(Words, " ");
    vector<string>::iterator iter = vString.end();
    while (iter != vString.begin())
    {
        iter--;
        ReverseWords += *iter + " ";
    }
    return ReverseWords.substr(0, ReverseWords.length() - 1);
}

// Fonction pour remplacer des mots dans une chaîne de caractères en utilisant des fonctions intégrées
string ReplaceWordsInStringUsingInBuilt(string Words, string Replaced, string Replacement)
{

    short pos = Words.find(Replaced);
    while (pos != Words.npos)
    {
        Words = Words.replace(pos, Replaced.length(), Replacement);
        pos = Words.find(Replaced);
    }
    return Words;
}

// Fonction pour supprimer toute la ponctuation d'une chaîne de caractères
string RemoveAllPunctuation(string Words)
{
    string S;
    for (short i = 0; i < Words.length(); i++)
    {
        if (!ispunct(Words[i]))
        {
            S += Words[i];
        }
    }
    return S;

    /*for (char& word : Words)
    {
        if (ispunct(word))
            word = NULL;
    }
    return Words;*/
}

// Fonction pour lire les données d'un client depuis l'entrée standard
vector <string> ReadClientData(stClientData& ClientData, int AccountNumber)
{
    vector <string> vClientData;
    
    ClientData.AccountNumber = AccountNumber;
    vClientData.push_back(to_string(ClientData.AccountNumber));

    ClientData.PinCode = ReadNumber("enter pin code: ");
    vClientData.push_back(to_string(ClientData.PinCode));

    cin.ignore(1, '\n');

    ClientData.Name = ReadString("enter name: ");
    vClientData.push_back(ClientData.Name);

    ClientData.Phone = ReadString("enter phone: ");
    vClientData.push_back(ClientData.Phone);

    ClientData.AccountBalance = ReadFloatNumber("enter account balance: ");
    vClientData.push_back(to_string(ClientData.AccountBalance));

    return vClientData;
}

// Fonction pour convertir une ligne de données en un enregistrement de client
stClientData ConvertLineDataToRecord(string LineData, string Delim)
{
    stClientData ClientData;
    vector<string> vLineData;

    vLineData = SplitString(LineData, Delim);
    ClientData.AccountNumber = stoi(vLineData[0]);
    ClientData.PinCode = stoi(vLineData[1]);
    ClientData.Name = vLineData[2];
    ClientData.Phone = vLineData[3];
    ClientData.AccountBalance = stof(vLineData[4]);

    return ClientData;
}

// Fonction pour convertir un enregistrement de client en une ligne de données
string ConvertRecordToLineData(stClientData ClientData, string Delim)
{
    string LineData;

    LineData += to_string(ClientData.AccountNumber) + Delim;
    LineData += to_string(ClientData.PinCode) + Delim;
    LineData += ClientData.Name + Delim;
    LineData += ClientData.Phone + Delim;
    LineData += to_string(ClientData.AccountBalance);

    return LineData;
}

// Fonction pour afficher les données d'un client
void PrintClientRecord(stClientData ClientData)
{
    
    cout << "Clients Details:\n";
    cout << "----------------------------\n";
    cout << "account number\t: " << ClientData.AccountNumber << "\n";
    cout << "pin code\t: " << ClientData.PinCode << "\n";
    cout << "name\t\t: " << ClientData.Name << "\n";
    cout << "phone\t\t: " << ClientData.Phone << "\n";
    cout << "account balance\t: " << ClientData.AccountBalance << "\n";
    cout << "----------------------------\n";
}

// Fonction pour ajouter une ligne de données dans un fichier
void AddDataLineToFile(string FileName, string LineData)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << LineData << "\n";
        MyFile.close();
    }
}

// Fonction pour ajouter un nouveau client
void AddNewClient(int AccountNumber)
{
    stClientData ClientData;
    vector <string> vClientData;

    vClientData = ReadClientData(ClientData, AccountNumber);
    AddDataLineToFile("ClientsData.text", JoinString(vClientData, "#//#"));

}

// Fonction pour sauvegarder les données des clients dans un fichier
void SaveClientsDataInFile(int AccountNumber)
{
    char AddClient;
    do
    {
        AddNewClient(AccountNumber);

        cout << "client added successfully, do u want to add more clients(y/n)? ";
        cin >> AddClient;
    } while (toupper(AddClient) == 'Y');
}

// Fonction pour afficher les données des clients depuis un fichier
void PrintClientsDataFromFile(vector<string> vClientData)
{
    stClientData ClientData;
    cout << "                                         Client List (" << vClientData.size() << ") Client(s)." << endl;
    cout << endl << "--------------------------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(22) << "| Account Number";
    cout << left << setw(22) << "| Pin Code";
    cout << left << setw(22) << "| Client Name";
    cout << left << setw(22) << "| Phone";
    cout << left << setw(22) << "| Balance";
    cout << endl << "--------------------------------------------------------------------------------------------------------------" << endl;
    for (string& Line : vClientData)
    {
        ClientData = ConvertLineDataToRecord(Line, "#//#");
        cout << endl;
        cout << "| " << left << setw(20) << ClientData.AccountNumber;
        cout << "| " << left << setw(20) << ClientData.PinCode;
        cout << "| " << left << setw(20) << ClientData.Name;
        cout << "| " << left << setw(20) << ClientData.Phone;
        cout << "| " << left << setw(20) << ClientData.AccountBalance;
    }
    cout << endl << "--------------------------------------------------------------------------------------------------------------" << endl;
    
}

// Fonction pour sauvegarder les données des clients dans un vecteur
vector<stClientData> SaveClientsDataToVector(string FileName)
{
    vector<stClientData> vClientsData;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {

            vClientsData.push_back(ConvertLineDataToRecord(Line, "#//#"));
        }
        MyFile.close();
    }
    return vClientsData;
}

// Fonction pour trouver un client par son numéro de compte
bool FindClientByAccountNumber(int AccountNumber, stClientData& Client, string FileName)
{
    
    vector<stClientData> vClientsData;
    vClientsData = SaveClientsDataToVector(FileName);
    for (stClientData& C : vClientsData)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return 1;
        }
    }
    return 0;
}

// Fonction pour supprimer un client
void DeleteClientByAccountNumber(string FileName, int AccountNumber)
{
    vector <string> vFileName;
    stClientData ClientData;
    SaveFileToVector(FileName, vFileName);

    for (string& Line : vFileName)
    {
        ClientData = ConvertLineDataToRecord(Line, "#//#");
        if (ClientData.AccountNumber == AccountNumber)
        {
            Line = "";
        }
    }

    SaveVectorToFile(vFileName, FileName);
}

// Fonction pour mettre à jour les données d'un client
void MarkClientForDelete(int AccountNumber, vector<stClientData>& vClientsData)
{
    for (stClientData& C : vClientsData)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;

        }
    }

}

// Fonction pour marquer un client pour mise à jour
void MarkClientForUpdate(int AccountNumber, vector<stClientData>& vClientsData)
{
    for (stClientData& C : vClientsData)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForUpdate = true;

        }
    }

}

// Fonction pour sauvegarder les données des clients dans un fichier
void SaveClientsDataToFile(string FileName, vector<stClientData> vClientsData)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;
    if (MyFile.is_open())
    {
        for (stClientData C : vClientsData)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLineData(C, "#//#");
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
}

// Fonction pour mettre à jour les données des clients dans un fichier
void UpdateClientsDataToFile(string FileName, vector<stClientData>& vClientsData)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;
    if (MyFile.is_open())
    {
        for (stClientData& C : vClientsData)
        {
            if (C.MarkForUpdate == false)
            {
                DataLine = ConvertRecordToLineData(C, "#//#");
                MyFile << DataLine << endl;
            }
            if (C.MarkForUpdate == true)
            {
                C.PinCode = ReadNumber("enter pin code: ");
                cin.ignore(1, '\n');
                C.Phone = ReadString("enter phone: ");
                C.AccountBalance = ReadFloatNumber("enter account balance: ");
                DataLine = ConvertRecordToLineData(C, "#//#");
                MyFile << DataLine << endl;
            }

        }
        MyFile.close();
    }
}

//Fonction pour executer la suppression un client
void Delete_Client_By_Account_Number(string FileName, vector<stClientData>& vClientsData)
{
    char DeleteClient;
    stClientData ClientData;
    cout << "----------------------------\n";
    cout << "   Delete Client Screen   \n";
    cout << "----------------------------\n";
    int AccountNumber = ReadNumber("enter account number");

    if (FindClientByAccountNumber(AccountNumber, ClientData, FileName))
    {
        PrintClientRecord(ClientData);
        cout << "\nr u sure u want to delete this client(y/n)?  ";
        cin >> DeleteClient;
        if (toupper(DeleteClient) == 'Y')
        {
            MarkClientForDelete(AccountNumber, vClientsData);
            SaveClientsDataToFile(FileName, vClientsData);
            vClientsData = SaveClientsDataToVector(FileName);

            cout << "\nclient deleted successfully!\n";
        }

    }
    else
    {
        cout << "client with account number " << AccountNumber << " not found";

    }
}

//Fonction pour executer la mise à jour d'un client
void UpdateClientByAccountNumber(string FileName, vector<stClientData>& vClientsData)
{
    char Update;
    stClientData ClientData;
    cout << "--------------------------------\n";
    cout << "   Update Client Info Screen   \n";
    cout << "--------------------------------\n";
    int AccountNumber = ReadNumber("enter account number");

    if (FindClientByAccountNumber(AccountNumber, ClientData, FileName))
    {
        PrintClientRecord(ClientData);
        cout << "\nr u sure u want to update this client(y/n)?  ";
        cin >> Update;
        if (toupper(Update) == 'Y')
        {
            MarkClientForUpdate(AccountNumber, vClientsData);
            UpdateClientsDataToFile(FileName, vClientsData);

            cout << "\nclient updated successfully!\n";
        }

    }
    else
    {
        cout << "client with account number " << AccountNumber << " not found";

    }
}

//Fonction pour executer la recherche d'un client
void FindClientScreen(int AccountNumber, stClientData ClientData)
{
    cout << "----------------------------\n";
    cout << "   Find Client Screen   \n";
    cout << "----------------------------\n";
    AccountNumber = ReadNumber("enter account number");
    if (!FindClientByAccountNumber(AccountNumber, ClientData, "ClientsData.text"))
    {
        cout << "client with [" << AccountNumber << "] is not found ";
    }
    else
        PrintClientRecord(ClientData);
}

//Fonction pour afficher l'écran de fin du programme
void ProgramEndsScreen()
{
    cout << "----------------------------\n";
    cout << "   Program Ends :-)   \n";
    cout << "----------------------------\n";
}

//Fonction pour ajouter un nouveau client
void AddNewClientScreen(int AccountNumber, stClientData ClientData, vector<stClientData> vClientsData)
{
    cout << "----------------------------\n";
    cout << "   Add New Clients Screen   \n";
    cout << "----------------------------\n";
    cout << "Adding new clients:\n\n";
    do
    {
        AccountNumber = ReadNumber("enter account number: ");
        if (FindClientByAccountNumber(AccountNumber, ClientData, "ClientsData.text"))
        {
            cout << "client with [" << AccountNumber << "] already exists, ";
        }
    } while (FindClientByAccountNumber(AccountNumber, ClientData, "ClientsData.text"));
    SaveClientsDataInFile(AccountNumber);
}

//Fonction pour executer les options du menu principal
void PerformMainMenu(eMainMenuOptions MainMenuOption)
{
    int AccountNumber = 0;
    stClientData ClientData;
    vector<string> vClientData;
    vector<stClientData> vClientsData = SaveClientsDataToVector("ClientsData.text");
    SaveFileToVector("ClientsData.text", vClientData);

    
    switch (MainMenuOption)
    {
    case eClientsList:
        system("cls");
        PrintClientsDataFromFile(vClientData);
        GoBackToMainMenu();
        break;
    case eAddNewClient:
        system("cls");
        AddNewClientScreen(AccountNumber, ClientData, vClientsData);
        GoBackToMainMenu();
        break;
    case eDeleteClient:
        system("cls");
        Delete_Client_By_Account_Number("ClientsData.text", vClientsData);
        GoBackToMainMenu();
        break;
    case eUpdateClient:
        system("cls");
        UpdateClientByAccountNumber("ClientsData.text", vClientsData);
        GoBackToMainMenu();
        break;
    case eFindClient:
        system("cls");
        FindClientScreen(AccountNumber, ClientData);
        GoBackToMainMenu();
        break;
    case eExit:
        system("cls");
        ProgramEndsScreen();
        break;
    }
}

//Fonction pour afficher l'écran du menu principal
void MainMenuScreen()
{
    system("cls");
    cout << "======================================\n";
    cout << "        Main Menu Screen\n";
    cout << "======================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "======================================\n";
    
    PerformMainMenu((eMainMenuOptions)ReadNumber("Choose what do you want to do? [1 to 6]? "));
    
}



int main()
{
   
    MainMenuScreen();

    return 0;
}















// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
