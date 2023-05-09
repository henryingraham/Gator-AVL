//
// Created by Henry Ingraham on 2/19/23.
//
#include <iostream>
#include <queue>
#include "sstream"
using namespace std;

struct Student
{
    string gatorID;
    string name;
    int height;
    Student *left;
    Student *right;
public:
    Student() : gatorID(""), name(""), height(1), left(nullptr), right(nullptr) {}
    Student(string idNum, string n) : gatorID(idNum), name(n), height(1), left(nullptr), right(nullptr) {}
};
class AVLTree {
private:
    Student *insertHelper(Student *root, string ufid, string name) {
        if (root == nullptr) {
            Student *s = new Student(ufid, name);
            return s;
        }
        else if (root->gatorID < ufid) {
            root->right = insertHelper(root->right, ufid, name);
        } else {
            root->left = insertHelper(root->left, ufid, name);
        }
        //update heights

        if (getHeight(root->left) > getHeight(root->right))
            root->height = getHeight(root->left) + 1;
        else
            root->height = getHeight(root->right) + 1;

        //calculate new balance factors for rotations
        //left-right > 1:left heavy imbalance
        if (balanceFactor(root) > 1) {
            if (balanceFactor(root->left) > 0) {
                return rightRotate(root);
            } else {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }
            //left-right < -1: right heavy imbalance
        else if (balanceFactor(root) < -1) {
            if (balanceFactor(root->right) < 0) {
                return leftRotate(root);
            } else {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        return root;
    }

    Student *removeHelper(Student *root, string ufid) {
        if (root == nullptr) {
            return root;
        }
        if (ufid < root->gatorID) {
            root->left = removeHelper(root->left, ufid);
        } else if (root->gatorID < ufid) {
            root->right = removeHelper(root->right, ufid);
        } else {
            if (root->left == nullptr || root->right == nullptr) {
                if (root->left != nullptr) {
                    Student *temp = root->left;
                    root->gatorID = temp->gatorID;
                    root->name = temp->name;
                    root->left = nullptr;

                } else if (root->right != nullptr) {
                    Student *temp = root->right;
                    root->gatorID = temp->gatorID;
                    root->name = temp->name;
                    root->right = nullptr;
                } else {
                    root = nullptr;
                }
            } else {
                Student *next = getInorderNext(root->right);
                root->gatorID = next->gatorID;
                root->name = next->name;
                root->right = removeHelper(root->right, next->gatorID);
            }
        }
        if (root == nullptr) {
            return root;
        }
        return root;
    }


    int getHeight(Student *s) {
        if (s == nullptr)
            return 0;
        return max(getHeight(s->left), getHeight(s->right)) + 1;
    }


    Student *leftRotate(Student *s) {
        Student *grandchild = s->right->left;
        Student *newParent = s->right;
        newParent->left = s;
        s->right = grandchild;
        newParent->height = max(getHeight(newParent->left), getHeight(newParent->left)) + 1;
        s->height = max(getHeight(s->left), getHeight(s->left)) + 1;

        return newParent;
    }

    Student *rightRotate(Student *s) {
        Student *grandchild = s->left->right;
        Student *newParent = s->left;
        newParent->right = s;
        s->left = grandchild;
        newParent->height = max(getHeight(newParent->left), getHeight(newParent->left)) + 1;
        s->height = max(getHeight(s->left), getHeight(s->left)) + 1;
        return newParent;
    };

public:
    Student *root = nullptr;

    int balanceFactor(Student *s) {
        if (s == nullptr)
            return 0;
        return getHeight(s->left) - getHeight(s->right);
    }

    Student* searchID(Student *s, string ufid) {
        if (s == nullptr) {
            return s;
        } else if (s->gatorID == ufid) {
            return s;
        } else if (ufid < s->gatorID) {
            return searchID(s->left, ufid);
        } else if (ufid > s->gatorID) {
            return searchID(s->right, ufid);
        }
    }

    string getName(Student *s) {
        if (s == nullptr)
            return "unsuccessful";
        return s->name;
    }

    void searchName(Student *s, string find) {
        queue<Student *> q;
        q.push(root);
        bool success = false;
        for (int i = 1; i <= getHeight(root); ++i) {
            int levelNodes = q.size();
            for (int j = 0; j < levelNodes; ++j) {
                if (q.front()->left != nullptr)
                    q.push(q.front()->left);
                if (q.front()->right != nullptr)
                    q.push(q.front()->right);
                if (q.front()->name == find) {
                    cout << q.front()->gatorID << endl;
                    success = true;
                }
                q.pop();

            }
        }
        if (!success)
            cout << "unsuccessful" << endl;

    }

    Student* getInorderNext(Student* s){
        Student* current = s;
        while(current->left != nullptr){
            current = current->left;
        }
        return current;
    }
    void removeID(string ufid){
        root = removeHelper(root, ufid);
    }

    void insertNameID(string ufid, string name){
        this->root = insertHelper(root, ufid, name);
    }

    void printInorder(Student* s, string& str){
        if(s != nullptr){
            printInorder(s->left, str);
            str = str + s->name + ", ";
            printInorder(s->right, str);
        }

    }
    void printPreorder(Student* s, string& str){
        if(s != nullptr){
            str = str + s->name + ", ";
            printPreorder(s->left, str);
            printPreorder(s->right, str);
        }
    }
    void printPostorder(Student* s, string& str){
        if(s != nullptr){
            printPostorder(s->left, str);
            printPostorder(s->right, str);
            str = str + s->name + ", ";
        }
    }
    void printLevelCount(Student* s){
        if (root == nullptr)
            cout << 0 << endl;
        else
            cout << root->height << endl;
    }
    Student* removeInorder(Student* root, int& count, int n){
        if (++count == n ){
            if (root->left == nullptr) {
                Student *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Student *temp = root->left;
                delete root;
                return temp;
            }
            else{
                Student* temp = getInorderNext(root->right);
                root->gatorID = temp->gatorID;
                root->name = temp->name;
                root->right = removeHelper(root->right, temp->gatorID);
            }
        }
        root->right = removeInorder(root->right, count, n);

            return root;
    }

};
