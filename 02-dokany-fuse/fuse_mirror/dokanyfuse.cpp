/*
  FUSE: Filesystem in Userspace
  Fuse example using dokan library in Windows

  Copyright (C) 2022       Rubén Alcolea Núñez <ruben.crash@gmail.com>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
*/

/** @file
 * @tableofcontents
 *
 * dokanyfuse.cpp - FUSE: Filesystem in Userspace
 *
 * \section section_compile compiling this example
 * 
 * Compile this demo using Cygwin:
 * g++ dokanyfuse.cpp -I../include -D_FILE_OFFSET_BITS=64 -L. -lcygdokanfuse2 -o dokanyfuse.exe
 *
 * Run this demo:
 * ./dokanyfuse.exe h       # Mount a crash filesystem / as drive H:\
 * 
 * \section section_source the complete source
 * \include dokanyfuse.cpp
 */

#define FUSE_USE_VERSION 30

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef linux
/* For pread()/pwrite()/utimensat() */
#define _XOPEN_SOURCE 700
#endif

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <windows.h>
#ifdef HAVE_SETXATTR
#include <sys/xattr.h>
#endif

static const char *filepath = "/.crash";
static const char *filename = ".crash";
static const char *content = "Hello World crash!";

static int getattr_callback(const char *path, struct stat *stbuf) {
    memset(stbuf, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        return 0;
    }

    if (strcmp(path, filepath) == 0) {
        stbuf->st_mode = S_IFREG | 0777;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(content);
        return 0;
    }

    return -ENOENT;
}

static int readdir_callback(const char *path, void *buf, fuse_fill_dir_t filler,
                            off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    filler(buf, filename, NULL, 0);

    return 0;
}

static int open_callback(const char *path, struct fuse_file_info *fi) {
    return 0;
}

static int read_callback(const char *path, char *buf, size_t size, off_t offset,
                         struct fuse_file_info *fi) {

    if (strcmp(path, filepath) == 0) {
        long unsigned int len = strlen(content);
        if (offset >= (off_t) len) {
            return 0;
        }

        if (offset + size > len) {
            memcpy(buf, content + offset, len - offset);
            return len - offset;
        }

        memcpy(buf, content + offset, size);
        return size;
    }

    return -ENOENT;
}

static struct fuse_operations xmp_oper = {
    .getattr = getattr_callback,
    .open = open_callback,
    .read = read_callback,
    .readdir = readdir_callback,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
