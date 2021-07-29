#include "main.h"
#include "chunk.h"
#include "constants.h"
#include <iostream>
int main()
{
	constants con;
	chunk c;
	std::vector<chunk> chunkarr = c.create_chunks();
	return 0;
}