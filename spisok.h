struct node {
    int data = 0;
    node* prev = 0;
    node* next = 0;
};

struct spisok {
    int length;
    node* head;
};

spisok* sozdat_spisok(int n = 0);
void ochistit_spisok(spisok*);
void delete_spisok(spisok*, unsigned);
node* get_spisok(spisok*, unsigned);
node* insert_spisok(spisok*, unsigned, int n = 0);
void change_spisok(spisok*, unsigned, unsigned);
unsigned dlina_spiska(spisok*);