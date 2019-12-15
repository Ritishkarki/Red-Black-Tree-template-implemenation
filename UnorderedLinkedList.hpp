#include <iostream>
template <class T>
struct LLNode {
    LLNode(T data) : data(data), next(NULL) {}
    T data;
    LLNode<T> *next;
};

template <class T>
class UnorderedLinkedList {
    template<class U>
    friend std::ostream &operator<<(std::ostream &os, const UnorderedLinkedList<U> &rhs);
    private:
        LLNode<T> *head;
    public:
        UnorderedLinkedList() : head(NULL) {};
        ~UnorderedLinkedList();
        UnorderedLinkedList(const UnorderedLinkedList &rhs);
        UnorderedLinkedList &operator=(const UnorderedLinkedList &rhs);
        void insert(const T data);
        bool search(const T data) const;
        void remove(const T data);
        bool isEmpty() const;
        bool operator==(const UnorderedLinkedList<T> &rhs) const;
        bool operator!=(const UnorderedLinkedList<T> &rhs) const;
        bool operator<(const UnorderedLinkedList<T> &rhs) const;
        bool operator>(const UnorderedLinkedList<T> &rhs) const;
};


template <class T>
bool UnorderedLinkedList<T>::operator!=(const UnorderedLinkedList<T> &rhs) const
{
    return !(*this == rhs);
}

template<class T>
bool UnorderedLinkedList<T>::operator<(const UnorderedLinkedList<T>& rhs) const
{
    LLNode<T> *lhsTemp = head;
    LLNode<T> *rhsTemp = rhs.head;
    while (lhsTemp != NULL && rhsTemp != NULL)
    {
        if (lhsTemp->data > rhsTemp->data)
            return false;
        lhsTemp = lhsTemp->next;
        rhsTemp = rhsTemp->next;
    }
    return true;
}

template<class T>
bool UnorderedLinkedList<T>::operator>(const UnorderedLinkedList<T>& rhs) const
{
    return rhs < *this;
}

template <class T>
bool UnorderedLinkedList<T>::operator==(const UnorderedLinkedList<T> &rhs) const
{
    LLNode<T> *lhsTemp = head;
    LLNode<T> *rhsTemp = rhs.head;
    while (lhsTemp != NULL || rhsTemp != NULL)
    {
        if (lhsTemp != NULL && rhsTemp == NULL || lhsTemp == NULL && rhsTemp != NULL)
            return false;
        else if (lhsTemp->data != rhsTemp->data)
            return false;
        lhsTemp = lhsTemp->next;
        rhsTemp = rhsTemp->next;
    }
    return true;
}

template<class T>
UnorderedLinkedList<T>::~UnorderedLinkedList()
{
    while (head != NULL)
    {
        LLNode<T> *tmp = head;
        head = head->next;
        delete tmp;
    }
    delete head;
}

template<class T>
UnorderedLinkedList<T>::UnorderedLinkedList(const UnorderedLinkedList & rhs) : head(NULL)
{
    *this = rhs;
}


template <class T>
UnorderedLinkedList<T> & UnorderedLinkedList<T>::operator=(const UnorderedLinkedList<T> &rhs)
{
    if (this != &rhs)
    {
        LLNode<T> *temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }

        if (rhs.head != NULL)
            head = new LLNode<T>(rhs.head->data);

        LLNode<T> *tmpHead = head;

        for (LLNode<T> *tmp = rhs.head->next; tmp != NULL; tmp = tmp->next)
        {
            tmpHead->next = new LLNode<T>(tmp->data);
            tmpHead = tmpHead->next;
        }
    }
    return *this;
}

template<class T>
void UnorderedLinkedList<T>::insert(const T data)
{
    if (head == NULL)
    {
        head = new LLNode<T>(data);
    }
    else
    {
        LLNode<T> *temp = head;
        for (temp = head; temp->next != NULL; temp = temp->next);
        temp->next = new LLNode<T>(data);
    }
}

template<class T>
bool UnorderedLinkedList<T>::search(const T data) const
{
    if (head == NULL)
        return false;

    for (LLNode<T> *tmp = head; tmp != NULL; tmp = tmp->next)
        if (tmp->data == data)
            return true;

    return true;
}

template<class T>
void UnorderedLinkedList<T>::remove(const T data)
{
    bool removed = false;
    LLNode<T> *curr = head;
    LLNode<T> *prev = head;

    for (; curr != NULL && removed == false; curr = curr->next)
    {
        if (head->data == data)
        {
            LLNode<T> *tmp = head;
            head = head->next;
            delete tmp;
            removed = true;
        }
        else if (curr->data == data)
        {
            LLNode<T> *tmp = curr;
            prev->next = curr->next;
            delete tmp;
            removed = true;
        }
        prev = curr;
    }
}

template<class T>
bool UnorderedLinkedList<T>::isEmpty() const
{
    return head == NULL;
}

template<class T>
std::ostream & operator<<(std::ostream & os, const UnorderedLinkedList<T>& rhs)
{
    for (LLNode<T> *temp = rhs.head; temp != NULL; temp = temp->next)
    {
        os << temp->data;
        if (temp->next != NULL)
            os << ", ";
    }
    return os;
}