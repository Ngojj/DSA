#include <iostream>
#include <sstream>

using namespace std;

template <class T>
class DLinkedList
{
public:
    class Node; // Forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    DLinkedList();
    ~DLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    int size();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    T removeAt(int index);
    bool removeItem(const T &item);
    bool empty();
    void clear();
    string toString();

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };
};

template <class T>
DLinkedList<T>::DLinkedList()
{
    head = NULL;
    tail = NULL;
    count = 0;
}

template <class T>
DLinkedList<T>::~DLinkedList()
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
void DLinkedList<T>::add(const T &e)
{
    Node *newNode = new Node(e);
    if (tail == NULL)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
    }

    count++;
}

template <class T>
void DLinkedList<T>::add(int index, const T &e)
{
    if (index > count || index < 0)
    {
        throw std::out_of_range("index is ou of range");
    }
    Node *newNode = new Node(e);
    if (index == 0)
    {
        if (tail == NULL)
            head = tail = newNode;
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }
    else if (index == count)
    {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
    }
    else
    {
        Node *temp = head;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        newNode->previous = temp;
        newNode->next = temp->next;
        temp->next->previous = newNode;
        temp->next = newNode;
    }
    count++;
}

template <class T>
int DLinkedList<T>::size()
{
    return count;
}

template <class T>
T DLinkedList<T>::get(int index)
{
    /* Give the data of the element at given index in the list. */
    if (index >= count || index < 0)
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
void DLinkedList<T>::set(int index, const T &e)
{
    /* Assign new value for element at given index in the list */
    if (index >= count || index < 0)
    {
        throw std::out_of_range("index is out of range");
    }
    Node *temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    temp->data = e;
}

template <class T>
bool DLinkedList<T>::empty()
{
    /* Check if the list is empty or not. */
    return count == 0;
}

template <class T>
int DLinkedList<T>::indexOf(const T &item)
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
        index++;
        temp = temp->next;
    }
    return -1;
}

template <class T>
bool DLinkedList<T>::contains(const T &item)
{
    /* Check if item appears in the list */
    return indexOf(item) != -1;
}

template <class T>
T DLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("index is out of range");
    }
    Node *temp = head;
    T removed;
    if (index == 0)
    {

        head = head->next;
        removed = temp->data;
        delete temp;
        temp = NULL;
        head->previous = NULL;
    }
    else if (index == count - 1)
    {
        while (temp->next != tail)
        {
            temp = temp->next;
        }
        removed = tail->data;
        tail = tail->previous;
        delete (tail->next);
        tail->next = NULL;
    }
    else
    {
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        Node *temp2 = temp->next;
        temp->next = temp2->next;
        temp2->next->previous = temp;
        delete temp2;
        temp2 = NULL;
    }
    count--;
    return removed;
}

template <class T>
bool DLinkedList<T>::removeItem(const T &item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    Node *temp = head;
    int index = 0;
    while (temp != NULL)
    {
        if (temp->data == item)
        {
            removeAt(index);
            return true;
        }
        index++;
        temp = temp->next;
    }
    return false;
}

template <class T>
void DLinkedList<T>::clear()
{
    /* Remove all elements in list */
    Node *temp = head;
    while (temp != NULL)
    {
        delete temp;
        temp = temp->next;
    }
    head = tail = NULL;
    count = 0;
}

template <class T>
string DLinkedList<T>::toString()
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
    // DLinkedList<int> list;
    // int size = 10;
    // for (int idx = 0; idx < size; idx++)
    // {
    //     list.add(idx);
    // }
    // cout << list.toString();
    //
    DLinkedList<int> list;
    int size = 10;
    int value[] = {2, 5, 6, 3, 67, 332, 43, 1, 0, 9};

    for (int idx = 0; idx < size; idx++)
    {
        list.add(value[idx]);
    }
    list.removeAt(0);
    cout << list.toString();
}