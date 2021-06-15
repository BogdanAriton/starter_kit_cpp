/*
Since we already have linked list implemented in the standard we should not care about implementing one ourselfs.
But in the intrest of learning we should try to do a minimum implementation.
*/

#include <iostream>
#include <string>
#include <type_traits>

namespace helper
{
    // these expressions will be evaluated at compile time
    template <typename T>
    constexpr typename std::enable_if<!std::is_convertible<T, std::string>::value, std::string>::type
    to_string(const T &val) // cannot be converted directly thus we have to use type traits to determine if we can use to_string
    {
        return std::to_string(val);
    };

    template <typename T>
    constexpr typename std::enable_if<std::is_convertible<T, std::string>::value, std::string>::type
    to_string(const T &val) // converts to string directly
    {
        return val;
    };
}

// We will build a linked list class that will contain the node info inside it
template <typename T>
class LinkedList
{
    using Data = T;
    struct Node
    {
        // the node holds only the data we want to store
        // and the link to the next node in the list
        Data data{}; // we will assume that data will have a basic type and can be deep copied
        Node* next = nullptr;

        operator std::string() const
        {
            return helper::to_string(this->data);
        }
    };

    // we always need to know where the link starts, thus we need a head node
    Node* head = nullptr;
    // we also need to keep track of how many numbers are in the list
    std::size_t size = 0;

public:

    LinkedList() = default; // just creating an empty list
    // we should implement copy, move semantics because the data inside the list is not trivial
    LinkedList(const LinkedList& other) noexcept
    {
        // the copy constructor will have to go though all the nodes in other and make a copy of them into our list
        // for that we need to be able to add the new nodes in to this list, basically we need to copy the data and recreate the links
        std::cout << "*** Copy constructor ***" << '\n';
        if (other.head == nullptr) return;

        head = new Node(other.head->data); // we need to know who head is - thus it needs to be initialized separately 
        Node* current = head;

        Node* otherCurrent = other.head->next;
        while (otherCurrent != nullptr)
        {
            current->next = new Node(otherCurrent->data);
            otherCurrent = otherCurrent->next;
            current = current->next;
            size++;
        }
    }
    LinkedList& operator=(const LinkedList& other) noexcept
    {
        std::cout << "*** Copy assignment operator ***" << '\n';
        LinkedList tempList(other);
        std::swap(head, tempList.head);
        std::swap(size, tempList.size);
        return *this;
    }
    LinkedList(LinkedList&& other) noexcept
    {
        std::cout << "*** Move constructor ***" << '\n';
        head = std::move(other.head);
        size = other.size;

        other.head = nullptr;
        other.size = 0;
    }
    LinkedList& operator=(LinkedList&& other) noexcept
    {
        std::cout << "*** Move assignment operator ***" << '\n';
        this->clear();

        head = std::move(other.head);
        size = other.size;

        other.head = nullptr;
        other.size = 0;

        return *this;
    }
    void clear() noexcept
    {
        // we iterrate though the list and remove all the nodes we have created
        if (!isEmpty())
        {
            Node* current = head;
            while (current != nullptr)
            {
                Node* temp = current;
                current = current->next;
                std::cout << "delete current node: " << std::string(*temp) << '\n';
                delete temp;
            }
            head = nullptr;
            size = 0;
        }
    }
    // we need to be able to traverse the list so we need to implement an iterator

    // A very usefull think is to reverse the list
    void reverse() noexcept
    {
        // to reverse the list we simply have to switch the nodes until the head becomes the tail
        Node* current = head;
        Node* next = nullptr;
        Node* temp = nullptr;

        while (current != nullptr)
        {
            next = current->next;
            current->next = temp;
            temp = current;
            current = next;
        }
        head = temp;
    }
    // eventually the list is also responsible for deleting all the Nodes that have been stored
    ~LinkedList() noexcept
    {
        clear();
    }

    std::size_t getSize() const noexcept { return size; };
    bool isEmpty() const { return getSize() == 0; };
    Node* getHead() const { return this->head; };

    // adding a node at the end
    void push_front(Data data) 
    {
        // if the list is empty we're going to add head
        if (isEmpty())
        {
            head = new Node(data, nullptr);
            size++;
        }
        else
        {
            Node* newNode = new Node(data);
            newNode->next = head;
            head = newNode;
            size++;
        }
    };

    void push_back(Data data) noexcept
    {
        // if the list is empty we're going to add head
        if (isEmpty())
        {
            head = new Node(data, nullptr);
            size++;
        }
        else
        {
            Node* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = new Node(data);
            size++;
        }
    }

    void printList() const
    {
        if (isEmpty())
        {
            std::cout << "Empty list" << '\n';
        }
        else
        {
            Node* current = head;
            while (current != nullptr)
            {
                std::cout << std::string(*current) << '\n';
                current = current->next;
            }        
        }
    }
};

int main()
{
    {
        LinkedList<int> myList1;
        myList1.push_front(1);
        myList1.printList();

        LinkedList<int> myList2;
        myList2.push_front(1);
        myList2.push_back(2);
        myList2.push_front(3);
        myList2.push_back(4);
        myList2.push_front(5);
        myList2.push_back(6);
        myList2.push_front(7);
        myList2.push_back(8);
        myList2.push_front(9);

        //myList2.printList();

        myList1 = myList2;
        myList2.printList();
        myList1.printList();

        LinkedList<std::string> myList3;
        myList3.push_front("ala");
        myList3.push_front("bala");
        myList3.push_front("portocala");
        myList3.push_front("paco");
        myList3.push_front("pini");
        myList3.push_front("wini");
        myList3.push_front("cini");
        myList3.push_front("ucu");
        myList3.push_front("pucu");

        //myList3.printList();
        LinkedList<std::string> test = std::move(myList3);
        //test.printList();
        LinkedList<std::string> test2;

        test2 = std::move(test);

        test2.reverse();
        test2.printList();
    }

}