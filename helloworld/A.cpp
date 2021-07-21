#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
using namespace std;

void split(string s, vector<string>& ans)
{
	istringstream iss(s);
	for (string s1; iss >> s1;)
		ans.push_back(s1);
}

void initialiseWithoutElement(string name, string type, string size, bool common)
{
	cout << type;
	if (!common) cout << "*";
	cout << " " << name << "[" << size << "]" << ";";
}

void initialiseWithE(string name, string type, string size, string elements, bool common)
{
	vector<string> ans;
	split(elements, ans);
	cout << type;
	if (!common) cout << "*";
	cout << " " << name << "[" << size << "]" << " " << "=" << " " << "{";

	for (int i = 0; i < ans.size(); i++) {
		if (i == ans.size() - 1)
			cout << " " << ans[i];
		else
			cout << " " << ans[i] << ",";
	}

	cout << "}";

	cout << ";";
}

int main()
{
	string str;
	cout << "array initialisation" << endl;
	cout << "1. Common Array\n2. Dynamic Array" << endl;
	cout << "Enter your choice - " << endl;
	//str = recognize_from_mic();
	str = "dynamic";
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
		cout << "Invalid Choice" << endl;

	cout << "Please enter name of an array" << endl;
	string name = "arr";

	cout << "Please enter type of an array" << endl;
	string type = "char";

	cout << "Please enter number of elements in an array" << endl;
	string size = "4";

	cout << "Do you want to enter element in array now" << endl;
	str = "No";

	//str = recognize_from_mic();
	str = "yes";

	if (str.find("yes") != string::npos)
	{
		cout << "Please enter the elements" << endl;
		string elements = "20 10 20 10 10 10";
		initialiseWithE(name, type, size, elements, common);
	}
	else if (str.find("no") != string::npos)
	{
		initialiseWithoutElement(name, type, size, common);
	}
	else
		cout << "Invalid Choice" << endl;

	return 0;
}