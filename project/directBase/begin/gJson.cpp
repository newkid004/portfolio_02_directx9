#include "gJson.h"

using namespace std;

void gJson::write(json & in_json, const std::string & filepath)
{
	ofstream file(filepath);
	file << in_json;
}

void gJson::read(json & out_json, const string & filepath)
{
	ifstream file(filepath);
	string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	out_json = json::parse(content);
}
