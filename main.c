#include "so_long.h"



int function(int keycode, char *ds)
{
    printf("%d - %s\n", keycode, ds);
    return (0);
}

int main(int argc, char **argv)
{
    void    *mld;
    void    *win;

    parcing(argc, argv);
    if(validate_map(argv))
    {
        mld = mlx_init();
        if (!mld)
        {
            return (1);
        }
        
        win = mlx_new_window(mld, 800, 600, "Zakaria");
        if (!win)
        {
            return (1);
        }
        mlx_loop(mld);
    }
    // void *mld;


    // mld = mlx_init();
    // //-----------
    // void *win = mlx_new_window(mld, 800, 600, "MyWindow");

    // mlx_key_hook(win, function, "ll");

    // mlx_loop(mld);

    return (0);
}
