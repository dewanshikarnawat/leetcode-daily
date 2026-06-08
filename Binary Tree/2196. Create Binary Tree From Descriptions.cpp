//Problem: 2196. Create Binary Tree From Descriptions
//TOpic: Binary Tree Construction
//Pattern: Medium

class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> mp;
        unordered_set<int> isChild;

        for (auto &d : descriptions) {
            int parent = d[0];
            int child = d[1];
            int isLeft = d[2];

            if (!mp.count(parent)) {
                mp[parent] = new TreeNode(parent);
            }
            if (!mp.count(child)) {
                mp[child] = new TreeNode(child);
            }

            if (isLeft == 1) {
                mp[parent]->left = mp[child];
            } else {
                mp[parent]->right = mp[child];
            }

            isChild.insert(child);
        }

        TreeNode* root = nullptr;
        for (auto &it : mp) {
            if (!isChild.count(it.first)) {
                root = it.second;
                break;
            }
        }

        return root;
    }
};
