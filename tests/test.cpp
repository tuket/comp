#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "token.hpp"
#include "utils.hpp"

constexpr int BUFFER_SIZE = 4*1024;
static char buffer[BUFFER_SIZE];

constexpr tkc::Token makeExpectedToken(tkc::EToken type, const char* str = "")
{
	tkc::Token t = {};
	t.type = type;
	t.strBegin = str;
	t.strEnd = str + strlen(str);
	return t;
}

static bool isSame(tkc::Token t, tkc::Token e)
{
	if(t.type != e.type)
		return false;
	if(t.type == tkc::EToken::LITERAL_INT ||
	   t.type == tkc::EToken::LITERAL_REAL ||
	   t.type == tkc::EToken::LITERAL_STRING ||
	   t.type == tkc::EToken::IDENTIFIER)
	{
		const int tl = t.strEnd - t.strBegin;
		const int el = e.strEnd - e.strBegin;
		if(tl != el)
			return false;
		return memcmp(t.strBegin, e.strBegin, tl) == 0;
	}
	return true;
}

static void printExpectedVsGot(tkc::Token e, tkc::Token t)
{
	tkc::tokenToStr(buffer, BUFFER_SIZE, e);
	printf("\texpected: %s\n", buffer);
	tkc::tokenToStr(buffer, BUFFER_SIZE, t);
	printf("\tgot:      %s\n", buffer);
}

static const char* code_0 = {
R"CODE(
func (a int, b float) : float
{
	return float(a) + b;
}
)CODE"
};

static const tkc::Token expected_0[] =
{
	makeExpectedToken(tkc::EToken::FUNC),
	makeExpectedToken(tkc::EToken::PARENTH_OPEN),
	makeExpectedToken(tkc::EToken::IDENTIFIER, "a"),
	makeExpectedToken(tkc::EToken::TYPE_INT),
	makeExpectedToken(tkc::EToken::COMMA),
	makeExpectedToken(tkc::EToken::IDENTIFIER, "b"),
	makeExpectedToken(tkc::EToken::TYPE_FLOAT),
	makeExpectedToken(tkc::EToken::PARENTH_CLOSE),
	makeExpectedToken(tkc::EToken::COLON),
	makeExpectedToken(tkc::EToken::TYPE_FLOAT),
	makeExpectedToken(tkc::EToken::CURLY_OPEN),
	makeExpectedToken(tkc::EToken::RETURN),
	makeExpectedToken(tkc::EToken::TYPE_FLOAT),
	makeExpectedToken(tkc::EToken::PARENTH_OPEN),
	makeExpectedToken(tkc::EToken::IDENTIFIER, "a"),
	makeExpectedToken(tkc::EToken::PARENTH_CLOSE),
	makeExpectedToken(tkc::EToken::PLUS),
	makeExpectedToken(tkc::EToken::IDENTIFIER, "b"),
	makeExpectedToken(tkc::EToken::SEMICOLON),
	makeExpectedToken(tkc::EToken::CURLY_CLOSE),
	makeExpectedToken(tkc::EToken::END)
};

static void tokenizationTest(const char* code, tkc::Span<const tkc::Token> expected)
{
	enum class WhatToDo { PRINT = 1, TEST = 2 };
	constexpr WhatToDo whatToDo = WhatToDo::TEST;

	if(whatToDo == WhatToDo::PRINT)
	{
		tkc::tokenize(code,
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

		struct UserData {
			tkc::Span<const tkc::Token> expected;
			int i;
		};
		UserData userData { expected, i };
		tkc::tokenize(code,
		[](const tkc::Token& t, void* userData) -> bool
		{
			auto& expected = ((UserData*)userData)->expected;
			int& i = ((UserData*)userData)->i;
			if(i >= expected.size()) {
				printf("Tokenized test failed because it emitted more tokens than expected\n");
				return false;
			}
			const tkc::Token& e = expected[i];
			if(isSame(t, e)) {
				i++;
				//printExpectedVsGot(e, t);
				return true;
			}
			printf("Tokenizer test failed at token (%d)\n", i);
			printExpectedVsGot(e, t);
			return false;
		}, &userData);

		if(i == expected.size()) {
			printf("Tokenizer test passed OK!\n");
		}
		else {
			printf("Tokenizer test FAILED!\n");
			printf("\texpected token count: %d\n", expected.size());
			printf("\tgot token count:      %d\n", i);
		}
	}
	else {
		assert(false);
	}
}

void tokenizationTests()
{
	tokenizationTest(code_0, expected_0);
}

int main()
{
	tokenizationTests();
}