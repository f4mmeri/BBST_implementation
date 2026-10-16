#include <iostream>
using namespace std;

template<typename T>
struct AVL {

    struct TreeNode {
        T data;
        int height;
        TreeNode* left;
        TreeNode* right;

        TreeNode(T data) : data(data), height(0), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    AVL() {
        root = nullptr;
    }

    ~AVL() {
        destroy(root);
    }

    void destroy(TreeNode* u) {
        if (u == nullptr) return;
        destroy(u -> left);
        destroy(u -> right);
        delete u;
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u -> height;
    }

    void update(TreeNode* u) {
        int hl = h(u -> left);
        int hr = h(u -> right);
        u -> height = 1 + (hl > hr ? hl : hr);
    }

    int FB(TreeNode* u) {
        return h(u -> left) - h(u -> right);
    }

    TreeNode* rotate_right(TreeNode* y) {
        TreeNode* x = y -> left;
        y -> left = x -> right;
        x -> right = y;
        update(y);
        update(x);
        return x;
    }

    TreeNode* rotate_left(TreeNode* x) {
        TreeNode* y = x -> right;
        x -> right = y -> left;
        y -> left = x;
        update(x);
        update(y);
        return y;
    }

    TreeNode* rebalance(TreeNode* u) {
        update(u);
        if (FB(u) > 1) {
            if (FB(u -> left) < 0) {
                u -> left = rotate_left(u -> left);
            }
            return rotate_right(u);
        }
        if (FB(u) < -1) {
            if (FB(u -> right) > 0) {
                u -> right = rotate_right(u -> right);
            }
            return rotate_left(u);
        }
        return u;
    }

    TreeNode* insert(TreeNode* u, T value) {
        if (u == nullptr) {
            return new TreeNode(value);
        }
        if (value < u -> data) {
            u -> left = insert(u -> left, value);
        }
        else if (value > u -> data) {
            u -> right = insert(u -> right, value);
        }
        else {
            return u;
        }
        return rebalance(u);
    }

    void insert(T value) {
        root = insert(root, value);
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        while (u -> left != nullptr) {
            u = u -> left;
        }
        return u;
    }

    TreeNode* max_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        while (u -> right != nullptr) {
            u = u -> right;
        }
        return u;
    }

    TreeNode* min_element() {
        return min_element(root);
    }

    TreeNode* max_element() {
        return max_element(root);
    }

    TreeNode* erase(TreeNode* u, T value) {
        if (u == nullptr) return nullptr;
        if (value < u -> data) {
            u -> left = erase(u -> left, value);
        }
        else if (value > u -> data) {
            u -> right = erase(u -> right, value);
        }
        else {
            if (u -> left == nullptr) {
                TreeNode* r = u -> right;
                delete u;
                return r;
            }
            if (u -> right == nullptr) {
                TreeNode* l = u -> left;
                delete u;
                return l;
            }
            TreeNode* s = min_element(u -> right);
            u -> data = s -> data;
            u -> right = erase(u -> right, u -> data);
        }
        return rebalance(u);
    }

    void erase(T value) {
        root = erase(root, value);
    }

    bool search(T key) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current -> data == key) {
                return true;
            }
            if (current -> data > key) {
                current = current -> left;
            }
            else {
                current = current -> right;
            }
        }
        return false;
    }

    void print_inorder() {
        print_subtree_inorder(root);
        cout << endl;
    }

    void print_subtree_inorder(TreeNode* u) {
        if (u == nullptr) return;
        print_subtree_inorder(u -> left);
        cout << u -> data << " ";
        print_subtree_inorder(u -> right);
    }

    void print_preorder() {
        print_subtree_preorder(root);
        cout << endl;
    }

    void print_subtree_preorder(TreeNode* u) {
        if (u == nullptr) return;
        cout << u -> data << " ";
        print_subtree_preorder(u -> left);
        print_subtree_preorder(u -> right);
    }

    void print_postorder() {
        print_subtree_postorder(root);
        cout << endl;
    }

    void print_subtree_postorder(TreeNode* u) {
        if (u == nullptr) return;
        print_subtree_postorder(u -> left);
        print_subtree_postorder(u -> right);
        cout << u -> data << " ";
    }
};

int main() {
    int n;
    cin >> n;
    AVL<int> T;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        T.insert(x);
        cout << T.h(T.root) << " " << T.root -> data << '\n';
    }
    return 0;
}
