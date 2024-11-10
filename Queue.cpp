#include <iostream>
#include <initializer_list>
using namespace std;

template <typename T>
class Queue
{
    private:
        T* _arr;
        T* _top;
        T* _end;

    public:
        explicit Queue(int size)
        {
            _arr = new T[size];
            _top = _arr - 1;
            _end = _arr + size - 1;
        }

        Queue(int size, initializer_list<T> list)
        {
            if (list.size() > size)
                throw "List size is more than Queue size";

            _arr = new T[size];
            for (auto i : list)
            {
                *(_arr++) = i;
            }
            _arr -= list.size();

            _end = _arr + size - 1;
            _top = _end - (size - list.size());
        }

        Queue(const Queue& queue)
        {
            _arr = new T[queue.getQueueSize()];
            for (size_t i = 0; i < queue.getQueueSize(); i++)
            {
                _arr[i] = queue._arr[i];
            }

            _end = _arr + queue.getQueueSize() - 1;
            _top = _end - (queue.getQueueSize() - queue.getCurrentSize());
        }

        Queue(Queue&& queue)
        {
            _arr = queue._arr;
            _top = queue._top;
            _end = queue._end;

            queue._arr = nullptr;
            queue._top = nullptr;
            queue._end = nullptr;
        }

        ~Queue()
        {
            delete[] _arr;
            _arr = nullptr;
            _top = nullptr;
            _end = nullptr;
        }

        bool isFull() const
        {
            return _top == _end;
        }

        bool isEmpty() const
        {
            return _top + 1 == _arr;
        }

        int getCurrentSize() const
        {
            return _top - _arr + 1;
        }

        int getQueueSize() const
        {
            return _end - _arr + 1;
        }

        Queue& clear()
        {
            _top = _arr - 1;
            return *this;
        }

        Queue& enqueue(T value)
        {
            if (!isFull())
                *++_top = value;

            return *this;
        }

        T peek()
        {
            if (isEmpty())
                throw "Out of range";

            return *_arr;
        }

        T dequeue()
        {
            T res      = *_arr;

            T* current = _arr;
            while (current < _top)
            {
                *current = *(current + 1);
                current++;
            }
            _top--;

            return res;
        }

        friend ostream& operator<<(ostream& out, const Queue& queue)
        {
            T* current = queue._arr;
            while (current <= queue._top)
            {
                out << *current++ << '\t';
            }
            out << endl;

            return out;
        }
};

int main()
{
     Queue<int> q(5, {1,2,3});

     q.enqueue(4);
     q.enqueue(5);

     cout << q << endl;

    return 0;
}
