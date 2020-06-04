#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "token.hpp"
#include "utils.hpp"

constexpr int BUFFER_SIZE = 4*1024;
static char buffer[BUFFER_SIZE];

const char* str =
R"CODE(
func (a int, b float) : float
{
	return float(a) + b;
}
)CODE";

struct ExpectedToken
{
	tkc::EToken type;
	const char* str;
};

static bool isSame(tkc::Token t, ExpectedToken e)
{
	if(t.type != e.type)
		return false;
	if(t.type == tkc::EToken::LITERAL_INT ||
	   t.type == tkc::EToken::LITERAL_REAL ||
	   t.type == tkc::EToken::LITERAL_STRING ||
	   t.type == tkc::EToken::IDENTIFIER)
	{
		const int tl = t.strEnd - t.strBegin;
		const int el = strlen(e.str);
		if(tl != el)
			return false;
		return memcmp(t.strBegin, e.str, tl);
	}
	return true;
}

static const ExpectedToken expected[] = {
	{tkc::EToken::FUNC},
	{tkc::EToken::PARENTH_OPEN},
	{tkc::EToken::IDENTIFIER, "a"},
	{tkc::EToken::TYPE_INT},
	{tkc::EToken::COMMA},
	{tkc::EToken::IDENTIFIER, "b"},
	{tkc::EToken::TYPE_FLOAT},
	{tkc::EToken::PARENTH_CLOSE},
	{tkc::EToken::COLON},
	{tkc::EToken::TYPE_FLOAT},
	{tkc::EToken::CURLY_OPEN},
	{tkc::EToken::RETURN},
	{tkc::EToken::TYPE_FLOAT},
	{tkc::EToken::PARENTH_OPEN},
	{tkc::EToken::IDENTIFIER, "a"},
	{tkc::EToken::PARENTH_CLOSE},
	{tkc::EToken::PLUS},
	{tkc::EToken::IDENTIFIER, "b"},
	{tkc::EToken::SEMICOLON},
	{tkc::EToken::CURLY_CLOSE},
	{tkc::EToken::END}
};

int main()
{
	enum class WhatToDo { PRINT, TEST };
	constexpr WhatToDo whatToDo = WhatToDo::TEST;

	if(whatToDo == WhatToDo::PRINT)
	{
		tkc::tokenize(str,
		[](const tkc::Token& t, void* userData) -> bool
		{
			const int numChars = t.strEnd - t.strBegin;
			tokenToStr(buffer, BUFFER_SIZE, t);
			printf("%s\n", buffer);
			return true;
		});
	}
	else if(whatToDo == WhatToDo::TEST)
	{
		int i = 0;

		tkc::tokenize(str,
		[](const tkc::Token& t, void* userData) -> bool
		{
			const int n = tkc::size(expected);
			int& i = *(int*)userData;
			if(i >= n) {
				printf("Tokenized test failed because it emitted more tokens than expected\n");
				return false;
			}
			const ExpectedToken& e = expected[i];
			if(isSame(t, e)) {
				i++;
				return true;
			}

			printf("Tokenizer test failed at token (%d)\n", i);
			return false;
		}, &i);

		if(i == tkc::size(expected)) {
			printf("Tokenizer test passed OK!\n");
		}
		else {
			printf("Tokenizer test FAILED!\n");
		}
	}
	else {
		assert(false);
	}
}