#include <iostream>
#include <string>
#include <cstdlib>
#include "node.h"

using namespace std;

class RedBlack {
	node* root;
	int size;
	
	node* addNode(int num, bool isRed, node* par) {
		node* n = (node*) calloc(1, sizeof(node));
		n->elem = num;
		n->isRed = isRed;
		n->parent = par;
		return n;
	}
	
	public:
	
	RedBlack() {
		root = NULL;
		size = 0;
	}
	
	void insert (int num) {
		// TODO: create the insert method before 1500H
		if (root == NULL) {
	        node* n = addNode(num, false, NULL);
	        root = n;
	        size++;
	        return;
	    }
	
	    node* curr = root;
	    node* parent = NULL;
	    while (curr != NULL) {
	        parent = curr;
	        if (num < curr->elem) {
	            curr = curr->left;
	        } else {
	            curr = curr->right;
	        }
	    }
	
	    node* newNode = addNode(num, true, parent);
	    if (num < parent->elem) {
	        parent->left = newNode;
	    } else {
	        parent->right = newNode;
	    }
	
	    size++;
	    insertBalance(newNode); 
	}
	
	void insertBalance(node* n) {
		while (n != root && n->parent->isRed) {
	        if (n->parent == n->parent->parent->left) {
	            node* uncle = n->parent->parent->right;
	            if (uncle != NULL && uncle->isRed) {
	                n->parent->isRed = false;
	                uncle->isRed = false;
	                n->parent->parent->isRed = true;
	                n = n->parent->parent;
	            } else {
	                if (n == n->parent->right) {
	                    n = n->parent;
	                    zigLeft(n);
	                }
	                n->parent->isRed = false;
	                n->parent->parent->isRed = true;
	                zigRight(n->parent->parent);
	            }
	        } else {
	            node* uncle = n->parent->parent->left;
	            if (uncle != NULL && uncle->isRed) {
	                n->parent->isRed = false;
	                uncle->isRed = false;
	                n->parent->parent->isRed = true;
	                n = n->parent->parent;
	            } else {
	                if (n == n->parent->left) {
	                    n = n->parent;
	                    zigRight(n);
	                }
	                n->parent->isRed = false;
	                n->parent->parent->isRed = true;
	                zigLeft(n->parent->parent);
	            }
	        }
	    }
	    root->isRed = false;
				
	}
	
	void zigRight(node* y) {
	    node* x = y->left;
	    y->left = x->right;
	    if (x->right != NULL) {
	    	x->right->parent = y;
	    }
	    x->parent = y->parent;
	    if (y->parent == NULL) {
	        root = x;
	    } else if (y == y->parent->left) {
	        y->parent->left = x;
	    } else {
	        y->parent->right = x;
	    }
	    x->right = y;
	    y->parent = x;		
	}
	
	void zigLeft(node* x) {
		node* y = x->right;
	    x->right = y->left;
	    if (y->left != NULL) {
	        y->left->parent = x;
	    }
	    y->parent = x->parent;
	    if (x->parent == NULL) {
	        root = y;
	    } else if (x == x->parent->left) {
	        x->parent->left = y;
	    } else {
	        x->parent->right = y;
	    }
	    y->left = x;
	    x->parent = y;
	}
	
	void print () {
		cout << "Size: " << size << endl;
		print("", 'Q', root);
	}
	
	void print(string pre, char loc, node* n) {
		if (!n) {
			return;
		}
		print(pre+"    ", 'L', n->left);
		cout << pre << "|--" << loc << ": " << n->elem;
		
		if (n->isRed) {
			cout << " (R)" << endl;
		} else {
			cout << " (B)" << endl;
		}
		print(pre+"    ", 'R', n->right);
		
	}
};

