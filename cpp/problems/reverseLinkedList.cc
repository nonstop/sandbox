#include <iostream>

using namespace std;

struct Item
{
    const char* v;
    Item* next;

    Item(const char* v_)
        : v(v_), next(NULL)
    {}
};

Item* reverseList(Item* item)
{
    Item* prev = NULL;
    while (item) {
        Item* next = item->next;
        item->next = prev;
        prev = item;
        if (next == NULL) {
            return item;
        } else {
            item = next;
        }
    }
    return item;
}

void printList(const Item* item)
{
    while (item) {
        cout << " [" << item->v << ']';
        item = item->next;
    }
    cout << endl;
}

int main(int ac, char* av[])
{
    if (ac < 2) {
        return -1;
    }
    Item* head = new Item(av[1]);
    Item* item(head);
    for (int i = 2; i < ac; ++i) {
        Item* newItem = new Item(av[i]);
        item->next = newItem;
        item = newItem;
    }
    printList(head);
    printList(reverseList(head));
    return 0;
}
