#pragma once
#include <string>

struct FBullCowCount
{
	int Bulls = 0;
	int Cows = 0;
};

enum class EWordStats
{
	Invalid_Stats,//make actual error
	OK,
	Not_Isogram,
	To_Wrong,
	N_LCase
};

class FBullCowGame
{
public:
	FBullCowGame();//Construct
	//meths
	void Reset();
	int GetMaxTry() const;
	int GetCurrentTry() const;
	int GetHiddenWordLength() const;
	bool IsGameWon() const;
	std::string GetHiddinWord() const;
	EWordStats ChechGuessValidity(std::string) const;
	FBullCowCount SubmitValidGuess(std::string);//count bulls/cows points


private://initialization on construt
	int MyCurrentTry;
	std::string MyHiddenWord;
	bool bWonLos;

	bool IsIsogram(std::string) const;
	bool IsLowerCase(std::string) const;
};
