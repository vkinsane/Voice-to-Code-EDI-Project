
#include "stdafx.h"
// <code>
#include <iostream>
#include <speechapi_cxx.h>

#include <cstring>
#include <algorithm>

//for file handling
#include <fstream>

//default variable initialization
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <ctype.h>

using namespace std;

using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

string allSyntax[5];

string dataType();

void fileHandler(string s) {
	ofstream outfileof;  // Create Object of Ofstream

	outfileof.open("./userInputText/afile.txt", ios::app); // Append mode

	outfileof << s << endl;

	outfileof.close();
}

void fileAccessing() {
	fstream my_file;
	my_file.open("./userInputText/afile.txt", ios::in);
	if (!my_file) {
		cout << "No such file";
	}
	else {
		string str;
		int i = 0;
		while (getline(my_file, str)) {
			//cout << str<<endl;
			allSyntax[i] = str;
			i++;
		}
	}
	my_file.close();
}

string recognize_from_mic() {
	//int k;
	string k;
	auto config = SpeechConfig::FromSubscription("e776a7bfcae64eae8e6a930595ec2809", "eastus");

	auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();
	auto recognizer = SpeechRecognizer::FromConfig(config, audioConfig);

	cout << "Speak into your microphone." << std::endl;
	auto result = recognizer->RecognizeOnceAsync().get();
	cout << "RECOGNIZED as : Text=" << result->Text << std::endl;

	//cout << "Is Recognized properly ? ( If Yes type 1 | If No type 0)";
	//cin >> k;

	cout << "Is Recognized properly ? Yes or No : \n";
	cout << "Speak into your microphone" << std::endl;
	auto result1 = recognizer->RecognizeOnceAsync().get();
	cout << "RECOGNIZED as : Text=" << result1->Text << std::endl;

	k = result1->Text;
	transform(k.begin(), k.end(), k.begin(), ::tolower);//tolowercase
	if (k.back() == '.') {
		k = k.substr(0, k.size() - 1);
	}


	while (k != "yes") {
		cout << "Speak into your microphone. in while" << std::endl;
		auto result = recognizer->RecognizeOnceAsync().get();
		cout << "RECOGNIZED as : Text=" << result->Text << std::endl;

		cout << "Is Recognized properly ? Yes or No : \n";
		cout << "Speak into your microphone" << std::endl;
		auto result1 = recognizer->RecognizeOnceAsync().get();
		cout << "RECOGNIZED as : Text=" << result1->Text << std::endl;
		k = result1->Text;

		transform(k.begin(), k.end(), k.begin(), ::tolower);
		if (k.back() == '.') {
			k = k.substr(0, k.size() - 1);
		}

		if (k == "yes") {
			string syntax = result->Text;//result->Text recognized text
			//tolowercase
			transform(syntax.begin(), syntax.end(), syntax.begin(), ::tolower);
			if (syntax.back() == '.') {
				syntax = syntax.substr(0, syntax.size() - 1);
			}
			return syntax;
		}

	};

	string syntax = result->Text;//result->Text recognized text
	transform(syntax.begin(), syntax.end(), syntax.begin(), ::tolower);
	if (syntax.back() == '.') {
		syntax = syntax.substr(0, syntax.size() - 1);
	}
	return syntax;

}

string* variableInitialization() {
	int n;
	cout << "How many variables you want to declare : ";
	cin >> n;
	string* str = new string[n];
	string dt;
	string name;
	string value;
	for (int i = 0; i < n; i++)
	{
		cout << "Datatype of " << i+1 << " variable :";
		dt = dataType();

		cout << "\nEnter variable name :";
		name = recognize_from_mic();
		if (name.find(" ") != string::npos)
		{
			//changing ' ' to '_'
			replace(name.begin(), name.end(), ' ', '_');
		}

		cout << "\nEnter variable value :";
		value = recognize_from_mic();

		//concatenating
		if (dt == "char")
		{
			str[i] = dt + " " + name + " = " + "\'" + value + "\'";
		}
		else if (dt == "string")
		{
			str[i] = dt + " " + name + " = " + "\"" + value + "\"";
		}
		else if (dt == "float")
		{
			float value_int = std::stof(value);
			value_int = value_int + 0.0f;
			str[i] = dt + " " + name + " = " + to_string(value_int);
		}
		else if (dt == "double")
		{
			double value_int = std::stod(value);//11balls => 11
			value_int = value_int + 0.000000;
			str[i] = dt + " " + name + " = " + to_string(value_int);
		}
		else
			str[i] = dt + " " + name + " = " + value;

		//printing the recognized text initialization
		cout << "-------------------\n";
		cout << str[i] << endl;
		cout << "------------------\n";

	}

	return str;
}

string dataType() {

	string dt = recognize_from_mic();

	if (dt.find("int") != string::npos)
	{
		return "int";
	}
	else if (dt.find("float") != string::npos)
	{
		return "float";
	}
	else if (dt.find("char") != string::npos)
	{
		return "char";
	}
	else if (dt.find("double") != string::npos)
	{
		return "double";
	}
	else if (dt.find("string") != string::npos)
	{
		return "string";
	}
	else {
		cout << "Please speak again";
		dataType();
	}
}

void removeCommas(string& str1, int len)
{
	int j = 0;

	for (int i = 0; i < len; i++)
	{
		if (str1[i] == ',')
		{
			continue;
		}
		else
		{
			str1[j] = str1[i];
			j++;
		}
	}

	str1[j] = '\0';
}

void default_init() {

	string dt;
	string str;
	string s = recognize_from_mic();

	//============
	removeCommas(s, s.length());
	istringstream iss(s);
	vector<string> result;
	for (string s1;iss >> s1;)
		result.push_back(s1);
	int n = result.size();
	string data_type;
	string name;
	string value;
	data_type = result[1];
	name = result[3];
	value = result[6];
	//==========

	dt = data_type;

	if (dt.find("int") != string::npos)
	{
		dt = "int";
	}
	else if (dt.find("float") != string::npos)
	{
		dt = "float";
	}
	else if (dt.find("char") != string::npos)
	{
		dt = "char";
	}
	else if (dt.find("double") != string::npos)
	{
		dt = "double";
	}
	else if (dt.find("string") != string::npos)
	{
		dt = "string";
	}

	//concatenating
	if (dt == "char")
	{
		str = dt + " " + name + " = " + "\'" + value + "\'";
	}
	else if (dt == "string")
	{
		str = dt + " " + name + " = " + "\"" + value + "\"";
	}
	else if (dt == "float")
	{
		float value_int = std::stof(value);
		value_int = value_int + 0.0f;
		str = dt + " " + name + " = " + to_string(value_int);
	}
	else if (dt == "double")
	{
		double value_int = std::stoi(value);
		value_int = value_int + 0.000000;
		str = dt + " " + name + " = " + to_string(value_int);
	}
	else
		str = dt + " " + name + " = " + value;
	cout << "\n-------------------\n";
	cout << str << endl;
	cout << "------------------\n";
}

int main() {
	
	int choice;

	string syntax;
	string total_syntax[5];
	string instructions[] = {"Syntax for variable initialization","Syntax for if statement","Syntax for else if statement","Syntax for else statement","Syntax for for loop"};

	cout << "Have you already declared the syntax ? \n If yes type : 1 \nelse type : 0\nChoice : \n";
	cin >> choice;

	if (choice == 0) {
		ofstream outfileof;
		outfileof.open("./userInputText/afile.txt");
		outfileof.close();
		for (int i = 0;i < 5;i++) {
			syntax = recognize_from_mic();
			total_syntax[i] = syntax;
		}

		for (int i = 0;i < 5;i++) {
			fileHandler(total_syntax[i]);
		}
	}

	//storing the user inputs in allSyntax array
	fileAccessing();

	//printing the allSyntax array
	for (int i = 0;i < 5;i++) {
		cout << allSyntax[i] << endl;
	}
	
	cout << "-----------------------------------------------------------------------------------\n\n";

	string choice2 = "yes";
	while (choice2 == "yes")
	{
		cout << "Please enter your choice :\n1. User defined variable initialization method\n2. Default variable initialization method\n\n";
		choice2 = recognize_from_mic();
		if (choice2.find("user defined") != string::npos) {
			variableInitialization();
		}
		else {
			default_init();
		}
		cout << "\nDo you want to continue ? Yes or No\n";
		choice2 = recognize_from_mic();
		cout << "---X---X---X---X---X---X---X---X---\n\n";	

	}
	//Initialize integer variable X with value 13.
	//Initialize character variable car with value T.
	//Initialize float variable X with value 4.8.

	return 0;
}
