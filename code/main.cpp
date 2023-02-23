
#include "Core.h"

int main() {
	srand((unsigned int)time(0));

	if (!GET_SINGLE(CCore)->Init()) {
		DESTROY_SINGLE(CCore);
		return 0;
	}

	GET_SINGLE(CCore)->Run();

	DESTROY_SINGLE(CCore);

	return 0;
}