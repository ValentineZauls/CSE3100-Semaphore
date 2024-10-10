#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>

int main()
{
    const char *zone = "/memzone1";
    int md = shm_open(zone, O_RDWR, S_IRWXU);

    int *t = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FILE, md, 0);
}