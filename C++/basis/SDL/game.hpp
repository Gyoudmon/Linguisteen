#ifndef _SYNTAX_GAME_H
#define _SYNTAX_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <cstdint>

namespace WarGrey::STEM {
    /**********************************************************************************************/
    typedef struct timer_frame {
        uint32_t interval;
        uint32_t count;
        uint32_t uptime;
    } timer_frame_t;

    typedef void (*timer_update_t)(timer_frame_t*, void*, SDL_Renderer*);

    typedef struct timer_parcel {
        timer_update_t update_game_world;
        void* user_datum;
        timer_frame_t frame;
    } timer_parcel_t;

    /**********************************************************************************************/
    void game_initialize(uint32_t flags, int fontsize = 16);
    SDL_Texture* game_create_world(int width, int height, SDL_Window** window, SDL_Renderer** renderer);
    uint32_t game_start(uint32_t fps, timer_update_t update_game_world, void* user_datum);
    
    void game_world_reset(SDL_Renderer* renderer, SDL_Texture* texture, uint32_t fgcolor, uint32_t bgcolor);
    void game_world_refresh(SDL_Renderer* renderer, SDL_Texture* texture);
    
    TTF_Font* game_create_font(const char* face, int fontsize);
    void game_font_destroy(TTF_Font* font);

    void game_draw_grid(SDL_Renderer* renderer, int nx, int ny, int grid_size, int xoff = 0, int yoff = 0);
    void game_fill_grid(SDL_Renderer* renderer, int* grids, int nx, int ny, int grid_size, int xoff = 0, int yoff = 0);

    /**********************************************************************************************/
    extern TTF_Font* GAME_DEFAULT_FONT;
    extern TTF_Font* game_sans_serif_font;
    extern TTF_Font* game_serif_font;
    extern TTF_Font* game_monospace_font;
    extern TTF_Font* game_math_font;
}

#endif
