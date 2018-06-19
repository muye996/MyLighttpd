#include "Master.h"
#include "Worker.h"

#include <iostream>

int main(int argc, char * argv[])
{
	Master master;
	std::cout << "----Slighttpd----" << std::endl;
	if (!master.StartMaster())
		return -1;
	std::cout << "----Goodbye----" << std::endl;
	return 0;
}
