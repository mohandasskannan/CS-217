/*
    Binary trees
*/

#include <iostream>
#include <queue>
#include <string> // Added this header

using namespace std;

class Node
{
private:
    char data;
    Node* left;
    Node* right;
    Node* parent;

public:
    Node(int d)
    {
        data = d;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    friend class ExpressionTree;
};

/* * Expression tree for algebraic expression, assuming every operand has one single digit
 */
class ExpressionTree
{
private:
    Node* root;

    /*
     * Helper function for deleting a subtree rooted at x;
     * Called by destructor method to delete the entire tree
     */
    void destroy(Node* x)
    {
        if (x == nullptr) 				// empty subtree
            return;
        else							// the subtree rooted at x is not empty
        {
            destroy(x->left);
            destroy(x->right);
            delete x;
        }
    }

    /*
     * Recursive helper function to build an expression subtree
     * for a given subexpression (in string exp between indices left~right)
     * Return pointer to the root of the subtree
     */
    Node* build(string exp, int left, int right)
    {
        Node* newNode = nullptr;

        if (left == right)                              // expression only contains an operand
        {
            newNode = new Node(exp.at(left));
            return (newNode);
        }

        int loc = findAddSubtract(exp, left, right);   // try to find the right-most + or - that is outside the outer-most parentheses
        if (loc != -1)                                   // right-most + or - outside the outer-most parentheses was found
            newNode = new Node(exp.at(loc));     	// create a node for + or -
        else
        {
            loc = findMulDiv(exp, left, right);        // try to find the right-most * or / that is outside the outer-most parentheses
            if (loc != -1)                               // right-most * or / outside the outer-most parentheses was found
                newNode = new Node(exp.at(loc));     	// create a node for * or /
        }

        if (loc == -1)                                  // no +, -, * or / outside the outer-most parentheses
            return build(exp, left + 1, right - 1); 		// eliminate outer-most parentheses 
        else
        {
            newNode->left = build(exp, left, loc - 1);		// build the left subtree of the root
            newNode->right = build(exp, loc + 1, right);		// build the right subtree of the root
            return newNode;
        }
    }

    /**
     * * Find the right-most + or - that is outside the outer-most parentheses, and return its index
     */
    int findAddSubtract(string exp, int left, int right)
    {
        int count = 0;                                  				// 0: currently outside parentheses
        int loc = right;                                				// scan the expression starting from the right end

        while (loc >= left)
        {
            if (exp.at(loc) == ')')
                count++;
            else if (exp.at(loc) == '(')
                count--;
            else if (exp.at(loc) == '+' || exp.at(loc) == '-')
            {
                if (count == 0)                                      // found a + or - outside parentheses
                    return loc;
            }

            loc--;
        }

        return -1;		// not found
    }

    /**
     * * Find the right-most * or / that is outside the outer-most parentheses, and return its index
     */
    int findMulDiv(string exp, int left, int right)
    {
        int count = 0;                                       // 0: currently outside parentheses
        int loc = right;                                     // scan the expression starting from the right end

        while (loc >= left)
        {
            if (exp.at(loc) == ')')
                count++;
            else if (exp.at(loc) == '(')
                count--;
            else if (exp.at(loc) == '*' || exp.at(loc) == '/')
            {
                if (count == 0)
                    return loc;
            }

            loc--;
        }
        return -1;
    }

    // helper function to traverse the subtree rooted at x and generate infix expression
    void infix(Node* x)
    {
        if (x != nullptr)
        {
            if (x->data != '+' && x->data != '-' && x->data != '*' && x->data != '/')	// x is an operend
                cout << x->data << " ";
            else
            {
                cout << "(";
                infix(x->left);
                cout << x->data << " ";
                infix(x->right);
                cout << ")";
            }
        }
    }

    // helper function to traverse the subtree rooted at x and generate prefix expression
    void prefix(Node* x)
    {
        if (x != nullptr)
        {
            cout << x->data << ' ';
            prefix(x->left);
            prefix(x->right);
        }
    }

    // helper function to traverse the subtree rooted at x and generate postfix expression
    void postfix(Node* x)
    {
        if (x != nullptr)
        {
            postfix(x->left);
            postfix(x->right);
            cout << x->data << ' ';
        }
    }

public:
    ExpressionTree()
    {
        root = nullptr;			// contruct an empty tree
    }

    ~ExpressionTree()
    {
        destroy(root);			// delete all nodes in the tree
    }

    /**
     * * Build an expression tree based on the given algebraic expression (specified by string exp)
     */
    void build(string exp)
    {
        root = build(exp, 0, exp.length() - 1);
    }

    /**
     * * Traverse the expression tree and generate prefix, infix or postfix expression
     * Parameter flag: 0 - prefix    1 - infix    2 - postfix
     */
    int traverse(int flag)
    {
        switch (flag)
        {
        case 1:
            prefix(root);
            break;
        case 2:
            infix(root);
            break;
        case 3:
            postfix(root);
            break;
        default:
            flag = -1;
        }
        return flag;
    }

    void infix()
    {
        infix(root);
        cout << endl;
    }

    void prefix()
    {
        prefix(root);
        cout << endl;
    }

    void postfix()
    {
        postfix(root);
        cout << endl;
    }

    int evaluate() {
        return evaluate(root);
    }

    int evaluate(Node* x) {
        if (x == nullptr) {
            return 0;
        }

        if (x->left == nullptr && x->right == nullptr) {
            return x->data - '0';
        }

        int leftVal = evaluate(x->left);
        int rightVal = evaluate(x->right);

        if (x->data == '+') return leftVal + rightVal;
        if (x->data == '-') return leftVal - rightVal;
        if (x->data == '*') return leftVal * rightVal;
        if (x->data == '/') return leftVal / rightVal;

        return 0;
    }
};

int main()
{
    ExpressionTree tree;

    string exp;
    cout << "Enter an infix expression: ";
    cin >> exp;
    tree.build(exp);

    int option;
    do
    {
        cout << "\nChoose from: " << endl;
        cout << "1: Prefix " << endl;
        cout << "2: Infix " << endl;
        cout << "3: Postfix " << endl;
        cout << "Other to exit " << endl;

        cin >> option;
        if (tree.traverse(option) < 0)  break;
        cout << endl;
    } while (true);

    cout << "Evaluation result = " << tree.evaluate() << endl;

    return 0;
}