/*
See md for explanation
*/

#include <unordered_map>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Trie
{
    struct Node;
    using node = std::unique_ptr<Node>;

    struct Node
    {
        char value = '\0';
        std::unordered_map<char, node> subNodes{};
        bool isWord = false;
    };
    node root = std::make_unique<Node>();

    void printRec(Node* node, std::string& word)
    {
        word.push_back(node->value);
        if (node->subNodes.size() == 0) 
        {
            std::cout << word << '\n';
            return;
        }
        for (const auto& item: node->subNodes)
        {
            printRec(item.second.get(), word);
            word.pop_back();
        }
    }

    void getWordsFromNode(Node* node, std::string& word, std::vector<std::string>& words)
    {
        word.push_back(node->value);
        if (node->subNodes.size() == 0) 
        {
            words.push_back(word);
            return;
        }
        for (const auto& item: node->subNodes)
        {
            getWordsFromNode(item.second.get(), word, words);
            word.pop_back();
        }
    }

public:
    void insertWord(const std::string& word)
    {
        Node* current = root.get();
        for (int i = 0; i < word.size(); ++i)
        {
            auto ptrNode = current->subNodes.find(word[i]);
            if (ptrNode == current->subNodes.end())
            {
                node newNode = std::make_unique<Node>();
                newNode->value = word[i];
                if (i == word.size()-1) newNode->isWord = true;
                current->subNodes.insert(std::pair(word[i], std::move(newNode)));
                ptrNode = current->subNodes.find(word[i]);
            }
            current = (*ptrNode).second.get();
        }
    }

    bool isWord(const std::string& word)
    {
        Node* current = root.get();
        for (int i = 0; i < word.size(); ++i)
        {
            std::cout << word[i] << " ";
            auto ptrNode = current->subNodes.find(word[i]);
            if (ptrNode == current->subNodes.end()) return false;
            current = current->subNodes[word[i]].get();
            if (i == word.size()-1)
            {
                if (current->isWord == true) return true;
                return false;
            }
        }
        return false;
    }

    bool isPrefix(const std::string& word) // it can also be a word
    {
        Node* current = root.get();
        for (int i = 0; i < word.size(); ++i)
        {
            auto ptrNode = current->subNodes.find(word[i]);
            if (ptrNode == current->subNodes.end()) return false;
            current = current->subNodes[word[i]].get();
        }
        return true;
    }

    auto getWordsStartWith(const std::string& word) -> std::vector<std::string>
    {
        std::vector<std::string> result = {};
        std::string str;
        if (word.size() == 0) 
        {
            getWordsFromNode(root.get(), str, result);
            return result;
        }

        Node* current = root.get();
        for (int i = 0; i < word.size(); ++i)
        {
            auto ptrNode = current->subNodes.find(word[i]);
            if (ptrNode == current->subNodes.end()) return result;
            current = current->subNodes[word[i]].get();
            str.push_back(current->value);
        }
        // we have to recurse starting with last node from where we found the prefix
        str.pop_back();
        getWordsFromNode(current, str, result);
        return result;
    }

    void printWords()
    {
        Node* current = root.get();
        std::string word;
        printRec(current, word);
    }

};

int main()
{
    //re trie val
    Trie dictionary;
    /*
                b ... 27
                a ... 27
                n ... 27
                a d ... 27
                n a i ... 27
                a n n ... 27
                  a a ... 27
    */

    dictionary.insertWord("banana");
    dictionary.insertWord("bandana");
    dictionary.insertWord("bandina");

    dictionary.insertWord("cacarocha");
    dictionary.insertWord("cacadoo");

    dictionary.insertWord("pacopini");
    dictionary.insertWord("pacolache");
    dictionary.insertWord("pacoluna");
    dictionary.insertWord("pacoluniii");
    //dictionary.printWords();

    //std::cout << "pacopini "<< (dictionary.isWord("pacopini") ? "was found" : "was not found") << '\n';
    //std::cout << "pacoluni "<< (dictionary.isPrefix("pacoluni") ? "was found" : "was not found") << '\n';

    auto words = dictionary.getWordsStartWith("paco");
    
    std::cout << "All word that start with paco: " << '\n';
    for (auto& word : words)
    {
        std::cout << "  - " << word << '\n';
    }

    //dictionary.printWords();
}