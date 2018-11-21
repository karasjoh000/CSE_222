#define MYNULL -1
#define LIST_SIZE 100
struct node{ //def. of the structure
	int data;
	int next;
	int valid;
};

void usage(void);
void init(struct node *x);
int get_node(struct node *ptr);
void release_node(struct node *ptr, int index);
int delete(struct node *ptr, int num);
void print(struct node* ptr);
int search(struct node* ptr, int num);
int add(struct node* ptr, int num);
int swap(struct node *ptr, int prev, int new, int next, int num);
