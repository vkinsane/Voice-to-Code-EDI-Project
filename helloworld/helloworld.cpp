#include <speechapi_cxx.h>
#include "VoicetoCode.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include <ctype.h>
using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

void welcome()
{
	string instruction = "Welcome User";
	cout << "\n\n        ******************************************* ["<< instruction <<"] *********************************************\n"<< endl;
	espeak(instruction, "female");
	instruction = "I am Joyce, your code assistant";
	cout << "-[ "<<instruction<<" ]" << endl;
	espeak(instruction, "female");
	instruction = "You can tell me some commands and I will generate code accordingly";
	cout << "-[ " << instruction << " ]" << endl;
	espeak(instruction, "female");
	instruction = "Here are few commands, Try saying any one of them.";
	cout << "-[ " << instruction << " ]" << endl;
	espeak(instruction, "female");
	instruction = "-> Generate a for loop \n-> Initialize Variable \n-> Create a switch case \n-> Create if else ladder \n-> Declare or Define function";
	cout << instruction << endl;
}


void check_string(string s)
{
	if ((s.find("for loop") != s.npos) || (s.find("forloop") != s.npos) || (s.find("loop") != s.npos) || s.find("looping") != s.npos)
	{
		call_loops(s);
	}
	else if ((s.find("if else") != s.npos) || (s.find("if") != s.npos) || (s.find("condition ladder") != s.npos) || (s.find("conditional block") != s.npos))
	{
		if_else_code();
	}
	else if ((s.find("declare function") != s.npos) || (s.find("define function") != s.npos) || (s.find("function") != s.npos))
	{
		init_function(s);
	}
	else if ((s.find("switch case") != s.npos) || (s.find("switch ladder") != s.npos))
	{
		switchcase();
	}
	else if ((s.find("array") != s.npos))
	{
		array_s();
	}
	else if ((s.find("Variable") != s.npos) || (s.find("variable") != s.npos) || (s.find("create variable") != s.npos) || (s.find("make variable") != s.npos))
	{
		variableInitialization();
	}
	else if ((s.find("exit") != s.npos)|| (s.find("Exit") != s.npos) || (s.find("Close") != s.npos) || (s.find("close") != s.npos))
	{
		exit();
	}
	else
	{
		string instruction = "Sorry , I didn't find anything";
		cout << instruction << "!" << endl;
		espeak(instruction, "female");
	}
}

int main()
{
	//File handling
	my_file.open("codes.txt", ios::out);
	if (!my_file)
	{
		//cout << "File not created!";
	}
	else
	{
	//	cout << "File created successfully!";
		// my_file << "\n";
	}
	string s, confirm, instruction;
	welcome();
	do
	{
		s = recognize_from_mic();
		check_string(s);
		//string s = "generate if block with condition t less than 10";
		if (exitInvoked == false) {
			instruction = "Do you want to continue?";
			cout << "\n" <<instruction << endl;
			espeak(instruction, "female");
			confirm = recognize_from_mic();
			confirm = lower(confirm);
		}
	} while (confirm.find("yes") != s.npos);
	if (exitInvoked == false)
	{
		exit();
	}
	my_file.close();
}