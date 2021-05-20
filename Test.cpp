#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

#include "BinaryTree.hpp"
#include "doctest.h"
using namespace ariel;
using namespace std;

bool t = true; // delete?
TEST_CASE("Basic <int> tree")
{
    BinaryTree<int> intTree;
    CHECK_NOTHROW(intTree.add_root(1)
                      .add_left(1, 9)    // Now 9 is the left child of 1
                      .add_left(9, 4)    // Now 4 is the left child of 9
                      .add_right(9, 5)   // Now 5 is the right child of 9
                      .add_right(1, 8)   // Now 8 is the right child of 1
                      .add_right(1, 3)   // Now 3 is the left child of 1, instead of 8.
                      .add_left(1, 2)    // Now 2 is the left child of 1, instead of 9 (the children of 9 remain in place)
                      .add_left(1, 2);); // Now 2 is the left child of 1.

    cout << intTree << endl;

    vector<int> pre{1, 2, 4, 5, 3};
    vector<int> in{4, 2, 5, 1, 3};
    vector<int> post{4, 5, 2, 3, 1};
    unsigned long i = 0, j = 0, k = 0, t = 0;
    for (auto it = intTree.begin_preorder(); it != intTree.end_preorder(); ++it)
    {
        CHECK(*it == pre.at(i));
    }
    for (auto it = intTree.begin_inorder(); it != intTree.end_inorder(); ++it)
    {
        CHECK(*it == in.at(j));
    }
    for (auto it = intTree.begin_postorder(); it != intTree.end_postorder(); ++it)
    {
        CHECK(*it == in.at(k));
    }

    for (int element : intTree)
    { // this should work like inorder
        CHECK(element == in.at(t));
    }
}

TEST_CASE("Basic <char> tree")
{
    BinaryTree<char> charTree;
    CHECK_NOTHROW(charTree.add_root('1')
                      .add_left('1', '9')    // Now '9' is the left child of '1'
                      .add_left('9', '4')    // Now '4' is the left child of '9'
                      .add_right('9', '5')   // Now '5' is the right child of '9'
                      .add_right('1', '8')   // Now '8' is the right child of '1'
                      .add_right('1', '3')   // Now '3' is the left child of '1', instead of '8'.
                      .add_left('1', '2')    // Now '2' is the left child of '1', instead of '9' (the children of '9' remain in place)
                      .add_left('1', '2');); // Now '2' is the left child of '1'.

    cout << charTree << endl;

    std::vector<char> pre{'1', '2', '4', '5', '3'};
    std::vector<char> in{'4', '2', '5', '1', '3'};
    std::vector<char> post{'4', '5', '2', '3', '1'};
    unsigned long i = 0, j = 0, k = 0, t = 0;
    for (auto it = charTree.begin_preorder(); it != charTree.end_preorder(); ++it)
    {
        CHECK(*it == pre.at(i));
    }
    for (auto it = charTree.begin_inorder(); it != charTree.end_inorder(); ++it)
    {
        CHECK(*it == in.at(j));
    }
    for (auto it = charTree.begin_postorder(); it != charTree.end_postorder(); ++it)
    {
        CHECK(*it == post.at(k));
    }

    for (char element : charTree)
    { // this should work like inorder
        CHECK(element == in.at(t));
    }
}

class studentName
{
    string name;

public:
    studentName(string s) : name(s) {}

    bool operator==(const studentName &rhs) const { return name == rhs.name; }

    friend ostream &operator<<(ostream &os, const studentName &s_name)
    {
        return (os << s_name.name);
    }
};

TEST_CASE("Object tree case")
{
    BinaryTree<studentName> studTree;

    CHECK_NOTHROW(studTree.add_root(studentName("1"))
                      .add_left(studentName("1"), studentName("9"))    // Now '9' is the left child of '1'
                      .add_left(studentName("9"), studentName("4"))    // Now '4' is the left child of '9'
                      .add_right(studentName("9"), studentName("5"))   // Now '5' is the right child of '9'
                      .add_right(studentName("1"), studentName("8"))   // Now '8' is the right child of '1'
                      .add_right(studentName("1"), studentName("3"))   // Now '3' is the left child of '1', instead of '8'.
                      .add_left(studentName("1"), studentName("2"))    // Now '2' is the left child of '1', instead of '9' (the children of '9' remain in place)
                      .add_left(studentName("1"), studentName("2"));); // Now '2' is the left child of '1'.

    cout << studTree << endl;

    std::vector<studentName> pre{studentName("1"), studentName("2"), studentName("4"), studentName("5"), studentName("3")};
    std::vector<studentName> in{studentName("4"), studentName("2"), studentName("5"), studentName("1"), studentName("3")};
    std::vector<studentName> post{studentName("4"), studentName("5"), studentName("2"), studentName("3"), studentName("1")};
    unsigned long i = 0, j = 0, k = 0, t = 0;
    for (auto it = studTree.begin_preorder(); it != studTree.end_preorder(); ++it)
    {
        CHECK(*it == pre.at(i));
    }
    for (auto it = studTree.begin_inorder(); it != studTree.end_inorder(); ++it)
    {
        CHECK(*it == in.at(j));
    }
    for (auto it = studTree.begin_postorder(); it != studTree.end_postorder(); ++it)
    {
        CHECK(*it == post.at(k));
    }

    for (studentName element : studTree)
    { // this should work like inorder
        CHECK(element == in.at(t));
    }
}

TEST_CASE("add_root function")
{

    BinaryTree<string> strTree;
    CHECK_NOTHROW(strTree.add_root("roei"););
    for (string element : strTree)
    {
        CHECK(element == "roei");
    }
    CHECK_NOTHROW(strTree.add_root("noa"););
    for (string element : strTree)
    {
        CHECK(element != "roei");
        CHECK(element == "noa");
    }

    BinaryTree<int> intTree;
    for (int i = 0; i < 25; ++i)
    {
        CHECK_NOTHROW(intTree.add_root(i););
        for (int element : intTree)
        {
            CHECK(element == i);
        }
    }
}

TEST_CASE("add_left function")
{

    BinaryTree<int> intTree;
    set<int> intSet;
    vector<int> intVec;
    bool isRoot = true;
    int prevTemp;

    for (int i = 0; i < 25; ++i)
    {
        intSet.insert(rand() % 100);
    }

    for (int element : intSet)
    {
        if (isRoot)
        {
            CHECK_NOTHROW(intTree.add_root(element));
            intVec.push_back(element);
            isRoot = false;
            prevTemp = element;
        }
        else
        {

            CHECK_NOTHROW(intTree.add_left(element, element));
            intVec.push_back(element);
            prevTemp = element;
        }
    }

    unsigned long i = 0, j = intVec.size() - 1;
    for (auto it = intTree.begin_preorder(); it != intTree.end_preorder(); ++it)
    {
        CHECK(*it == intVec.at(i++));
    }
    for (auto it = intTree.begin_inorder(); it != intTree.end_inorder(); ++it)
    {
        CHECK(*it == intVec.at(j--));
    }
}

TEST_CASE("add_right function")
{

    BinaryTree<int> intTree;
    set<int> intSet;
    vector<int> intVec;
    bool isRoot = true;
    int prevTemp;

    for (int i = 0; i < 25; ++i)
    {
        intSet.insert(rand() % 100);
    }

    for (int element : intSet)
    {
        if (isRoot)
        {
            CHECK_NOTHROW(intTree.add_root(element));
            intVec.push_back(element);
            isRoot = false;
            prevTemp = element;
        }
        else
        {

            CHECK_NOTHROW(intTree.add_right(element, element));
            intVec.push_back(element);
            prevTemp = element;
        }
    }

    unsigned long i = 0, j = intVec.size() - 1;
    for (auto it = intTree.begin_preorder(); it != intTree.end_preorder(); ++it)
    {
        CHECK(*it == intVec.at(i++));
    }
    for (auto it = intTree.begin_postorder(); it != intTree.end_postorder(); ++it)
    {
        CHECK(*it == intVec.at(j--));
    }
}

// TEST_CASE("add_root")
// {
//         BinaryTree<int> my_Tree;
//         CHECK_NOTHROW(my_Tree.add_root(1));
//         CHECK_EQ(*my_Tree.begin_preorder(), 1);
//         CHECK_EQ(*my_Tree.begin_inorder(), 1);
//         CHECK_EQ(*my_Tree.begin_postorder(), 1);
// }
