#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
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
    void collectWords(TrieNode* node, string current, vector<string>& results) {
        if (node->isEnd)
            results.push_back(current);


        for (auto &pair : node->children)
            collectWords(pair.second, current + pair.first, results);
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
    vector<string> autocomplete(const string& prefix) {
        TrieNode* current = root;


        for (char c : prefix) {
            if (current->children.find(c) == current->children.end())
                return {};  // No matches
            current = current->children[c];
        }


        vector<string> results;
        collectWords(current, prefix, results);
        return results;
    }


};

int main() {
     Trie t;
    vector<string> dictionary = {
    "the","of","and","to","a","in","for","is","on","that",
    "by","this","with","i","you","it","not","or","be",
    "are","from","at","as","your","all","have","new","more",
    "an","was","we","will","home","can","us","about","if",
    "page","my","has","search","free","but","our","one","other",
    "do","no","information","time"
};
    for (auto &w : dictionary)
        t.insert(w);


    cout << "Loaded " << dictionary.size() << " words.\n";


   string prefix;
    cout << "\nEnter prefix: ";
    cin >> prefix;


    vector<string> results = t.autocomplete(prefix);


    cout << "\nSuggestions:\n";
    for (string s : results)
        cout << " - " << s << endl;




    return 0;
}