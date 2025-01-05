//! Copyright [2023] <Pedro>
namespace structures {

template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {  // implementar cada um dos métodos de Node
     public:
        explicit Node(const T& data) {
data_ = data;
}
Node(const T& data, Node* next) {
data_ = data;
next_ = next;
}
Node(const T& data, Node* prev, Node* next) {
data_ = data;
next_ = next;
prev_ = prev;
}
T& data() {  // getter: dado
return data_;
}
const T& data() const {  // getter const: dado
return data_;
}
Node* prev() {
return prev_;
}
const Node* prev() const {
return prev_;
}
void prev(Node* node) {
prev_ = node;
}
Node* next() {  // getter: próximo
return next_;
}
const Node* next() const {  // getter const: próximo
return next_;
}
void next(Node* node) {  // setter: próximo
next_ = node;
}

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;  // primeiro da lista
    Node* tail;  // ultimo da lista
    std::size_t size_;
};

}  // namespace structures
template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    size_ = 0;
}
template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}
template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}
template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    if (empty()) {
        push_front(data);
        return;
    }
    Node *novo, *temp;
    temp = head;
    novo = new Node(data, nullptr);
    if (novo == nullptr) {
        throw std::out_of_range("Memória cheia");
    } else {
        while (temp->next() != nullptr) {
            temp = temp->next();
        }
        temp->next(novo);
        size_++;
    }
}
template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node *novo;
    novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Memória cheia");
    } else {
        novo->next(head);
        head = novo;
        size_++;
    }
}
template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if ((0 <= static_cast<int>(index)) && (index <= size())) {
        if (static_cast<int>(index) == 0) {
            push_front(data);
            return;
        } else if (index == size()) {
            push_back(data);
            return;
        } else {
            Node *novo, *temp;
            temp = head;
            novo = new Node(data);
            if (novo == nullptr) {
                throw std::out_of_range("Memória cheia");
            } else {
                for (int i = 1; i < static_cast<int>(index); i++) {
                    temp = temp->next();
                }
                novo->next(temp->next());
                temp->next(novo);
                size_++;
            }
        }
    } else {
        throw std::out_of_range("Posição fora da lista");
    }
}
template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    Node *temp;
    temp = head;
    int i = 0;
    while (i < static_cast<int>(size_) && temp->data() < data) {
        temp = temp->next();
        i++;
    }
    insert(data, i);
}
template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (empty() || !(0 <= static_cast<int>(index) && index < size_)) {
        throw std::out_of_range("Lista vazia");
    } else {
        Node *p = head;
        for (int i = 0; i < static_cast<int>(index) - 1; i++) {
            p = p->next();
        }
        Node *q = p->next();
        p->next(q->next());
        T aux = q->data();
        delete q;
        size_--;
        return aux;
    }
}
template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else if (size_ == 1) {
        return pop_front();
    } else {
        Node *p = head;
        for (int i = 0; i < static_cast<int>(size_) - 2; i++) {
            p = p->next();
        }
        Node *q = p->next();
        p->next(nullptr);
        T aux = q->data();
        delete q;
        size_--;
        return aux;
    }
}
template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        Node *p = head;
        head = p->next();
        T aux = p->data();
        delete p;
        size_--;
        return aux;
    }
}
template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    return (size_ == 0);
}
template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    Node *temp = head;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if (temp->data() == data) {
            return true;
        }
        temp = temp->next();
    }
    return false;
}
template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    int i = 0;
    Node *temp = head;
    while (i < static_cast<int>(size_) && temp->data() != data) {
        temp = temp->next();
        i++;
    }
    return i;
}
template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        if (contains(data)) {
            std::size_t i = find(data);
            pop(i);
        }
    }
}
template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}
template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    if (static_cast<int>(index) >= 0 && index < size_) {
        Node *p = head;
        for (int i = 0; i < static_cast<int>(index); i++) {
            p = p->next();
        }
        T& aux = p->data();
        return aux;
    } else {
        throw std::out_of_range("Elemento fora da lista");
    }
}
