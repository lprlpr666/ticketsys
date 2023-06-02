//
// Created by 陆鹏睿 on 2023/6/2.
//

#ifndef CODE_STACK_H
#define CODE_STACK_H
template <class elemType>
class stack
{
public:
    virtual bool isEmpty() const = 0;
    virtual void push(const elemType &x) = 0;
    virtual elemType  pop() = 0;
    virtual elemType  top() const = 0;
    virtual ~stack() {}
};
template <class elemType>
class seqStack: public stack<elemType>
{
private:
    elemType *elem;
    int top_p=0;
    int maxSize;
    void doubleSpace();
public:
    seqStack(int initSize = 10) ;
    ~seqStack()   {     delete [] elem;     }
    bool isEmpty() const ;
    void push(const elemType &x);
    elemType  pop();
    elemType  top() const  {     return elem[top_p];  }
};

template<class elemType>
elemType seqStack<elemType>::pop() {
    {     return elem[top_p];  }
}


template <class elemType>
void seqStack<elemType>::push(const elemType &x)
{
    if (top_p == maxSize - 1)
        doubleSpace();
    elem[top_p] = x;
}
template <class elemType>
seqStack<elemType>::seqStack(int initSize) {
    elem = new elemType[initSize];
    maxSize = initSize ;
    top_p = 0;
}template<class elemType>
bool seqStack<elemType>::isEmpty() const {
    return top_p==-1;
}
template <class elemType>
void seqStack<elemType>::doubleSpace()
{
    elemType *tmp = elem;

    elem = new elemType[2 * maxSize];
    for (int i = 0; i < maxSize; ++i)
        elem[i] = tmp[i];
    maxSize *= 2;
    delete [] tmp;
}
struct Node {
    int data;
    Node* next;
};
class Queue {
public:
    Node* front; // 队首指针
    Node* rear;  // 队尾指针
    Queue() : front(nullptr), rear(nullptr) {}
    ~Queue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
    // 判断队列是否为空
    bool isEmpty() {
        return (front == nullptr);
    }

    // 入队
    void enqueue(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;

        // 如果队列为空，新节点既是队首也是队尾
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            // 将新节点添加到队尾，并更新队尾指针
            rear->next = newNode;
            rear = newNode;
        }
    }

    // 出队
    void dequeue() {
        if (isEmpty()) return;
        Node* temp = front; // 保存当前队首节点的指针
        front = front->next; // 更新队首指针

        // 如果队列只有一个节点，出队后队列为空，需要更新队尾指针
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp; // 释放原队首节点的内存
    }

    // 获取队首元素
    int getFront() {
        if (isEmpty()) return -1;
        return front->data;
    }

};
#endif //CODE_STACK_H
