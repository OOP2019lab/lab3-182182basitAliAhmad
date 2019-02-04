#include<iostream>
#include<fstream>
#include "gitHubUser.h"

void readDataFromFile(gitHubUser* &users, int &size, string filepath) // reading data from file
{
	 ifstream fin;
	 fin.open(filepath);
	 if(fin) // check if file is opened
	 {
		 fin >> size;
		 users = new gitHubUser[size];
		 for (int i = 0; i < size; i++)
		 {
			 fin >> users[i].firstName;
			 fin >> users[i].userName;
			 fin >> users[i].email;
			 fin >> users[i].folderCount;
			 users[i].gitHubFolders = new string[users[i].folderCount];
			 fin.ignore();
			 for (int j = 0; j < users[i].folderCount; j++)
				 getline(fin,users[i].gitHubFolders[j]);

			 // initializing the pointers to nullptr to avoid dangling pointing
			 users[i].instituteName = nullptr;
			 users[i].qualificationLevel = nullptr;
		 }
		 fin.close();
	 }
	 else
		 cout << "File not found!" << endl;
}

int searchUser(const gitHubUser* arr, const int size, const string userName) // searches the user's record based on its username and returns its index.
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i].userName == userName)
			return i;
	}
	cout << "User not found!" << endl;
	return -1;
}

void setEduBckGrnd(gitHubUser &user) // assign heap memory against pointersfor optional fields and take input from user.
{
	user.instituteName = new string;
	cout << user.firstName << " !Your Institute Name ----> ";
	cin >> *user.instituteName; // getline does not operate on heap memory

	user.qualificationLevel = new string;
	cout << user.firstName << " !Your Qualification ----> ";
	cin >> *user.qualificationLevel;
}

void print(const gitHubUser var) // printing indivisual object
{
		cout << "Name :     " << var.firstName << endl;
		cout << "Username : " << var.userName << endl;
		cout << "Email :    " << var.email << endl;
		cout << "No. of folders : " << var.folderCount << endl;
		for (int j = 0; j < var.folderCount; j++)
			cout << "Folder # " << j + 1 << " " << var.gitHubFolders[j] << endl;
		if (var.instituteName != nullptr) // if pointer is null, means the record does not exists
			cout << "Institute Name :  " << *var.instituteName << endl;
		if (var.qualificationLevel != nullptr) // as above
			cout << "Qualification : " << *var.qualificationLevel << endl;
		cout << endl;
}

void remove(gitHubUser &var) // deallocates the memory against the both string pointers
{
	cout << "Are you sure to remove your educational information (Y/N)? ";
	char ch = '\0';
	cin >> ch;
	if (ch == 'y' || ch == 'Y') // confirmation
	{
		delete var.instituteName;
		delete var.qualificationLevel;
		var.instituteName = nullptr;
		var.qualificationLevel = nullptr;
	}
	else
		cout << "Aborted! Record not removed." << endl;
}

void printMenu()
{
	cout << "0 - Exit the program" << endl;
	cout << "1 - Set education background information" << endl;
	cout << "2 - Print details of user" << endl;
	cout << "3 - Remove educational details" << endl;
	cout << "Enter your choice ----> ";
}

void backup(const gitHubUser *originalArry, gitHubUser* &backupArry, const int userCount)
{
	backupArry = new gitHubUser[userCount];
	for (int i = 0; i < userCount; i++)
	{
		backupArry[i] = originalArry[i]; // variable data will deep copy and pointers will have shallow copy.
		backupArry[i].gitHubFolders = new string; // new memory for deep copy - 1
		for (int j = 0; j < backupArry[i].folderCount; i++)
			backupArry[i].gitHubFolders[j] = originalArry[i].gitHubFolders[j]; //deep copy - 2

		if (backupArry[i].instituteName != nullptr)
		{
			backupArry[i].instituteName = new string;  // same - 1
			*backupArry[i].instituteName = *originalArry[i].instituteName; // same - 2
		}

		if (backupArry[i].qualificationLevel != nullptr)
		{
			backupArry[i].qualificationLevel = new string; // same - 1
			*backupArry[i].qualificationLevel = *originalArry[i].qualificationLevel; // same - 2
		}
	}
	cout << "Backup successful" << endl;
}

void deallocate(gitHubUser* &var, const int size)
{
	for (int i = 0; i < size; i++)
	{
		delete[]var[i].gitHubFolders; // deleting folder names
		var[i].gitHubFolders = nullptr;

		delete var[i].instituteName; // deleting optional fields
		delete var[i].qualificationLevel; // as above
		var[i].instituteName = nullptr;
		var[i].qualificationLevel = nullptr;
	}

	delete[]var; // deleting whole record
	var = nullptr;
}

void main()
{
	gitHubUser* arr = nullptr;
	gitHubUser* bckUp = nullptr;
	int size = 0, selection = 0, index = 0;
	string userName;
	readDataFromFile(arr,size,"input.txt");
	cout << "File read successfully. Do you wany to create a backup for this data? (Y/N)  ";
	char choice = '\0';
	cin >> choice;
	if(choice == 'y' || choice == 'Y')
		backup(arr,bckUp,size);

	do
	{
		do
		{
			cout << "Enter username to search user ----> ";
			cin >> userName;
			index = searchUser(arr,size,userName);
			
		} while (index == -1);
		
		printMenu();
		cin >> selection;

		switch (selection)
		{
			case 0:
				cout << "Program terminated!!" << endl;
				break;
			case 1:
				if (arr[index].instituteName == nullptr && arr[index].qualificationLevel == nullptr)
					setEduBckGrnd(arr[index]);
				else
					cout << "Data already existed!" << endl;
				break;

			case 2:
				print(arr[index]);
				break;

			case 3:
				if (arr[index].instituteName == nullptr && arr[index].qualificationLevel == nullptr)
					remove(arr[index]);
				else
					cout << "Data already existed!" << endl;
				break;

			default:
				cout << "Invalid selection! try again." << endl;
				break;
		}
		
	} while (selection != 0);

	deallocate(arr,size);
	if(bckUp != nullptr) // check if backup was created or not
		deallocate(bckUp,size);
}