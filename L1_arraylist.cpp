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
};
int main()
{
    ArrayList<int> arr;
    int size = 20;

    for (int index = 0; index < size; index++)
    {
        arr.add(0, index);
    }

    cout << arr.toString() << '\n';
    cout << arr.size() << '\n';
    arr.ensureCapacity(5);
}