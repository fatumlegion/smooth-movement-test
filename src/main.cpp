#include "Application.hpp"

int main(int argc, char **argv)
{
	Application *p = Application::getSingleton();
	p->initialize();
	return p->run(argc, argv);
}