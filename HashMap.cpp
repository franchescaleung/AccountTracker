// HashMap.cpp
#include "HashMap.hpp"


namespace	// simple hash function for string to use in default
{
	int hash(std::string const& str) // adds value of chars in string
	{
		int hashValue = 0;
		for (int a = 0; a < str.length(); a++)
		{
			hashValue += (unsigned int)(str[a]);

		}
		return hashValue;
	}
	
}


HashMap::HashMap()
	: hasher{hash}, bucketSize{initialBucketCount}, totalBuckets{0}, bucketArray{new Node * [bucketSize] }
	{
		fillAllBuckets();
	}


HashMap::HashMap(HashFunction hasher)
	: bucketSize{initialBucketCount}, totalBuckets{0}, bucketArray{new Node * [bucketSize]}
	{
		this->hasher = hasher;
		fillAllBuckets();
	}


HashMap::HashMap(const HashMap& hm)
	: hasher{hm.hasher}, bucketSize{hm.bucketSize}, totalBuckets{hm.totalBuckets}, bucketArray{new Node * [hm.bucketSize]}
	{
		fillAllBuckets();
		arrayCopy(hm.bucketArray, bucketArray, hm.bucketSize);
	}


HashMap::~HashMap() // DESTRUCTOR
{
	for (int a = 0; a < bucketSize; a++)	
	{
		Node* currentNode = bucketArray[a];
		Node* nodeToDelete = bucketArray[a];
		while (currentNode != nullptr)
		{
			nodeToDelete = currentNode;
			currentNode = currentNode->next;
			delete nodeToDelete; // making sure to clean up and delete old pointer
			

		}
	}

	delete[] bucketArray; // delete bucketArray
}


HashMap& HashMap::operator=(const HashMap& hm) // set one hm equal to another
{
	if (this != &hm)
	{
		delete[] bucketArray; // first delete self bucket array
		hasher = hm.hasher;
		bucketSize = hm.bucketSize;
		totalBuckets = hm.totalBuckets;
		bucketArray = new Node * [hm.bucketSize]; // new bucket array = hm bucket
		arrayCopy(hm.bucketArray, bucketArray, hm.bucketSize);

	}

	return *this;
}



// public functions


void HashMap::add(const std::string& key, const std::string& value) // add key and value to hashmap
{
	if (contains(key)) // if key already in HashMap, don't do anything
	{
		return;
	}

	else	// when not key is not in HashMap, add to HashMap
	{		
	
		unsigned int bucketIndex = hasher(key) % bucketSize; // find bucket index based off given hash function
		Node* nodePointer = bucketArray[bucketIndex];
		Node* placeHolderToAddNode = bucketArray[bucketIndex];
		Node* toAddNode = new Node{key, value}; // node created to add later
		if (nodePointer == nullptr) // if linked list is empty, just add node to start
		{

			bucketArray[bucketIndex] = toAddNode;

		}
		else
		{
			
			while (nodePointer != nullptr) // find end of linked list
			{
				placeHolderToAddNode = nodePointer;
				nodePointer = nodePointer->next;

			}	

			placeHolderToAddNode->next = toAddNode; // add node to end

		}

		totalBuckets++; // increase total buckets every time a node is added
		
	}

	// check load factor, if load factor exceeds 0.8
	if (loadFactor() > 0.8)
	{

		// number of buckets increased by doubling and adding 1
		unsigned int previousSize = bucketSize;
		bucketSize = (bucketSize * 2) + 1;


		// rehashed into new buckets
		rehashBuckets(previousSize, bucketSize);
	}
	
}


 
void HashMap::remove(const std::string& key) // takes key and removes it from hashmap
{
	if (contains(key)) // if key exists, then remove
	{
		unsigned int bucketIndex = hasher(key) % bucketSize;
		Node* nodeToDelete = bucketArray[bucketIndex];
		Node* nodePointer = bucketArray[bucketIndex];

		while (nodeToDelete != nullptr)
		{

			if (nodeToDelete->key == key) 
			{

				if (nodePointer->key == key) // if first iterm is equal to key
				{
					bucketArray[bucketIndex] = nodePointer->next; // points to second node now
					delete nodeToDelete; // delete first node
					totalBuckets--; 
					break;
				}

				else // make next point ahead and delete the one with same key
				{
					nodePointer->next = nodeToDelete->next; 
					delete nodeToDelete;
					totalBuckets--;
					break;
				}
				
			}

			else
			{	
				// go to next pair of nodes in list
				nodePointer = nodeToDelete;
				nodeToDelete = nodeToDelete->next; 
			}
			
		}
			
	}
	
}




bool HashMap::contains(const std::string& key) const // returns whether key is in HashMap
{
	unsigned int bucketIndex = hasher(key) % bucketSize;
	Node* nodePointer = bucketArray[bucketIndex];
	while (nodePointer != nullptr)
	{

		if (nodePointer->key == key) // searches every key, if key in HashMap, continues to return true
		{
			return true;

		}
		
		nodePointer = nodePointer->next;  // go to next item in list
		
		
	}

	return false; // returns false if reaches nullpointer and key still not found
}


// returns value associated with key or empty string when key is not in HashMap
std::string HashMap::value(const std::string& key) const 
{

	if (!contains(key)) // return empty string if not in Hashmap
	{
		return std::string();
	}
	else // looks for key
	{
		unsigned int bucketIndex = hasher(key) % bucketSize;
		Node* nodePointer = bucketArray[bucketIndex];

		while (nodePointer != nullptr)
		{
			
			if (nodePointer->key == key)
			{
				std::string v = nodePointer->value;
				return v;

			}

			nodePointer = nodePointer->next;
		}
		return std::string();  // have to put return statement here or error without this return statement
	}
}


unsigned int HashMap::size() const // returns the number of key/vale pairs
{
	return totalBuckets; // total buckets keep track of key/value pairs

}


unsigned int HashMap::bucketCount() const // returns number of buckets allocated in HashMap
{
	return bucketSize; // only changes when load factor > 0.8
}



double HashMap::loadFactor() const // returns load factor aka number of key.value pairs/number of buckets
{
	double lf = double(size())/double(bucketCount());
	return lf;
	
}


    // maxBucketSize() returns the number of key/value pairs stored in this
    // HashMap's largest bucket.
unsigned int HashMap::maxBucketSize() const 
{
	
	int maxBucketSize = 0; // keep track of max bucket size
	// go through every bucket 
	for (int a = 0; a < bucketSize; a++)
	{
		int length = 0;
		Node* currentNode = bucketArray[a];

		while (currentNode != nullptr) // count nodes
		{
			length += 1;
			currentNode = currentNode->next;
		}

		// if length of current bucket is greater or equal to last max size, make current bucket
		// length the new max bucket size
		if (length >= maxBucketSize) 
		{
			maxBucketSize = length;
		}
	}

	return maxBucketSize;
}


// does clear reset the dynamically allocated array size aka bucketsize

void HashMap::clearAll() // clears HashMap
{

	if (bucketSize > 0)
	{


		for (int a = 0; a < bucketSize; a++)
		{
			Node* currentNode = bucketArray[a];
			Node* nodeToDelete = bucketArray[a];

			while (currentNode != nullptr)
			{
				nodeToDelete = currentNode;
				currentNode = currentNode->next;
				delete nodeToDelete;
			}

		}

		fillAllBuckets();
		totalBuckets = 0;
	}	



}


// private methods

// initializes buckets in array
void HashMap::fillAllBuckets()
{

	for (int a = 0; a < bucketSize; a++)
	{
		bucketArray[a] = nullptr;
	}
}



void HashMap::arrayCopy(Node** source, Node** &target, unsigned int count)
{
	fillAllBuckets();
	for (unsigned int a = 0; a < count; a++)
	{
		Node* currentNode = source[a];
		if (currentNode != nullptr)
		{
			target[a] = new Node{currentNode->key, currentNode->value}; // try using add node later
			Node* insideNode = target[a];
			currentNode = currentNode->next;
			while (currentNode != nullptr)
			{
				insideNode->next = new Node{currentNode->key, currentNode->value};
				currentNode = currentNode->next;
				insideNode = insideNode->next;

			}
		}

		else
		{
			target[a] = nullptr;
		}
	}

}


void HashMap::rehashBuckets(unsigned int previousSize, unsigned int newBucketSize)  // stores information from old bucketArray into new bucketArray
{
	Node** oldBucketArray = bucketArray;
	bucketArray = new Node * [newBucketSize];
	totalBuckets = 0; // resets total buckets and adds old buckets to new array
	fillAllBuckets(); // fill all new linked list in buckets with null pointers


	for (int a = 0; a < previousSize; a++)	// add all nodes from old bucket
	{
		
		Node* currentNode = oldBucketArray[a];
		Node* nodeToDelete = oldBucketArray[a];
		
		while (currentNode != nullptr)
		{
			
			add(currentNode->key, currentNode->value);
			nodeToDelete = currentNode;
			currentNode = currentNode->next;
			delete nodeToDelete;
			

		}
	
	}

	delete[] oldBucketArray;
}

