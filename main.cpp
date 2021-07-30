#include "world/chunk.h"
#include <vector>

int main()
{
	std::vector<chunk> chunkarr = chunk::create_chunks(0,0); // temp - 0,0. coords will be put based on camera later
	return 0;
}