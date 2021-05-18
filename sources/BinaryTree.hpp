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
            Node(const T &v, Node *f, Node *r, Node *l)
                : m_value(v), m_father(f), m_right(r), m_left(l)
            {
            }

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

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree &b){
            return os;
        }

        class iterator
        {

        private:
            Node *pointer_to_current_node;

        public:
            iterator(Node *ptr = nullptr)
                : pointer_to_current_node(ptr)
            {
            }

            // Note that the method is const as this operator does not
            // allow changing of the iterator.
            // Note that it returns T& as it allows to change what it points to.
            // A const_iterator class will return const T&
            // and the method will still be const
            T &operator*() const
            {
                //return *pointer_to_current_node;
                return pointer_to_current_node->m_value;
            }

            T *operator->() const
            {
                return &(pointer_to_current_node->m_value);
            }

            // ++i;
            iterator &operator++()
            {
                //++pointer_to_current_node;
                pointer_to_current_node = pointer_to_current_node->m_right; return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            const iterator operator++(int)
            {
                iterator tmp = *this;
                pointer_to_current_node = pointer_to_current_node->m_right;
                return tmp;
            }

            bool operator==(const iterator &rhs) const
            {
                return pointer_to_current_node == rhs.pointer_to_current_node;
            }

            bool operator!=(const iterator &rhs) const
            {
                return pointer_to_current_node != rhs.pointer_to_current_node;
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
            return end_postorder();
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