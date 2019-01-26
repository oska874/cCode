/*	unzip.c Copyright (c) 2015 zeerd.com.
 *
 *  http://opensource.org/licenses/bsd-license.php
 *
 *	Compile:
 *	./configure --prefix=/usr
 *	make && sudo make isntall
 *	gcc unzip.c -lzip -o unzip
 *
 *	Got libzip from http://www.nih.at/libzip
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

#include <zip.h>

#define DBG_SEQ 0
#define LOGI printf
#define LOGD printf
#define LOGE printf

int pmkdir(const char *path) 
{ 
	char name[ PATH_MAX ]; 
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
				if (mkdir(name, 0755) == -1) {  
					LOGE("mkdir error");  
					return -1;  
				} 
			}
			name[i] = '/'; 
		} 
	} 

	return 0; 
} 

int main(int argc, char *argv[])
{
	int err = 0;
	char strerr[1024];
	struct zip *z = NULL;

	if (argc < 2) {
		printf(
			"\nUn-Archive a zip file to the current path.\n"
			"Usage:%s <zip>\n"
			"Example:\n%s foo.zip\n",
			argv[0], argv[0]);
		return -1;
	}

	z = zip_open(argv[1], ZIP_CREATE, &err);
	if (z != NULL) {
		zip_int64_t i, c = zip_get_num_entries(z, ZIP_FL_UNCHANGED);
		for (i=0; i<c ; i++) {
			const char * name = zip_get_name(z, i, ZIP_FL_ENC_GUESS);
			LOGI("find %s\\n", name);
			char *d = strdup(name);
			if (d != NULL) {
				char *p = strrchr(d, '/');
				if(p != NULL) {
					*p = '\\0';
					pmkdir(d);
				}
				free(d);

				FILE *fp = fopen(name, "w+b");
				struct zip_file *f = zip_fopen(z, name, 0);
				if (f != NULL && fp != NULL) {
					zip_int64_t j, n = 0;
					char buf[8192] = "";
					while ((n = zip_fread(f, buf, sizeof(buf))) > 0) {
                        printf("%d\n",n);
						for (j=0;j<n;j++) {
							putc(buf[j], fp);
						}
					}
					fclose(fp);
					zip_fclose(f);
				}
			} else {
				LOGE("memory low\\n");
			}
		}

		err = zip_close(z);
	} else {
		zip_error_to_str(strerr, 1024, err, errno);
		LOGE("operated zip fail for %s\\n", strerr);
	}

	return 0;
}
