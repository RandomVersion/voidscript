#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <ostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include <map>

#define version 1.2
#define MAX_BUFFER_SIZE 254

char buffer[255];

std::map<std::string, int> vars_int;
std::map<std::string, std::string> vars_char;

class function_list {
  public:
    std::string name;
    std::string regex;
};

void print(std::string input) {
    std::cout << input << std::endl;
}

void print_variable_int(std::string input) {
  std::cout << vars_int[input] << std::endl;
}

void print_variable_char(std::string input) {
  std::cout << vars_char[input] << std::endl;
}

void execute(std::string input) {
    const char *comamnd = input.c_str();
    system(comamnd);
}

void exec_char(std::string input) {
  const char *command = vars_char[input].c_str();
  // const char *comamnd = input.c_str();
  system(command);
}

void create_variable_int(std::string variable_name, int variable_value) {
  vars_int[variable_name] = variable_value;
}

void create_variable_char(std::string variable_name, std::string variable_value) {
  vars_char[variable_name] = variable_value;
}

void input() {
  fgets(buffer, MAX_BUFFER_SIZE, stdin);
}

void save_input(std::string variable_name) {
  fgets(buffer, MAX_BUFFER_SIZE, stdin);
  vars_char[variable_name] = buffer;
}

void init() {
    std::cout << "Voidscript interpreter " << version << '\n' << std::endl;
}

void parse(std::string where) {
  function_list print_class;
  print_class.name = "print";
  print_class.regex = "^print\\(\"(\\w+.*)\"\\);$";

  function_list execute_class;
  execute_class.name = "execute";
  execute_class.regex = "^execute\\(\"(\\w+.*)\"\\);$";

  function_list variable_create_int;
  variable_create_int.name = "var_create_int";
  variable_create_int.regex = "^int (\\w*\\S) = (\\w\\d*);$";

  function_list variable_create_char;
  variable_create_char.name = "var_create_char";
  variable_create_char.regex = "^char (\\w*\\S) = \"(\\w*.*)\";$";

  function_list variable_print_int;
  variable_print_int.name = "var_print_int";
  variable_print_int.regex = "^print\\(int: (\\w+.*)\\);$";

  function_list variable_print_char;
  variable_print_char.name = "var_print_char";
  variable_print_char.regex = "^print\\(char: (\\w+.*)\\);$";

  function_list get_input;
  get_input.name = "get_input";
  get_input.regex = "^input\\(\\);$";

  function_list save_input_to_char;
  save_input_to_char.name = "save_input";
  save_input_to_char.regex = "^char (\\w*\\S) = input\\(\\);$";

  function_list execute_char;
  execute_char.name = "execute_char";
  execute_char.regex = "^execute\\(char: (\\w+.*)\\);$";
  
  std::string line;
  std::ifstream file;
  file.open(where);
  std::list<std::string> list1 = {print_class.name, execute_class.name, variable_create_int.name, variable_create_char.name, variable_print_int.name, variable_print_char.name, get_input.name, save_input_to_char.name, execute_char.name};

  if (!file.is_open()) {
    perror("Error open");
    exit(EXIT_FAILURE);
  }

  while (getline(file, line)) {
    const std::string s = line;
        for (auto const &i : list1) {
            std::ostringstream os;

            if (i == print_class.name) {
              os << print_class.regex;
            } else if (i == execute_class.name) {
              os << execute_class.regex;
            } else if (i == variable_create_int.name) {
              os << variable_create_int.regex;
            } else if (i == variable_print_int.name) {
              os << variable_print_int.regex;
            } else if (i == variable_print_char.name) {
              os << variable_print_char.regex;
            } else if (i == get_input.name) {
              os << get_input.regex;
            } else if (i == variable_create_char.name) {
              os << variable_create_char.regex;
            } else if (i == save_input_to_char.name) {
              os << save_input_to_char.regex;
            } else if (i == execute_char.name) {
              os << execute_char.regex;
            }

            std::string rgx = os.str();
            std::smatch match;
            if (std::regex_search(s.begin(), s.end(), match, std::regex(rgx))) {
              if (i == print_class.name) {
                print(match[1]);
              } else if (i == execute_class.name) {
                execute(match[1]);
              } else if (i == variable_create_int.name) {
                std::string variable_name = match[1];
                int variable_value = std::stoi(match[2]);
                create_variable_int(variable_name, variable_value);
              } else if (i == variable_create_char.name) {
                std::string variable_name = match[1];
                std::string variable_value = match[2];
                create_variable_char(variable_name, variable_value);
              } else if (i == variable_print_int.name) {
                std::string variable_name = match[1];
                print_variable_int(variable_name);
              } else if (i == variable_print_char.name) {
                std::string variable_name = match[1];
                print_variable_char(variable_name);
              } else if (i == get_input.name) {
                input();
              } else if (i == variable_create_char.name) {
                std::string variable_name = match[1];
                print_variable_char(variable_name);
              } else if (i == save_input_to_char.name) {
                std::string variable_name = match[1];
                save_input(variable_name);
              } else if (i == execute_char.name) {
                std::string variable_name = match[1];
                exec_char(variable_name);
              }
            }
        }
  }
}

int main(int argc, char *argv[]) {
    init();
    parse(argv[1]);
    return 0;
}