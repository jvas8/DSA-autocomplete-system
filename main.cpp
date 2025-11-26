#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
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

    bool search(const string& word) {
        TrieNode* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end())
                return false;
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
                return {};
            current = current->children[c];
        }

        vector<pair<string,int>> temp;
        collectWords(current, prefix, temp);

        sort(temp.begin(), temp.end(),
            [](auto &a, auto &b){ return a.second > b.second; });

        vector<string> results;
        for (auto &p : temp)
            results.push_back(p.first);

        return results;
    }
};

int main() {
    Trie t;

    vector<pair<string,int>> dictionary = {
        {"the",5000},{"of",4800},{"and",4700},{"to",4500},{"a",4400},
        {"in",4200},{"for",4000},{"is",3900},{"on",3800},{"that",3700},
        {"by",3500},{"this",3400},{"with",3300},{"i",3200},{"you",3100},
        {"it",3000},{"not",2900},{"or",2800},{"be",2700},{"are",2600},
        {"from",2500},{"at",2400},{"as",2300},{"your",2200},{"all",2100},
        {"have",2000},{"new",1900},{"more",1800},{"an",1700},{"was",1600},
        {"we",1500},{"will",1400},{"home",1300},{"can",1200},{"us",1100},
        {"about",1000},{"if",900},{"page",800},{"my",700},{"has",600},
        {"search",500},{"free",400},{"but",300},{"our",200},{"one",100},
        {"other",90},{"do",80},{"no",70},{"information",60},{"time",50}
    };

    for (auto &p : dictionary)
        t.insert(p.first, p.second);

    cout << "Loaded " << dictionary.size() << " words.\n";

    string prefix;
    cout << "\nEnter prefix: ";
    cin >> prefix;

    vector<string> results = t.autocomplete(prefix);

    cout << "\nSuggestions:\n";
    for (string s : results)
        cout << " - " << s << "\n";

    return 0;
}
