//This program creates a binary search tree which can add, remove, and search nodes
//Author: Mark Daniloff
//Date: 3/18/2020

#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

//Struct for node
struct Node {
  Node* right;
  Node* left;
  Node* next;
  char data;
};

//Struct for printing the tree
struct Trunk {
  Trunk *prev;
  char str[10];

  
};
//Function initializations
void manualInput(Node* &head);
void fileInput(Node* &head);
void parseInput(Node* &head, char* input, int* token, int* heaparr, int num, int count, int total, int exp, int j);
void insert(int* arr, int n, Node* &head);
void buildTree(int val, Node* &head, Node* current);
void showTrunks(Trunk *p);
void printTree(Node* head, Trunk *prev, bool isLeft);

int main() {
  //Declare nodes to null
  Node* head = NULL;
  Node* right = NULL;
  Node* left = NULL;
  //The first half of this project is basically the same as heap
  bool running = true;
  int mainInput;
  int mainInput2;
  //Ask user for input
  cout << "Enter 1 to enter through keyboard, and 2 to enter through a file" << endl;
  cin >> mainInput;
  cin.ignore();
  //Manual input
  if (mainInput == 1) {
    manualInput(head);
  }
  //File input
  if (mainInput == 2) {
    fileInput(head);
  }
  //Ask user if they want to add, remove, search, display, or quit
  while (running == true) {
    cout << "Enter 1 to add, 2 to remove, 3 to search, 4 to display, or 5 to quit" << endl;
    cin >> mainInput2;
    cin.ignore();
    //Add
    if (mainInput2 == 1) {

    }
    //Remove
    if (mainInput2 == 2) {

    }
    //Search
    if (mainInput2 == 3) {

    }
    //Display
    if (mainInput2 == 4) {

    }
    //Quit
    if (mainInput2 == 5) {
      running = false;
    }
  }
}

//Keyboard entry
void manualInput(Node* &head) {
  char input[100];
  int token[100];
  int ftoken[100];
  //Ask for input
  cout << "Enter a series of numbers separated by spaces" << endl;
  cin.get(input, 100);
  int count = 0;
  int total = 0;
  int num = 0;
  int exp = 0;
  int j = 0;
  //Parse the input
  parseInput(head, input, token, ftoken, num, count, total, exp, j);
  
}

//File entry
void fileInput(Node* &head) {
  //Initialize variables
  char input[100];
  int token[100];
  int ftoken[100];
  int count = 0;
  int total = 0;
  int num = 0;
  int exp = 0;
  int j = 0;
  //Ask user for filename
  char filename[100];
  cout << "Enter the name of the file " << endl;
  cin.get(filename, 100);
  cin.ignore();
  //This code is from Stefan Ene, period 3, who in turn got it from Omar Nassar. This code reads in a file
  streampos size;
  //in opens the file, binary makes sure new line characters aren't translated,
  //and ate means that the output position starts at the end of the file
  ifstream file(filename, ios::in | ios::binary | ios::ate);
  //If the file exists
  if (file.is_open()) {
    //Get input position
    size = file.tellg();
    //Seek to 0 characters from the beginning of the file
    file.seekg(0, ios::beg);
    //Read the file and assign to input
    file.read(input, size);
    //Close the file
    file.close();
    //Parse the input
    parseInput(head, input, token, ftoken, num, count, total, exp, j);
  }
  //If the file can't be opened
  else {
    cout << "The file can't be opened" << endl;
  }
}

//Parse the input
//I used the same parsing method here that I did in Heap
void parseInput(Node* &head, char* input, int* token, int* heaparr, int num, int count, int total, int exp, int j) {
  int outputarr[100];
  //Set the arrays to all zeros
  for (int i = 0; i < 100; i++) {
    heaparr[i] = 0;
    outputarr[i] = 0;
    token[i] = 0;
  }
  for (int i = 0; i < 100; i++) {
    //Null character
    if (input[i] == '\0') {
      i = 100;
    }
    //Single digit number
    else if (isdigit(input[i]) && !isdigit(input[i+1]) && input[i] != '\0') {
      token[i] = (int)input[i] - 48;
    }
    //Multiple digit number
    else if (isdigit(input[i]) && isdigit(input[i+1])) {
      //While input[i] isn't a space
      while (isdigit(input[i])) {
	count++;
	i++;
      }
      //If input[i] is a space
      if (!isdigit(input[i])) {
	for (int j = count; j > 0; j--) {
	  num = input[i-j] - 48;
	  exp = pow(10, j-1);
	  total += num * exp;
	}
      }
      token[i] = total;
      total = count = 0;
    }
  }
  heaparr[0] = 0;
  //Place parsed values into another array with no zeros
  for (int i = 0; i < 100; i++) {
    if (token[i] != 0) {
      heaparr[j] = token[i];
      j++;
      count++;
    }
  }
  insert(heaparr, count, head);
}

//Insert nodes into tree
void insert(int* heaparr, int n, Node* &head) {
  for (int i = 0; i < n; i++) {
    buildTree(heaparr[i], head, head);
  }
}
//Build tree
void buildTree(int val, Node* &head, Node* current) {
  //If the head is NULL
  if (head == NULL) {
    //Set the head to the first index in the array
    head = new Node();
    head->data = val;
  }
  //If the head isn't NULL
  else if (head != NULL) {
    //If val is greater than head->val
    if (val > head->data) {
      //If head->right is NULL
      if (head->right == NULL) {
	current->right = new Node();
	current->right->data = val;
      }
      //If head->right isn't NULL
      else if (head->right != NULL) {
	buildTree(val, head, current->right);
      }
    }
    //If val is less than head->val
    else if (val < head->data) {
      //If head->left is NULL
      if (head->left == NULL) {
	current->left = new Node();
	current->left->data = val;
      }
      //If head->left isn't NULL
      else if (head->left != NULL) {
	buildTree(val, head, current->left);
      }
    }
  }
}
//These print tree functions are partially from techiedelight with help from Stefan Ene, period 3
//www.com/techiedelight.com/c-program-print-binary-tree
//www.com/github.com/Stefanene/Binary-Search-Tree/blob/master/main.cpp

//Print branches of the binary tree
void showTrunks(Trunk *p) {
  //If the trunk is empty
  if (p == NULL) {
    return;
  }
  //Recursively call the function
  showTrunks(p->prev);
  cout << p->str << endl;
}
