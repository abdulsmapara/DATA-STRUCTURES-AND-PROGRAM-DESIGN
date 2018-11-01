#include <bits/stdc++.h>
using namespace std;
const int ALPHABET_SIZE = 26;

class TrieNode{


public:
	int terminating;
	TrieNode* trieNodes[ALPHABET_SIZE];

	TrieNode(){
		terminating = 0;
		for (int i = 0; i < ALPHABET_SIZE; ++i){
			trieNodes[i] = NULL;
		}
	}
	TrieNode* next(const char c){
		return trieNodes[c-'a'];
	}
	~TrieNode(){
		for (int i = 0; i < ALPHABET_SIZE; ++i)
		{
			delete trieNodes[i];
		}
	}
};
class Trie
{
	TrieNode* root;
public:
	Trie(){
		root = new TrieNode();
	}

	void insert_(std::string s){
		TrieNode* current = root;
		for (int i = 0; i < s.length(); ++i){
			if(current->trieNodes[s[i]-'a'] == NULL){
				current->trieNodes[s[i]-'a'] = new TrieNode();
			}
			current = current->next(s[i]);
		}
		current->terminating += 1;
	}

	void delete_(std::string s){
		TrieNode* current = root;
		for (int i = 0; i < s.length(); ++i){
			if(current->trieNodes[s[i]-'a'] == NULL){
				throw "No such string exists !";
			}
			current = current->next(s[i]);
		}
		if(current->terminating == 0){
			throw "No such string exists !";			
		}else{
			current->terminating -= 1;
		}

	}

	int query_(std::string s){
		TrieNode* current = root;
		for (int i = 0; i < s.length(); ++i){
			if(current == NULL){
				return 0;
			}
			current = current->next(s[i]);
		}
		return current->terminating;
	}
	void update_(std::string old,std::string newString){

		delete_(old);
		insert_(newString);

	}

	~Trie(){
		//destructor
		delete root;
	}
	
};

int main(){
	
	std::string pqrs("pqrs");
	std::string pprt("pprt");
	std::string psst("psst");
	std::string qqrs("qqrs");
	std::string abc("abc");

	std::vector<std::string> setOfStrings;
	setOfStrings.push_back(pqrs);
	setOfStrings.push_back(pprt);
	setOfStrings.push_back(psst);
	setOfStrings.push_back(qqrs);
	setOfStrings.push_back(pqrs);

	Trie* trie = new Trie();
	for(string s : setOfStrings)
		trie->insert_(s);

	cout << trie->query_(pqrs) << endl;
	cout << trie->query_(psst) << endl << trie->query_(abc) << endl;


	delete trie;	//free memory

	return 0;
}
