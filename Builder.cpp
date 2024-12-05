#include "Builder.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdlib>

Builder::Builder() : _makefile("Makefile"), _main("main.cpp") , _isPathDefined(false), _isMakefileCreated(false), _isMainCreated(false)
{
	// std::cout << "\e[2mDefault constructor Builder called\e[0m" << std::endl;
}

Builder::~Builder()
{
	// std::cout << "\e[2mDestructor Builder called\e[0m" << std::endl;
}

void	Builder::setup()
{
	std::string	path;
	std::string	class_name;

	std::cout << MSG_PATH;
	std::getline(std::cin, path);
	if (!(path.empty()))
	{
		this->set_is_path_defined(true);
		this->set_path(path + "/");
	}
	while (true)
	{
		std::cout << MSG_CL;
		std::getline(std::cin, class_name);
		if (class_name.empty())
			break;
		class_name[0] = toupper(class_name[0]);
		this->set_class_name(class_name);
		this->create_hpp_cpp();
		this->add_class_to_array(class_name);
	}
}

void	Builder::setup(const std::string &class_name)
{
	std::string	modified_class_name;
	
	modified_class_name = class_name;
	modified_class_name[0] = toupper(modified_class_name[0]);
	this->set_class_name(modified_class_name);
	this->create_hpp_cpp();
	this->add_class_to_array(modified_class_name);
}

void	Builder::create_header()
{
	std::ofstream	f;

	this->set_header_name(this->get_class_name() + ".hpp");
	open_file(f, this->get_header_name());
	if (f.is_open())
	{
		f << "#ifndef " << this->to_upper(this->get_class_name()) << "_HPP\n";
		f << "#define " << this->to_upper(this->get_class_name()) << "_HPP\n\n";
		f << "#include <string>\n\n";
		f << "class " << this->get_class_name() << "\n";
		f << "{\n";
		f << "	private:\n";
		f << "		\n";
		f << "	public:\n";
		f << "	// Constructor\n";
		f << "		" << this->get_class_name() << "();\n\n";
		f << "	// Parameterized constructor\n";
		f << "		\n";
		f << "	// Copy constructor\n";
		f << "		" << this->get_class_name() << "(" << this->get_class_name() << " const &);\n";
		f << "		\n";
		f << "	// Destructor\n";
		f << "		~" << this->get_class_name() << "();\n";
		f << "		\n";
		f << "	// Overloads\n";
		f << "		" << this->get_class_name() << "	&operator=(" << this->get_class_name() << " const &);\n";
		f << "		\n";
		f << "	// Member functions\n";
		f << "		\n";
		f << "	// Getters\n";
		f << "		\n";
		f << "	// Setters\n";
		f << "		\n";
		f << "};\n\n";
		f << "#endif\n";
		f.close();
	}
	else
		std::cerr << ERR_OPEN << std::endl;
}

void	Builder::create_cpp()
{
	std::ofstream	f;

	this->set_cpp_name(this->get_class_name() + ".cpp");
	open_file(f, this->get_cpp_name());
	if (f.is_open())
	{
		f << "#include \"" << this->get_class_name() << ".hpp\"\n\n";
		f << "#include <iostream>\n\n";
		f << "// Constructor\n";
		f << this->get_class_name() << "::" << this->get_class_name() << "()\n";
		f << "{\n";
		f << "	std::cout << \"\\e[2mDefault constructor " << this->get_class_name() << " called\\e[0m\" << std::endl;\n";
		f << "}\n\n";
		f << "// Parameterized constructor\n";
		f << "// " << this->get_class_name() << "::" << this->get_class_name() << "()\n";
		f << "// {\n";
		f << "// 	std::cout << \"\\e[2mParameterized constructor " << this->get_class_name() << " called\\e[0m\" << std::endl;\n";
		f << "// }\n\n";
		f << "// Copy constructor\n";
		f << this->get_class_name() << "::" << this->get_class_name() << "(" << this->get_class_name() << " const &)\n";
		f << "{\n";
		f << "	std::cout << \"\\e[2mCopy constructor " << this->get_class_name() << " called\\e[0m\" << std::endl;\n";
		f << "}\n\n";
		f << "// Destructor\n";
		f << this->get_class_name() << "::~" << this->get_class_name() << "()\n";
		f << "{\n";
		f << "	std::cout << \"\\e[2mDestructor " << this->get_class_name() << " called\\e[0m\" << std::endl;\n";
		f << "}\n\n";
		f << "// Overloads\n";
		f << this->get_class_name() << "	&" << this->get_class_name() << "::operator=(" << this->get_class_name() << " const &)\n";
		f << "{\n";
		f << "	std::cout << \"\\e[2mAssignation operator " << this->get_class_name() << " called\\e[0m\" << std::endl;\n";
		f << "	return (*this);\n";
		f << "}\n\n";
		f << "// Member functions\n\n";
		f << "// Getters\n\n";
		f << "// Setters\n";
		f.close();
	}
	else
		std::cerr << ERR_OPEN << std::endl;
}

void	Builder::create_makefile()
{
	std::ofstream	f;
	std::string		project_name;
	int				i;

	std::cout << MSG_PRJCT;
	std::getline(std::cin, project_name);
	this->set_project_name(project_name);
	open_file(f, this->get_makefile());
	if (f.is_open())
	{
		f << "SRCS = main.cpp";
		i = 0;
		while(i < ARRAY_LIMIT)
		{
			if (this->_class_array[i].empty())
				break;
			f << " " << this->_class_array[i++] << ".cpp";
		}
		f << "\n";
		f << "NAME = " << this->get_project_name() << "\n";
		f << "CC = clang++\n";
		f << "CFLAGS = -Wall -Wextra -Werror\n";
		f << "STD = -std=c++98\n";
		f << "ifdef DEV\n";
		f << "	DEV_FLAGS = -g3 -fsanitize=address\n";
		f << "else\n";
		f << "	DEV_FLAGS =\n";
		f << "endif\n";
		f << "\n";
		f << "OBJS = $(SRCS:.cpp=.o)\n";
		f << "\n";
		f << "all: $(NAME)\n";
		f << "\n";
		f << "$(NAME): $(OBJS)\n";
		f << "	$(CC) $(CFLAGS) $(STD) $(DEV_FLAGS) $(OBJS) -o $(NAME)\n";
		f << "# ./$(NAME)\n";
		f << "\n";
		f << "%.o: %.cpp\n";
		f << "	$(CC) $(CFLAGS) $(STD) $(DEV_FLAGS) -c $< -o $@\n";
		f << "\n";
		f << "clean:\n";
		f << "	rm -f $(OBJS)\n";
		f << "fclean : clean\n";
		f << "	rm -f $(NAME)\n";
		f << "re: fclean all\n";
		f << ".PHONY: all clean fclean re\n";
		f.close();
	}
	else
		std::cerr << ERR_OPEN << std::endl;
}

void	Builder::create_main()
{
	std::ofstream	f;
	int				i;

	open_file(f, this->get_main());
	if (f.is_open())
	{
		i = 0;
		while(i < ARRAY_LIMIT)
		{
			if (this->_class_array[i].empty())
				break;
			f << "#include \"" << this->_class_array[i++] << ".hpp\"\n";
		}
		f << "\n";
		f << "#include <iostream>\n";
		f << "#include <string>\n\n";
		f << "int	main(int argc, char *argv[])\n";
		f << "{\n";
		f << "	(void)argc;\n";
		f << "	(void)argv;\n";
		f << "	\n";
		f << "	return 0;\n";
		f << "}\n";
		f.close();
	}
	else
		std::cerr << ERR_OPEN << std::endl;
}


void	Builder::create_hpp_cpp()
{
	this->create_header();
	this->create_cpp();
}

std::string	Builder::to_upper(const std::string &str)
{
	std::string	upper;
	size_t		i;

	i = 0;
	while (i < str.length())
		upper += toupper(str[i++]);
	return (upper);
}

void	Builder::open_file(std::ofstream &f, const std::string &filename)
{
	std::string	modified_filename;

	modified_filename = filename;
	if (this->get_is_path_defined())
	{
		if (!directory_exists(this->get_path()))
			create_directory(this->get_path());
		modified_filename = this->get_path() + filename;
	}
	f.open(modified_filename.c_str());
}

bool	Builder::directory_exists(const std::string &path)
{
	struct stat	info_dir;

	if (stat(path.c_str(), &info_dir) != 0)
		return (false);
	else if (info_dir.st_mode & S_IFDIR)
		return (true);
	else
		return (false);
}

void	Builder::create_directory(const std::string &path)
{
	if (mkdir(path.c_str(), 0755) == -1)
	{
		std::cerr << RED "Error :" << path << ": failed to create directory" RESET << std::endl;
		exit(1);
	}
}

void	Builder::add_class_to_array(const std::string &class_name)
{
	static int	i = 0;
	if (i == ARRAY_LIMIT)
	{
		std::cerr << ERR_TOO_MANY << std::endl;
		exit(1);
	}
	this->_class_array[i] = class_name;
	i++;
}

void	Builder::setup_makefile()
{
	bool			noClassCreated;
	std::string		answer;
	std::string		file_path;
	std::ifstream	f;

	noClassCreated = this->get_array_member(0).empty();
	if (noClassCreated)
	{
		std::cout << MSG_MK_NCL;
		std::getline(std::cin, answer);
		if (answer != "y")
			return;
	}
	file_path = this->get_path() + this->get_makefile();
	f.open(file_path.c_str());
	if (f.good())
	{
		std::cout << MSG_MK_OVWRT;
		std::getline(std::cin, answer);
		f.close();
		if (answer != "y")
			return;
		this->set_is_makefile_created(true);
		this->create_makefile();
	}
	else
	{
		if (!noClassCreated)
		{
			std::cout << MSG_MK_CREATE;
			std::getline(std::cin, answer);
			if (answer != "y")
				return;
		}
		this->set_is_makefile_created(true);
		this->create_makefile();
	}
}

void Builder::setup_main()
{
	std::string		answer;
	std::ifstream	f;
	bool			noClassCreated;

	noClassCreated = this->get_array_member(0).empty();
	if (noClassCreated)
	{
		std::cout << MSG_MAIN_NCL;
		std::getline(std::cin, answer);
		if (answer != "y")
			return;
	}
	f.open((this->get_path() + this->get_main()).c_str());
	if (f.good())
	{
		std::cout << MSG_MAIN_OVRWRT;
		f.close();
		std::getline(std::cin, answer);
		if (answer != "y")
			return;
		this->set_is_main_created(true);
		this->create_main();
	}
	else
	{
		if (!noClassCreated)
		{
			std::cout << MSG_MAIN_CREATE;
			std::getline(std::cin, answer);
			if (answer != "y")
				return;
		}
		this->set_is_main_created(true);
		this->create_main();
	}
}

//setters
void Builder::set_class_name(const std::string &class_name)
{
	this->_class_name = class_name;
}

void Builder::set_path(const std::string &path)
{
	this->_path = path;
}

void Builder::set_header_name(const std::string &header_name)
{
	this->_header_name = header_name;
}

void Builder::set_cpp_name(const std::string &cpp_name)
{
	this->_cpp_name = cpp_name;
}

void Builder::set_project_name(const std::string &project_name)
{
	this->_project_name = project_name;
}

void Builder::set_is_path_defined(bool isPathDefined)
{
	this->_isPathDefined = isPathDefined;
}

void Builder::set_is_makefile_created(bool isMakefileCreated)
{
	this->_isMakefileCreated = isMakefileCreated;
}

void Builder::set_is_main_created(bool isMainCreated)
{
	this->_isMainCreated = isMainCreated;
}

//getters
std::string Builder::get_class_name() const
{
	return (this->_class_name);
}

std::string Builder::get_path() const
{
	return (this->_path);
}

std::string Builder::get_header_name() const
{
	return (this->_header_name);
}

std::string Builder::get_cpp_name() const
{
	return (this->_cpp_name);
}

std::string Builder::get_makefile() const
{
	return (this->_makefile);
}

std::string Builder::get_main() const
{
	return (this->_main);
}

std::string Builder::get_project_name() const
{
	return (this->_project_name);
}

std::string Builder::get_array_member(int i) const
{
	return (this->_class_array[i]);
}

bool Builder::get_is_path_defined() const
{
	return (this->_isPathDefined);
}

bool Builder::get_is_makefile_created() const
{
	return (this->_isMakefileCreated);
}

bool Builder::get_is_main_created() const
{
	return (this->_isMainCreated);
}
