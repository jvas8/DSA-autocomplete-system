#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class TrieNode {
public:
    bool isEnd;
    int freq;  
    unordered_map<char, TrieNode*> children;

    TrieNode() {
        isEnd = false;
        freq = 0;
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

        bool shouldDelete = deleteHelper(node->children[c], word, index + 1);

        if (shouldDelete) {
            delete node->children[c];
            node->children.erase(c);
            return node->children.empty() && !node->isEnd;
        }
        return false;
    }

    void collectWords(TrieNode* node, string current, vector<pair<string,int>>& results) {
        if (node->isEnd)
            results.push_back({current, node->freq});

        for (auto &p : node->children)
            collectWords(p.second, current + p.first, results);
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word, int frequency) {
        TrieNode* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end())
                current->children[c] = new TrieNode();
            current = current->children[c];
        }

        current->isEnd = true;
        current->freq = frequency;
    }

    vector<string> autocomplete(const string& prefix) {
        TrieNode* current = root;

        for (char c : prefix) {
            if (current->children.find(c) == current->children.end())
                return {};
            current = current->children[c];
        }

        vector<pair<string,int>> collected;
        collectWords(current, prefix, collected);

        sort(collected.begin(), collected.end(),
            [](auto &a, auto &b){ return a.second > b.second; });

        vector<string> results;
        for (auto &p : collected)
            results.push_back(p.first);

        return results;
    }
};

void loadDictionaryFromFile(Trie &t, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return;
    }

    string word;
    int freq;

    while (file >> word >> freq) {
        t.insert(word, freq);
    }

    file.close();
}

int main() {
    Trie t;

    loadDictionaryFromFile(t, "dictionary.txt");

    cout << "Dictionary loaded successfully.\n";

    string prefix;
    cout << "\nEnter prefix: ";
    cin >> prefix;

    vector<string> results = t.autocomplete(prefix);

    cout << "\nSuggestions:\n";
    for (string s : results)
        cout << " - " << s << endl;

    return 0;
}
