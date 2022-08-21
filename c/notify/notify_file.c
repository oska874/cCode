#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <time.h>
#include <utmp.h>
#include "notify_file.h"

#define BUF_LEN 1024

struct notify_node {
    int n_wd;
    char *n_dir;
    struct notify_node *next, *previous;
};

int init_notify_list(struct notify_node **n)
{
    (*n) = NULL;
    return 0;
}

int is_empty_notify_list(struct notify_node *n)
{
    return n == NULL;
}

struct notify_node * find_position(struct notify_node *l, int wd)
{
    struct notify_node *p;

    p = l;
    if (p == NULL)
        return NULL;
    while (p->next != NULL) {
        // p = (p->n_wd < wd) ?  p->next : return(p);
        if (p->n_wd < wd)
            p = p->next;
        else
            break;
    }
    return p;
}

int add_notify_list_node(struct notify_node **l, int wd, char *dir)
{
    int len;
    struct notify_node *p, *position;

    len = strlen(dir);

    if ((*l) == NULL) {
        (*l) = (struct notify_node *)calloc(1, sizeof(struct notify_node));
        (*l)->n_wd = wd;
        (*l)->n_dir = (char *)calloc(1, len + 1);
        strcpy((*l)->n_dir, dir);
        (*l)->n_dir[len] = '\0';

        return 0;
    }

    p = (struct notify_node *)calloc(1, sizeof(struct notify_node));
    p->next = p->previous = NULL;
    p->n_wd = wd;
    p->n_dir = (char *)calloc(1, len + 1);
    strcpy(p->n_dir, dir);
    p->n_dir[len] = '\0';

    position = find_position((*l), wd);
    if (position->n_wd > wd) {
        if (position->previous == NULL) {
            position->previous = p;
            p->next = position;
            (*l) = p;
        } else {
            p->previous = position->previous;
            position->previous->next = p;
            p->next = position;
            position->previous = p;
        }
    } else {
        position->next = p;
        p->previous = position;
    }

    return 0;
}

void delete_notify_list(struct notify_node **l)
{
    struct notify_node *p, *flag;

    p = flag = (*l);

    while (p != NULL) {
        p = p->next;
        free(flag->n_dir);
        free(flag);
        flag = p;
    }

}
void display(struct notify_node ** l)
{
    struct notify_node *p;

    p = (*l);
    while (p != NULL) {
        printf("%s----->%d\n", p->n_dir, p->n_wd);
        p = p->next;
    }
}
struct notify_node* find_notify_list_node(struct notify_node *l, int wd)
{
    struct notify_node *p;

    p = l;
    if (p == NULL)
        return NULL;
    while (p != NULL) {
        // p = (p->n_wd < wd) ?  p->next : return(p);
        if (p->n_wd == wd)
            break;
        else
            p = p->next;
    }
    return p;

}

int recursive_inotify(int fd, char *dir, uint32_t mask, struct notify_node **list)
{
    DIR *dp;
    int wd;
    struct dirent *ep;
    struct stat fstat;
    char directory[1024] = {0,};


    dp = opendir(dir);
    if (dp == NULL) {
        printf("Open Error: %s\n", dir);
        perror("opendir");
        exit(EXIT_FAILURE);
        return 2;
    }

    chdir(dir);

    //dps
    while (ep = readdir(dp)) {
        if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0)
            continue;

        lstat(ep->d_name, &fstat);
        if (S_ISDIR(fstat.st_mode) && !S_ISLNK(fstat.st_mode)) {
            // puts(ep->d_name);
            // printf("st_mode:%u\n", fstat.st_mode);
            //chdir(ep->d_name);
            bzero(directory, 1024);
            getcwd(directory, 1024);
            if (directory[strlen(directory) - 1] != '/')
                strcat(directory, "/");
            strcat(directory, ep->d_name);
            //  puts(directory);
            wd =  inotify_add_watch(fd, directory, mask);  // add watch
            if (wd < 0) {
                printf("ERROR:%s\n", directory);
                perror("inotify_add_watch");
                exit(EXIT_FAILURE);
            }
            add_notify_list_node(list, wd, directory);

            //	  printf("Beeeee%s\n", directory);
            recursive_inotify(fd, directory, mask, list);
        }

        /* getcwd(directory, 1024); */

        /* puts(directory); */

    }
    chdir("..");
    closedir(dp);
}

int notify_dir(char *dir, uint32_t mask)
{
    int fd;
    int wd;
    char buf[BUF_LEN] __attribute__((aligned(4)));
    ssize_t len, i = 0;
    fd_set set;
    char *action;
    char directory[1024];
    char users[1024];
    struct notify_node *list, *p;

    init_notify_list(&list);

    fd = inotify_init();
    openlog("notify_dir", LOG_CONS, LOG_AUTH);

    if (fd == -1) {
        perror("inotify_init");
        return 1;			/* 1 for intofy_init error */
    }
    wd = inotify_add_watch(fd, dir,  mask);  // watch the input directory
    if (wd == -1) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    recursive_inotify(fd, dir, mask, &list);       // recursive watch the subdirectory
    //  display(&list);
#if !DEBUG
    while (1) {
        i = 0;
        FD_ZERO(&set);
        FD_SET(fd, &set);
        bzero(buf, BUF_LEN);

        select(fd + 1, &set, NULL, NULL, NULL);
        /* read BUF_LEN bytes' worth of events */

        if (FD_ISSET(fd, &set)) {
            len = read (fd, buf, BUF_LEN);
            if (len < 0)
                perror("read");
            while (i < len) {
                /* loop over every read event until none remain */
                struct inotify_event *event = (struct inotify_event *) &buf[i];
                if (event->len) {
                    if (event->mask & IN_ACCESS) {
                        puts("Access:");
                        action = "Access:";
                    } else if (event->mask & IN_CREATE) {
                        puts("Create:");
                        action = "Create:";
                    } else if (event->mask & IN_MOVE) {
                        puts("Move:");
                        action = "Move:";
                    } else if (event->mask & IN_DELETE) {
                        puts("Delete:");
                        action = "Delete:";
                    } else if (event->mask & IN_MODIFY) {
                        puts("Modify:");
                        action = "Modify:";
                    }
                    printf ("%s wd=%d mask=%d cookie=%d len=%d dir=%s\n",
                            action,
                            event->wd, event->mask,
                            event->cookie, event->len,
                            event->name);
                    p = find_notify_list_node(list, event->wd);
                    if (p) {
                        get_user(users);
                        puts(users);
                        strcpy(directory, p->n_dir);

                        if (directory[strlen(directory) - 1] != '/')
                            strcat(directory, "/");
                        strcat(directory, event->name);
                        strcat(directory, users);
                        printf("%d-->%s\n", p->n_wd, directory);
                        syslog(LOG_AUTH,"%s%s", action, directory);
                    }
                }
                /* if there is a name, print it */
                //	      if (event->len)
                //		printf ("name=%s\n", event->name);
                /* update the index to the start of the next event */
                i += sizeof (struct inotify_event) + event->len;
            }

        }
        puts("----------------------------------------------------------");
    }
#endif
    delete_notify_list(&list);
    close(fd);
    return 0;
}

int get_user(char *l)
{
    struct utmp *p;
    char line[1024];
    time_t t, now;
    char *s;

    time(&now);
    s = ctime(&now);
    while (p = getutent()) {
        if (p->ut_type == USER_PROCESS) {
            t =(time_t) p->ut_tv.tv_sec;
            sprintf(line, "\t%s %s %s %s", p->ut_user, p->ut_line, p->ut_host, ctime(&t));
            line[strlen(line)-1] = '\0';
            strcat(l, line);
        }
    }
}

int main(int argc, char *argv[])
{
#define MASK IN_ACCESS | IN_CREATE | IN_MOVE | IN_DELETE |  IN_MODIFY
#define DEBUG 0
    if (argc != 2) {
        puts("Usage: notify_dir directory");
        return 2;
    }
    notify_dir(argv[1], MASK);
    //  recursive_inotify(1, "/home/lyhux/Documents/curl-7.25.0", MASK);
    return 0;
}
