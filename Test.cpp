#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

string extractData(const string& data, const string& regEx);

struct date
{
	day _day;
	month _month;
	year _year;

	date() = default;

	date(int _dayIn, int _monthIn, int _yearIn)
	{
		_day = day{ static_cast<unsigned>(_dayIn) };
		_month = month{ static_cast<unsigned>(_monthIn) };
		_year = year{ static_cast<int>(_yearIn) };
	}

	string toString()
	{
		string out = to_string(int(_year)) + "." + to_string(unsigned(_month)) + "." + to_string(unsigned(_day));
		return out;
	};

	void outputDate(std::ostream& os)
	{
		os << toString();
	}

};

class File
{
	string name;
	date fileDate;
	int size;

public:
	File(string _name, string _date, int _size)
	{
		name = _name;
		size = _size;
		vector<string> ymd;
		stringstream ss(_date);
		string part;
		while (getline(ss, part, '.'))
			ymd.push_back(part);
		fileDate = { stoi(ymd[2]), stoi(ymd[1]), stoi(ymd[0]) };
	}

	File(string str) : File(
		extractData(str, R"([A-Za-z]{1,20}\.[a-zA-Z0-9]{1,10})"),
		extractData(str, R"(\d{4}\.\d{2}\.\d{2})"),
		stoi(extractData(str, R"(\d{4,10}(?=\s|$))"))
	) {
	};

	string getFileName()
	{
		return name;
	}

	date getFileDate()
	{
		return fileDate;
	}

	int getSize()
	{
		return size;
	}

	string getDataAboutFile()
	{
		string outputData;
		string buf;
		buf = getFileName();
		outputData += buf + ' ';
		buf = getFileDate().toString();
		outputData += buf + ' ';
		buf = to_string(getSize());
		outputData += buf;
		return outputData;
	}
};

vector<File> Filter(vector<File> vec);

int main()
{
	ifstream in("in.txt");
	string text;
	vector<File> Files, FilesFilter;

	for (int i = 0; !in.eof(); i++)
	{
		getline(in, text);
		if (text == "")
			break;
		try {
			Files.push_back(text);
			cout << Files[i].getDataAboutFile() << endl;
		}
		catch (string s) {};
	}
}

string extractData(const string& data, const string& regEx)
{
	regex name(regEx);

	smatch match;
	regex_search(data, match, name);
	return match.str();
}

vector<File> Filter(vector<File> vec) {
	vector<File> vec1;
	for (auto e : vec) {
		if (e.getFileDate().toString() > "2025") {
			vec1.push_back(e);
		}
	}
	return vec1;
}