#include <iostream>
#include <vector>
using namespace std;

template<typename T>
struct AVL {

    struct TreeNode {
        T data;
        int height;
        int left;
        int right;
    };

    vector<TreeNode> t;
    vector<int> libres;
    int root;

    AVL() {
        t.push_back(TreeNode());
        root = 0;
    }

    int new_node(T value) {
        int u;
        if (!libres.empty()) {
            u = libres.back();
            libres.pop_back();
        }
        else {
            u = t.size();
            t.push_back(TreeNode());
        }
        t[u].data = value;
        t[u].height = 0;
        t[u].left = 0;
        t[u].right = 0;
        return u;
    }

    int h(int u) {
        return u == 0 ? -1 : t[u].height;
    }

    void update(int u) {
        int hl = h(t[u].left);
        int hr = h(t[u].right);
        t[u].height = 1 + (hl > hr ? hl : hr);
    }

    int FB(int u) {
        return h(t[u].left) - h(t[u].right);
    }

    int rotate_right(int y) {
        int x = t[y].left;
        t[y].left = t[x].right;
        t[x].right = y;
        update(y);
        update(x);
        return x;
    }

    int rotate_left(int x) {
        int y = t[x].right;
        t[x].right = t[y].left;
        t[y].left = x;
        update(x);
        update(y);
        return y;
    }

    int rebalance(int u) {
        update(u);
        if (FB(u) > 1) {
            if (FB(t[u].left) < 0) {
                int r = rotate_left(t[u].left);
                t[u].left = r;
            }
            return rotate_right(u);
        }
        if (FB(u) < -1) {
            if (FB(t[u].right) > 0) {
                int r = rotate_right(t[u].right);
                t[u].right = r;
            }
            return rotate_left(u);
        }
        return u;
    }

    int insert(int u, T value) {
        if (u == 0) {
            return new_node(value);
        }
        if (value < t[u].data) {
            int r = insert(t[u].left, value);
            t[u].left = r;
        }
        else if (value > t[u].data) {
            int r = insert(t[u].right, value);
            t[u].right = r;
        }
        else {
            return u;
        }
        return rebalance(u);
    }

    void insert(T value) {
        root = insert(root, value);
    }

    int min_element(int u) {
        if (u == 0) return 0;
        while (t[u].left != 0) {
            u = t[u].left;
        }
        return u;
    }

    int max_element(int u) {
        if (u == 0) return 0;
        while (t[u].right != 0) {
            u = t[u].right;
        }
        return u;
    }

    int min_element() {
        return min_element(root);
    }

    int max_element() {
        return max_element(root);
    }

    int erase(int u, T value) {
        if (u == 0) return 0;
        if (value < t[u].data) {
            int r = erase(t[u].left, value);
            t[u].left = r;
        }
        else if (value > t[u].data) {
            int r = erase(t[u].right, value);
            t[u].right = r;
        }
        else {
            if (t[u].left == 0) {
                int r = t[u].right;
                libres.push_back(u);
                return r;
            }
            if (t[u].right == 0) {
                int l = t[u].left;
                libres.push_back(u);
                return l;
            }
            int s = min_element(t[u].right);
            t[u].data = t[s].data;
            int r = erase(t[u].right, t[u].data);
            t[u].right = r;
        }
        return rebalance(u);
    }

    void erase(T value) {
        root = erase(root, value);
    }

    bool search(T key) {
        int current = root;
        while (current != 0) {
            if (t[current].data == key) {
                return true;
            }
            if (t[current].data > key) {
                current = t[current].left;
            }
            else {
                current = t[current].right;
            }
        }
        return false;
    }

    void print_inorder() {
        print_subtree_inorder(root);
        cout << endl;
    }

    void print_subtree_inorder(int u) {
        if (u == 0) return;
        print_subtree_inorder(t[u].left);
        cout << t[u].data << " ";
        print_subtree_inorder(t[u].right);
    }

    void print_preorder() {
        print_subtree_preorder(root);
        cout << endl;
    }

    void print_subtree_preorder(int u) {
        if (u == 0) return;
        cout << t[u].data << " ";
        print_subtree_preorder(t[u].left);
        print_subtree_preorder(t[u].right);
    }

    void print_postorder() {
        print_subtree_postorder(root);
        cout << endl;
    }

    void print_subtree_postorder(int u) {
        if (u == 0) return;
        print_subtree_postorder(t[u].left);
        print_subtree_postorder(t[u].right);
        cout << t[u].data << " ";
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
        cout << T.h(T.root) << " " << T.t[T.root].data << '\n';
    }
    return 0;
}

//
