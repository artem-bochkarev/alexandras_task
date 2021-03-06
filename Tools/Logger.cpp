#include <Logger.h>

using namespace Tools;

Logger::Logger()
:ofs("Log.txt")
{
}

Logger::Logger( const std::string& str)
:ofs(str.c_str())
{
}

Logger& Logger::operator <<(int n)
{
	ofs << n;
    ofs.flush();
	return *this;
}

Logger& Logger::operator <<(const std::string & str)
{
	ofs << str.c_str();
    ofs.flush();
	return *this;
}

Logger& Logger::operator <<(const char * str)
{
	ofs << str;
    ofs.flush();
	return *this;
}

Logger::~Logger()
{
	ofs.close();
}