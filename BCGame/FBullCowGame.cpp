#include "FBullCowGame.h"
#include <map>
#define TMap std::map
//git test

FBullCowGame::FBullCowGame() { Reset(); }


int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bWonLos; }
std::string FBullCowGame::GetHiddinWord() const { return MyHiddenWord; }

int FBullCowGame::GetMaxTry() const 
{ 
	TMap<int, int> WordLMTries{ {3,2}, {4,3}, {5,4}, {6,5} };
	return WordLMTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const std::string HIDDEN_WORD = "plane";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

//check for a VALID gues.
FBullCowCount FBullCowGame::SubmitValidGuess(std::string Guess)
{
	FBullCowCount BullCowCount;
	int HiddenWordLength = MyHiddenWord.length();
	for (int HWC = 0; HWC < HiddenWordLength; HWC++)
	{
		for (int GChar = 0; GChar < HiddenWordLength; GChar++)
		{	//compare
			if (Guess[GChar] == MyHiddenWord[HWC])
			{
				if (HWC == GChar)
					BullCowCount.Bulls++; 
				else
					BullCowCount.Cows++;
			}
		}
	}

	if (BullCowCount.Bulls == HiddenWordLength)
		bWonLos = true;
	else
		bWonLos = false;

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(std::string x) const
{
	if (x.length() <= 1)
		return true;

	//setup map
	TMap<char, bool> LetterSeen;
	for (auto letter : x)
	{
		letter = tolower(letter);
		if (LetterSeen[letter])
			return false;
		else
			LetterSeen[letter] = true;
	}

	return true;
}

bool FBullCowGame::IsLowerCase(std::string x) const
{
	for (auto letter : x)
	{
		if(!islower(letter))
			return false;
	}
	return true;
}

EWordStats FBullCowGame::ChechGuessValidity(std::string x) const
{
	if (!IsIsogram(x))//not isogram
		return EWordStats::Not_Isogram;
	else if (!IsLowerCase(x))//CapsLock ON
		return EWordStats::N_LCase;
	else if (x.length() != GetHiddenWordLength())//wrong size
		return EWordStats::To_Wrong;
	else//ok
		return EWordStats::OK;
}
