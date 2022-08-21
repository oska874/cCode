#include <unistd.h>
#include <zip.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



struct file_info {
    char *name;
    ssize_t len;
    char *path;
    mode_t mode;
};

int32_t delete_file_dir(char *path)
{
    return remove(path);
}
int pmkdir(const char *path)
{
    char name[strlen(path)];
    strcpy(name, path);
    int i, len = strlen(name);
    if (name[len-1]!='/') {
        strcat(name, "/");
    }

    len = strlen(name);
    for (i=1 ; i<len ; i++) {
        if (name[i]=='/') {
            name[i] = 0;
            if ( access(name, NULL) !=0 ) {
                if (mkdir(name, 0777) == -1) {
                    printf("mkdir error");
                    return -1;
                }
            }
            name[i] = '/';
        }
    }
    return 0;
}

int32_t compress_files(char **fnames, int32_t file_num, char *compressed, int32_t type)
{
    int32_t ret;
    char strerr[1024];
    if(compressed == NULL || fnames == NULL || file_num <1) {
        printf("para wrong: %d %s %s\n",file_num, fnames,compressed);
        ret = EINVAL;
    } else {
        struct zip *z = NULL;
        struct zip_source *s=NULL;
        int32_t err=0;

        z = zip_open(compressed, ZIP_CREATE|ZIP_EXCL, &err);
        if(z != NULL) {
            for(int32_t i=0; i<file_num; i++) {
                //printf("%s\n", fnames[i]);
                s = zip_source_file(z, fnames[i], 0, -1);
                if(s!=NULL) {
                    if (zip_file_add(z, fnames[i], s, ZIP_FL_OVERWRITE|ZIP_FL_ENC_GUESS)<0) {
                        printf("error adding file: %s\n", zip_strerror(z));
                    }
                } else {
                    printf("source fail \n");
                    ret = -2;
                }
            }
            err =zip_close(z);
            if(err != 0) {
                zip_error_to_str(strerr, 1024, err, errno);
                printf("op zip fail %s\n",strerr);
                ret = -1;
            } else {
                ret = 0;
            }
        } else {
            ret = -3;
        }
    }
    return ret;
}

int32_t uncompress_file(char *compressed, char *dest_dir, int32_t type)
{
    int32_t ret;
    char strerr[1024];

    if(compressed == NULL || dest_dir == NULL) {
        printf("para wrong: %s %s\n",compressed, dest_dir);
        ret = EINVAL;
    } else {
        if (access(compressed, R_OK|F_OK) != 0||access(dest_dir, W_OK)!=0) {
            printf("path err %s %s\n", compressed, dest_dir);
            ret = EINVAL;
        } else {
            struct zip *z = NULL;
            struct zip_source *s=NULL;
            int32_t err=0;

            char *dest_path_joint = malloc(strlen(dest_dir)+100);
            if( dest_path_joint == NULL) {
                perror("dest path malloc fail");
                ret = -1;
            } 
            else {
#if 1
                size_t plen = strlen(dest_dir);
                memcpy(dest_path_joint, dest_dir, plen);
                dest_path_joint[plen] = '/';
#endif
                z = zip_open(compressed, ZIP_CREATE, &err);
                if (z != NULL) {
                    zip_int64_t f_cnt = zip_get_num_entries(z, ZIP_FL_UNCHANGED);
                    for(zip_int64_t i=0; i<f_cnt; i++) {
                        const char *name = zip_get_name(z, i, ZIP_FL_ENC_GUESS);
                        //printf("find %s\n", name);
                        char *d = strdup(name);
                        if( d != NULL) {
                            char *p = strrchr(d, '/');
                            if(p != NULL) {
#if 1
                                p++;
                                //printf("A %s,%d\n",p,strlen(p));
                                //printf("!?%s,%d\n",dest_path_joint,strlen(dest_path_joint));
                                memcpy(&dest_path_joint[plen], p, strlen(p));
                                dest_path_joint[plen+strlen(p)] ='\0';
#endif
                                //*p = '\\0';
                                //pmkdir(d);
                            }
                            else{
#if 1
                                //printf("B %s,%d\n",d,strlen(d));
                                memcpy(&dest_path_joint[plen], d, strlen(d));
                                dest_path_joint[plen+strlen(d)] ='\0';
#endif
                            }
                            free(d);
                        //    printf("!%s %d\n",dest_path_joint,strlen(dest_path_joint));
                            int32_t fd = open(dest_path_joint, O_WRONLY|O_CREAT|O_TRUNC, 0777);
                            struct zip_file *f = zip_fopen(z, name, 0);
                            if (f != NULL && fd > 0) {
                                zip_int64_t j, n = 0;
                                char buf[1024];
                                while ((n = zip_fread(f, buf, 1024))> 0) {
                                    write(fd, buf, n);
                                }
                                syncfs(fd);
                                close(fd);
                                zip_fclose(f);
                            }
                        } else {
                            perror("low mem\n");
                            ret = -2;
                        }
                    }
                    err = zip_close(z);
                    ret = 0;
                }
            }
        }
    }
    return ret;
}

int32_t list_compressed(char *compressed, struct file_info *info_list)
{
    int32_t ret;

    return ret;
}


int main()
{
    int32_t ret=0;
    char **names;
    char *name_buf;
    char tmp[]="a\0";//"/home/ezio/src/cCode/other/a\0";
    name_buf = malloc(10*(strlen(tmp)+1));
    if(name_buf == 0) {
        perror("req nb fail");
        return -1;
    }
    names=malloc(10*sizeof(char*));
    if(names== 0) {
        perror("req name fail");
        return -2;
    }

    size_t nlen = strlen(tmp);
//    printf("%d\n",nlen);
    for(int i=0; i<8; i++) {
        tmp[nlen-1]+=1;
        memcpy(&name_buf[i*(nlen+1)], tmp, nlen+1);
        names[i] = &name_buf[i*(nlen+1)];
  //      printf("%s , %d %d\n",names[i],strlen(tmp),strlen(names));
    }
    printf("compress zip\n");
    ret = compress_files(names, 8, "alpha.zip", 0);
    if(ret <0) {
        printf("compress fail %d\n",ret);
    }
    printf("uncompress zip\n");
    ret = uncompress_file("/home/ezio/src/cCode/other/alpha.zip","/home/ezio/src/cCode/other/x/",0);
    if(ret <0) {
        printf("uncompress fail %d\n",ret);
    }
    printf("delete zip\n");
    ret = delete_file_dir("/home/ezio/src/cCode/other/alpha.zip");
    if(ret != 0){
        perror("delete fail");
        printf("path %s\n", "/home/ezio/src/cCode/other/alpha.zip");
    }
    return 0;
}
