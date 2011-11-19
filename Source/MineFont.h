#ifndef MINE_FONT_H
#define MINE_FONT_H

#include <SDL/SDL.h>

typedef struct __mine_font Font;

struct __mine_font
{
	int          width;
	int          height;
	SDL_Surface *surface;
};

Font * MineFont_Load( const char *filename, int width, int height );
void MineFont_Unload( Font *font );
int MineFont_TextWidth( Font *font, const char *text );
void MineFont_DrawText( Font *font, const char *text, int x, int y );

#endif /* __FONT_H__ */
