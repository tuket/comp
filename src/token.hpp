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
	SEMICOLON;

	PLUS, // +
	PLUS2, // ++
	PLUS_EQUAL, // +=
	MINUS, // -
	MINUS2, // --
	MINUS_EQUAL, // -=
	STAR, // *
	SLASH, // /
	EQUAL, // =
	EQUAL2

	VAR,
	TYPE_INT,
	TYPE_FLOAT,

	LITERAL_INT,
	LITERAL_REAL,
	LITERAL_STRING,

	IF,
	ELSE,

	IDENTIFIER,

	END,

	COUNT
};

struct Token
{
	EToken type;
	union {
		int64_t integer;
		// double lit_real;
		struct {
			const char* strBegin;
			const char* strEnd;
		};
	};
};

enum class ETokenizeError {
	NONE,
	ERR
};

typedef bool (*TokenCallback)(const Token&, void*);

void tokenize(const char* str, TokenCallback cb, void* userPtr = nullptr);

}