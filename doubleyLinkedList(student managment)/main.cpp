#include <iostream>
#include <cstring>
using namespace std;

class Node
{
public:
    int roll_number;
    char name[50];
    char gender[50];
    Node *prev;
    Node *next;
};

class DoubleLinkedList
{
    Node *start;

public:
    DoubleLinkedList();
    void add();
    bool Search(int rollno, Node **current, Node **previous, Node **successor);
    bool listEmpty();
    bool deleteNode(int rollno);
    void traverse();
    ~DoubleLinkedList(); // Destructor to free memory
};

DoubleLinkedList::DoubleLinkedList()
{
    start = NULL;
}

void DoubleLinkedList::add()
{
    int rollno;
    char nm[50];
    char gen[50];
    cout << "Enter the roll number of the student: " << endl;
    cin >> rollno;
    cout << "Enter the name of the student: " << endl;
    cin >> nm;
    cout << "Enter the gender:" << endl;
    cin >> gen;

    Node *newnode = new Node;
    newnode->roll_number = rollno;
    strcpy(newnode->name, nm);
    strcpy(newnode->gender, gen);
    newnode->prev = NULL;
    newnode->next = NULL;

    if (start == NULL || rollno < start->roll_number)
    {
        newnode->next = start;
        if (start != NULL)
        {
            start->prev = newnode;
        }
        start = newnode;
    }
    else
    {
        Node *temp = start;
        while (temp->next != NULL && temp->next->roll_number < rollno)
        {
            temp = temp->next;
        }
        newnode->next = temp->next;
        newnode->prev = temp;
        if (temp->next != NULL)
        {
            temp->next->prev = newnode;
        }
        temp->next = newnode;
    }
}

bool DoubleLinkedList::listEmpty()
{
    return (start == NULL);
}

bool DoubleLinkedList::deleteNode(int rollno)
{
    Node *current, *previous, *successor;
    if (!Search(rollno, &current, &previous, &successor))
    {
        return false;
    }
    if (current == start)
    {
        start = start->next;
        if (start != NULL)
        {
            start->prev = NULL;
        }
    }
    else
    {
        previous->next = current->next;
        if (current->next != NULL)
        {
            current->next->prev = previous;
        }
    }
    delete current;
    return true;
}

bool DoubleLinkedList::Search(int rollno, Node **current, Node **previous, Node **successor)
{
    *previous = NULL;
    *current = start;
    *successor = start;

    while (*current != NULL && rollno > (*current)->roll_number)
    {
        *previous = *current;
        *current = (*current)->next;
        *successor = (*current != NULL) ? (*current)->next : NULL;
    }

    return (*current != NULL && (*current)->roll_number == rollno);
}

void DoubleLinkedList::traverse()
{
    if (listEmpty())
    {
        cout << "List is empty." << endl;
    }
    else
    {
        cout << "The records in the list are:" << endl;
        Node *currentNode = start;

        while (currentNode != NULL)
        {
            cout << currentNode->roll_number << "     " << currentNode->name << "     " << currentNode->gender << endl;
            currentNode = currentNode->next;
        }
        cout << endl;
    }
}

DoubleLinkedList::~DoubleLinkedList()
{
    // Destructor to free dynamically allocated memory (Nodes)
    Node *current = start;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
}

int main()
{
    DoubleLinkedList obj;
    char ch;

    while (true)
    {
        cout << endl
             << "Menu";
        cout << endl
             << "1. Add a record to the list" << endl;
        cout << "2. Delete a record from the list" << endl;
        cout << "3. View records in the list" << endl;
        cout << "4. Search for a record in the list" << endl;
        cout << "5. Exit" << endl;
        cout << endl
             << "Select the operation that has to be performed: ";
        cin >> ch;

        switch (ch)
        {
        case '1':
            obj.add();
            break;

        case '2':
            if (obj.listEmpty())
            {
                cout << "Empty list" << endl;
            }
            else
            {
                int rollno;
                cout << endl
                     << "Enter the roll number of the record to be deleted: ";
                cin >> rollno;
                if (obj.deleteNode(rollno))
                {
                    cout << endl
                         << "Record with roll number " << rollno << " deleted." << endl;
                }
                else
                {
                    cout << "Invalid record" << endl;
                }
            }
            break;

        case '3':
            obj.traverse();
            break;

        case '4':
            if (obj.listEmpty())
            {
                cout << "List is empty" << endl;
            }
            else
            {
                int rollno;
                cout << endl
                     << "Enter the roll number to search for: ";
                cin >> rollno;
                Node *previous, *current;
                if (obj.Search(rollno, &current, &previous, nullptr))
                {
                    cout << endl
                         << "Record found:" << endl;
                    cout << "Roll number: " << current->roll_number << endl;
                    cout << "Name: " << current->name << endl;
                    cout << "Gender: " << current->gender << endl;
                    cout << endl;
                }
                else
                {
                    cout << endl
                         << "Record not found." << endl;
                }
            }
            break;

        case '5':
            return 0; // Terminating the program

        default:
            cout << "Invalid option" << endl;
            break;
        }
    }

    return 0;
}

