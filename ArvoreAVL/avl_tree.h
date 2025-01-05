// Copyright [2023] <Pedro>


#include "array_list.h"


namespace structures {

template<typename T>
class AVLTree {
public:
    AVLTree() {
        root = nullptr;
        size_ = 0;
    }

    ~AVLTree() {
        root = nullptr;
        size_ = 0;
    }

    void insert(const T& data) {
        if (empty()) {
            root = new Node(data);
        } else {
            root->insert(data);
        }
        size_++;
        root->updateHeight();
    }

    void remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("Árvore vazia");
        } else {
            root->remove(data);
            size_--;
            root->updateHeight();
        }
    }

    bool contains(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Árvore vazia");
        } else {
            return root->contains(data);
        }
    }

    bool empty() const {
        return (size() == 0);
    }

    std::size_t size() const {
        return (size_);
    }

    int height() const {
        return root->height();
    }

    ArrayList<T> pre_order() const {
        ArrayList<T> v = ArrayList<T>(size());
        if (empty()) {
            throw std::out_of_range("Árvore vazia");
        } else {
            root->pre_order(v);
        }
        return v;
    }

    ArrayList<T> in_order() const {
        ArrayList<T> v = ArrayList<T>(size());
        if (empty()) {
            throw std::out_of_range("Árvore vazia");
        } else {
            root->in_order(v);
        }
        return v;
    }

    ArrayList<T> post_order() const {
        ArrayList<T> v = ArrayList<T>(size());
        if (empty()) {
            throw std::out_of_range("Árvore vazia");
        } else {
            root->post_order(v);
        }
        return v;
    }

private:
    struct Node {
        explicit Node(const T& data):
            data{data},
            height_{-1},
            left{nullptr},
            right{nullptr}
        {}

        T data;
        int height_;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            Node *novo;
            novo = new Node(data_);
            novo->left = nullptr;
            novo->right = nullptr;
            novo->data = data_;
            if (data_ < this->data) {
                if (this->left == nullptr) {
                    this->left = novo;
                } else {
                    left->insert(data_);
                }
            } else {
                if (this->right == nullptr) {
                    this->right = novo;
                } else {
                    right->insert(data_);
                }
            }
            this->updateHeight();
            int balance = this->getBalance();
            if (balance > 1) {
                // left heavy, rotate right
                if (data_ < left->data) {
                    this->simpleRight();
                } else {
                    this->doubleRight();
                }
            } else if (balance < -1) {
                // right heavy, rotate left
                if (data_ > right->data) {
                    this->simpleLeft();
                } else {
                    this->doubleLeft();
                }
            }
        }

        bool remove(const T& data_) {
            bool removed = false;
            Node *tmp;
            // Caso esquerda
            if (left != nullptr && data_ == left->data) {
                if (left->left == nullptr && left->right == nullptr) {
                    left = nullptr;
                    removed = true;
                } else if (left->left != nullptr && left->right == nullptr) {
                    left = left->left;
                    removed = true;
                } else if (left->left == nullptr && left->right != nullptr) {
                    left = left->right;
                    removed = true;
                } else {
                    tmp = right;
                    while (tmp->left != nullptr) {
                        tmp = tmp->left;
                    }
                    this->data = tmp->data;
                    tmp->remove(this->data);
                    removed = true;
                }
            } else if (right != nullptr && data_ == right->data) {
                if (right->left == nullptr && right->right == nullptr) {
                    right = nullptr;
                    removed = true;
                } else if (right->left != nullptr && right->right == nullptr) {
                    right = right->left;
                    removed = true;
                } else if (right->left == nullptr && right->right != nullptr) {
                    right = right->right;
                    removed = true;
                } else {
                    tmp = right;
                    while (tmp->left != nullptr) {
                        tmp = tmp->left;
                    }
                    this->data = tmp->data;
                    tmp->remove(this->data);
                    removed = true;
                }
            } else if (right != nullptr && data_ > this->data) {
                return this->right->remove(data_);
            } else if (left != nullptr && data_ < this->data) {
                return this->left->remove(data_);
            }

            if (removed == true) {
                this->updateHeight();
                int balance = this->getBalance();
                if (balance > 1) {
                    if (data_ < left->data) {
                        this->simpleRight();
                    } else {
                        this->doubleRight();
                    }
                } else if (balance < -1) {
                    if (data_ > right->data) {
                        this->simpleLeft();
                    } else {
                        this->doubleLeft();
                    }
                }
                return true;
            } else {
                return false;
            }
        }

        bool contains(const T& data_) const {
            if (this->data == data_) {
                return true;
            } else {
                if (this->left != nullptr && data_ < this->data) {
                    return this->left->contains(data_);
                } else if (this->right != nullptr && data_ > this->data) {
                    return this->right->contains(data_);
                }
            }
            return false;
        }

        void updateHeight() {
            if (left == nullptr && right == nullptr) {
                this->height_ = 0;
            } else if (left != nullptr && right == nullptr) {
                left->updateHeight();
                this->height_ = left->height()+1;
            } else if (left == nullptr && right != nullptr) {
                right->updateHeight();
                this->height_ = right->height()+1;
            } else {
                left->updateHeight();
                right->updateHeight();
                if (left->height() > right->height()) {
                    this->height_ = left->height()+1;
                } else {
                    this->height_ = right->height()+1;
                }
            }
        }

        int getBalance() {
            int balance;
            int esq;
            int dir;
            if (left == nullptr) {
                esq = -1;
            } else {
                esq = left->height();
            }

            if (right == nullptr) {
                dir = -1;
            } else {
                dir = right->height();
            }
            balance = esq - dir;
            return balance;
        }

        Node* simpleLeft() {
            Node* pivot = this->right;
            T thisData = this->data;

            this->data = pivot->data;
            pivot->data = thisData;

            this->right = pivot->right;
            pivot->right = pivot->left;
            pivot->left = this->left;
            this->left = pivot;

            return this;
        }

        Node* simpleRight() {
            Node* pivot = this->left;
            T thisData = this->data;

            this->data = pivot->data;
            pivot->data = thisData;

            this->left = pivot->left;
            pivot->left = pivot->right;
            pivot->right = this->right;
            this->right = pivot;

            return this;
        }

        Node* doubleLeft() {
            right->simpleRight();
            this->simpleLeft();

            return this;
        }

        Node* doubleRight() {
            left->simpleLeft();
            this->simpleRight();

            return this;
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(this->data);
            if (this->left != nullptr) {
                this->left->pre_order(v);
            }
            if (this->right != nullptr) {
                this->right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (this->left != nullptr) {
                this->left->in_order(v);
            }
            v.push_back(this->data);
            if (this->right != nullptr) {
                this->right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (this->left != nullptr) {
                this->left->post_order(v);
            }
            if (this->right != nullptr) {
                this->right->post_order(v);
            }
            v.push_back(this->data);
        }

        int height() {
            return height_;
        }
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures
