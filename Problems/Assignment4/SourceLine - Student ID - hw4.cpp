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


}

void SourceLine::delStrConst()
{


}

void SourceLine::delCharConst()
{


}

void SourceLine::extractIdentifiers( vector< Identifier > &identifiers )
{


}

bool operator==( const SourceLine &lhs, const SourceLine &rhs )
{
   return lhs.sourceLine == rhs.sourceLine;
}

bool operator!=( const SourceLine &lhs, const SourceLine &rhs )
{
   return !( lhs == rhs );
}