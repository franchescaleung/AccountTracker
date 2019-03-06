// UserInterface.cpp
#include "UserInterface.hpp"
#include "HashMap.hpp"




void create(std::string username, std::string password, HashMap& hashmap) // create new account
{
	if (hashmap.contains(username) == false)	// if not in hashmap, add
	{
		hashmap.add(username, password);
		std::cout << "CREATED" << std::endl;
	}

	else
	{
		std::cout << "EXISTS" << std::endl;		// already in hm
	}

}


void remove(std::string username, HashMap& hashmap) // remove account
{
	if (hashmap.contains(username)) 	// remove from hm if found
	{
		hashmap.remove(username);
		std::cout << "REMOVED" << std::endl;
	}

	else
	{
		std::cout << "NONEXISTENT" << std::endl;
	}



}

void login(std::string username, std::string password, HashMap& hashmap) // user login
{
	if (hashmap.contains(username))
	{
		if (hashmap.value(username) == password)
		{
			std::cout << "SUCCEEDED" << std::endl; // if username and password matches
		}

		else
		{
			std::cout << "FAILED" << std::endl; // incorrect password
		}
	}

	else
	{
		std::cout << "FAILED" << std::endl; // username not found
	}
}


void clear(HashMap& hashmap) // clear all in hashmap
{
	
	hashmap.clearAll();
	std::cout << "CLEARED" << std::endl;

}



void debug(bool& status, std::string command, HashMap& hashmap) // debugging tools
{
	if (status == true)
	{
		
		if (command == "LOGIN") // login count
		{
			std::cout << hashmap.size() << std::endl;	// print bucketsize
		}

		else if (command == "BUCKET") // bucket count
		{
			std::cout << hashmap.bucketCount() << std::endl;	// print total buckets
		}

		else if (command == "LOAD") // load factor
		{
			std::cout << double(hashmap.loadFactor()) << std::endl;	// print load factor
		}

		else if (command == "MAX") // max bucket size
		{
			std::cout << hashmap.maxBucketSize() << std::endl;	// print max bucket size
		}

		else
		{
			std::cout << "INVALID" << std::endl;
		}

	}

	else // if status == false
	{

		std::cout << "INVALID" << std::endl;
		

	}
}