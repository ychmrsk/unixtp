/* filesize.c -- print the size of passwd file

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
#include <sys/stat.h>

int main(void)
{
  struct stat infobuf;

  if (stat("/etc/passwd", &infobuf) == -1)
    perror("/etc/passwd");
  else
    printf("The size of /etc/passwd is %ld\n", infobuf.st_size);
}
