#pragma once 
#include <std_lib_facilities.h>
#include "FBullCowGame.h"

//prototypes
void Intro_Game();
void Login_Entrace();
bool Ask_PlayAgain();
string User_Login(string);
string Check_Valid(string);

//estance
FBullCowGame BCGame;

int main()
{
	bool PlayAgain_Count = false;
	do
	{
		system("cls");
		Intro_Game();
		Login_Entrace();
		PlayAgain_Count = Ask_PlayAgain();
	} while (PlayAgain_Count);
	return 0;
}

void Intro_Game()//Intro Game
{
	int RWordL = BCGame.GetHiddenWordLength();
	cout << "Welcome to Bulls & Cow\n";
	cout << "          }   {         ___ " << endl;
	cout << "          (o o)        (o o) " << endl;
	cout << "   /-------\\ /          \\ /--------\\ " <<endl;
	cout << "  / | BULL |O            O|   COW  |\\ " << endl;
	cout << " *  |-,--- |              |----,,--| * " << endl;
	cout << "    ^      ^              ^      ^ " << endl;
	cout << "Can you guess the " << RWordL << " isogram I'm think of?\n\n";
}

void Login_Entrace()//entrace of data process fase
{
	constexpr int WORD_LENGHT = 30;

	int currentplay = 1;
	int count1 = 0;
	int MaxTry = BCGame.GetMaxTry();
	int CurrentTry = BCGame.GetCurrentTry();
	string Hiden = BCGame.GetHiddinWord();
	string Guess[WORD_LENGHT];

	count1++;
	if (count1 > 1)
		cout << "You say yes =)\n";

	cout << "How Many Player?:\t";
	int HMPlay = 0;
	cin >> HMPlay;

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//begin process fase
	for (int i = 0; i < HMPlay; i++)
	{
		CurrentTry = 1;
		for (int i = 0; i < MaxTry; i++) 
		{
			cout << "Life{" << CurrentTry << "/" << MaxTry << "}";
			cout << "Enter with Guess " << currentplay << ": ";
			Guess[i] = User_Login(Guess[i]);
			Guess[i] = Check_Valid(Guess[i]);
			system("cls");
			FBullCowCount BCCount = BCGame.SubmitValidGuess(Guess[i]);
			cout << "Guess " << currentplay << "  try is: " << Guess[i] << "\n";
			cout << "Bulls= " << BCCount.Bulls << "\t";
			cout << "Cows= " << BCCount.Cows << "\n";

			if (BCGame.IsGameWon()) 
			{
				cout << "You Won!!\n\n";
				break;
			}else
				cout << "You Lose =/\n\n";
			CurrentTry++;
		}
		currentplay++;
	}//end process fase
}

string Check_Valid(string x)
{
	EWordStats Status = EWordStats::Invalid_Stats;
	do
	{
		EWordStats Status = BCGame.ChechGuessValidity(x);
		switch (Status)
		{
		case EWordStats::Not_Isogram:
			cout << "Please don't write word has repeated letters.\n";
			x = User_Login(x);
			break;

		case EWordStats::N_LCase:
			cout << "Please don't use upper case. Verify your Caps Lock.\n";
			x = User_Login(x);
			break;

		case EWordStats::To_Wrong:
			cout << "Please enter " << BCGame.GetHiddenWordLength() << " letters.\n";
			x = User_Login(x);
			break;

		default:
			return x;//assume is OK
			break;
		}
	} while (Status != EWordStats::OK);

	return NULL;
}

bool Ask_PlayAgain()
{
	string resp;

	cout << "Do wanna play again? (y/n)\n";
	cin >> resp;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (resp[0] == 'Y' || resp[0] == 'y')
		return true;

	if (resp[0] == 'N' || resp[0] == 'n')
	{
		system("cls");
		cout << "You say no. =(\n";
		return false;
	}else{
		system("cls");
		cout << "Wrong awnser please try again\n";
		return Ask_PlayAgain();
	}

	return NULL;
}

//Read user login name
string User_Login(string x)
{
	getline(cin, x);
	return x;
}