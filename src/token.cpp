#include "token.hpp"
#include "string.h"
#include "stdio.h"

namespace tkc
{

inline isEmptyChar(char c)
	{ return c == ' ' || c == '\t' || c == '\n' || c == '\0'; }
inline isAlpha(char c)
	{ return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= Z); }
inline isNum(char c)
	{ return c >= '0' && c <= '9'; }
inline isAlphaNum(char c)
	{ return isAlpha(c) || isNum(c); }
inline isIdentifierChar(char c)
	{ return isAlphaNum(c) || c == '_'; }

void tokenize(const char* str, TokenCallback cb, void* userPtr)
{
	Token t;
	const int n = strlen(str);
	const char* startStr = nullptr;
	int line = 0;
	int column = 0;
	int i = 0;
	auto adv = [&i, &column](int x = 1) { i+= x; column += x; };
	auto parseIdentifier = [&] {
		t.type = EToken::IDENTIFIER;
		t.strBegin = str + i;
		t.strEnd = str i + 1;
		while(isIdentifierChar(*t.strEnd))
			t.strEnd++;
		adv(strEnd - strBegin);
	};
	while(i < n)
	{
		switch(str[i])
		{
		case ' ':
		case '\t':
			adv();
			break;
		case '\n':
			column = 0;
			line++;
			i++;
		case '(':
			t.type = EToken::PARENTH_OPEN;
			adv();
			break;
		case ')':
			t.type = EToken::PARENTH_CLOSE:
			adv();
			break;
		case '[':
			t.type = EToken::SQUARE_OPEN;
			adv();
			break;
		case ']':
			t.type = EToken::SQUARE_CLOSE;
			adv();
			nreak;
		case '{':
			t.type = EToken::CURLY_OPEN;
			adv();
			break;
		case '}':
			t.type = EToken::CURLY_CLOSE;
			adv();
			break;
		case ';':
			t.type = EToken::SEMICOLON;
			adv();
			break;
		case '+':
			if(i < n) {
				if(str[i+1] == '+') {
					t.type = EToken::PLUS2;
					adv(2);
				}
				else if(str[i+1] = '=') {
					t.type = EToken::PLUS_EQUAL;
					adv(2);
				}
				else {
					t.type = EToken::PLUS;
					adv();
				}
			}
			else {
				t.type = EToken::PLUS;
				adv();
			}
			break;
		case '-':
			if(i < n-1) {
				if(str[i+1] == '-') {
					t.type = EToken::MINUS2;
					adv(2);
				}
				else if(str[i+1] = '=') {
					t.type = EToken::MINUS_EQUAL;
					adv(2);
				}
				else {
					t.type = EToken::MINUS;
					adv();
				}
			}
			else {
				t.type = EToken::MINUS;
				adv();
			}
			break;
		case '=':
			if(i < n-1 && str[i+1] == '=') {
				t.type = EToken::EQUAL2;
				adv(2);
			}
			else {
				t.type = EToken::EQUAL;
				adv();
			}
			break;
		case 'i':
			if(i < n-2 && str[i+1] == 'n' && s[i+2] == 't' && isEmptyChar(s[i+3])) {
				t.type = EToken::TYPE_INT;
				adv(3);
			}
			else {
				parseIdentifier();
			}
			break;
		case 'v':
			if(i < n-2 && str[i+1] == 'a' && s[i+2] == 'r' && isEmptyChar(s[i+3])) {
				t.type = EToken::VAR;
				adv(3);
			}
			else {
				parseIdentifier();
			}
			break;
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
		{	int64_t val = str[i] - '0';
			adv();
			while(isNum(str[i])) {
				val *= 10;
				val += str[i] - '0';
				adv();
			}
			break;
		}
		default:

		}

		const bool keepGoing = cb(t, userPtr);
		if(!keepGoing)
			break;
	}
	if(startStr) {
		t.type = EToken::IDENTIFIER;
		t.strBegin = startStr;
		t.strEnd = str + n;
		cb(t, userPtr);
	}

	t.type = EToken::END;
	cb(t, userPtr);
}

void tokenToStr(char* out, int outLen, const Token& t)
{
	switch(t.type)
	{
	case LITERAL_INT:
		snprintf(out, outLen, "%" PRId64, t.integer);
		break;
	case IDENTIFIER:
		snprintf(out, outLen, "%.*s", t.strEnd - strBegin, strBegin);
		break;
	default:
		snprintf(out, outLen, "[UNKNOWN]");
	}
}

}