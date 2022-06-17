// wordleCLI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<conio.h>
#include<Windows.h>
#include <iostream>
#include <string>
#include <time.h>
#include <sstream>

using namespace std;
using std::cout;
using std::cin;

bool gameLoop = true;
int wordLegnth = 8;
int guessAmount = 6;

string MakeGuess();

string MyGuess = " ";
string awnser = "AAAAA";
string dificulty = "";
string awnsersFive[21] = {
	"HUMOR",
	"FRAME",
	"ELDER",
	"SKILL",
	"ALOFT",
	"SHARD",
	"MOIST",
	"DRINK",
	"THOSE",
	"TIGER",
	"LIGHT",
	"COULD",
	"PERKY",
	"MOUNT",
	"WHACK",
	"SUGAR",
	"SOLAR",
	"PRICK",
	"ROBOT",
	"POINT",
	"PROXY",
};
string awnsersEight[21] = {
	"SLAPPING",
	"CREDITED",
	"ABSTRACT",
	"AIRCRAFT",
	"ANYWHERE",
	"PLEASANT",
	"POWERFUL",
	"SOMEBODY",
	"SPECIFIC",
	"SOFTWARE",
	"THIRTEEN",
	"WORKSHOP",
	"INFORMED",
	"GENEROUS",
	"GOODWILL",
	"GRAPHICS",
	"HARDWARE",
	"INCIDENT",
	"DOMINANT",
	"CREATIVE",
	"CONTRACT",
};
string awnsersTwelve[21] = {
	"BACKBREAKING",
	"ACADEMICALLY",
	"ABSURDNESSES",
	"ACCELERATION",
	"AVAILABILITY",
	"BROTHERHOODS",
	"UNCATALOGUED",
	"TRANSLATIONS",
	"TRANSPARENCY",
	"THUNDERSTORM",
	"SURVEILLANCE",
	"TEMPERATURES",
	"SUPPLEMENTAL",
	"SPIRITUALITY",
	"SLAUGHTERING",
	"SKATEBOARDER",
	"SKELETONISED",
	"RELATIONSHIP",
	"PREASSEMBLED",
	"OVERTHINKING",
	"BACKTRACKING",
};

string GetRandAwnser(int a) {
	int i = rand() % 21;
	i = rand() % 21;
	switch (a)
	{
		case(1):
		default:
			wordLegnth = 5;
			guessAmount = 6;
			dificulty = "Normal";
			return awnsersFive[i];
		case(2):
			wordLegnth = 8;
			guessAmount = 6;
			dificulty = "Moderate";
			return awnsersEight[i];
		case(3):
			wordLegnth = 12;
			guessAmount = 10;
			dificulty = "Backbreaking";
			return awnsersTwelve[i];
	}
	
}

string errorMSG = "";
struct letterColorStruct {
	char letter = ' ';
	char color = 'N';
};
struct guessStruct
{
	string guess;
	string color;
	letterColorStruct* lettercolors;
};
guessStruct* guesses;
guessStruct Compare(string guess);
void PrintGuessStruct(guessStruct g);
int guessPos = 0;
string usedletters = "";
string lastMSG = "";
HANDLE myColors;
void DrawUI();
int AskForDificulty() { 
	string inputstr = "0";
	int num = 0;
	cout << "Wordle\n";
	cout << "Pick A dificulty:" << endl;
	SetConsoleTextAttribute(myColors, 15 | BACKGROUND_GREEN);

	cout << "\t 1) Normal (5 letters)" << endl;
	SetConsoleTextAttribute(myColors, 15 | BACKGROUND_GREEN | BACKGROUND_RED);

	cout << "\t 2) Moderate (8 letters)" << endl;
	SetConsoleTextAttribute(myColors, 15 | BACKGROUND_RED);

	cout << "\t 3) Backbreaking (12 letters)" << endl;

	SetConsoleTextAttribute(myColors, 15);

	getline(cin, inputstr);


	while (inputstr.find_first_not_of("123") != -1 || inputstr.empty())
	{
		cout << "Invalid awnser - Try again" << endl;

		getline(cin, inputstr);
	}

	stringstream(inputstr) >> num;
	return num;
} 
int AskForContinue() {
	string inputstr = "0";
	int num = 0;

	cout << "Continue?" << endl;
	SetConsoleTextAttribute(myColors, 15 | BACKGROUND_GREEN);

	cout << "\t 1) Yes" << endl;
	SetConsoleTextAttribute(myColors, 15 | BACKGROUND_GREEN | BACKGROUND_RED);

	cout << "\t 2) No" << endl;
	SetConsoleTextAttribute(myColors, 15 | BACKGROUND_RED);

	SetConsoleTextAttribute(myColors, 15);

	getline(cin, inputstr);

	while (inputstr.find_first_not_of("12") != -1 || inputstr.empty())
	{
		cout << "Invalid awnser - Try again" << endl;

		getline(cin, inputstr);
	}

	stringstream(inputstr) >> num;
	return num;
}
bool doContinue = true;
int main()
{
	while (doContinue)
	{
		gameLoop = true;
		MyGuess = " ";
		awnser = "AAAAA";
		dificulty = "";
		myColors = GetStdHandle(STD_OUTPUT_HANDLE);
		srand(time(NULL));
		int p = AskForDificulty();
		awnser = GetRandAwnser(p);
		usedletters = "";
		lastMSG = "";
		errorMSG = "";
		
		guessPos = 0;
		SetConsoleTextAttribute(myColors, 15);
		guesses = new guessStruct[guessAmount];
		system("cls");
		while (gameLoop) {
		
			DrawUI();


			SetConsoleTextAttribute(myColors, 15 | BACKGROUND_GREEN | BACKGROUND_RED);
			cout << "A";
			SetConsoleTextAttribute(myColors, 15);
			cout << " The word has that letter" << endl;
			SetConsoleTextAttribute(myColors, 15 | BACKGROUND_GREEN);
			cout << "A";
			SetConsoleTextAttribute(myColors, 15);
			cout << " The word has that letter, in that exact position" << endl;
			cout << endl << "Letters Not In the word: ";
			SetConsoleTextAttribute(myColors, 0 | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE);
			cout << usedletters << endl;
			SetConsoleTextAttribute(myColors, 15);
			cout << endl << endl;

			cout << "Your guess: ";
			MyGuess = MakeGuess();
			if (MyGuess == "!_!_!_!") {
				SetConsoleTextAttribute(myColors, 15 | BACKGROUND_RED);
				cout << errorMSG;
				SetConsoleTextAttribute(myColors, 15);
				system("pause ");
			}
			else {
				guesses[guessPos] = Compare(MyGuess);
				guessPos++;
				if (MyGuess == awnser) {
					lastMSG = "You WON!!";
					gameLoop = false;
				}
				if (guessPos >= 6) {
					lastMSG = "Game Over\n Better luck next time \n word was: " + awnser;
					gameLoop = false;
				}
			}
			//Sleep(1000);
			system("cls");
		}

		DrawUI();
	

		SetConsoleTextAttribute(myColors, 15 | BACKGROUND_GREEN );
		cout << lastMSG << endl;
		SetConsoleTextAttribute(myColors, 15);
		system("pause");

		doContinue = (AskForContinue() == 1);
		system("cls");
	}
	cout << "goodbye" << endl;
	system("pause");

	/*for (int i = 0; i < guessAmount; i++)
	{
		delete[] guesses[i].lettercolors;
	}
	delete[] guesses;*/

}
void PrintGuessStruct(guessStruct g) {
	if (g.guess.empty()) {
		SetConsoleTextAttribute(myColors, 15);
		for (int i = 0; i < wordLegnth; i++)
		{
			cout << "-" ;
		}
		return;
	}
	for (int i = 0; i < wordLegnth; i++)
	{
		if (g.lettercolors[i].color == 'Y') {
			SetConsoleTextAttribute(myColors, 15 | BACKGROUND_GREEN | BACKGROUND_RED);
		}
		else if (g.lettercolors[i].color == 'G') {
			SetConsoleTextAttribute(myColors, 15 | BACKGROUND_GREEN);
		}
		else {
			SetConsoleTextAttribute(myColors, 15);
		}
		cout << g.lettercolors[i].letter;
	}
	SetConsoleTextAttribute(myColors, 15);
}

guessStruct Compare(string guess) {
	guessStruct r;
	r.guess = guess;
	r.lettercolors = new letterColorStruct[wordLegnth];
	for (int x = 0; x < wordLegnth; x++) {
		r.lettercolors[x].letter = guess[x];
		for (int i = 0; i < wordLegnth; i++)
		{
			if (guess[x] == awnser[i]) {
				//yellow
				r.lettercolors[x].color = 'Y';
			}
		}
	}

	for (int i = 0; i < wordLegnth; i++)
	{
		if (guess[i] == awnser[i]) {
			r.lettercolors[i].color = 'G';
			//green
		}
	}
	for (int i = 0; i < wordLegnth; i++)
	{
		if (r.lettercolors[i].color == 'N') {
			if (!(usedletters.find(r.lettercolors[i].letter) != std::string::npos))
			{
				usedletters += guess[i];
				usedletters += " ";
			}
		}
	}
	
	return r;
}
string MakeGuess() {
	string inputstr = "";
	bool isValid = false,
		 isSized = false,
		 hasNumber = false,
		 hasSpecial = false,
		 hasSpaces = false;
	

	while (isValid == false) {

		getline(cin, inputstr);
		
		isSized = (inputstr.size() == wordLegnth);

		for (int i = 0; i < inputstr.size(); i++)
		{
			inputstr[i] = toupper(inputstr[i]);
			hasSpaces =  (hasSpaces == true || isspace(inputstr[i])); // has space
			hasNumber =  (hasNumber == true || isdigit(inputstr[i]) != 0);//has number
			hasSpecial = (hasSpecial == true || (!isalnum(inputstr[i]) && !isspace(inputstr[i]) && !(isdigit(inputstr[i]) != 0))); // is symbol
		}


		isValid = (isSized && !hasSpaces && !hasNumber && !hasSpecial);
		if (isValid == false) {
			errorMSG = "Invalid Awnser\n";
			if (!isSized)		errorMSG += "\t- only "+ to_string(wordLegnth) +" charcter long words\n";
			if (hasSpaces)		errorMSG += "\t- No Spaces\n";
			if (hasNumber)		errorMSG += "\t- No numbers\n" ;
			if (hasSpecial)		errorMSG += "\t- No special character\n" ;
			

			isValid = false;
			isSized = false;
			hasNumber = false;
			hasSpecial = false;
			hasSpaces = false;
			return "!_!_!_!";
		}
		else {
			return inputstr;
		}
	}
}

void DrawUI() {
	cout << "Wordle :: "<< dificulty <<"\n";
	for (int i = 0; i < guessAmount; i++)
	{
		cout << "\t";

		PrintGuessStruct(guesses[i]);
		SetConsoleTextAttribute(myColors, 15);
		cout << endl;
	}
	cout << endl << endl;
	
}

