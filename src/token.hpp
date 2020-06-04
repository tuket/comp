#pragma once

#include <stdint.h>

namespace tkc
{

enum class EToken
{
	PARENTH_OPEN,
	PARENTH_CLOSE,
	SQUARE_OPEN,
	SQUARE_CLOSE,
	CURLY_OPEN,
	CURLY_CLOSE,
	COMMA,
	DOT,
	COLON,
	SEMICOLON,

	PLUS, // +
	PLUS2, // ++
	PLUS_EQUAL, // +=
	MINUS, // -
	MINUS2, // --
	MINUS_EQUAL, // -=
	STAR, // *
	SLASH, // /
	EQUAL, // =
	EQUAL2,

	VAR,
	FUNC,
	TYPE_INT,
	TYPE_FLOAT,

	LITERAL_INT,
	LITERAL_REAL,
	LITERAL_STRING,

	IF,
	ELSE,
	RETURN,
	BREAK,
	CONTINUE,

	IDENTIFIER,

	ERROR,

	END,

	NONE,
	COUNT
};

struct Token
{
	EToken type;
	const char* strBegin;
	const char* strEnd;
};

enum class ETokenizeError {
	NONE,
	ERR
};

typedef bool (*TokenCallback)(const Token&, void*);

void tokenize(const char* str, TokenCallback cb, void* userPtr = nullptr);

void tokenToStr(char* out, int outLen, const Token& t);

}