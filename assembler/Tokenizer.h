
// CODESTYLE: v2.0

// Tokenizer.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: classes that implement a simple string tokenizer and support parsing functions

#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <string>
#include <vector>

namespace VCOMP
{
	class Tokenizer
	{
	public:
		/**
		 * Splits a string into tokens delimited by the given \a delimiters
		 * @param source a C++-string to be split
		 * @param delimiters a C++-string of characters to split by
		 * \return an STL vector of C++-strings holding each token in the string \a source
		 */
		static std::vector<std::string> Tokenize(const std::string& source, const std::string& delimiters);
		
	private:
		Tokenizer();
	}; // end class
	
	namespace PARSING
	{
		class StringProcessor
		{
		public:
			static bool IsCharacterNumeric(char c);
			static bool IsCharacterWhiteSpace(char c);
			static bool IsCharacterIdentifier(char c);
			static bool IsCharacterDelimiter(char c);
			static bool IsStringInteger(char* str);
			static bool IsStringFloat(char* str);
			static bool IsStringWhiteSpace(char* str);
			static bool IsStringIdentifier(char* str);
			
		private:
			StringProcessor();
		};
	} // end namespace

} // end namespace
#endif


