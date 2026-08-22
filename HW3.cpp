#include <iostream>
#include <string>

using namespace std;

// Custom Node for the Linked List Stack
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T d) : data(d), next(nullptr) {}
};

// Requirement 1: Implement a stack using a linked list without predefined classes
template <typename T>
class Stack {
private:
    Node<T>* topNode;
public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T item) {
        Node<T>* newNode = new Node<T>(item);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop() {
        if (!isEmpty()) {
            Node<T>* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    T top() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return topNode->data;
    }

    bool isEmpty() {
        return topNode == nullptr;
    }
};

// Requirement 2: Implement StringProcessor class
class StringProcessor {
public:
    string processStringInput(string s) {
        Stack<char> charStack;

        // Push non-backspaces, pop on backspace '<'
        for (char c : s) {
            if (c == '<') {
                if (!charStack.isEmpty()) {
                    charStack.pop();
                }
            }
            else {
                charStack.push(c);
            }
        }

        string result = "";
        // Reconstruct string (popping reverses it, so prepend)
        while (!charStack.isEmpty()) {
            result = charStack.top() + result;
            charStack.pop();
        }
        return result;
    }

    bool isPalindrome(string s) {
        Stack<char> charStack;

        for (char c : s) {
            charStack.push(c);
        }

        // Check if string reads the same backward by popping from stack
        for (char c : s) {
            if (charStack.top() != c) {
                return false;
            }
            charStack.pop();
        }
        return true;
    }
};

// Requirement 3: Test functions in main()
int main() {
    StringProcessor processor;
    string input;

    cout << "Enter a string (< for backspace): ";
    getline(cin, input);

    string processedString = processor.processStringInput(input);

    cout << "After processing backspaces, the string becomes: " << processedString << endl;

    if (processor.isPalindrome(processedString)) {
        cout << processedString << " is a palindrome" << endl;
    }
    else {
        cout << processedString << " is NOT a palindrome" << endl;
    }

    return 0;
}