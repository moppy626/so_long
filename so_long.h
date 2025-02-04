#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/X.h>
#include <fcntl.h>
#include "ft_printf/ft_printf.h"
#include "get_next_line/get_next_line.h"



# define FLOOR '0'
# define WALL '1'
# define PLAYER 'P'
# define EXIT 'E'
# define ITEM 'C'
# define VILAN 'V'
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define PIC_SIZE 48
# define INFO_BER 24

typedef struct s_object
{
	void			**img;
	ssize_t			x;
	ssize_t			y;
	ssize_t			flg;
	ssize_t			idx;
} t_object;
typedef struct s_list {
    t_object		object;
    struct s_list	*next;
} t_list;
typedef struct s_monster
{
	void *left[3];
	void *right[3];
} t_monster;
typedef struct s_player
{
	void 	*back[3];
	void 	*front[3];
	void 	*left[3];
	void 	*right[3];
	void 	*damage[3];
	void	*goal[3];
} t_player;

typedef struct s_wall
{
	void *top;
	void *stone;
	void *under;
} t_wall;

typedef struct s_system
{
	void	*bar;
	void	*coin;
	void	*foot;
	void	*goalframe;
} t_system;

typedef struct s_img
{
	void 		*floor;
	void 		*item;
	void 		*goal[5];
	t_wall 		wall;
	t_player	player;
	t_monster 	monster;
	t_system	system;
} t_img;

typedef struct s_map
{
    char        **map;
    ssize_t     row;
    ssize_t     column;
	ssize_t		allitems;
	ssize_t		getitems;
	ssize_t		count;
} t_map;

typedef struct s_data
{
	void 		*mlx;
	void 		*win;
    t_map       *map;
    t_img 		img;
	t_object	player;
	t_object	goal;
	t_list		*vilans;
} t_data;

void check_map(t_data *d);
void free_data(t_data *d);
void fail_and_exit(char *msg, t_data *d);
void free_and_exit(char *msg, t_data *d);
void get_map(t_data *d, char **argv);
void init_data(t_data *d);
void init_frame(t_data *d);
void my_put_image_to_window(t_data *d, void *img, ssize_t x, ssize_t y);
int render_next_frame(t_data *data);
void render_player(t_data *d);
void check_playable(t_data *d);
void end_game(t_data *d, char *msg);
void add_list(t_list **head, ssize_t x, ssize_t y, void *img);
t_object get_from_list(t_list **head);