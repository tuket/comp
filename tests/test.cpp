#include <stdio.h>
#include "token.hpp"

const char* str =
R"CODE(
func (a int, b float) : float
{
	return float(a) + b
}
)CODE";
constexpr int BUFFER_SIZE = 4*1024;
static char buffer[BUFFER_SIZE];

int main()
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