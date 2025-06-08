#include <iostream>
using namespace std;
#include <sstream>

template <class T>
class ArrayList
{
protected:
    T *data;      // dynamic array to store the list's items
    int capacity; // size of the dynamic array
    int count;    // number of items stored in the array
public:
    ArrayList()
    {
        capacity = 5;
        count = 0;
        data = new T[5]; // kieu du lieu cua mang la T
    }
    ~ArrayList() { delete[] data; }

    void add(T e) // them phan tu vao cuoi ds
    {
        ensureCapacity(this->count + 1);
        this->data[this->count] = e;
        this->count++;
    }
    void add(int index, T e) // them phan tu vao vi tri index
    {
        ensureCapacity(this->count + 1);

        T *newData = new T[this->count + 1];

        for (int i = 0; i < index; i++)
        {
            newData[i] = this->data[i];
        }
        for (int i = index; i < this->count; i++)
        {
            newData[i + 1] = this->data[i];
        }
        newData[index] = e;
        delete[] this->data;
        this->data = newData;
        this->count++;
    }
    int size()
    {
        return this->count;
    }
    void ensureCapacity(int capacity)
    {
        if (capacity > this->capacity)
        {
            int newCapacity = this->capacity * 2;
            T *newData = new T[newCapacity];
            for (int i = 0; i < this->count; i++)
            {
                newData[i] = data[i];
            }
            this->capacity = newCapacity;
            delete[] this->data;
            this->data = newData;
        }
    }
    string toString()
    {
        stringstream ss;
        ss << "[";
        for (int i = 0; i < this->count; i++)
        {
            ss << data[i];
            if (i < this->count - 1)
            {
                ss << ",";
            }
        }
        ss << "]";
        return ss.str();
    }
    void clear()
    {
        delete[] data;
        data = new T[5];
        count = 0;
        capacity = 5;
    }
    T removeAt(int index)
    {
        if (index < 0 || index > count)
            throw std::out_of_range("index out of range");
        T *newData = new T[count - 1];
        for (int i = 0; i < index; i++)
        {
            newData[i] = this->data[i];
        }
        T removeData = data[index];
        for (int i = index; i < count - 1; i++)
        {
            newData[i] = this->data[i + 1];
        }
        delete[] data;
        this->data = newData;
        count--;
        return removeData;
    }
    bool removeItem(T item)
    {
        for (int i = 0; i < count; i++)
        {
            if (data[i] == item)
            {
                removeAt(i);
                return true;
            }
        }
        return false;
    }
    // get the element at the index, if the index is out of range, "throw std::out_of_range("index is out of range");"
    T get(int index)
    {
        if (index < 0 || index > count)
        {
            throw std::out_of_range("index is out of range");
        }
        return this->data[index];
    }
    // set the index position in the list with the value e
    void set(int index, T e)
    {
        if (index < 0 || index > count)
        {
            throw std::out_of_range("index is out of range");
        }
        this->data[index] = e;
    }
    // get the first index of item in the list, else return -1
    int indexOf(T item)
    {
        for (int i = 0; i < count; i++)
        {
            if (data[i] == item)
                return i;
        }
        return -1;
    }
    bool contains(T item)
    {
        return indexOf(item) != -1;
    }
    bool empty()
    {
        return this->count == 0;
    }
};
int main()
{
    ArrayList<int> arr;
    int size = 10;
    for (int index = 0; index < size; index++)
    {
        arr.add(index);
    }
    cout << arr.toString() << '\n';
    arr.set(0, 100);
    cout << arr.get(0) << '\n';
    cout << arr.toString() << '\n';
    arr.clear();
    cout << arr.toString() << '\n';
    cout << arr.empty() << '\n';
    for (int index = 0; index < size; index++)
    {
        arr.add(index);
    }
    cout << arr.indexOf(7) << '\n';
    cout << arr.contains(15) << '\n';
}