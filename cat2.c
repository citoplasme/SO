#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define BUFSIZE 1024
 
// TO TEST:  ./a.out < filename 
 
typedef struct buffer_t {
    char* buf;
    size_t size;
    int fd;
    int start;
    int end;
}buffer_t;

int create_buffer(int fd, struct buffer_t *b, size_t nbyte) {
    if (!b) return -1;
    char *p = malloc(nbyte);
    //char *p = calloc(nbyte, sizeof (char));
    
    if (!p) return -1;
    b -> buf = p; // string de char
    b -> size = nbyte; // tamanho da string
    b -> fd = fd; // file 
    b -> start = 0; // inicio
    b -> end = nbyte; // fim
    return 0;
}

int destroy_buffer(struct buffer_t *b) {
    b -> start = 0;
    b -> end = 0;
    b -> fd = 0;
    b -> size = 0;
    free(b -> buf);
    free(b);
    return 0;
}

int readln (int fd, void* buf, size_t nbyte) {
    int length;

    while ((length = read (fd, buf, BUFSIZE)) > 0 ) {
        write (1, buf, length);
    }
    exit (0);
    return 0;
}



int main(){
    
    buffer_t b;
    create_buffer(0,&b,10000);

    void* comeco; 
    int n = readln(0, &b, sizeof(b));

    write(1,comeco,n);

    destroy_buffer(&b);
    
    return 0;
    
}
