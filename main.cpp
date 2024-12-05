#include "Builder.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
	Builder	builder;
	int		i;

	i = 1;
	while (i < argc)
		builder.setup(argv[i++]);
	if (argc == 1)
	{
		builder.setup();
		builder.setup_makefile();
		builder.setup_main();
	}
	std::cout << std::endl;
	if (builder.get_is_path_defined())
		std::cout << "Files created in " GREEN << builder.get_path() << RESET " :" << std::endl;
	else
		std::cout << "Files created in " << GREEN "current directory" RESET << " :" << std::endl;
	for (i = 0; i < ARRAY_LIMIT; i++)
	{
		if (builder.get_array_member(i).empty())
			break;
		std::cout << "- " << builder.get_array_member(i) << ".hpp/.cpp\n";
	}
	if (builder.get_is_makefile_created())
		std::cout << builder.get_makefile() << std::endl;
	if (builder.get_is_main_created())
		std::cout << builder.get_main() << std::endl;
	return 0;
}
