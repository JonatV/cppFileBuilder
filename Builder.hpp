#ifndef BUILDER_HPP
#define BUILDER_HPP

#include <string>

#define ARRAY_LIMIT			666
#define RESET				"\033[0m"
#define RED					"\033[31m"
#define GREEN				"\033[1;32m" 
#define YELLOW				"\033[4;33m"
#define BLUE				"\033[1;34m"
#define MAGENTA				"\033[1;35m"	// makefile
#define CYAN				"\033[1;36m"	// main.cpp
#define WHITE				"\033[37m"

#define MSG_PATH			"Enter " GREEN "PATH" RESET " \e[2m(or press Enter for current dir)" RESET ": "
#define MSG_CL				"Enter the " GREEN "CLASS name" RESET " \e[2m(press Enter to stop)" RESET ": "
#define MSG_PRJCT			"Enter the " GREEN "PROJECT name" RESET ": "
#define MSG_MK_NCL			YELLOW "No class" RESET " created, create " MAGENTA "Makefile" RESET "? (y/n): "
#define MSG_MK_OVWRT		MAGENTA "Makefile" RESET " found, overwrite it? (y/n): "
#define MSG_MK_CREATE		"Create " MAGENTA "Makefile" RESET "? (y/n): "
#define MSG_MAIN_NCL		YELLOW "No class" RESET " created, create " CYAN "main.cpp" RESET "? (y/n): "
#define MSG_MAIN_OVRWRT		CYAN "main.cpp" RESET " found, overwrite it? (y/n): "
#define MSG_MAIN_CREATE		"Create " CYAN "main.cpp" RESET "? (y/n): "
#define ERR_OPEN			RED "Unable to open file" RESET
#define ERR_TOO_MANY		RED "Error: too many classes" RESET

class Builder
{
	private:
		std::string	_class_name;
		std::string	_path;
		std::string	_header_name;
		std::string	_cpp_name;
		std::string	_makefile;
		std::string	_project_name;
		std::string	_main;
		std::string	_class_array[ARRAY_LIMIT];
		bool		_isPathDefined;
		bool		_isMakefileCreated;
		bool		_isMainCreated;

	// Private functions
		// utils
		std::string	to_upper(const std::string &str);
		void		open_file(std::ofstream &f, const std::string &filename);
		bool		directory_exists(const std::string &path);
		void		create_directory(const std::string &path);
		void		add_class_to_array(const std::string &class_name);
		// create
		void		create_cpp();
		void		create_header();
		void		create_hpp_cpp();
		void		create_makefile();
		void		create_main();
	
	public:
	// Constructors and destructors
		Builder();
		~Builder();

	// Public functions
		void		setup();
		void		setup(const std::string &class_name);
		void		setup_makefile();
		void		setup_main();
	// Setters
		void		set_class_name(const std::string &);
		void		set_path(const std::string &);
		void		set_header_name(const std::string &);
		void		set_cpp_name(const std::string &);
		void		set_is_path_defined(bool isPathDefined);
		void		set_project_name(const std::string &);
		void		set_is_makefile_created(bool isMakefileCreated);
		void		set_is_main_created(bool isMainCreated);
	// Getters
		std::string	get_class_name() const;
		std::string	get_path() const;
		std::string	get_header_name() const;
		std::string	get_cpp_name() const;
		std::string	get_makefile() const;
		std::string	get_main() const;
		std::string	get_array_member(int i) const;
		std::string	get_project_name() const;
		bool		get_is_path_defined() const;
		bool		get_is_makefile_created() const;
		bool		get_is_main_created() const;
};

#endif
