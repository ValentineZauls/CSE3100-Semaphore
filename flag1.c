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
    int md = shm_open(zone, O_RDWR | O_CREAT, S_IRWXU);

    // truncate the file to one page
    ftruncate(md, 4096);
    int *t = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, md, 0);
    sem_t *s = sem_open("/sema2", O_CREAT, 0666, 1);
    if (s == SEM_FAILED)
    {
        printf("Semaphore failed to open: %s\n", strerror(errno));
        exit(1);
    }
    memset(t, 0, 4096);
    for (int i = 0; i < 1000000000; i++)
    {
        sem_wait(s); // program hangs here
        t[0] = t[0] + 1;
        sem_post(s);
    }
    int final = t[0];
    munmap(t, 4096);
    close(md);
    shm_unlink("/sema2");
    printf("Final: %d\n", final);
    return 0;
}