
// CODESTYLE: v2.0

// Tokenizer.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: a class that implements a simple string tokenizer and support parsing functions

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include "Tokenizer.h"

namespace VCOMP
{
	std::vector<std::string> Tokenizer::Tokenize(const std::string& source, const std::string& delimiters)
	{
		std::vector<std::string> tokens;
		
		size_t p0 = 0;
		size_t p1 = std::string::npos;
		
		while (p0 != std::string::npos)
		{
			p1 = source.find_first_of(delimiters, p0);
			if (p1 != p0)
			{
				std::string token = source.substr(p0, p1 - p0);
				tokens.push_back(token);
			}
			p0 = source.find_first_not_of(delimiters, p1);
		}
		
		return tokens;
	}
		
	namespace PARSING
	{
		bool StringProcessor::IsCharacterNumeric(char c)
		{
			return static_cast<bool>((c >= '0' && c <= '9'));
		}
		
		bool StringProcessor::IsCharacterWhiteSpace(char c)
		{
			return static_cast<bool>((' ' == c || '\t' == c));
		}
		
		bool StringProcessor::IsCharacterIdentifier(char c)
		{
			return static_cast<bool>(
				(c >= '0' && c <= '9') ||
				(c >= 'A' && c <= 'Z') ||
				(c >= 'a' && c <= 'z') ||
				'_' == c
				);
		}
		
		bool StringProcessor::IsCharacterDelimiter(char c)
		{
			return static_cast<bool>(
				'"' == c ||
				'{' == c ||
				'}' == c ||
				'[' == c ||
				']' == c ||
				':' == c ||
				',' == c ||
				' ' == c ||
				'\t' == c
				);
		}
		
		bool StringProcessor::IsStringInteger(char* str)
		{
			if (!str)
			{
				return false;
			}
			
			unsigned int strLength = strlen(str);
			
			if (0 == strLength)
			{
				return false;
			}
			
			unsigned int index = 0;
			
			for (index = 0; index < strLength; index++)
			{
				if (!('-' == str[index]) && !StringProcessor::IsCharacterNumeric(str[index]))
				{
					return false;
				}
			}
			
			for (index = 0; index < strLength; index++)
			{
				if ('-' == str[index])
				{
					return false;
				}
			}
			
			return true;
		}
		
		bool StringProcessor::IsStringFloat(char* str)
		{
			if (!str)
			{
				return false;
			}
			
			unsigned int strLength = strlen(str);
			
			if (0 == strLength)
			{
				return false;
			}
			
			unsigned int index = 0;
			
			for (index = 0; index < strLength; index++)
			{
				if (!('.' == str[index]) && !('-' == str[index]) && !StringProcessor::IsCharacterNumeric(str[index]))
				{
					return false;
				}
			}
			
			bool foundRadix = false;
			
			for (index = 0; index < strLength; index++)
			{
				if ('.' == str[index])
				{
					if (foundRadix)
					{
						return false;
					}
					else
					{
						foundRadix = true;
					}
				}
			}
			
			for (index = 0; index < strLength; index++)
			{
				if ('-' == str[index])
				{
					return false;
				}
			}
			
			if (foundRadix)
			{
				return true;
			}
			return false;
		}
		
		bool StringProcessor::IsStringWhiteSpace(char* str)
		{
			if (!str)
			{
				return false;
			}
			
			unsigned int strLength = strlen(str);
			
			if (0 == strLength)
			{
				return true;
			}
			
			for (unsigned int index = 0; index < strLength; index++)
			{
				if (!StringProcessor::IsCharacterWhiteSpace(str[index]))
				{
					return false;
				}
			}
			
			return true;
		}
		
		bool StringProcessor::IsStringIdentifier(char* str)
		{
			if (!str)
			{
				return false;
			}
			
			unsigned int strLength = strlen(str);
			
			if (0 == strLength)
			{
				return false;
			}
			
			if (str[0] >= '0' && str[0] <= '9')
			{
				// cannot start identifier with a number
				return false;
			}
			
			for (unsigned int index = 0; index < strLength; index++)
			{
				if (!StringProcessor::IsCharacterIdentifier(str[index]))
				{
					return false;
				}
			}
			
			return true;
		}
		
		char* StringProcessor::UCase(char* str)
		{
			char* iter;
			for (iter = str; *iter; ++iter)
			{
				*iter = toupper(*iter);
			}
			return str;
		}
		
		char* StringProcessor::LCase(char* str)
		{
			char* iter;
			for (iter = str; *iter; ++iter)
			{
				*iter = tolower(*iter);
			}
			return str;
		}
		
	} // end namespace
	
} // end namespace


