// SourceLine class member-function definitions.

#include <iostream>
using std::cout;

#include "SourceLine.h" // SourceLine class definition

SourceLine::SourceLine()
   : sourceLine()
{
}

SourceLine& SourceLine::operator=( const char * const ptr )
{
   sourceLine = ptr;
   return *this;
}

void SourceLine::delComments()
{
	for (size_t i = 0; i < sourceLine.size(); i++)
		if (sourceLine[i] == '/')
			sourceLine.erase(i);
}

void SourceLine::delStrConst()
{
	for (size_t i = 0; i < sourceLine.size(); i++)
		if (sourceLine[i] == char(34))  //char(34) == "
		{
			size_t j = sourceLine.find(char(34), i + 1);
			sourceLine.erase(i, j - i + 1);
		}
}

void SourceLine::delCharConst()
{
	for (size_t i = 0; i < sourceLine.size(); i++)
		if (sourceLine[i] == char(39))  //char(39) == '
		{
			size_t j = sourceLine.find(char(39), i + 1);
			sourceLine.erase(i, j - i + 1);
		}
}

void SourceLine::extractIdentifiers( vector< Identifier > &identifiers )
{
	//cout << sourceLine << "\n";

	Identifier temp;
	
	for (size_t i = 0, j = 0; i < sourceLine.size() ; i++)
		if ((sourceLine[i] >= char(97) && sourceLine[i] <= char(122)) || (sourceLine[j] >= char(65) && sourceLine[j] <= char(90))
			|| (sourceLine[j] >= char(48) && sourceLine[j] <= char(57)) || sourceLine[j] == char(95))
		{
			j = i;
			while ((sourceLine[j] >= char(97) && sourceLine[j] <= char(122)) || (sourceLine[j] >= char(65) && sourceLine[j] <= char(90))
				|| (sourceLine[j] >= char(48) && sourceLine[j] <= char(57)) || sourceLine[j] == char(95))
				j++;

			temp = sourceLine.substr(i, j);
			i = j;

			//cout << temp << "\n";     //有關s開頭的都不見了

			if(!temp.keyword())
				identifiers.insert(identifiers.end(), temp);
		}
}

bool operator==( const SourceLine &lhs, const SourceLine &rhs )
{
   return lhs.sourceLine == rhs.sourceLine;
}

bool operator!=( const SourceLine &lhs, const SourceLine &rhs )
{
   return !( lhs == rhs );
}