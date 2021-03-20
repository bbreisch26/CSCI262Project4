/*
	animal.cpp

	author: L. Henke and C. Painter-Wakefield
	date: 04 November 2019

	Animal/20 questions program for CSCI 262, starter code.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>

using namespace std;

class node {
public:
    string data;
    node* left;
    node* right;
};

void play_game(node*, queue<int>& qe);
node* read_game_tree();
node* read_preorder(ifstream& fin);
void write_preorder(ofstream& fout, node*);
void write_game_tree(node*);
void delete_game_tree(node*);

// TODO: Add helper method templates here, such as read_preorder().

/**
 * Handles showing the main menu/basic UI
 */
int main() {
	node* root = read_game_tree();
	if (root == NULL) return -1;

	while (true) {
		string tmp;
		int choice;

		cout << "Welcome to 20 questions!" << endl;
		cout << "  1) Play the game" << endl;
		cout << "  2) Save the game file" << endl;
		cout << "  3) Quit" << endl;
		cout << "Please make your selection: ";
		getline(cin, tmp);
		choice = atoi(tmp.c_str());
        queue<int> qe;
		switch (choice) {
		    case 1:
    			play_game(root,qe);
    			break;
    		case 2:
    			write_game_tree(root);
    			break;
    		case 3:
    			break;
    		default:
    		    cout << choice << endl;
    			cout << "Sorry, I don't understand." << endl << endl;
		}
		if (choice == 3) break;
	}

	delete_game_tree(root);
	return 0;
}

/**
 * Sets up the recursive call to the read_preorder
 * @return root of the tree
 */
node* read_game_tree() {
    // TODO: Implement me. See implementation hints! Reading is more complex than it may seem.
    ifstream fin("animal_game_tree.txt", std::ifstream::in);
    node* root = read_preorder(fin);
    fin.close();
    return root;
}
node* read_preorder(ifstream& fin) {
    node* root = new node;
    string line;
    getline(fin, line);
    root->data = line;
    cout << line << endl;
    if (line[1] == 'Q') {
        root->left = read_preorder(fin);
        root->right = read_preorder(fin);
    } else {
        root->left = nullptr;
        root->right = nullptr;
        return root;
    }
    return root;
}
/**
 * Plays the game
 * @param root Root of the game tree
 */
void play_game(node* root, queue<string>& qe) {
    if(root == nullptr) {
        cout << "something bad has happened" << endl;
        return;
    }
    // TODO: Implement me.
    node* next = new node;
    if(root->left != nullptr && root->right != nullptr) {
        string line = root->data;
        line = line.substr(3);

        cout << line << endl;
        char choice;
        cin >> choice;
        if(tolower(choice) == 'y') {
            next = root->left;
        }
        else if(tolower(choice) == 'n') {
            next = root->right;
        }
    }
    else {
        //leaf
        string line = root->data;
        line = line.substr(3);
        cout << line << endl;
        char choice;
        cin >> choice;
        if(choice == 'y') {
            cout << "YAY! I guessed your animal!" << endl;
            return;
        }
        else if(choice == 'n') {
            cout << "BOO! I don't know!" << endl;
            return;
        }
    }
    play_game(next);
}

/**
 * Writes the game tree, sets up a recursive call to write_preorder();
 * @param root The root of the tree
 */
void write_game_tree(node* root) {
	ofstream fout("fe.txt", std::ifstream::out);
	write_preorder(fout, root);
	fout.close();
}
void write_preorder(ofstream& fout, node* root) {
    if(root != nullptr) {
        fout << root->data << endl;
        if(root->left != nullptr && root->right != nullptr) {
            write_preorder(fout, root->left);
            write_preorder(fout, root->right);
        }
    }
    else {
        return;
    }

}
/**
 * Deletes the game tree
 * @param root Root of the game tree
 */
void delete_game_tree(node* root) {
    // Optional. Do a post-order deletion of the game tree.
    // This isn't strictly needed as the program exits after this is called,
    // which frees up all the memory anyway.
}
