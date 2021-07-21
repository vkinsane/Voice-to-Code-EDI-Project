#include <speechapi_cxx.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include <ctype.h>

#include <windows.h>
using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

//auto config = SpeechConfig::FromSubscription("e776a7bfcae64eae8e6a930595ec2809", "eastus");
auto config = SpeechConfig::FromSubscription("3cc09265ddde47ca844b0fb29d7f3066", "eastus");
auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();
auto recognizer = SpeechRecognizer::FromConfig(config, audioConfig);
string lower(string string_to_lower)
{
	transform(string_to_lower.begin(), string_to_lower.end(), string_to_lower.begin(), ::tolower);
	return string_to_lower;
}
string removeFullStop(string string_to_remove_fullstop)
{
	if (string_to_remove_fullstop.back() == '.')
	{
		string_to_remove_fullstop = string_to_remove_fullstop.substr(0, string_to_remove_fullstop.size() - 1);
	}
	return string_to_remove_fullstop;
}
int string_number_to_int_number(string string_number)
{
	int int_number;
	if (string_number == "one") //i want two numbers => i want 2 numbers
	{
		int_number = 1;
	}
	else if (string_number == "two")
	{
		int_number = 2;
	}
	else if (string_number == "three")
	{
		int_number = 3;
	}
	else if (string_number == "four")
	{
		int_number = 4;
	}
	else if (string_number == "five")
	{
		int_number = 5;
	}
	else if (string_number == "six")
	{
		int_number = 6;
	}
	else if (string_number == "seven")
	{
		int_number = 7;
	}
	else if (string_number == "eight")
	{
		int_number = 8;
	}
	else if (string_number == "nine")
	{
		int_number = 9;
	}
	return int_number;
}

void espeak(string toSpeak, string character)
{
	string person;
	person = "f2";
	if (character == "male")
	{
		person = "m2";
	}
	string command = "espeak -ven+" + person + " \"" + toSpeak + "\"";
	const char* charCommand = command.c_str();
	//cout << "\n"<<command<<"\n";
	system(charCommand);
}
string recognize_from_mic()
{
	string firstInstruction = "Try saying";
	string instruction = "Try saying";
	string k;
	cout << instruction << "..." << endl;

	espeak(instruction, "female");

	auto result = recognizer->RecognizeOnceAsync().get();

	string result2 = "Do you want to confirm " + result->Text;
	result2 = removeFullStop(result2);
	cout << result2 << " ?" << endl;
	espeak(result2, "female");

	//cout << "Say Yes or No\n";
	//cout << instruction << std::endl;
	auto result1 = recognizer->RecognizeOnceAsync().get();
	//cout << "Do you want to confirm " << result->Text << "?" << endl;

	k = lower(result1->Text);
	k = removeFullStop(k);

	while (k != "yes")
	{
		instruction = "Try saying again";
		cout << instruction << "..." << std::endl;
		espeak(instruction, "female");

		auto result = recognizer->RecognizeOnceAsync().get();
		string result2 = "Do you want to confirm " + result->Text;
		result2 = removeFullStop(result2);
		cout << result2 << "?" << endl;

		espeak(result2, "female");
		//cout << firstInstruction << endl;
		auto result1 = recognizer->RecognizeOnceAsync().get();

		k = lower(result1->Text);
		k = removeFullStop(k);

		if (k == "yes")
		{
			string syntax = lower(result->Text); //result->Text recognized text
			syntax = removeFullStop(syntax);
			return syntax;
		}
	};

	string syntax = lower(result->Text); //result->Text recognized text
	syntax = removeFullStop(syntax);

	return syntax;
}

//**************************************************** [ File Handling ] ******************************************************
fstream my_file;

//**************************************************** [ Basic Functions ] ******************************************************

string allSyntax[5];
string dataType();
vector<string> split(string s)
{
	istringstream iss(s);
	vector<string> result;
	for (string s1; iss >> s1;)
		result.push_back(s1);
	return result;
}
void removeCommas(string& str1)
{
	int len = str1.length();
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

	str1[j] = ' ';
	str1[j + 1] = '\0';
}
string get_return_type(string s)
{
	if (s.find("integer") != s.npos)
	{
		return "int";
	}
	else if (s.find("character") != s.npos)
	{
		return "char";
	}
	else
	{
		return s;
	}
}
string get_data_type(string s)
{
	vector<string> dt = split(s);
	if (dt[0].find("integer") != dt[0].npos)
	{
		return "int";
	}
	else if (dt[0].find("character") != dt[0].npos)
	{
		return "char";
	}
	else
	{
		return dt[0];
	}
}
string get_var_name(string s)
{
	vector<string> dt = split(s);
	return dt[1];
}

//**************************************************** [ Variable Initialization] ******************************************************
string* variableInitialization()
{
	int n;
	cout << "How many variables you want to declare : ";
	espeak("How many variables you want to declare", "female");
	string num_of_variables = recognize_from_mic();
	n = stoi(num_of_variables);
	//cin >> n;
	string* str = new string[n];
	string dt;
	string name;
	string value;
	for (int i = 0; i < n; i++)
	{
		cout
			<< "Datatype of " << i + 1 << " variable :";
		dt = dataType();

		cout
			<< "\nEnter variable name :";
		espeak("Enter variable name", "female");
		name = recognize_from_mic();
		if (name.find(" ") != string::npos)
		{
			//changing ' ' to '_'
			replace(name.begin(), name.end(), ' ', '_');
		}

		cout
			<< "\nEnter variable value :";
		espeak("Enter variable value", "female");
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
			str[i] = dt + " " + name + " = " + to_string(value_int) + ";";
		}
		else if (dt == "double")
		{
			double value_int = std::stod(value); //11balls => 11
			value_int = value_int + 0.000000;
			str[i] = dt + " " + name + " = " + to_string(value_int) + ";";
		}
		else
			str[i] = dt + " " + name + " = " + value + ";";

		//printing the recognized text initialization
		//Variable Initialize Final
		my_file << str[i] << "\n";
		cout << "-------------------\n";
		cout << str[i] << endl;
		cout << "------------------\n";
	}

	return str;
}

//**************************************************** [ Functions for Function Declaration] *******************************************

void declare_function(string s)
{
	//declare integer function Add with 2 parameters integer a, integer b
	removeCommas(s);
	vector<string> f = split(s);
	int n = f.size();
	string return_type = get_return_type(f[1]);
	string name = f[3];
	string no_of_params = f[5];
	//int no_params = stoi(no_of_params);
	int no_params = string_number_to_int_number(f[5]); //converted string number to integer number
	string* paramters = new string[no_params];
	for (int i = 0; i < no_params; i++)
	{
		paramters[i] = f[7 + (2 * i)] + " " + f[7 + (2 * i) + 1];
	}
	string final_syntax = return_type + " " + name + "(";
	for (int i = 0; i < no_params; i++)
	{
		if (i == no_params - 1)
		{
			final_syntax = final_syntax + get_data_type(paramters[i]) + " " + get_var_name(paramters[i]) + ");";
		}
		else
		{
			final_syntax = final_syntax + get_data_type(paramters[i]) + " " + get_var_name(paramters[i]) + ", ";
		}
	}
	//Declare Function Final
	cout << final_syntax;
	my_file << final_syntax << "\n";
}

void define_function(string s)
{
	//define integer function Add with 2 parameters integer a, integer b
	removeCommas(s);
	vector<string> f = split(s);
	int n = f.size();
	string return_type = get_return_type(f[1]);
	string name = f[3];
	string no_of_params = f[5];
	//int no_params = stoi(no_of_params);
	int no_params = string_number_to_int_number(f[5]); //converted string number to integer number
	string* paramters = new string[no_params];
	for (int i = 0; i < no_params; i++)
	{
		paramters[i] = f[7 + (2 * i)] + " " + f[7 + (2 * i) + 1];
	}
	string final_syntax = return_type + " " + name + "(";
	for (int i = 0; i < no_params; i++)
	{
		if (i == no_params - 1)
		{
			final_syntax = final_syntax + get_data_type(paramters[i]) + " " + get_var_name(paramters[i]) + "){";
		}
		else
		{
			final_syntax = final_syntax + get_data_type(paramters[i]) + " " + get_var_name(paramters[i]) + ", ";
		}
	}
	//Define Function Final
	cout << final_syntax << "\n   //Code"
		<< "\n}";
}

void init_function(string s)
{
	s = lower(s);
	string instruction;
	if (s.find("declare") != s.npos)
	{
		instruction = "Try Saying";
		cout << instruction << "\nex : declare integer function Add with 2 parameters integer a, integer b" << endl;
		espeak(instruction, "female");
		s = recognize_from_mic();
		declare_function(s);
	}
	else if (s.find("define") != s.npos)
	{
		instruction = "Try Saying";
		cout << instruction << "\nex : define integer function Add with 2 parameters integer a, integer b" << endl;
		espeak(instruction, "female");
		s = recognize_from_mic();
		define_function(s);
	}
	else
	{
		instruction = "Should I declare or define function ?";
		cout << instruction << endl;
		espeak(instruction, "female");
		string s1 = recognize_from_mic();
		init_function(s1);
	}
}

string generate_symbol(string s) // Generating Symbols
{
	if (s.find("plus plus") != s.npos)
		return "++";
	else if (s.find("minus minus") != s.npos)
		return "--";
	else if (s.find("less than or equal") != s.npos || s.find("less than equal") != s.npos)
		return "<=";
	else if (s.find("greater than or equal") != s.npos || s.find("greater than equal") != s.npos)
		return ">=";
	else if (s.find("greater than") != s.npos)
		return ">";
	else if (s.find("equal to equal to") != s.npos)
		return "==";
	else if (s.find("not equal") != s.npos)
		return "!=";
	else if (s.find("equal to") != s.npos || s.find("start from") != s.npos)
		return "=";
	else if (s.find("less than") != s.npos)
		return "<";
	else
		return "Invalid condition";
}

string inforloop(string s) // Initialization of for loop
{
	s = lower(s);
	if (s.find("initialize") != s.npos && s.find("for") != s.npos)
	{
		string forloop = "for(";
		return forloop;
	}
	else
	{
		cout
			<< "Invalid Command !";
	}
}

void print(std::vector<string> const& start) // Printing string vector
{
	std::cout
		<< "The vector elements are : ";

	for (int i = 0; i < start.size(); i++)
		std::cout << start.at(i) << ' ';
}

//**************************************************** [ FOR LOOP functions ] ****************************************************

string for1(string s1) // Statement 1 formation (for loop)
{
	int StartingofI;
	string s1final, dname, init;
	s1 = lower(s1);
	// s2 = lower(s2);
	// s3 = lower(s3);
	string sym = generate_symbol(s1);
	vector<string> start = split(s1);
	// print(start);
	if (s1.find("start") != s1.npos)
	{
		dname = start[0];
		init = start[4];
		if (sym != "Invalid condition")
		{
			/* code */
			s1final = dname + " " + sym + " " + init;
		}
	}
	return s1final;
}

string for2(string s2) // Statement 2 formation (for loop)
{

	string s1final, dname, init;
	s2 = lower(s2);
	string sym = generate_symbol(s2);
	vector<string> start = split(s2);
	// print(start);
	if (s2.find("than or equal") != s2.npos)
	{
		dname = start[0];
		init = start[6];
		if (sym != "Invalid condition")
		{
			/* code */
			s1final = dname + " " + sym + " " + init;
		}
	}
	else if (s2.find("less than") != s2.npos || s2.find("greater than") != s2.npos || s2.find("equal to") != s2.npos)
	{
		dname = start[0];
		init = start[3];
		if (sym != "Invalid condition")
		{
			/* code */
			s1final = dname + " " + sym + " " + init;
		}
	}
	return s1final;
}

string for3(string s3) // Statement 3 formation (for loop)
{
	int StartingofI;
	string s1final, dname;
	s3 = lower(s3);
	string sym = generate_symbol(s3);
	vector<string> start = split(s3);
	dname = start[0];
	// print(start);
	if (s3.find(dname) != s3.npos || s3.find("plus") != s3.npos || s3.find("minus") != s3.npos)
	{
		if (sym != "Invalid condition")
		{
			/* code */
			s1final = dname + sym;
		}
	}
	return s1final;
}

void displayfor() // for loop display
{

	string s = "Initialize for loop";
	string instruction = "Basic Syntax of for loop is given below";
	cout << instruction << endl;
	espeak(instruction, "female");

	cout << inforloop(s) << "int "
		<< "statement 1"
		<< " ; "
		<< "statement 2"
		<< " ; "
		<< "statement 3"
		<< ") " << endl;
	cout
		<< "{"
		<< "\n   //Code"
		<< "\n}" << endl;
	instruction = "Specify Statement 1";
	cout
		<< "Specify Statement 1 !!! e.g :  j will start from 1" << endl;
	espeak(instruction, "female");

	string s1 = recognize_from_mic();
	// string s2 = "j less than 10";
	// string s2 = "i less than or equal to 10 ";
	//string s2 = "j greater than or equal to 10 ";
	instruction = "Specify Statement 2";
	cout
		<< "Specify Statement 2 !!! e.g :  j less than 11 / j greater than or equal to 10" << endl;
	espeak(instruction, "female");

	string s2 = recognize_from_mic();
	//string s3 = "j plus plus";
	// string s3 = "i minus minus";
	instruction = "Specify Statement 3";
	cout
		<< "Specify Statement 3 !!! e.g :  j plus plus" << endl;
	espeak(instruction, "female");

	string s3 = recognize_from_mic();
	//For loop Final
	cout << inforloop(s) << "int " << for1(s1) << " ; " << for2(s2) << " ; " << for3(s3) << ") " << endl;
	cout << "{"
		<< "\n   //Code"
		<< "\n}" << endl;
	string final_for_loop_syntax = inforloop(s) + "int " + for1(s1) + " ; " + for2(s2) + " ; " + for3(s3) + ") " + "{"
		+ "\n   //Code"
		+ "\n}";
	my_file << final_for_loop_syntax;
}

//**************************************************** [ WHILE LOOP functions ] ****************************************************

string while1(string s2) // While loop formation
{

	string s1final, dname, init;
	s2 = lower(s2);
	string sym = generate_symbol(s2);
	vector<string> start = split(s2);
	if (s2.find("less than") != s2.npos || s2.find("greater than") != s2.npos || s2.find("equal to") != s2.npos)
	{
		dname = start[0];
		init = start[3];
		if (sym != "Invalid condition")
		{
			s1final = dname + " " + sym + " " + init;
		}
	}
	return s1final;
}

void displaywhile(string s2) //while loop display
{
	// string s1 = "Initialize while loop";

	cout << "while(" << while1(s2) << ")" << endl;
	cout << "{"
		<< "\n   //Code"
		<< "\n}" << endl;
}

//****************************************************[ DO WHILE LOOP functions ] ****************************************************

string dowhile(string s2) //do while loop formation
{
	string s1final, dname, init;
	s2 = lower(s2);
	string sym = generate_symbol(s2);
	vector<string> start = split(s2);
	if (s2.find("less than") != s2.npos || s2.find("greater than") != s2.npos || s2.find("equal to") != s2.npos)
	{
		dname = start[0];
		init = start[3];
		if (sym != "Invalid condition")
		{
			s1final = dname + " " + sym + " " + init;
		}
	}
	return s1final;
}

void displaydowhile(string s2) // do while loop display
{
	//string s1 = "Initialize do while loop";

	// cout << "while(" << dowhile(s2) << ")" << endl;
	cout << "do\n"
		<< "{"
		<< "\n   //Code"
		<< "\n}"
		<< "while(" << dowhile(s2) << ");" << endl;
}

void fileHandler(string s)
{
	ofstream outfileof; // Create Object of Ofstream

	outfileof.open("./userInputText/afile.txt", ios::app); // Append mode

	outfileof << s << endl;

	outfileof.close();
}

void fileAccessing()
{
	fstream my_file;
	my_file.open("./userInputText/afile.txt", ios::in);
	if (!my_file)
	{
		cout
			<< "No such file";
	}
	else
	{
		string str;
		int i = 0;
		while (getline(my_file, str))
		{
			//cout << str<<endl;
			//allSyntax[i] = str;
			i++;
		}
	}
	my_file.close();
}

string dataType()
{

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
	else
	{
		cout
			<< "Please speak again";
		espeak("Please speak again", "female");
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

void default_init()
{

	string dt;
	string str;
	string s = "";

	//============
	removeCommas(s, s.length());
	istringstream iss(s);
	vector<string> result;
	for (string s1; iss >> s1;)
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
		double value_int = std::stoi(value); //string to integer
		value_int = value_int + 0.000000;
		str = dt + " " + name + " = " + to_string(value_int);
	}
	else
		str = dt + " " + name + " = " + value;
	cout
		<< "\n-------------------\n";
	cout << str << endl;
	cout
		<< "------------------\n";
}

//**************************************************** [ If-Else functions ] ****************************************************

void user_defined_if_else()
{
	string choice, condition, sym, f_syntax;
	string instruction = "Which block do you want to generate";
	cout
		<< "Which block do you want to generate?" << endl;
	cout
		<< "If\tElse If\t\tElse" << endl;
	espeak(instruction, "female");

	choice = recognize_from_mic();

	//choice = "if";

	if (choice.find("if") != choice.npos)
	{

		string instruction = "Specify the condition for if block";
		cout
			<< "Specify the condition for if block \n ex : t less than 10" << endl;
		espeak(instruction, "female");

		condition = recognize_from_mic();
		//condition = "i less than j";
		vector<string> uif_syntax = split(condition);
		sym = generate_symbol(condition);
		if (sym != "Invalid condition")
		{
			f_syntax = "if (" + uif_syntax[0] + " " + sym + " " + uif_syntax[uif_syntax.size() - 1] + ")";
			cout << f_syntax << "\n{"
				<< "\n   //if body"
				<< "\n}" << endl;
		}
		else
			cout << sym << endl;
	}

	else if (choice.find("else if") != choice.npos)
	{
		string instruction = "Specify the condition for else if block";
		cout
			<< "Specify the condition for else if block \nex : t less than 30" << endl;
		espeak(instruction, "female");

		condition = recognize_from_mic();
		//condition = "i less than j";
		vector<string> uelif_syntax = split(condition);
		sym = generate_symbol(condition);
		if (sym != "Invalid condition")
		{
			f_syntax = "else if (" + uelif_syntax[0] + " " + sym + " " + uelif_syntax[uelif_syntax.size() - 1] + ")";
			cout << f_syntax << "\n{"
				<< "\n   //else if body"
				<< "\n}" << endl;
		}
		else
			cout << sym << endl;
	}

	else if (choice.find("else") != choice.npos)
	{
		f_syntax = "else";
		cout << f_syntax << "\n{"
			<< "\n   //else body"
			<< "\n}" << endl;
	}
}

void default_if_else()
{
	//syntax - generate else block

	string syntax, f_syntax, sym;
	syntax = recognize_from_mic();
	//syntax = "generate else block";
	vector<string> sp_syntax = split(syntax);
	sym = generate_symbol(syntax);

	//syntax - generate if block with condition t less than 10
	if (syntax.find("generate if") != string::npos)
	{
		if (sym != "Invalid condition")
		{
			f_syntax = "if (" + sp_syntax[5] + " " + sym + " " + sp_syntax[sp_syntax.size() - 1] + ")";
			cout << f_syntax << "\n{"
				<< "\n   //if body"
				<< "\n}" << endl;
		}
		else
			cout << sym << endl;
	}

	//syntax - generate else if block with condition t greater than 10
	else if (syntax.find("generate else if") != string::npos) //check for (syntax.find("generate else") != string::npos && syntax.find("if") != string::npos)
	{
		if (sym != "Invalid condition")
		{
			f_syntax = "else if (" + sp_syntax[6] + " " + sym + " " + sp_syntax[sp_syntax.size() - 1] + ")";
			cout << f_syntax << "\n{"
				<< "\n   //if body"
				<< "\n}" << endl;
		}
		else
			cout << sym << endl;
	}

	//syntax - generate else block
	else if (syntax.find("generate else") != string::npos)
	{
		f_syntax = "else";
		cout << f_syntax << "\n{"
			<< "\n   //else body"
			<< "\n}" << endl;
	}

	else
		cout << "Invalid Syntax";
}

void if_else_code()
{

	string str;
	string instruction = "Which syntax for if-else do you want to generate";
	cout
		<< "Which syntax for if-else do you want to generate ?" << endl;
	cout
		<< "1. User Defined Syntax\n 2. Default Syntax" << endl;
	espeak(instruction, "female");

	str = recognize_from_mic();
	//str = "user";

	if (str.find("user") != string::npos)
	{
		user_defined_if_else();
	}
	else if (str.find("default") != string::npos)
	{
		instruction = "Try Saying";
		cout << instruction << "\nex : Generate if block with condition t less than 10" << endl;
		espeak(instruction, "female");
		default_if_else();
	}
	else
		cout
		<< "Invalid Choice" << endl;
}

//**************************************************** [ For loop ] ****************************************************

void call_loops(string s)
{

	if (s.find("for loop") != s.npos || s.find("forloop") != s.npos)
	{
		displayfor();
	}

	else if (s.find("do while") != s.npos || s.find("dowhile loop") != s.npos)
	{
		string instruction = "Specify Condition";
		cout
			<< "Specify Condition !!! e.g :  i less than 10" << endl;
		espeak(instruction, "female");

		string s2 = recognize_from_mic();
		displaydowhile(s2);
	}

	else if (s.find("while") != s.npos || s.find("whileloop") != s.npos)
	{
		string instruction = "Specify Condition";
		cout
			<< "Specify Condition !!! e.g :  i less than 10" << endl;
		espeak(instruction, "female");

		//string s2 = "j equal to 10";
		string s2 = recognize_from_mic();
		displaywhile(s2);
	}

	//Case for just "Initialize" keyword to display which loop to make

	else if (s.find("initialize a loop") != s.npos || s.find("initialize loop") != s.npos || s.find("make loop") != s.npos)
	{

		string instruction = "Which looping statement should I make for you ?";
		cout << instruction << endl;
		espeak(instruction, "female");
		cout
			<< "for loop" << endl
			<< "do while loop" << endl
			<< "while loop" << endl;
		string s = recognize_from_mic();
		if (s.find("for loop") != s.npos || s.find("forloop") != s.npos)
		{
			displayfor();
		}

		else if (s.find("do while") != s.npos || s.find("dowhile loop") != s.npos)
		{
			cout
				<< "Specify Condition !!! e.g :  i less than 10" << endl;
			string s2 = recognize_from_mic();
			displaydowhile(s2);
		}

		else if (s.find("while") != s.npos || s.find("whileloop") != s.npos)
		{
			cout
				<< "Specify Condition !!! e.g :  i less than 10" << endl;
			//string s2 = "j equal to 10";
			string s2 = recognize_from_mic();
			displaywhile(s2);
		}
	}
}

//**************************************************** [ Switch Case ] ****************************************************

int casesCounter(vector<string> vect)
{
	int totalCaseWords = 0;
	for (int i = 0; i < vect.size(); i++)
	{
		if (vect[i] == "case")
		{
			totalCaseWords++;
		}
	}
	return totalCaseWords;
}

int indexOfVectorElement(vector<string> vect, string toFind, int begin)
{
	for (int i = begin; i < vect.size(); i++)
	{
		if (vect[i] == toFind)
		{
			return i;
		}
	}
	return 0;
}

string intToString(int x)
{
	string str;
	stringstream ss;
	ss << x;
	ss >> str;
	return str;
}

string casesMakerUserDefined(int case_blocks)
{
	string toReturn = "";
	string expression_for_case;
	for (int i = 0; i < case_blocks; i++)
	{
		//cout << "Specify the expression for case " << i + 1 << endl;
		// expression_for_case = recognize_from_mic();
		expression_for_case = intToString(i + 1);
		toReturn = toReturn + "case " + expression_for_case + " :\n\t //code \n\tbreak;\n";
	}
	toReturn = toReturn + "default :" + "\n\t //code \n\tbreak;";
	return toReturn;
}

string casesMakerDefault(string array[], int n)
{
	string toReturn = "";
	// string expression_for_case;
	for (int i = 0; i < n; i++)
	{
		toReturn = toReturn + "case " + array[i] + " :\n\t //code \n\tbreak;\n";
	}
	toReturn = toReturn + "default :" + "\n\t //code \n\tbreak;";
	return toReturn;
}

string generate_symbol_switch_case(string s)
{
	if (s.find("less than") != s.npos)
		return "<";
	else if (s.find("less than or equal") != s.npos || s.find("less than equal") != s.npos)
		return "<=";
	else if (s.find("greater than or equal") != s.npos || s.find("greater than equal") != s.npos)
		return ">=";
	else if (s.find("greater than") != s.npos)
		return ">";
	else if (s.find("equal to equal to") != s.npos)
		return "==";
	else if (s.find("not equal") != s.npos)
		return "!=";
	else if (s.find("equal to") != s.npos)
		return "=";
	else
		return "Invalid condition";
}

void user_defined_switch_case()
{
	string num_of_case_blocks, condition, sym, f_syntax, code;
	int case_blocks;

	string instruction = "How many cases to include?";
	cout
		<< "How many cases to include?" << endl;
	espeak(instruction, "female");
	num_of_case_blocks = recognize_from_mic();
	case_blocks = std::stoi(num_of_case_blocks);
	//case_blocks = 4;

	instruction = "Specify the condition or Expression for switch case";
	cout << instruction << endl;
	espeak(instruction, "female");
	condition = recognize_from_mic();
	//condition = "i less than j";
	vector<string> user_given_condition = split(condition);

	sym = generate_symbol_switch_case(condition);

	if (sym != "Invalid condition")
	{
		f_syntax = "switch (" + user_given_condition[0] + " " + sym + " " + user_given_condition[user_given_condition.size() - 1] + ")";
		code = f_syntax + "\n{" + "\n" + casesMakerUserDefined(case_blocks) + "\n}";

		//printing the final code

		instruction = "Generated Output is";
		cout << instruction << endl;
		espeak(instruction, "female");
		cout << code;
	}
	else
		cout << sym << endl;
}

void default_switch_case()
{
	string syntax, f_syntax, sym, code;

	syntax = "generate switch case block with condition t less than 10 & case false case 6 case hello";
	//recognized as : Generate switch case block with condition T less than 10 and case falls Case 6 case Hello.

	//variation can happen : syntax = "generate switch-case block with condition t less than 10 and case false, case 6, case hello";

	vector<string> sp_syntax = split(syntax);
	sym = generate_symbol(syntax);

	if (sym != "Invalid condition")
	{
		int totalCaseWords = casesCounter(sp_syntax);
		int lengthOfArray = totalCaseWords - 1;

		//array for storing values after case words
		string* caseValueArray = new string[lengthOfArray];

		//finding first match , but it is of no use so not putting it into array
		int indexOFCase = indexOfVectorElement(sp_syntax, "case", 0);
		for (int i = 0; i < lengthOfArray; i++)
		{
			indexOFCase = indexOfVectorElement(sp_syntax, "case", indexOFCase + 1);
			*(caseValueArray + i) = sp_syntax[indexOFCase + 1];
		}
		// cout << casesMakerDefault(caseValueArray, lengthOfArray);
		// f_syntax = "switch (" + sp_syntax[6] + " " + sym + " " + sp_syntax[9] + ")";
		f_syntax = "switch (" + sp_syntax[indexOfVectorElement(sp_syntax, "less", 0) - 1] + " " + sym + " " + sp_syntax[indexOfVectorElement(sp_syntax, "than", 0) + 1] + ")";
		code = f_syntax + "\n{" + "\n" + casesMakerDefault(caseValueArray, lengthOfArray) + "\n}";
		cout << code << endl;
	}
	else
		cout << sym << endl;
}

void switchcase()
{
	string str;
	cout
		<< "Switch Declaration" << endl;
	espeak("Which declaration you want ?", "female");
	cout
		<< "1. User Defined Syntax\n 2. Default Syntax" << endl;
	//cout << "Enter your choice - " << endl;
	str = recognize_from_mic();
	//str = "default";

	if (str.find("user") != string::npos)
	{
		user_defined_switch_case();
	}
	else if (str.find("default") != string::npos)
	{
		default_switch_case();
	}
	else if (str.find("loops") != string::npos || str.find("loop") != string::npos)
	{
		call_loops(str);
	}
	else
		cout
		<< "Invalid Choice" << endl;
}

//**************************************************** [ Sanket's Array Code ] ****************************************************

void split_array(string s, vector<string>& ans)
{
	istringstream iss(s);
	for (string s1; iss >> s1;)
		ans.push_back(s1);
}

void initialiseWithoutElement(string name, string type, string size, bool common)
{
	cout << type;
	if (!common)
		cout << "*";
	cout << " " << name << "[" << size << "]"
		<< ";";
}

void initialiseWithE(string name, string type, string size, string elements, bool common)
{
	vector<string> ans;
	split_array(elements, ans);
	type = lower(type);
	if (type.find("character") != type.npos || type.find("char") != type.npos)
		cout << "char";
	else if (type.find("integer") != type.npos || type.find("int") != type.npos)
		cout << "int";
	else if (type.find("string") != type.npos)
		cout << "string";
	else if (type.find("boolean") != type.npos)
		cout << "boolean";
	if (!common)
		cout << "*";
	cout << " " << name << "[" << size << "]"
		<< " "
		<< "="
		<< " "
		<< "{";

	for (int i = 0; i < ans.size(); i++)
	{
		if (i == ans.size() - 1)
			cout << " " << ans[i];
		else
			cout << " " << ans[i] << ",";
	}

	cout << "}";

	cout << ";";
}

void array_s()
{
	string str = "";
	cout
		<< "array initialisation" << endl;
	cout
		<< "Which array you want to initialize?\n1. Common Array\n2. Dynamic Array" << endl;
	espeak("Which array you want to initialize?", "female");
	//cout << "Enter your choice - " << endl;
	str = recognize_from_mic();
	//str = "dynamic";
	bool common = true;

	if (str.find("common") != string::npos)
	{
		common = true;
	}
	else if (str.find("dynamic") != string::npos)
	{
		common = false;
	}
	else
	{
		cout
			<< "Invalid Choice " << endl;
	}

	cout
		<< "Please enter name of an array" << endl;
	espeak("Please enter name of an array", "female");
	string name = recognize_from_mic();

	cout
		<< "Please enter type of an array" << endl;
	espeak("Please enter type of an array", "female");
	string type = recognize_from_mic();

	cout
		<< "Please enter number of elements in an array" << endl;
	espeak("Please enter number of elements in an array", "female");
	string size = recognize_from_mic();
	int size_of_array = std::stoi(size);

	cout
		<< "Do you want to enter elements in array now" << endl;
	espeak("Do you want to enter elements in array now", "female");
	str = recognize_from_mic();

	if (str.find("yes") != string::npos)
	{
		cout
			<< "Specify the elements" << endl;
		espeak("Specify the elements", "female");
		string elements = "";
		for (int i = 0; i < size_of_array; i++)
		{
			string temp = recognize_from_mic();
			elements += temp + " ";
		}
		initialiseWithE(name, type, size, elements, common);
	}
	else if (str.find("no") != string::npos)
	{
		initialiseWithoutElement(name, type, size, common);
	}
	else
	{
		espeak("Invalid Choice", "female");
		cout
			<< "Invalid Choice " << endl;
	}
}

void call_array()
{
	string str;
	str = recognize_from_mic();

	if (str.find("array") != str.npos)
	{
		array_s();
	}
}

//**************************************************** [ Exit ] ****************************************************
bool exitInvoked = false;
void exit()
{
	string instruction = "It was nice meeting with you. See you soon";
	cout << "\n\n       *****************************  [ It was nice meeting with you. See you soon ] ****************************       " << endl;
	espeak(instruction, "female");
	exitInvoked = true;
}