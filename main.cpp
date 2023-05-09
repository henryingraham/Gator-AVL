#include <iostream>
#include <queue>
#include "sstream"
#include "AVLTree.h"
using namespace std;
/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

int main(){
    AVLTree tree;
    int numCommands;

    string num;
    getline(cin, num);
    numCommands = stoi(num);

    for (int i = 0; i < numCommands+1; ++i) {
        string command;
        string name;
        string number;
        string searchTerm;

        string line;
        getline(cin, line);
        istringstream in(line);
        in >> command;

        if (command == "insert"){
            getline(in, name, '"');
            getline(in, name, '"');
            in >> number;
            bool success = true;
            for (char c: number) {
                if (!isdigit(c)) {
                    success = false;
                }
            }
            for (char c: name) {
                if (!isalpha(c)) {
                    success = false;
                }
            }
            if (number.size() == 8 && success) {
                cout << "successful" << endl;
                tree.insertNameID(number, name);
            } else
                cout << "unsuccessful" << endl;

        }

        else if (command == "remove"){
            in >> number;
            if (tree.searchID(tree.root, number) != nullptr){
                cout << "successful" << endl;
                tree.removeID(number);
            } else
                cout << "unsuccessful" << endl;
        }

        else if (command == "search"){
            in >> searchTerm;
            if (searchTerm.at(0) == '"'){
                searchTerm = searchTerm.substr(1, searchTerm.size()-2);
                tree.searchName(tree.root, searchTerm);
            }
            else{
                bool success = true;
                for (char c: searchTerm) {
                    if (!isdigit(c)) {
                        success = false;
                    }
                }
                if (!success)
                    cout << "unsuccessful" << endl;
                else {
                    if(tree.searchID(tree.root, searchTerm) != nullptr)
                        cout << tree.searchID(tree.root, searchTerm)->name << endl;
                    else
                        cout << "unsuccessful" << endl;
                }
            }

        }

        else if (command == "printInorder"){
            string s = "";
            if (tree.root == nullptr)
                cout << 0;
            else
                tree.printInorder(tree.root, s);
            cout << s.substr(0,s.size()-2);
            cout << endl;
        }

        else if (command == "printPreorder"){
            string s = "";
            if (tree.root == nullptr)
                cout << 0;
            else
                tree.printPreorder(tree.root, s);
            cout << s.substr(0,s.size()-2);
            cout << endl;
        }

        else if (command == "printPostorder"){
            string s = "";
            if (tree.root == nullptr)
                cout << 0;
            else
                tree.printPostorder(tree.root, s);
            cout << s.substr(0,s.size()-2);
            cout << endl;
        }

        if (command == "printLevelCount"){
            tree.printLevelCount(tree.root);
        }

        else if (command == "removeInorder"){
            int count = 0;
            in >> number;
            if (tree.removeInorder(tree.root, count, stoi(number)) == nullptr)
                cout << "unsuccessful" << endl;
            else
                cout << "successful" << endl;

        }
    }
    return 0;
}

