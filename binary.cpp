#include <iostream>
#include <queue>
using namespace std;

// Definition of a BST Node
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Class for Binary Search Tree
class BinarySearchTree {
private:
    Node* root;

    // Helper function for recursive in-order traversal
    void inOrderTraversal(Node* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }

    // Helper function to find the minimum value node (used for deletion)
    Node* findMin(Node* node) const {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Helper function for deletion
    Node* deleteNode(Node* node, int value) {
        if (node == nullptr) {
            return node; // Value not found
        }

        if (value < node->data) {
            node->left = deleteNode(node->left, value); // Go to left subtree
        }
        else if (value > node->data) {
            node->right = deleteNode(node->right, value); // Go to right subtree
        }
        else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children:
            // Get the inorder successor (smallest in the right subtree)
            Node* temp = findMin(node->right);

            // Copy the inorder successor's data to this node
            node->data = temp->data;

            // Delete the inorder successor
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    // Helper function to calculate the height of the tree
    int height(Node* node) const {
        if (node == nullptr) {
            return -1; // Height of an empty tree is -1
        }
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    // Helper function to deallocate memory
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    // Constructor
    BinarySearchTree() : root(nullptr) {}

    // Destructor
    ~BinarySearchTree() {
        destroyTree(root);
    }

    // Iterative insertion method
    void insert(int value) {
        Node* newNode = new Node(value);
        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (value < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    // Iterative search method
    bool search(int value) const {
        Node* current = root;

        while (current != nullptr) {
            if (value == current->data) {
                return true; // Found
            }
            if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return false; // Not found
    }

    // Public in-order traversal
    void inOrderTraversal() const {
        inOrderTraversal(root);
        cout << endl;
    }

    // Public deletion method
    void deleteNode(int value) {
        root = deleteNode(root, value);
    }

    // Public method to get the height of the tree
    int getHeight() const {
        return height(root);
    }

    // Public method for level-order traversal (BFS)
    void levelOrderTraversal() const {
        if (root == nullptr) return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        cout << endl;
    }
};

// Main function demonstrating the tree
int main() {
    BinarySearchTree bst;

    // Inserting nodes
    bst.insert(40);
    bst.insert(20);
    bst.insert(60);
    bst.insert(10);
    bst.insert(30);
    bst.insert(50);
    bst.insert(70);

    // Display the tree using in-order traversal
    cout << "In-order Traversal: ";
    bst.inOrderTraversal();

    // Level-order traversal
    cout << "Level-order Traversal: ";
    bst.levelOrderTraversal();

    // Searching for values
    cout << "Searching for 30: " << (bst.search(30) ? "Found" : "Not Found") << endl;
    cout << "Searching for 100: " << (bst.search(100) ? "Found" : "Not Found") << endl;

    // Deleting a node and re-displaying the tree
    cout << "Deleting 20 from the tree...\n";
    bst.deleteNode(20);

    cout << "In-order Traversal after deletion: ";
    bst.inOrderTraversal();

    // Display the height of the tree
    cout << "Height of the tree: " << bst.getHeight() << endl;

    return 0;
}
