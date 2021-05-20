#pragma once
#include <queue>

namespace ariel
{

    template <typename T>
    class BinaryTree
    {

    private:
        // inner class
        struct Node
        {
            T m_value;
            Node *m_right;
            Node *m_left;
            Node *m_father;
            Node(const T &v) : m_value(v), m_father(nullptr), m_right(nullptr), m_left(nullptr) {}

            ~Node()
            {
                delete m_left;
                delete m_right;
                delete m_father; // (?)
            }
        };

        // Avoid copying
        BinaryTree(const BinaryTree &rhs);
        BinaryTree &operator=(const BinaryTree &rhs);

        Node *findNode(Node *root, const T val)
        {
            if (root == nullptr)
            {
                return nullptr;
            }
            if (root->m_value == val)
            {
                return root;
            }

            Node *rightNode = findNode(root->m_right, val);
            if (rightNode == nullptr)
            {
                return findNode(root->m_left, val);
                ;
            }
            else
            {
                return rightNode;
            }
        }

        static void preV(Node **root, std::vector<Node *> &m_v)
        {
            if (*root != nullptr)
            {
                m_v.push_back(*root);
                preV(&(*root)->m_left, m_v);
                preV(&(*root)->m_right, m_v);
            }
        }

        static void inV(Node **root, std::vector<Node *> &m_v)
        {
            if (*root != nullptr)
            {
                inV(&(*root)->m_left, m_v);
                m_v.push_back(*root);
                inV(&(*root)->m_right, m_v);
            }
        }

        static void postV(Node **root, std::vector<Node *> &m_v)
        {
            if (*root != nullptr)
            {
                postV(&(*root)->m_left, m_v);
                postV(&(*root)->m_right, m_v);
                m_v.push_back(*root);
            }
        }

        // fields
        Node *m_root;

    public:
        BinaryTree() : m_root(nullptr) {}

        ~BinaryTree() { delete m_root; }

        bool isEmpty() const { return m_root == nullptr; }

        BinaryTree &add_root(T value)
        {
            m_root = new Node{value};
            return *this;
        }

        BinaryTree &add_left(T father, T child)
        {
            Node *temp = findNode(this->m_root, father);
            if (temp == nullptr)
            {
                throw std::invalid_argument("Illigal argument");
            }
            if (temp->m_left == nullptr)
            {
                temp->m_left = new Node(child);
            }
            else
            {
                temp->m_left->m_value = child;
            }

            return *this;
        }

        BinaryTree &add_right(T father, T child)
        {
            Node *temp = findNode(this->m_root, father);
            if (temp == nullptr)
            {
                throw std::invalid_argument("Illigal argument");
            }
            if (temp->m_right == nullptr)
            {
                temp->m_right = new Node(child);
            }
            else
            {
                temp->m_right->m_value = child;
            }

            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree &b) { return os << std::endl; }

        /////iterator - /////

        class iterator
        {

        private:
            int m_order;
            unsigned long m_index;
            Node *current_node;
            // queue<Node *> m_q;
            std::vector<Node *> m_v;

        public:
            iterator(Node *ptr = nullptr, int order = 0, unsigned long index = 0) : current_node(ptr), m_order(order), m_index(index)
            {
                m_v.clear();
                //  cout << "sizeB = " << m_v.size() << " order = " << order << endl;
                if (ptr != nullptr)
                {
                    if (order == -1)
                    {
                        preV(&ptr, m_v);
                    }
                    if (order == 0)
                    {
                        inV(&ptr, m_v);
                    }
                    if (order == 1)
                    {
                        postV(&ptr, m_v);
                    }
                }
                //   cout << "sizeA = " << m_v.size() << endl;

                m_v.push_back(nullptr);
                current_node = m_v.at(0);
            }

            T &operator*() const { return current_node->m_value; }

            T *operator->() const { return &(current_node->m_value); }

            iterator &operator++()
            {
                current_node = m_v.at(++m_index);
                return *this;
            }

            const iterator operator++(int)
            {
                iterator tmp = *this;
                current_node = m_v.at(++m_index);
                return tmp;
            }

            bool operator==(const iterator &rhs) const
            {
                return current_node == rhs.current_node;
            }

            bool operator!=(const iterator &rhs) const
            {
                return current_node != rhs.current_node;
            }

        }; // END OF CLASS ITERATOR

        iterator begin_preorder()
        {
            return iterator{m_root, -1};
        }

        iterator end_preorder()
        {
            // return nullptr;
            return iterator{nullptr, -1};
        }

        iterator begin_inorder()
        {
            return iterator{m_root, 0};
        }

        iterator end_inorder()
        {
            // return nullptr;
            return iterator{nullptr, 0};
        }

        iterator begin_postorder()
        {
            return iterator{m_root, 1};
        }

        iterator end_postorder()
        {
            return iterator{nullptr, 1};
        }

        iterator begin()
        {
            return begin_inorder();
        }

        iterator end()
        {
            return end_inorder();
        }

        // template <typename IT>
        // BinaryTree(IT begin, IT end) : BinaryTree()
        // {
        //     for (; begin != end; ++begin)
        //     {
        //         push(*begin);
        //     }
        // }
    };
}