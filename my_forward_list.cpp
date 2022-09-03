#include <iostream>

class My_forward_list
{
private:
    struct Node
    {
        int data;
        Node* next;
        Node() : data(0), next(nullptr) {}
        Node(int value) : data(value), next(nullptr) {}
    };
    Node* root;

public:
    My_forward_list() : root(nullptr) {}
    My_forward_list(int value)
    {
        root = new Node();
        root->next = new Node(value);
    }
    My_forward_list(const My_forward_list& obj)
    {
        root = deep_copy(obj.root);
    }
    My_forward_list(My_forward_list&& obj)
    {
        std::cout << "Move ctor";
        root = obj.root;
        obj.root = nullptr;
    }
    ~My_forward_list()
    {
        if (root == nullptr)
        {
            return;
        }
        deleter(root);
    }

public:
    My_forward_list& operator=(const My_forward_list& obj)
    {
        if (this == &obj)
        {
            return *this;
        }
        if (root != nullptr)
        {
            deleter(root);
        }
        root = deep_copy(obj.root);
        return *this;
    }
    My_forward_list& operator=(My_forward_list&& obj)
    {
        if (this == &obj)
        {
            return *this;
        }
        if (root != nullptr)
        {
            deleter(root);
        }
        root = obj.root;
        obj.root = nullptr;
        return *(this);
    }
    My_forward_list operator+(const My_forward_list& obj)
    {
        if (root == nullptr)
        {
            root = deep_copy(obj.root);
            return *this;
        }
        if (obj.root == nullptr)
        {
            return *this;
        }
        merge(find_end(root), obj.root->next);
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const My_forward_list& obj)
    {
        if (obj.root == nullptr)
        {
            return os;
        }
        obj.print(os, obj.root->next);
        return os;
    }

private:
    Node* deep_copy(Node* ptr)
    {
        if (ptr == nullptr)
        {
            return nullptr;
        }
        Node* tmp = new Node(ptr->data);
        tmp->next = deep_copy(ptr->next);
        return tmp;
    }
    void deleter(Node* ptr)
    {
        if (ptr == nullptr)
        {
            return;
        }
        deleter(ptr->next);
        delete ptr;
        ptr = nullptr;
    }
    void print(std::ostream& os, const Node* ptr) const
    {
        if (ptr == nullptr)
        {
            return;
        }
        os << ptr->data << ' ';
        print(os, ptr->next);
    }
    Node* insert_helper(Node* ptr, int index)
    {
        if (ptr == nullptr)
        {
            if (index >= 0)
            {
                return nullptr;
            }
        }
        if (index == 0)
        {
            if (ptr ==nullptr)
            {
                return nullptr;
            }
            return ptr;
        }
        return insert_helper(ptr->next, index - 1);
    }
    Node* find_end(Node* ptr)
    {
        if (ptr->next == NULL)
        {
            return ptr;
        }
        return find_end(ptr->next);
    }
    void merge(Node* ptr1, Node* ptr2)
    {
        if (ptr2 == nullptr)
        {
            return;
        }
        if (ptr1->next == nullptr)
        {
            ptr1->next = new Node(ptr2->data);
            merge(ptr1->next, ptr2->next);
            return;
        }
        merge(ptr1->next, ptr2);
    }
    Node* erase_helper(Node* ptr, int value)
    {
        if (ptr->next == nullptr)
        {
            return nullptr;
        }
        if (ptr->next->data == value)
        {
            return ptr;
        }

        return erase_helper(ptr->next, value);
    }

public:
    void insert_after(int index, int value)
    {
        if (root == nullptr)
        {
            return;
        }
        Node* ptr = insert_helper(root->next, index);
        if (ptr == nullptr)
        {
            return;
        }
        Node* tmp = new Node(value);
        tmp->next = ptr->next;
        ptr->next = tmp;
    }
    void push_front(int value)
    {
        if (root == nullptr)
        {
            root = new Node();
            root->next = new Node(value);
            return;
        }
        Node* tmp = new Node(value);
        tmp->next = root->next;
        root->next = tmp;
    }
    void remove(int value)
    {
        Node* tmp = erase_helper(root, value);
        if (tmp == nullptr)
        {
            return;
        }
        tmp->next = tmp->next->next;
    }
};

int main()
{
    My_forward_list obj1(453);
    obj1.push_front(53);
    obj1.push_front(7);
    std::cout << obj1 << std::endl;
    obj1.remove(89);
    std::cout << obj1 << std::endl;
}