#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#if 0

#include <iostream>
#include <fstream>
#include <string>
#include "split_utils.h"
#include "utils.h"
//#include "types.h"

using  namespace std;
std::vector<std::string> split2(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;

	str += pattern;
	size_t size = str.size();

	for (size_t i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}


void store_cmd(string cmd) {
	fstream os("./config.dat", ios::binary | ios::out | ios::app);
	os << cmd;
	const char *msg_split = "/";
	os << msg_split;
	os.close();
}
#endif