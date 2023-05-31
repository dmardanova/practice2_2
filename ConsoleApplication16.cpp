#include <limits> ﻿
#include <iostream>
#include <chrono>
#include "spisok.h"

using namespace std;
using namespace chrono;

int dai_chislo() {
    int value = 0;
    cin >> value;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

void vivod_spiska(spisok* list) {
    if (list) {
        for (int i = 0; i < list->length; i++)
            cout << get_spisok(list, i)->data << " ";
    }
    else
        cout << "spisok is not exist\n";
}

void sluchayniy_spisok(spisok*& list, unsigned n) {
    list = sozdat_spisok();
    list->length = n;

    node* prev = new node;
    prev->data = rand() % 100;
    list->head = prev;
    if (n != 0) {
        n--;
        while (n--) {
            node* curr = new node;
            curr->data = rand() % 100;
            prev->next = curr;
            curr->prev = prev;
            prev = curr;
        }
    }
}

void svoy_spisok(spisok*& list) {
    cout << "input numbers\n";
    list = sozdat_spisok();

    int val;
    node* prev = 0;
    bool flag = true;
    while (flag) {
        cin >> val;
        if (cin.fail())
            break;
        
        if (list->length == 0) {
            prev = new node;
            prev->data = val;
            list->head = prev;
        }
        else {
            node* curr = new node;
            curr->data = val;
            curr->prev = prev;
            if (prev)
                prev->next = curr;
            prev = curr;
        }
        list->length++;
        if (!val) {
            flag = false;
        }
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    spisok* list = 0;
    while (true) {
        vivod_spiska(list);
        cout << "\tChoose an option: \n";
        cout << "0. Exit\n";
        cout << "1. Fill with random numbers\n";
        cout << "2. Input numbers\n";
        cout << "3. Insert\n";
        cout << "4. Delete elements by index from spisak\n";
        cout << "5. Delete elements by value from spisak\n";
        cout << "6. Change elements step by step istead themselves you know like just swap them in spisak\n";
        cout << "7. Get elements from spisak\n";
        cout << "8. Get element by value from spisak\n";
        int choice = dai_chislo();
        cout << endl;
        switch (choice) {
          case 0:
            return 0;
        case 1: {
            if (list)
                ochistit_spisok(list);
            cout << "input amount n: ";
            int n = dai_chislo();
            auto t1 = steady_clock::now();
            sluchayniy_spisok(list, n);
            auto t2 = steady_clock::now();
            auto list_t = duration_cast<nanoseconds>(t2 - t1);
            cout << "Done in " << list_t.count() << " nanos.\n";
        }
              break;
        case 2:
            if (list)
                ochistit_spisok(list);

            svoy_spisok(list);
            break;
        case 3: {
            if (!list) {
                cout << "you need a list\n";
                break;
            }
            
            cout << "input inedx and value: ";
            int i = dai_chislo();
            int v = dai_chislo();
            auto t1 = steady_clock::now();
            insert_spisok(list, i, v);
            auto t2 = steady_clock::now();
            auto list_t = duration_cast<nanoseconds>(t2 - t1);
            cout << "Inserted in " << list_t.count() << " nanos.\n";
        }
              break;
        case 4: {
            if (!list) {
                cout << "you need a list\n";
                break;
            }
            if (list->length == 0) {
                cout << "list has no elements!\n";
                break;
            }
            cout << "input index: ";
            int i = dai_chislo();
            auto t1 = steady_clock::now();
            delete_spisok(list, i);
            auto t2 = steady_clock::now();
            auto list_t = duration_cast<nanoseconds>(t2 - t1);
            cout << "Deleted in " << list_t.count() << " nanos." << endl;
        }
              break;
        case 5: {
            if (!list) {
                cout << "you need a list\n";
                break;
            }
            if (list->length == 0) {
                cout << "list has no elements!\n";
                break;
            }
            cout << "input valye: ";
            int v = dai_chislo();
            auto t1 = steady_clock::now();
            node* prev = list->head;
            int nodeindex = 0;
            while (prev) {
                if (prev->data == v)
                    break;
                nodeindex++;
                prev = prev->next;
            }

            if (nodeindex < list->length)
                delete_spisok(list, nodeindex);
            auto t2 = steady_clock::now();
            auto list_t = duration_cast<nanoseconds>(t2 - t1);
            if (nodeindex == -1) {
                cout << "Not exist" << endl;
            }
            else {
                cout << "It was deleted was in " << list_t.count() << " nanos.\n";
            }
        }
              break;
        case 6: {
            if (!list) {
                cout << "you need a list\n";
                break;
            }

            cout << "input two indexes: ";
            int n1 = dai_chislo();
            int n2 = dai_chislo();
            if (n1 == n2)
                cout << "Identical indexes\n";
            else {
                auto t1 = steady_clock::now();
                change_spisok(list, n1, n2);
                auto t2 = steady_clock::now();
                auto list_t = duration_cast<nanoseconds>(t2 - t1);
                cout << "Changed was in " << list_t.count() << " nanos." << endl;
            }
        }
              break;
        case 7: {
            if (!list) {
                cout << "you need a list\n";
                break;
            }
            if (list->length == 0) {
                cout << "list has no elements!\n";
                break;
            }

            cout << "input index: ";
            int i = dai_chislo();
            auto t1 = steady_clock::now();
            int v1 = get_spisok(list, i)->data;
            auto t2 = steady_clock::now();
            auto list_t = duration_cast<nanoseconds>(t2 - t1);
            cout << "value is " << v1 << " found in " << list_t.count() << " nanos.\n";
        }
              break;
        case 8: {
            if (!list) {
                cout << "you need a list\n";
                break;
            }
            if (list->length == 0) {
                cout << "list has no elements!\n";
                break;
            }

            cout << "input value: ";
            int v = dai_chislo();
            auto t1 = steady_clock::now();
            node* prev = list->head;
            int nodeindex = 0;
            while (prev) {
                if (prev->data == v)
                    break;
                nodeindex++;
                prev = prev->next;
            }
            auto t2 = steady_clock::now();
            auto list_t = duration_cast<nanoseconds>(t2 - t1);
            if (nodeindex == -1) {
                cout << "not exist" << endl;
            }
            else {
                cout << "exists index " << nodeindex << " found in " << list_t.count() << " nanos.\n";
            }
        }
              break;
        default:
            cout << "option not exist\n";
            break;
        }
    }
    if (list) {
        ochistit_spisok(list);
    }
    return 0;
}
