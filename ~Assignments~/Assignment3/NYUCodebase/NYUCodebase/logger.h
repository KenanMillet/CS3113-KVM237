#pragma once

#include <cstdint>
#include <fstream>
#include <ctime>
#include <iomanip>

namespace Logger
{
	enum logTime : uint8_t
	{
		YES,
		NO,
		HIDDEN
	};

	template <class T>
	void log(T message, uint8_t indent = 0, logTime timestamp = YES, const char* end = "\n")
	{
		static auto mode(std::ios::trunc);
		static std::ofstream file;
		file.open("log.txt", mode);

		if(timestamp == YES)
		{
			auto t = time(0);
			tm now;
			localtime_s(&now, &t);
			file.fill('0');
			file << "[" << std::setw(2) << now.tm_mon + 1 << "/" << std::setw(2) << now.tm_mday << "/" << std::setw(2) << now.tm_year % 100
				<< " " << std::setw(2) << now.tm_hour << ":" << std::setw(2) << now.tm_min << ":" << std::setw(2) << now.tm_sec << "] ";
		}
		else if(timestamp == HIDDEN) file << "                    ";
		for(uint8_t i = 0; i < indent; ++i) file << "\t";
		file << message << end;

		file.close();
		mode = std::ios::app;
	}
}