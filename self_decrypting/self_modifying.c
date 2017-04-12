#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

extern unsigned char hidden_part[];
extern unsigned char end_part[];

int change_page_permissions_of_address(void *addr);

int change_page_permissions_of_address(void *addr) {
    printf("changing permissions on: %p\n", addr);

    int page_size = getpagesize();
    printf("PAGESIZE: %d\n", page_size);

    printf("adjusting for page boundary...\n");
    addr = addr - (unsigned long)addr % page_size;
    printf("addr adjusted for page boundary: %p\n", addr);

    if(mprotect(addr, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) == -1) {
        return -1;
    }
   return 0; 
}



int main() {

    void *main_addr = (void *)main;
    if(change_page_permissions_of_address(main_addr) == -1) {
        fprintf(stderr, "Error changing memory permissions: %s\n", strerror(errno));
        return 1;
    }

    unsigned char *ptr;

    printf("\n");
    printf("bytes before decrypting: ");
    for (ptr = hidden_part; ptr < end_part; ptr++){
        printf("%02hhx ", *ptr);
    }
    printf("\n\n");


    printf("***decrypting***\n\n");
    for (ptr = hidden_part; ptr < end_part; ptr++) {
        *ptr = (*ptr ^ 0xCC);
    }

    printf("bytes after decrypting:  ");
    for (ptr = hidden_part; ptr < end_part; ptr++){
        printf("%02hhx ", *ptr);
    }
    printf("\n\n");



    __asm__("hidden_part:");  

    printf("[hidden instructions are here!!]\n");

    __asm__("end_part:");   

    return 0;
}

/* VI mappings
  map <F8> :w<CR>:make<CR><CR>
  map <F9> :w<CR>:make<CR>:!./self_modifying<CR>
*/

