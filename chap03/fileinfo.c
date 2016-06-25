/* fileinfo.c -- using stat()

   other information `stat` supplies are
   + st_mode  type and permission
   + st_uid   owner ID
   + st_gid   group ID
   + st_size  file size (byte)
   + st_nlink number of links
   + st_mtime last modified time
   + st_atime last access time
   + st_ctime last property-modified time

 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

void show_stat_info(char *, struct stat *);

int main(int ac, char *av[])
{
  struct stat info;

  if (ac > 1)
    if (stat(av[1], &info) != -1) {
      show_stat_info(av[1], &info);
      return 0;
    } else
      perror(av[1]);
  return 1;
}

void show_stat_info(char *fname, struct stat *buf)
{
  printf("   mode: %o\n", buf->st_mode);  /* type + mode */
  printf("  links: %ld\n", buf->st_nlink);  /* num link */
  printf("   user: %d\n", buf->st_uid);  /* user ID */
  printf("  group: %d\n", buf->st_gid);  /* group ID */
  printf("   size: %ld\n", buf->st_size);  /* file size */
  printf("modtime: %ld\n", buf->st_mtime);  /* modified time */
  printf("   name: %s\n", fname);          /* file name */
}
