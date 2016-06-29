#ifndef PLUGIN_H
#define PLUGIN_H

#include "libntrplg\global.h"
#include "configs.h"
#include "common.h"

#define 	MENU_COUNT 	1
#define 	ENTRY_COUNT 	300
enum 		MENU		{BASE};

typedef enum
{
	STATE 			= BIT(0),
	FREEZE 			= BIT(1),
	SELECTABLE 		= BIT(2)
}				menu_flags;

typedef enum
{
	VISIBILITY		= BIT(0),
	SPOILABLE		= BIT(1),
	HEAD			= BIT(2),
	HEAD2			= BIT(3),
	CHILD			= BIT(4),
	ID_MASK			= (0xFF << 8),
	PARENT_ID_MASK		= (0xFF << 16),
}				spoiler_flags;

typedef struct	s_spoil
{
	int			id;
	int			space;
	enum MENU		m;
}				t_spoil;

typedef struct	s_menu
{
	int			count;
	int			status;
	u32			flags[ENTRY_COUNT];
	u32			spoiler[ENTRY_COUNT];
	int			args[ENTRY_COUNT];
	const char		*text[ENTRY_COUNT];
	void			(*f[ENTRY_COUNT])();
}				t_menu;

static inline u32		create_menu_flags(int state, int freeze, int selectable)
{
	return ((state) | (freeze << 1) | (selectable << 2));
}

static inline u32		create_spoiler_flags(int visibility, int spoilable, int head, int head2,  int child, int id, int parent_id)
{
	return ((visibility) | (spoilable << 1) | (head << 2) | (head2 << 3) | (child << 4) | ((id & 0xFF) << 8) | ((parent_id & 0xFF) << 16));
}

/*
**cheats_menu.c
*/
void	my_menus(void);

/*
**protect.c
*/
void	protect_region(void);

/*
**menu_display.c
*/

void	create_menu_entry(enum MENU m, const char *text, void(*f)(), int arg, u32 menu_flags, u32 spoiler_flags);
void	new_entry(char *text, void(*f)());
void	new_unselectable_entry(char *text);
void	new_separator(void);
void	new_line(void);

/*
** spoiler_display.c
*/

t_spoil	new_spoiler(char *text);
t_spoil new_child_spoiler(t_spoil parent, char *text);
void	new_spoiled_entry(t_spoil parent, char *text, void(*f)());




#endif
