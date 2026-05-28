//Problem: 3120. Count the number of special characters
//Topic: Trie + Strings
//Difficulty: Hard

class Solution {
public:
  struct TrieNode {
        int child[26];
        int idx;

        TrieNode() {
            memset(child, -1, sizeof(child));
            idx = -1;
        }
    };

    vector<TrieNode> trie;

    bool better(vector<string>& wordsContainer, int a, int b) {
        if (b == -1) return true;

        if (wordsContainer[a].size() < wordsContainer[b].size())
            return true;

        if (wordsContainer[a].size() == wordsContainer[b].size())
            return a < b;

        return false;
    }

    void insert(string &s, int index, vector<string>& wordsContainer) {

        int node = 0;

        if (better(wordsContainer, index, trie[node].idx))
            trie[node].idx = index;

        for (int i = s.size() - 1; i >= 0; i--) {

            int c = s[i] - 'a';

            if (trie[node].child[c] == -1) {
                trie[node].child[c] = trie.size();
                trie.push_back(TrieNode());
            }

            node = trie[node].child[c];

            if (better(wordsContainer, index, trie[node].idx))
                trie[node].idx = index;
        }
    }

    int query(string &s) {

        int node = 0;

        for (int i = s.size() - 1; i >= 0; i--) {

            int c = s[i] - 'a';

            if (trie[node].child[c] == -1)
                break;

            node = trie[node].child[c];
        }

        return trie[node].idx;
    }

    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
      trie.push_back(TrieNode());

        for (int i = 0; i < wordsContainer.size(); i++) {
            insert(wordsContainer[i], i, wordsContainer);
        }

        vector<int> ans;

        for (auto &q : wordsQuery) {
            ans.push_back(query(q));
        }

        return ans;
    }
};
