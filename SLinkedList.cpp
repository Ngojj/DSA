#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

template <class T>
class SLinkedList
{
public:
    class Node; // Forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    SLinkedList();
    ~SLinkedList();
    void add(T &e);
    void add(int index, T &e);
    int size();
    bool empty();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    T removeAt(int index);
    bool removeItem(const T &item);
    void clear();
    string toString();

public:
    class Node
    {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;

    public:
        Node()
        {
            next = 0;
        }
        Node(Node *next)
        {
            this->next = next;
        }
        Node(T data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
    };
};
template <class T>
SLinkedList<T>::SLinkedList()
{
    head = tail = NULL;
    count = 0;
}

template <class T>
SLinkedList<T>::~SLinkedList()
{
    Node *temp = head;
    while (temp != NULL)
    {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
}

template <class T>
void SLinkedList<T>::add(T &e)
{
    Node *newNode = new Node(e, NULL);

    if (tail != NULL)
    {
        tail->next = newNode;
    }
    tail = newNode;

    if (head == NULL)
        head = newNode;
    count++;
}

template <class T>
void SLinkedList<T>::add(int index, T &e)
{
    if (index > count || index < 0)
    {
        throw std::out_of_range(" index is out of range");
    }
    Node *newNode = new Node(e, NULL);
    if (index == 0)
    {
        if (tail == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        newNode->next = head;
        head = newNode;
    }
    else if (index == count)
    {
        if (tail != NULL)
            tail->next = newNode;
        tail = newNode;
        if (head == NULL)
            head = newNode;
    }
    else
    {
        Node *temp = head;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    count++;
}

template <class T>
int SLinkedList<T>::size()
{
    return count;
}

template <class T>
T SLinkedList<T>::get(int index)
{
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("index is out of range");
    }
    Node *temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp->data;
}

template <class T>
void SLinkedList<T>::set(int index, const T &e)
{
    /* Assign new value for element at given index in the list */
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("index is out of range");
    }
    Node *temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    // delete temp;
    temp->data = e;
}

template <class T>
bool SLinkedList<T>::empty()
{
    /* Check if the list is empty or not. */
    return count == 0;
}

template <class T>
int SLinkedList<T>::indexOf(const T &item)
{
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node *temp = head;
    int index = 0;
    while (temp != NULL)
    {
        if (temp->data == item)
        {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1;
}

template <class T>
bool SLinkedList<T>::contains(const T &item)
{
    /* Check if item appears in the list */
    return indexOf(item) != -1;
}

template <class T>
T SLinkedList<T>::removeAt(int index)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("index is out of range");
    }

    T removed;

    if (index == 0)
    {
        Node *delNode = head;
        removed = delNode->data;
        head = head->next;
        if (head == nullptr)
            tail = nullptr;
        delete delNode;
    }
    else
    {
        Node *prev = head;
        for (int i = 0; i < index - 1; i++)
        {
            prev = prev->next;
        }

        Node *delNode = prev->next;
        removed = delNode->data;
        prev->next = delNode->next;

        if (delNode == tail)
            tail = prev;

        delete delNode;
    }

    count--;
    return removed;
}

template <class T>
bool SLinkedList<T>::removeItem(const T &item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    Node *temp = head;
    int index = 0;

    for (int i = 0; i < count; i++)
    {
        if (temp->data == item)
        {
            removeAt(index);
            return true;
        }
        temp = temp->next;
        index++;
    }
    return false;
}

template <class T>
void SLinkedList<T>::clear()
{
    /* Remove all elements in list */
    while (!empty())
    {
        removeAt(0);
    }
}

template <class T>
string SLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node *temp = head;
    while (temp != NULL)
    {
        ss << temp->data;

        if (temp->next != NULL)
        {
            ss << ",";
        }
        temp = temp->next;
    }
    ss << "]";
    return ss.str();
}
int main()
{
    // SLinkedList<int> list;
    // int values[] = {10, 15, 2, 6, 4, 7, 40, 8};
    // int index[] = {0, 0, 1, 3, 2, 3, 5, 0};
    // int expvalues[] = {8, 15, 2, 4, 7, 10, 40, 6};

    // for (int idx = 0; idx < 8; idx++)
    // {
    //     list.add(index[idx], values[idx]);
    // }

    // assert(list.size() == 8);

    // for (int idx = 0; idx < 8; idx++)
    // {
    //     assert(list.get(idx) == expvalues[idx]);
    // }

    // cout << list.toString();
    SLinkedList<int> list;

    assert(list.empty() == true);
    cout << list.toString();
    return 0;
}