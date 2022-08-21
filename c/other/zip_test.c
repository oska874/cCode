/*	zip.c Copyright (c) 2015 zeerd.com.
 *
 *  http://opensource.org/licenses/bsd-license.php
 *
 *	Compile:
 *	./configure --prefix=/usr
 *	make && sudo make isntall
 *	gcc zip.c -lzip -o zip
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

static int root_len = 0;
static char path[ PATH_MAX ];
static struct zip *z = NULL;

void search_dir ( const char * name )
{
	struct stat _stbuf;
	
	char pathBak[ PATH_MAX ];
	strcpy(pathBak, path);
	strncat( path, name, sizeof( path ));

	if (DBG_SEQ) 
        LOGI( "searching %s\n", path );
	if( stat( path, &_stbuf ) == 0 ) {
		if( S_ISDIR( _stbuf.st_mode )) {
			DIR * _dir;
			struct dirent * _file;
			_dir	=	opendir( path );
			if( _dir ) {
				if (DBG_SEQ) 
                    LOGD("find folder %s\n", path);
				//Caution : no need to do this unless there is a empty folder
				//zip_dir_add(z, name, ZIP_FL_ENC_GUESS); 
				strncat( path, "/", sizeof( path ));
				while(( _file = readdir( _dir )) != NULL ) {
					if( strncmp( _file->d_name, ".", 1 ) != 0 ) {
						search_dir( _file->d_name);
					}
				}
				closedir( _dir );
			}
			else {
				LOGE( "open dir failed: %s\n", path );
			}
		}
		else {
			if (DBG_SEQ) 
                LOGD("find file %s\n", path);

			struct zip_source *s = zip_source_file(z, path, 0, -1);
			if(s != NULL) {
				// the file name give to zip_file_add() would include the path
				zip_file_add(z, &path[root_len+1], s,
					ZIP_FL_OVERWRITE|ZIP_FL_ENC_GUESS);
				//would be used and freed by zip_close(),
				//so don't free the zip_source here.
				//zip_source_free(s); 
			} else {
				LOGE( "zip_source_file failed for %s with the reason %s\n",
					path, zip_strerror(z) );
			}
		}
	}
	else {
		LOGE( "stat failed\n" );
	}
	/* remove parsed name */
	strcpy(path, pathBak);
}


int main(int argc, char *argv[])
{
	int err = 0;
	char strerr[1024];

	if (argc < 3) {
		printf(
			"\nArchive a folder to a zip file.\n"
			"Usage:%s <path> <zip>\n"
			"Example:%s /home/foo/foo /home/foo/foo.zip\n\n",
			argv[0], argv[0]);
		return -1;
	}

	root_len = strlen(argv[1]);
	z = zip_open(argv[2], ZIP_CREATE|ZIP_EXCL, &err);

	if (z != NULL) {
		search_dir(argv[1]);
		err = zip_close(z);
    } 

    if (err != 0) {
    	zip_error_to_str(strerr, 1024, err, errno);
    	LOGE("operated zip fail for %s\n", strerr);
    }

	return 0;
}
