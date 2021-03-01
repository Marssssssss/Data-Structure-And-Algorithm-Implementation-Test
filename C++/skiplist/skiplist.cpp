#include <vector>
#include <iostream>

class SkippedListNode {
public:
    SkippedListNode* next;
    SkippedListNode* upper;
    SkippedListNode* lower;
    int layer;
    int val;

    SkippedListNode(int value) : next(nullptr), upper(nullptr), lower(nullptr), val(value), layer(0) {};
};


class SkippedList {
public:
    vector<SkippedListNode*> roots;
    int max_layer;

    SkippedList(int layer) : max_layer(layer) {
        srand((unsigned int)time(0));
    };

    void insert(int val) {
        int layer = 0;
        while (rand() % 2 == 0 && layer < max_layer - 1 && roots.size() > layer) {
            layer++;
        }
        SkippedListNode* lower = nullptr;
        for (int i = 0; i <= layer; i++) {
            SkippedListNode* new_node = new SkippedListNode(val);
            if (roots.size() > i)
                // 这里可以做个优化，下一层的插入可以从上一层的前一个节点对应的下一层节点开始找
                insertToLayer(i, new_node);
            else {
                roots.push_back(new_node);
                new_node->layer = roots.size() - 1;
            }
            new_node->lower = lower;
            if (lower != nullptr)
                lower->upper = new_node;
            lower = new_node;
        }
    }

    void insertToLayer(int layer, SkippedListNode* target) {
        SkippedListNode* cur_node = roots[layer];
        if (cur_node->val > target->val) {
            roots[layer] = target;
            target->next = cur_node;
            return;
        }
        while (true) {
            if (cur_node->next == nullptr) {
                target->next = cur_node->next;
                cur_node->next = target;
                break;
            }
            else if (cur_node->next->val > target->val) {
                target->next = cur_node->next;
                cur_node->next = target;
                break;
            }
            cur_node = cur_node->next;
        }
        target->layer = layer;
    }

    SkippedListNode* find(int val) {
        SkippedListNode* left = nullptr;
        SkippedListNode* right = nullptr;
        left = roots[roots.size() - 1];
        while (left != nullptr) {
            if (left == right) return nullptr;
            if (left->val == val)
                return left;
            else if (left->val > val) {
                right = left->lower;
                left = (left->layer == 0 ? nullptr : roots[left->layer - 1]);
            }
            else if (left->next == nullptr) {
                left = left->lower;
                right = nullptr;
            }
            else if (left->next->val > val) {
                right = left->next->lower;
                left = left->lower;
            }
            else if (left->next->val < val)
                left = left->next;
            else
                return left;
        }
        return nullptr;
    }

    void graph() {
        for (int i = roots.size() - 1; i > -1; i--) {
            SkippedListNode* root = roots[i];
            while (root != nullptr) {
                cout << root->val << " ";
                root = root->next;
            }
            cout << endl;
        }
    }
};