#ifndef NOTIFY_FILE_H
#define NOTIFY_FILE_H

struct notify_node;

int init_notify_list(struct notify_node **n);
int is_empty_notify_list(struct notify_node * n);
struct notify_node* find_notify_list_node(struct notify_node *l, int wd);
int add_notify_list_node(struct notify_node **p, int wd, char *dir);
void delete_notify_list(struct notify_node **n);
static struct notify_node* find_position(struct notify_node * n, int wd);
int get_user(char *);


#endif
