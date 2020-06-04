#include "token.hpp"
#include <string.h>
#include <stdio.h>
#include <assert.h>

namespace tkc
{

inline bool isEmptyChar(char c)
	{ return c == ' ' || c == '\t' || c == '\n' || c == '\0'; }
inline bool isAlpha(char c)
	{ return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
inline bool isNum(char c)
	{ return c >= '0' && c <= '9'; }
inline bool isAlphaNum(char c)
	{ return isAlpha(c) || isNum(c); }
inline bool isAlphaUnd(char c)
	{ return isAlpha(c) || c == '_'; }
	inline bool isAlphaNumUnd(char c)
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
	auto parseIdentifier = [&]() {
		t.type = EToken::IDENTIFIER;
		t.strBegin = str + i;
		t.strEnd = str + i + 1;
		while(isAlphaNumUnd(*t.strEnd))
			t.strEnd++;
		adv(t.strEnd - t.strBegin);
	};
	auto parseNumericLiteral = [&]() {
		t.strBegin = str + i;
		t.strEnd = str + i + 1;
		while(isNum(*t.strEnd))
			t.strEnd++;
		if(*t.strEnd == '.') {
			while(isNum(*t.strEnd))
				t.strEnd++;
			if(isAlphaUnd(*t.strEnd))
				t.type = EToken::ERROR;
			else
				t.type = EToken::LITERAL_REAL;
		}
		else if(isAlphaUnd(*t.strEnd)) {
			t.type = EToken::ERROR;
		}
		else {
			t.type = EToken::LITERAL_INT;
		}
		adv(t.strEnd - t.strBegin);
	};
	while(i < n)
	{
		switch(str[i])
		{
		case ' ':
		case '\t':
			t.type = EToken::NONE;
			adv();
			break;
		case '\n':
			t.type = EToken::NONE;
			column = 0;
			line++;
			i++;
			break;
		case '(':
			t.type = EToken::PARENTH_OPEN;
			adv();
			break;
		case ')':
			t.type = EToken::PARENTH_CLOSE;
			adv();
			break;
		case '[':
			t.type = EToken::SQUARE_OPEN;
			adv();
			break;
		case ']':
			t.type = EToken::SQUARE_CLOSE;
			adv();
			break;
		case '{':
			t.type = EToken::CURLY_OPEN;
			adv();
			break;
		case '}':
			t.type = EToken::CURLY_CLOSE;
			adv();
			break;
		case ',':
			t.type = EToken::COMMA;
			adv();
			break;
		case '.':
			t.type = EToken::DOT;
			adv();
			break;
		case ':':
			t.type = EToken::COLON;
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
				else if(str[i+1] == '=') {
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
				else if(str[i+1] == '=') {
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
		case 'b':
			if(i < n-4 && str[i+1] == 'r' &&
						  str[i+2] == 'e' &&
						  str[i+3] == 'a' &&
						  str[i+4] == 'k' &&
						  isEmptyChar(str[i+5]))
			{
				t.type = EToken::BREAK;
				adv(5);
			}
			else {
				parseIdentifier();
			}
			break;
		case 'c':
			if(i < n-7 && str[i+1] == 'o' &&
						  str[i+2] == 'n' &&
						  str[i+3] == 't' &&
						  str[i+4] == 'i' &&
						  str[i+5] == 'n' &&
						  str[i+6] == 'u' &&
						  str[i+7] == 'e' &&
						  isEmptyChar(str[i+8]))
			{
				t.type = EToken::CONTINUE;
				adv(8);
			}
			else {
				parseIdentifier();
			}
			break;
		case 'i':
			if(i < n-1 && str[i+1] == 'f' && isEmptyChar(str[i+2])) {
				t.type = EToken::IF;
				adv(2);
			}
			else if(i < n-2 && str[i+1] == 'n' &&
							   str[i+2] == 't' &&
							   isEmptyChar(str[i+3]))
			{
				t.type = EToken::TYPE_INT;
				adv(3);
			}
			else {
				parseIdentifier();
			}
			break;
		case 'f':
			if(i < n-3 && str[i+1] == 'u' &&
						  str[i+2] == 'n' &&
						  str[i+3] == 'c' &&
						  isEmptyChar(str[i+4]))
			{
				t.type = EToken::FUNC;
				adv(4);
			}
			else {
				parseIdentifier();
			}
			break;
		case 'v':
			if(i < n-2 && str[i+1] == 'a' &&
						  str[i+2] == 'r' &&
						  isEmptyChar(str[i+3])) {
				t.type = EToken::VAR;
				adv(3);
			}
			else {
				parseIdentifier();
			}
			break;
		case 'r':
			if(i < n-5 && str[i+1] == 'e' &&
						  str[i+2] == 't' &&
						  str[i+3] == 'u' &&
						  str[i+4] == 'r' &&
						  str[i+5] == 'n' &&
						  isEmptyChar(str[i+6]))
			{
				t.type = EToken::RETURN;
				adv(6);
			}
			else {
				parseIdentifier();
			}
			break;
		default:
			if(isNum(str[i]))
				parseNumericLiteral();
			else if(isAlphaUnd(str[i]))
				parseIdentifier();
			else
				assert(false);
		}

		if(t.type != EToken::NONE) {
			const bool keepGoing = cb(t, userPtr);
			if(!keepGoing)
				break;
		}
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
	auto tokenPrint = [&](const char* type) {
		snprintf(out, outLen, "%s(%.*s)",
			type, int(t.strEnd - t.strBegin), t.strBegin);
	};
	auto print = [&](const char* str) {
		snprintf(out, outLen, "%s" ,str);
	};
	switch(t.type)
	{
	case EToken::PARENTH_OPEN:
		print("(");
		break;
	case EToken::PARENTH_CLOSE:
		print(")");
		break;
	case EToken::SQUARE_OPEN:
		print("[");
		break;
	case EToken::SQUARE_CLOSE:
		print("]");
		break;
	case EToken::CURLY_OPEN:
		print("{");
		break;
	case EToken::CURLY_CLOSE:
		print("}");
		break;
	case EToken::COMMA:
		print(",");
		break;
	case EToken::DOT:
		print(".");
		break;
	case EToken::COLON:
		print(":");
		break;
	case EToken::SEMICOLON:
		print(";");
		break;
	case EToken::PLUS:
		print("+");
		break;
	case EToken::PLUS2:
		print("++");
		break;
	case EToken::PLUS_EQUAL:
		print("+=");
		break;
	case EToken::MINUS:
		print("-");
		break;
	case EToken::MINUS2:
		print("--");
		break;
	case EToken::MINUS_EQUAL:
		print("-=");
		break;
	case EToken::STAR:
		print("*");
		break;
	case EToken::SLASH:
		print("/");
		break;
	case EToken::EQUAL:
		print("=");
		break;
	case EToken::EQUAL2:
		print("==");
		break;
	case EToken::VAR:
		print("var");
		break;
	case EToken::FUNC:
		print("func");
		break;
	case EToken::TYPE_INT:
		print("int");
		break;
	case EToken::TYPE_FLOAT:
		print("float");
		break;
	case EToken::LITERAL_INT:
		tokenPrint("LITERAL_INT");
		break;
	case EToken::LITERAL_REAL:
		tokenPrint("LITERAL_REAL");
		break;
	case EToken::LITERAL_STRING:
		tokenPrint("LITERAL_STRING");
		break;
	case EToken::IF:
		print("if");
		break;
	case EToken::ELSE:
		print("else");
		break;
	case EToken::RETURN:
		print("return");
		break;
	case EToken::BREAK:
		print("break");
		break;
	case EToken::CONTINUE:
		print("continue");
		break;
	case EToken::IDENTIFIER:
		tokenPrint("IDENTIFIER");
		break;
	case EToken::ERROR:
		print("ERROR");
		break;
	case EToken::END:
		print("END");
		break;
	default:
		snprintf(out, outLen, "[UNKNOWN]");
	}
}

}