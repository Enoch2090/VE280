//     Subclass            Children                                        Description
//     --------            --------                                        -----------
//   ASTNode:                                                              the base class
//     ProgramNode         DeclListNode                                    the whole program
//     DeclListNode        a list of DeclNode                              a list of declarations, e.g. int a; void f(){}
//
//     DeclNode:                                                           a declaration
//       VarDeclNode       TypeNode, IdNode                                a variable declaration, e.g. int a;
//       FnDeclNode        TypeNode, IdNode, FormalsListNode, FnBodyNode   a function definition, e.g. void f(...){...}
//       FormalDeclNode    TypeNode, IdNode                                a funtion parameter declaration, e.g. int a
//
//     FormalsListNode     a list of FormalDeclNode                        a list of function parameters, e.g. (int a, bool b)
//     FnBodyNode          DeclListNode, StmtListNode                      the function body
//     StmtListNode        a list of StmtNode                              a list of statements
//
//     TypeNode:                                                           a type keyword
//       IntNode           -- none --                                      the keyword int
//       BoolNode          -- none --                                      the keyword bool
//       VoidNode          -- none --                                      the keyword void
//
//     StmtNode:                                                           a statement end with semicolon ;
//       AssignStmtNode      AssignNode                                    an assign statement, e.g. a=1;
//       PostIncStmtNode     ExpNode                                       a post increase statement, e.g. a++;
//       PostDecStmtNode     ExpNode                                       a pose decrease statement, e.g. a--;
//
//     ExpNode:                                                            an expression
//       IntLitNode          -- none --                                    an int literal, e.g. 1
//       TrueNode            -- none --                                    the keyword true
//       FalseNode           -- none --                                    the keyword false
//       IdNode              -- none --                                    an identifier, e.g. a, f, main
//       AssignNode          ExpNode, ExpNode                              an assignemnt expression, e.g. a=1 (notice no ";")

#include <iostream>
#include <string>

using namespace std;

// constants used
#define MAX_NUM_NODE 100
#define MAX_NUM_CHILD 10
#define SIZE_TAB 4

// forward declaration of classes
class ASTNode;
class ProgramNode;
class DeclListNode;
class DeclNode;
class VarDeclNode;
class FnDeclNode;
class FormalDeclNode;
class FormalsListNode;
class FnBodyNode;
class StmtListNode;
class TypeNode;
class IntNode;
class BoolNode;
class VoidNode;
class StmtNode;
class AssignStmtNode;
class PostIncStmtNode;
class PostDecStmtNode;
class ExpNode;
class IntLitNode;
class TrueNode;
class FalseNode;
class IdNode;
class AssignNode;

// **********************************************************************
// ASTNode class (base class for all other kinds of nodes)
// **********************************************************************

class ASTNode
{
public:
    ASTNode(int n = 0) : num_child(n) {}
    virtual ~ASTNode(){};

    int numChild()
    {
        return num_child;
    }

    void setChild(int index, ASTNode *ptr)
    {
        children[index] = ptr;
    }

    void addIndent(int indent)
    {
        for (int i = 0; i < indent; ++i)
        {
            cout << " ";
        }
    }

    virtual void unparse(int indent) = 0;

protected:
    int num_child;
    ASTNode *children[MAX_NUM_CHILD];
};

// **********************************************************************
// ProgramNode,  DeclListNode, FormalsListNode, FnBodyNode, StmtListNode
// **********************************************************************

class ProgramNode : public ASTNode
{
public:
    ProgramNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent)
    {
        children[0]->unparse(indent); // unparse DeclListNode
    }
};

class DeclListNode : public ASTNode
{
public:
    DeclListNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent)
    {
        for (int i = 0; i < num_child; ++i)
        {
            children[i]->unparse(indent); // unparse DeclNode
        }
    }
};

class FormalsListNode : public ASTNode
{
public:
    FormalsListNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent)
    {
        for (int i = 0; i < num_child; ++i)
        {
            children[i]->unparse(indent); // unparse FormalNode
            if (i != num_child - 1)
            {
                cout << ", ";
            }
        }
    }
};

class FnBodyNode : public ASTNode
{
public:
    FnBodyNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent)
    {
        for (int i = 0; i < num_child; ++i)
        {
            children[i]->unparse(indent + 1); // unparse DeclListNode and StmtListNode
        }
    }
};

class StmtListNode : public ASTNode
{
public:
    StmtListNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent)
    {
        for (int i = 0; i < num_child; ++i)
        {
            children[i]->unparse(indent); // unparse StmtNode
        }
    }
};

// **********************************************************************
// DeclNode and its subclasses
// **********************************************************************

class DeclNode : public ASTNode
{
public:
    DeclNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class VarDeclNode : public DeclNode
{
public:
    VarDeclNode(int n = 0) : DeclNode(n) {}

    void unparse(int indent)
    {
        addIndent(indent);
        children[0]->unparse(indent); // unparse TypeNode
        cout << " ";
        children[1]->unparse(indent); // unparse IdNode
        cout << ";" << endl;
    }
};

class FnDeclNode : public DeclNode
{
public:
    FnDeclNode(int n = 0) : DeclNode(n) {}

    void unparse(int indent)
    {
        addIndent(indent);
        children[0]->unparse(indent); // unparse TypeNode
        cout << " ";
        children[1]->unparse(indent); // unparse IdNode
        cout << "(";
        children[2]->unparse(indent); // unparse FormalsListNode
        cout << ") {" << endl;
        children[3]->unparse(indent); // unparse FnBodyNode
        addIndent(indent);
        cout << "}" << endl;
    }
};

class FormalDeclNode : public DeclNode
{
public:
    FormalDeclNode(int n = 0) : DeclNode(n) {}

    void unparse(int indent)
    {
        children[0]->unparse(indent); // unparse TypeNode
        cout << " ";
        children[1]->unparse(indent); // unparse IdNode
    }
};

// **********************************************************************
// TypeNode and its Subclasses
// **********************************************************************

class TypeNode : public ASTNode
{
public:
    TypeNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class IntNode : public TypeNode
{
public:
    IntNode(int n = 0) : TypeNode(n) {}

    void unparse(int indent)
    {
        cout << "int";
    }
};

class BoolNode : public TypeNode
{
public:
    BoolNode(int n = 0) : TypeNode(n) {}

    void unparse(int indent)
    {
        cout << "bool";
    }
};

class VoidNode : public TypeNode
{
public:
    VoidNode(int n = 0) : TypeNode(n) {}

    void unparse(int indent)
    {
        cout << "void";
    }
};

// **********************************************************************
// StmtNode and its subclasses
// **********************************************************************

class StmtNode : public ASTNode
{
public:
    StmtNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class AssignStmtNode : public StmtNode
{
public:
    AssignStmtNode(int n = 0) : StmtNode(n) {}

    void unparse(int indent)
    {
        addIndent(indent);
        children[0]->unparse(indent); // unparse AssignNode
        cout << ";" << endl;
    }
};

class PostIncStmtNode : public StmtNode
{
public:
    PostIncStmtNode(int n = 0) : StmtNode(n) {}

    void unparse(int indent)
    {
        addIndent(indent);
        children[0]->unparse(indent); // unparse ExpNode
        cout << "++";
        cout << ";" << endl;
    }
};

class PostDecStmtNode : public StmtNode
{
public:
    PostDecStmtNode(int n = 0) : StmtNode(n) {}

    void unparse(int indent)
    {
        addIndent(indent);
        children[0]->unparse(indent); // unparse ExpNode
        cout << "--";
        cout << ";" << endl;
    }
};

// **********************************************************************
// ExpNode and its subclasses
// **********************************************************************

class ExpNode : public ASTNode
{
public:
    ExpNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class IntLitNode : public ExpNode
{
public:
    IntLitNode(int n = 0, int val = 0)
    {
        num_child = n;
        myVal = val;
    }

    void unparse(int indent)
    {
        cout << this->myVal;
    }

private:
    int myVal;
};

class TrueNode : public ExpNode
{
public:
    TrueNode(int n = 0) : ExpNode(n) {}

    void unparse(int indent)
    {
        cout << "true";
    }
};

class FalseNode : public ExpNode
{
public:
    FalseNode(int n = 0) : ExpNode(n) {}

    void unparse(int indent)
    {
        cout << "false";
    }
};

class IdNode : public ExpNode
{
public:
    IdNode(int n = 0, string str = "")
    {
        num_child = n;
        myName = str;
    }

    virtual void unparse(int indent)
    {
        cout << this->myName;
    }

private:
    string myName;
};

class AssignNode : public ExpNode
{
public:
    AssignNode(int n = 0) : ExpNode(n) {}

    void unparse(int indent)
    {
        children[0]->unparse(indent); // unparse ExpNode1
        cout << " = ";
        children[1]->unparse(indent); // unparse ExpNode2
    }
};

int main()
{
    int nodeNum;
    int paramVal;
    int childNodeNum;
    string nodeName;
    string paramName;
    ASTNode *nodes[MAX_NUM_NODE];
    cin >> nodeNum;
    for (int nodeIndex = 0; nodeIndex < nodeNum; nodeIndex++)
    {
        cin >> nodeName;
        if (nodeName == "IdNode")
        {
            cin >> childNodeNum >> paramName;
            nodes[nodeIndex] = new IdNode(childNodeNum, paramName);
        }
        else if (nodeName == "IntLitNode")
        {
            cin >> childNodeNum >> paramVal;
            nodes[nodeIndex] = new IntLitNode(childNodeNum, paramVal);
        }
        else if (nodeName == "TrueNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new TrueNode(childNodeNum);
        }
        else if (nodeName == "FalseNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new FalseNode(childNodeNum);
        }
        else if (nodeName == "AssignNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new AssignNode(childNodeNum);
        }
        else if (nodeName == "IntNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new IntNode(childNodeNum);
        }
        else if (nodeName == "BoolNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new BoolNode(childNodeNum);
        }
        else if (nodeName == "VoidNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new VoidNode(childNodeNum);
        }

        else if (nodeName == "PostIncStmtNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new PostIncStmtNode(childNodeNum);
        }
        else if (nodeName == "PostDecStmtNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new PostDecStmtNode(childNodeNum);
        }
        else if (nodeName == "AssignStmtNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new AssignStmtNode(childNodeNum);
        }
        else if (nodeName == "VarDeclNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new VarDeclNode(childNodeNum);
        }
        else if (nodeName == "FnDeclNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new FnDeclNode(childNodeNum);
        }
        else if (nodeName == "FormalDeclNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new FormalDeclNode(childNodeNum);
        }
        else if (nodeName == "DeclListNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new DeclListNode(childNodeNum);
        }
        else if (nodeName == "FormalsListNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new FormalsListNode(childNodeNum);
        }
        else if (nodeName == "FnBodyNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new FnBodyNode(childNodeNum);
        }
        else if (nodeName == "StmtListNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new StmtListNode(childNodeNum);
        }
        else if (nodeName == "ProgramNode")
        {
            cin >> childNodeNum;
            nodes[nodeIndex] = new ProgramNode(childNodeNum);
        }
    }
    int len = nodeNum - 1;
    for (int nodeIndex = nodeNum - 1; nodeIndex >= 0; nodeIndex--)
    {
        for (int childIndex = len; childIndex > len - nodes[nodeIndex]->numChild(); childIndex--)
        {
            nodes[nodeIndex]->setChild(nodes[nodeIndex]->numChild() - (len - childIndex) - 1, nodes[childIndex]);
        }
        len -= nodes[nodeIndex]->numChild();
    }
    // call unparse() of root to print whole program
    ASTNode *root = nodes[0];
    root->unparse(0);
    for (int nodeIndex = 0; nodeIndex < nodeNum; nodeIndex++)
    {
        delete nodes[nodeIndex];
    }
}
