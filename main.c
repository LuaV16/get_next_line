#include "get_next_line.h"

int main(void)
{
    int fd = open("files/multiple_line_no_nl", O_RDONLY);
    size_t n = 1;

    while (get_next_line(fd) != NULL)
    {
        printf("LINE %zu: %s\n", n, get_next_line(fd));
        n++;
    }
    
    return 0;
}
