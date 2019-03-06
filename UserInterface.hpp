// UserInterface.hpp
#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include <iostream>
#include <string>
#include "HashMap.hpp"

// user facing commands

void create(std::string username, std::string password, HashMap& hashmap);
void remove(std::string username, HashMap& hashmap);
void login(std::string username, std::string password, HashMap& hashmap);
void clear(HashMap& hashmap);


// debug commands

void debug(bool& status, std::string command, HashMap& hashmap);







#endif 