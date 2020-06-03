#include <stdio.h>
#include "token.hpp"

const char* str = "a b c 10";

int main()
{
	tkc::tokenize(str,
	[](const tkc::Token& t, void* userData) -> bool
	{
		const int numChars = t.strEnd - t.strBegin;
		printf("%.*s\n", numChars, t.strBegin);
		return true;
	});
}