// Copyright [2023] <Pedro Henrique de Sena Trombini Taglialenha>

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <vector>
#include <cstdint>

namespace structures {

template<typename T>
//! Binary Tree
class BinaryTree {
 public:
    //! Destructor
    ~BinaryTree() {
        while (!empty()) {
            remove(root->node_data);
        }
    }

    //! Insert
    void insert(const T& node_data) {
        if (empty()) {
            root = new Node(node_data);
        } else {
            root->insert(node_data);
        }
        ++size_;
    }

    //! Remove
    void remove(const T& node_data) {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }
        root->remove(node_data);
        --size_;
    }

    //! Contains
    bool contains(const T& node_data) const {
        if (empty()) {
            return false;
        }
        return root->contains(node_data);
    }

    //! Empty
    bool empty() const {
        return size() == 0;
    }

    //! Size
    std::size_t size() const {
        return size_;
    }

    //! Pre ordered
    std::vector<T> pre_order() const {
        auto vector = std::vector<T>{};
        if (!empty()) {
            root->pre_order(vector);
        }
        return vector;
    }

    //! Normal order
    std::vector<T> in_order() const {
        auto vector = std::vector<T>{};
        if (!empty()) {
            root->in_order(vector);
        }
        return vector;
    }

    //! Post ordered
    std::vector<T> post_order() const {
        auto vector = std::vector<T>{};
        if (!empty()) {
            root->post_order(vector);
        }
        return vector;
    }

 private:
    struct Node {
        //! Node
        explicit Node(const T& node_data) {
            this->node_data = node_data;
        }

        //! Insert
        void insert(const T& data) {
            if (data <= node_data) {
                if (left == nullptr) {
                    left = new Node(data);
                } else {
                    left->insert(data);
                }
            } else {
                if (right == nullptr) {
                    right = new Node(data);
                } else {
                    right->insert(data);
                }
            }
        }

        //! Remove
        bool remove(const T& data) {
            if (data == node_data) {
                node_data = T{};
                return true;
            } else if (data < node_data) {
                return (left) and left->remove(data);
            } else {
                return (right) and right->remove(data);
            }
        }

        //! Contains
        bool contains(const T& data) const {
            if (data < node_data) {
                return left  == nullptr ? false : left->contains(data);
            } else if (data > node_data) {
                return right == nullptr ? false : right->contains(data);
            } else {
                return true;
            }
        }

        //! Pre order
        void pre_order(std::vector<T>& v) const {
            v.push_back(node_data);
            if (left) {
                left->pre_order(v);
            }
            if (right) {
                right->pre_order(v);
            }
        }

        //! Normal order
        void in_order(std::vector<T>& v) const {
            if (left) {
                left->in_order(v);
            }
            v.push_back(node_data);
            if (right) {
                right->in_order(v);
            }
        }

        //! Post order
        void post_order(std::vector<T>& v) const {
            if (left) {
                left->post_order(v);
            }
            if (right) {
                right->post_order(v);
            }
            v.push_back(node_data);
        }

        T node_data;
        Node* left{nullptr};
        Node* right{nullptr};
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures

#endif
