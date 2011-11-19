#include "MineInclude.h"
#include "MineFont.h"
#include "MineEngine.h"

#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_image.h>

Font * MineFont_Load( const char *filename, int width, int height )
{
	Font *font = (Font *)malloc(sizeof(Font));
	if( NOT font ) {
		return NULL;
	}
	memset(font, 0, sizeof(Font));
	font->surface = IMG_Load(filename);
	if( NOT font->surface ) {
		free(font);
		return NULL;
	}
	font->width = width;
	font->height = height;
	return font;
}

void MineFont_Unload( Font *font )
{
	if( font ) {
		SDL_FreeSurface(font->surface);
		free(font);
	}
}

int MineFont_TextWidth( Font *font, const char *text )
{
	return strlen(text) * font->width;
}

/*
SDL_Surface * MineFont_DrawText( Font *font, const char *text )
{
	SDL_Surface* text_surface = graphics_manager_create_surface(font_get_text_width(font, text), font->height);
	
	unsigned int length = strlen(text);
	unsigned int i;
	
	for( i = 0; i < length; i++ )
	{
		SDL_Rect src_rect;
		SDL_Rect dest_rect;
		
		int c = (int)text[i];
		
		src_rect.x = (c % 16) * font->width;
		src_rect.y = (c / 16) * font->height;
		src_rect.w = font->width;
		src_rect.h = font->height;
		
		dest_rect.x = i * font->width;;
		dest_rect.y = 0;
		dest_rect.w = font->width;
		dest_rect.h = font->height;
		
		SDL_BlitSurface(font->surface, &src_rect, text_surface, &dest_rect);
	}

	return text_surface;
}
*/

void MineFont_DrawText( Font *font, const char *text, int x, int y )
{
	unsigned int length = strlen(text);
	unsigned int i;
	
	for( i = 0; i < length; i++ )
	{
		SDL_Rect src_rect;
		SDL_Rect dst_rect;
		
		int c = (int)text[i];
		
		src_rect.x = (c % 16) * font->width;
		src_rect.y = (c / 16) * font->height;
		src_rect.w = font->width;
		src_rect.h = font->height;
		
		dst_rect.x = x + (i * font->width);
		dst_rect.y = y;
		dst_rect.w = font->width;
		dst_rect.h = font->height;
		
		SDL_BlitSurface(font->surface, &src_rect, MineEngine_VideoSurface, &dst_rect);
	}
}

