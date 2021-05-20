#pragma once

namespace ariel
{

    template <typename T>
    class BinaryTree
    {

    private:
        // Avoid copying
        BinaryTree(const BinaryTree &rhs);
        BinaryTree &operator=(const BinaryTree &rhs);

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
                delete m_father;
            }
        };

        // fields
        Node *m_root;

    public:
        BinaryTree() : m_root(nullptr)
        {
        }

        ~BinaryTree()
        {
            delete m_root;
        }

        bool isEmpty() const //??
        {
            return m_root == nullptr;
        }

        const T &getRoot() const //??
        {
            return m_root->m_value;
        }

        T &getRoot() //??
        {
            return m_root->m_value;
        }

        BinaryTree &add_root(T value)
        {
            m_root = new Node{value};
            return *this;
        }
        BinaryTree &add_left(T father, T child)
        {
            return *this;
        }
        BinaryTree &add_right(T father, T child)
        {
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree &b)
        {
            return os << std::endl;
        }

        /////iterator -

        class iterator
        {

        private:
            Node *current_node;

        public:
            iterator(Node *ptr = nullptr) : current_node(ptr) {}

            T &operator*() const { return current_node->m_value; }

            T *operator->() const { return &(current_node->m_value); }

            iterator &operator++()
            {
                current_node = current_node->m_right;
                return *this;
            }

            const iterator operator++(int)
            {
                iterator tmp = *this;
                current_node = current_node->m_right;
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
            // return &(m_root->m_value);
            return iterator{m_root};
        }

        iterator end_preorder()
        {
            // return nullptr;
            return iterator{nullptr};
        }

        iterator begin_inorder()
        {
            // return &(m_root->m_value);
            return iterator{m_root};
        }

        iterator end_inorder()
        {
            // return nullptr;
            return iterator{nullptr};
        }

        iterator begin_postorder()
        {
            // return &(m_root->m_value);
            return iterator{m_root};
        }

        iterator end_postorder()
        {
            // return nullptr;
            return iterator{nullptr};
        }

        iterator begin()
        {
            // return &(m_first->m_value);
            return begin_inorder();
        }

        iterator end()
        {
            // return nullptr;on
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