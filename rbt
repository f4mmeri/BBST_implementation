#include <iostream>
using namespace std;

template<typename T>
struct RBTree {

    struct TreeNode {
        T data;
        bool red;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;

        TreeNode(T data = T()) : data(data), red(false), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    TreeNode* nil;
    TreeNode* root;

    RBTree() {
        nil = new TreeNode();
        nil -> left = nil;
        nil -> right = nil;
        nil -> parent = nil;
        root = nil;
    }

    ~RBTree() {
        destroy(root);
        delete nil;
    }

    void destroy(TreeNode* u) {
        if (u == nil) return;
        destroy(u -> left);
        destroy(u -> right);
        delete u;
    }

    void rotate_left(TreeNode* x) {
        TreeNode* y = x -> right;
        x -> right = y -> left;
        if (y -> left != nil) {
            y -> left -> parent = x;
        }
        y -> parent = x -> parent;
        if (x -> parent == nil) {
            root = y;
        }
        else if (x == x -> parent -> left) {
            x -> parent -> left = y;
        }
        else {
            x -> parent -> right = y;
        }
        y -> left = x;
        x -> parent = y;
    }

    void rotate_right(TreeNode* y) {
        TreeNode* x = y -> left;
        y -> left = x -> right;
        if (x -> right != nil) {
            x -> right -> parent = y;
        }
        x -> parent = y -> parent;
        if (y -> parent == nil) {
            root = x;
        }
        else if (y == y -> parent -> right) {
            y -> parent -> right = x;
        }
        else {
            y -> parent -> left = x;
        }
        x -> right = y;
        y -> parent = x;
    }

    void insert_fixup(TreeNode* z) {
        while (z -> parent -> red) {
            if (z -> parent == z -> parent -> parent -> left) {
                TreeNode* y = z -> parent -> parent -> right;
                if (y -> red) {
                    z -> parent -> red = false;
                    y -> red = false;
                    z -> parent -> parent -> red = true;
                    z = z -> parent -> parent;
                }
                else {
                    if (z == z -> parent -> right) {
                        z = z -> parent;
                        rotate_left(z);
                    }
                    z -> parent -> red = false;
                    z -> parent -> parent -> red = true;
                    rotate_right(z -> parent -> parent);
                }
            }
            else {
                TreeNode* y = z -> parent -> parent -> left;
                if (y -> red) {
                    z -> parent -> red = false;
                    y -> red = false;
                    z -> parent -> parent -> red = true;
                    z = z -> parent -> parent;
                }
                else {
                    if (z == z -> parent -> left) {
                        z = z -> parent;
                        rotate_right(z);
                    }
                    z -> parent -> red = false;
                    z -> parent -> parent -> red = true;
                    rotate_left(z -> parent -> parent);
                }
            }
        }
        root -> red = false;
    }

    void insert(T value) {
        TreeNode* y = nil;
        TreeNode* x = root;
        while (x != nil) {
            y = x;
            if (value < x -> data) {
                x = x -> left;
            }
            else if (value > x -> data) {
                x = x -> right;
            }
            else {
                return;
            }
        }
        TreeNode* z = new TreeNode(value);
        z -> parent = y;
        z -> left = nil;
        z -> right = nil;
        z -> red = true;
        if (y == nil) {
            root = z;
        }
        else if (value < y -> data) {
            y -> left = z;
        }
        else {
            y -> right = z;
        }
        insert_fixup(z);
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nil) return nil;
        while (u -> left != nil) {
            u = u -> left;
        }
        return u;
    }

    TreeNode* max_element(TreeNode* u) {
        if (u == nil) return nil;
        while (u -> right != nil) {
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

    TreeNode* successor(TreeNode* x) {
        if (x -> right != nil) {
            return min_element(x -> right);
        }
        TreeNode* y = x -> parent;
        while (y != nil and x == y -> right) {
            x = y;
            y = y -> parent;
        }
        return y;
    }

    TreeNode* predecessor(TreeNode* x) {
        if (x -> left != nil) {
            return max_element(x -> left);
        }
        TreeNode* y = x -> parent;
        while (y != nil and x == y -> left) {
            x = y;
            y = y -> parent;
        }
        return y;
    }

    TreeNode* find(T key) {
        TreeNode* current = root;
        while (current != nil) {
            if (key < current -> data) {
                current = current -> left;
            }
            else if (key > current -> data) {
                current = current -> right;
            }
            else {
                return current;
            }
        }
        return nil;
    }

    bool search(T key) {
        return find(key) != nil;
    }

    void transplant(TreeNode* u, TreeNode* v) {
        if (u -> parent == nil) {
            root = v;
        }
        else if (u == u -> parent -> left) {
            u -> parent -> left = v;
        }
        else {
            u -> parent -> right = v;
        }
        v -> parent = u -> parent;
    }

    void erase_fixup(TreeNode* x) {
        while (x != root and !x -> red) {
            if (x == x -> parent -> left) {
                TreeNode* w = x -> parent -> right;
                if (w -> red) {
                    w -> red = false;
                    x -> parent -> red = true;
                    rotate_left(x -> parent);
                    w = x -> parent -> right;
                }
                if (!w -> left -> red and !w -> right -> red) {
                    w -> red = true;
                    x = x -> parent;
                }
                else {
                    if (!w -> right -> red) {
                        w -> left -> red = false;
                        w -> red = true;
                        rotate_right(w);
                        w = x -> parent -> right;
                    }
                    w -> red = x -> parent -> red;
                    x -> parent -> red = false;
                    w -> right -> red = false;
                    rotate_left(x -> parent);
                    x = root;
                }
            }
            else {
                TreeNode* w = x -> parent -> left;
                if (w -> red) {
                    w -> red = false;
                    x -> parent -> red = true;
                    rotate_right(x -> parent);
                    w = x -> parent -> left;
                }
                if (!w -> left -> red and !w -> right -> red) {
                    w -> red = true;
                    x = x -> parent;
                }
                else {
                    if (!w -> left -> red) {
                        w -> right -> red = false;
                        w -> red = true;
                        rotate_left(w);
                        w = x -> parent -> left;
                    }
                    w -> red = x -> parent -> red;
                    x -> parent -> red = false;
                    w -> left -> red = false;
                    rotate_right(x -> parent);
                    x = root;
                }
            }
        }
        x -> red = false;
    }

    void erase(T value) {
        TreeNode* z = find(value);
        if (z == nil) return;
        TreeNode* y = z;
        TreeNode* x;
        bool y_was_red = y -> red;
        if (z -> left == nil) {
            x = z -> right;
            transplant(z, z -> right);
        }
        else if (z -> right == nil) {
            x = z -> left;
            transplant(z, z -> left);
        }
        else {
            y = min_element(z -> right);
            y_was_red = y -> red;
            x = y -> right;
            if (y -> parent == z) {
                x -> parent = y;
            }
            else {
                transplant(y, y -> right);
                y -> right = z -> right;
                y -> right -> parent = y;
            }
            transplant(z, y);
            y -> left = z -> left;
            y -> left -> parent = y;
            y -> red = z -> red;
        }
        delete z;
        if (!y_was_red) {
            erase_fixup(x);
        }
    }

    void print_inorder() {
        print_subtree_inorder(root);
        cout << endl;
    }

    void print_subtree_inorder(TreeNode* u) {
        if (u == nil) return;
        print_subtree_inorder(u -> left);
        cout << u -> data << " ";
        print_subtree_inorder(u -> right);
    }

    void print_preorder() {
        print_subtree_preorder(root);
        cout << endl;
    }

    void print_subtree_preorder(TreeNode* u) {
        if (u == nil) return;
        cout << u -> data << " ";
        print_subtree_preorder(u -> left);
        print_subtree_preorder(u -> right);
    }

    void print_postorder() {
        print_subtree_postorder(root);
        cout << endl;
    }

    void print_subtree_postorder(TreeNode* u) {
        if (u == nil) return;
        print_subtree_postorder(u -> left);
        print_subtree_postorder(u -> right);
        cout << u -> data << " ";
    }
};

int main() {
    int n;
    cin >> n;
    RBTree<int> T;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        T.insert(x);
    }
    T.print_inorder();
    T.print_preorder();
    return 0;
}
