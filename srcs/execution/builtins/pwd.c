#include "minishell.h"

void ft_pwd(void)
{
    char *cwd = getcwd(NULL, 0);
    int alloc = 1;

    if (!cwd)
    {
        cwd = getenv("PWD");
        alloc = 0;
    }

    if (cwd)
        ft_putendl_fd(cwd, 1);

    if (alloc)  
        free(cwd);
}
