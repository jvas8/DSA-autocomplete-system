#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class TrieNode {
public:
    bool isEnd;
    unordered_map<char, TrieNode*> children;

    TrieNode() {
        isEnd = false;
    }
};

class Trie {
private:
    TrieNode* root;
    bool deleteHelper(TrieNode* node, const string& word, int index) {
        if (index == word.size()) {
            if (!node->isEnd) return false;
            node->isEnd = false;
            return node->children.empty();
        }

        char c = word[index];
        if (node->children.find(c) == node->children.end())
            return false;

        bool shouldDeleteChild = deleteHelper(node->children[c], word, index + 1);

        if (shouldDeleteChild) {
            delete node->children[c];
            node->children.erase(c);

            return node->children.empty() && !node->isEnd;
        }

        return false;
    }


public:
    Trie() {
        root = new TrieNode();
    }

   void insert(const string& word) {
        TrieNode* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }

        current->isEnd = true;
    }

    bool search(const string& word) {
        TrieNode* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }

        return current->isEnd;
    }
     void removeWord(const string& word) {
        deleteHelper(root, word, 0);
    }

};

int main() {
     Trie t;

    t.insert("cat");
    t.insert("car");
    t.insert("dog");

    cout << "Inserted: cat, car, dog\n";

    cout << "\n=== SEARCH TEST ===\n";
    cout << "Search cat: " << t.search("cat") << endl;
    cout << "Search car: " << t.search("car") << endl;
    cout << "Search cap: " << t.search("cap") << endl;
    cout << "Search dog: " << t.search("dog") << endl;
    
     cout << "Before delete, search cat: " << t.search("cat") << endl;

    t.removeWord("cat");

    cout << "After delete, search cat: " << t.search("cat") << endl;



    return 0;
}