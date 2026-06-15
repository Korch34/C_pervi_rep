#include <iostream>
enum class Quality
{
    Low,
    Medium,
    Hard
};
struct Patients
{
    std::string name;
    Quality Prior;
    size_t age;
};
struct Node
{
    Node* next = nullptr;
    Node* prev = nullptr;
    Patients Human;
};
struct PrioryQueue
{
    Node* Head = nullptr;
    Node* Tail = nullptr;
};
bool isEmpty(PrioryQueue Queue)
{
    return Queue.Head == nullptr && Queue.Tail == nullptr;
}
bool isHigherPriority(Patients Il1, Patients Il2)
{
    if (Il1.Prior != Il2.Prior)
    {
        return static_cast<int>(Il1.Prior) > static_cast<int>(Il2.Prior);
    }
    return Il1.age < Il2.age;
}
void Push(PrioryQueue& Queue, Patients People)
{
    Node* tmp = new Node;
    tmp->Human = People;  

    if (isEmpty(Queue))
    {
        Queue.Head = tmp;
        Queue.Tail = tmp;
        return;
    }

    Node* current = Queue.Head;
    while (current != nullptr && isHigherPriority(current->Human, People))
    {
        current = current->next;
    }
    if (current == nullptr)
    {
        tmp->prev = Queue.Tail;
        Queue.Tail->next = tmp;
        Queue.Tail = tmp;
    }
    else if (current == Queue.Head)
    {
        tmp->next = Queue.Head;
        Queue.Head->prev = tmp;
        Queue.Head = tmp;
    }
    else
    {
        tmp->prev = current->prev;
        tmp->next = current;
        current->prev->next = tmp;
        current->prev = tmp;
    }
}
Patients Pop(PrioryQueue& Queue)
{
    Node* tmp = Queue.Head;
    Patients res = tmp->Human;
    Queue.Head = Queue.Head->next;
    if (Queue.Head != nullptr)
    {
        Queue.Head->prev = nullptr;
    }
    else
    {
        Queue.Tail = nullptr;
    }
    delete tmp;
    return res;
}
void printPatient(const Patients& p)
{
    std::string priorStr;
    switch (p.Prior)
    {
    case Quality::Low:    priorStr = "Low"; break;
    case Quality::Medium: priorStr = "Medium"; break;
    case Quality::Hard:   priorStr = "Hard"; break;
    }
    std::cout << p.name << " (" << priorStr << ", age=" << p.age << ")\n";
}
int main()
{
    PrioryQueue queue;
    Push(queue, { "Alice",   Quality::Medium, 30 });
    Push(queue, { "Bob",     Quality::Hard,   45 });
    Push(queue, { "Charlie", Quality::Low,    25 });
    Push(queue, { "Diana",   Quality::Hard,   35 });
    Push(queue, { "Eve",     Quality::Medium, 22 });
    Push(queue, { "Frank",   Quality::Low,    60 });
    while (!isEmpty(queue))
    {
        Patients p = Pop(queue);
        printPatient(p);
    }   
}