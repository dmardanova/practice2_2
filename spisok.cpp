#include <iostream>
#include "spisok.h"

spisok* sozdat_spisok(int n) {
    spisok* list = new spisok{};
    if (n <= 0)
        return list;

    node* current = 0;
    node* next = 0;
    for (int i = 1; i <= n; i++) {
        current = new node;
        current->next = next;
        if (next)
            next->prev = current;
        next = current;
    }

    list->head = current;
    list->length = n;

    return list;
}

node* get_spisok(spisok* list, unsigned index)
{
    node* node = list->head;
    while (node && (index--))
        node = node->next;
    return node;
}

unsigned dlina_spiska(spisok* list)
{
    unsigned length = 0;
    node* node = list->head;
    while (node)
    {
        length++;
        node = node->next;
    }
    return length;
}

void delete_spisok(spisok* list, unsigned index)
{
    if (index == 0)
    {
        node* item = list->head->next;
        delete list->head;
        item->prev = 0;
        list->head = item;
        list->length--;
    }
    else {
        node* prevItem = get_spisok(list, index - 1);
        if (prevItem) {
            node* delItem = prevItem->next;
            prevItem->next = delItem->next;

            if (prevItem->next)
                prevItem->next->prev = prevItem;
            delete delItem;
            list->length--;
        }
    }
}

void ochistit_spisok(spisok* list)
{
    node* next;
    node* current = list->head;
    while (current)
    {
        next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

node* insert_spisok(spisok* list, unsigned index, int value)
{
    node* item = new node;
    item->data = value;
    if (!(list->head)) // когда в списке нет элементов
        list->head = item;
    else if (index == 0) {
        node* first = list->head;
        list->head = item;
        item->next = first;
        first->prev = item;
    }
    else {
        node* prev = list->head;
        index--;
        while (prev->next && (index--))
            prev = prev->next;
        item->prev = prev;
        item->next = prev->next;
        if (prev->next) 
            prev->next->prev = item;
        prev->next = item;
    }
    list->length++;
    return item;
}

void change_spisok(spisok* list, unsigned index1, unsigned index2)
{
    node* node1 = get_spisok(list, index1);
    node* node2 = get_spisok(list, index2);
    if (index1 == index2 || !node1 || !node2)
        return;
    
    if (node1->prev)
        node1->prev->next = node2;
    if (node2->prev)
        node2->prev->next = node1;
    std::swap(node1->prev, node2->prev);
    if (node2->next)
        node2->next->prev = node1;
    if (node1->next)
        node1->next->prev = node2;
    std::swap(node1->next, node2->next);

    if ((list->head) == node1)
        list->head = node2;
    else if ((list->head) == node2)
        list->head = node1;
}
