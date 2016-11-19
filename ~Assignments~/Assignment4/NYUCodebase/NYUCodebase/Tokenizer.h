#pragma once
#include <string>
#include <fstream>
#include <sstream>

class Tokenizer
{
public:
	virtual const Tokenizer* parse(const std::string&) = 0;
};