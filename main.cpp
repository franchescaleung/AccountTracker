#include <sstream>
#include "HashMap.hpp"
#include "UserInterface.hpp"

// for debug commands to avoid less code
// checks if there;s extra words and if not, go to debugging functions in userinterface
void extra_word_debug(std::string extra_words, bool debugger, std::string command, HashMap& hm)
{
	if (extra_words == "") // sees if there are extra words
	{

		debug(debugger, command, hm);
	}

	else
	{
		std::cout << "INVALID" << std::endl;
	}
}


int main()
{
	HashMap hm;
	bool debugger = false; // keeps track of whether debugger is on
	std::string command;
	

	do
	{
		std::stringstream s;
		std::string extra_words;
		std::string temp;

		std::getline(std::cin, temp);
		s << temp;
		s >> command;

		if (command == "CREATE")
		{

			std::string username;
			std::string password;
			s >> username;
			s >> password;
			s >> extra_words;

			if ((username != "") && (password != "") && (extra_words == "")) // sees if there are extra words
			{
				
				create(username, password, hm);
			}

			else
			{
				std::cout << "INVALID" << std::endl;
				
			}
		}

		else if (command == "LOGIN")
		{
			
			std::string usernameORcount;
			s >> usernameORcount;
			

			if (usernameORcount == "COUNT") // if second word is count
			{
				s >> extra_words;
				extra_word_debug(extra_words, debugger, command, hm);
			}

			else
			{
				
				std::string password;
				s >> password;
				s >> extra_words;

				// check if there is username and password
				if ((usernameORcount != "") && (password != "") && (extra_words == "")) // sees if there are extra words
				{

					login(usernameORcount, password, hm);
				}

				else
				{
					
					std::cout << "INVALID" << std::endl;
				}
				
			}
		}


		else if (command == "QUIT")
		{
			s >> extra_words;

			if (extra_words == "")
			{
				continue;
			}

			else
			{
				command = "";
				std::cout << "INVALID" << std::endl;
			}
			
		}


		else if (command == "REMOVE")
		{
			
			std::string username;
			s >> username;
			s >> extra_words;

			if ((username != "") && (extra_words == "")) // sees if there are extra words
			{

				remove(username, hm); // remove username
			}

			else
			{
				std::cout << "INVALID" << std::endl;
			}
			
		}

		else if (command == "CLEAR")
		{
			
			s >> extra_words;

			if (extra_words == "")
			{
				clear(hm); // clear hashmap
			}

			else
			{
				std::cout << "INVALID" << std::endl;
			}
			
		}

		else if (command == "DEBUG")
		{
				
			std::string onOrOFF;
			s >> onOrOFF;
			s >> extra_words;

			if (onOrOFF == "ON")
			{

				if ((extra_words == "") && (debugger == false)) // turn on debugger
				{

					debugger = true;
					std::cout << "ON NOW" << std::endl;
				}

				else if ((extra_words == "") && (debugger == true))
				{
					std::cout << "ON ALREADY" << std::endl;
				}


				else 
				{
					std::cout << "INVALID" << std::endl;
				}
				
				
						
			}

			else if (onOrOFF == "OFF")
			{

				if ((extra_words == "") && (debugger == true)) // turns off debugger
				{

					debugger = false;
					std::cout << "OFF NOW" << std::endl;
				}

				else if ((extra_words == "") && (debugger == false))
				{
					std::cout << "OFF ALREADY" << std::endl;
				}


				else 
				{
					std::cout << "INVALID" << std::endl;
				}
				
			}

			else
			{

				std::cout << "INVALID" << std::endl;
			}
		}


		else if (command == "LOAD")
		{
			std::string factor;
			s >> factor;
			s >> extra_words;

			if (factor != "")
			{
				extra_word_debug(extra_words, debugger, command, hm); // return load factor
			}

			else
			{
				std::cout << "INVALID" << std::endl;
			}
			
		}

		else if (command == "MAX")
		{
			std::string bucket;
			std::string size;
			s >> bucket;
			s >> size;
			s >> extra_words;
			
			if ((bucket == "BUCKET") && (size == "SIZE"))
			{
				extra_word_debug(extra_words, debugger, command, hm);
			}

			else
			{
				std::cout << "INVALID" << std::endl;
			}
			

		}

		else if (command == "BUCKET")
		{
			std::string count;
			s >> count;
			s >> extra_words;
			if (count == "COUNT")
			{
				extra_word_debug(extra_words, debugger, command, hm);
			}
			
			else
			{
				std::cout << "INVALID" << std::endl;
			}
		}
		
		else
		{
			std::cout << "INVALID" << std::endl;
			
		}

	}

	while (command != "QUIT");

	std::cout << "GOODBYE" << std::endl;
    return 0;
}

