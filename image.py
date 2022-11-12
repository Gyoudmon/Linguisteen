import sdl2
import sdl2.sdlimage as sdlimg

from .geometry import *

###################################################################################################
def game_blank_image(width, height):
    return sdlimg.SDL_CreateRGBSurface(0, int(width), int(height), 32, 0, 0, 0, 0)

def game_load_image(file):
    return sdlimg.IMG_Load(file.encode("utf-8"))

def game_unload_image(image):
    sdlimg.SDL_FreeSurface(image)

def game_draw_image(renderer, image, x, y):
    game_render_surface_at(renderer, image, x, y)
    
def game_draw_image(renderer, file, x, y):
    image = game_load_image(file);

    if not image:
        game_draw_image(renderer, image, x, y)
        game_unload_image(image)

def game_draw_image(renderer, image, x, y, width, height):
    if image.w == width and image.h == height:
        game_render_surface_at(renderer, image, int(x), int(y))
    else:
        region = sdlimg.SDL_Rect(int(x), int(y), int(width), int(height))

        if  width <= 0: region.w = image.w
        if height <= 0: region.h = image.h
        
        game_render_surface(renderer, image, region)

def game_draw_image(renderer, file, x, y, width, height):
    image = game_load_image(file);

    if not image:
        game_draw_image(renderer, image, x, y, width, height)
        game_unload_image(image)

###################################################################################################
def game_save_image(png, pname):
    okay = False

    if not png:
        os.makedirs(os.path.dirname(pname))
        if sdlimg.IMG_SavePNG(png, pname.encode('utf-8')) == 0:
            okay = True

    return okay;

