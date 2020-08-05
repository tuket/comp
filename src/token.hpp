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
	STAR_EQUAL, // *=
	SLASH, // /
	SLASH_EQUAL, // /=
	PERCENT, // %
	PERCENT_EQUAL, // %=
	EQUAL, // =
	EQUAL2, // ==
	LOWER, // <
	GREATER, // >
	LOWER_OR_EQUAL, // <=
	GREATER_OR_EQUAL, // >=
	NOT, // !
	NOT_EQUAL, // !=
	AND, // &
	AND_EQUAL, // &=
	AND2, // &&
	AND2_EQUAL, // &&=
	OR, // |
	OR_EQUAL, // |=
	OR2, // ||
	OR2_EQUAL, // ||=
	XOR, // ^
	XOR_EQUAL, // ^=
	LEFT_SHIFT, // <<
	LEFT_SHIFT_EQUAL, // <<=
	RIGHT_SHIFT, // >>
	RIGHT_SHIFT_EQUAL, // <<=

	VAR,
	FUNC,
	TYPE_INT,
	TYPE_FLOAT,

	LITERAL_INT,
	LITERAL_REAL,
	LITERAL_STRING,
	LITERAL_CHAR,

	IF,
	ELSE,
	WHILE,
	FOR,
	RETURN,
	BREAK,
	CONTINUE,

	IDENTIFIER,

	COMMENT,

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