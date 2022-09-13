#!/usr/bin/env python3

import os            # 操作系统相关函数
import sys           # 系统相关参数和函数
import ctypes        # 外语接口
import atexit        # 用于管理程序退出时执行的函数

import sdl2          # 原始 (C 风格) SDL2 函数
import sdl2.sdlttf   # 原始 (C 风格) SDL2_TTF 函数
import sdl2.sdlimage # 原始 (C 风格) SDL2_Image 函数

import sdl2.ext      # Python 风格的 SDL2 函数

###############################################################################
def Call_With_Error_Message(init, message, GetError):
    if init != 0:
        print(message + GetError().decode('utf-8'))
        os._exit(1)
    
def Call_With_Safe_Exit(init, message, fquit, GetError):
    Call_With_Error_Message(init, message, GetError)
    atexit.register(fquit)

def Call_For_Variable(init, failure, message, GetError):
    if (init == failure):
        print(message + GetError().decode('utf-8'))
        os._exit(1)
        
    return init

def game_initialize(flags, fontsize = 16):
    Call_With_Safe_Exit(sdl2.SDL_Init(flags), "SDL 初始化失败：", sdl2.SDL_Quit, sdl2.SDL_GetError)
    Call_With_Safe_Exit(sdl2.sdlttf.TTF_Init(), "TTF 初始化失败：", sdl2.sdlttf.TTF_Quit, sdl2.sdlttf.TTF_GetError)
    sdl2.sdlimage.IMG_Init(sdl2.sdlimage.IMG_INIT_JPG | sdl2.sdlimage.IMG_INIT_PNG)
    
    maybe_err = sdl2.sdlimage.IMG_GetError()
    if len(maybe_err):
        print("IMG 初始化失败：" + maybe_err)
        os._exit(1)

    atexit.register(sdl2.sdlimage.IMG_Quit)

def game_world_reset(renderer, fgc, bgc, texture = None):
    fc = sdl2.ext.color.RGBA(fgc)
    bc = sdl2.ext.color.RGBA(bgc)

    if texture == None:
        sdl2.SDL_SetRenderTarget(renderer, texture)

    sdl2.SDL_SetRenderDrawColor(renderer, fc.r, fc.g, fc.b, fc.a)
    sdl2.SDL_RenderClear(renderer)
    sdl2.SDL_SetRenderDrawColor(renderer, bc.r, bc.g, bc.b, bc.a)

def game_world_refresh(renderer, texture):
    sdl2.SDL_SetRenderTarget(renderer, None)
    sdl2.SDL_RenderCopy(renderer, texture, None, None)
    sdl2.SDL_RenderPresent(renderer)
    sdl2.SDL_SetRenderTarget(renderer, texture)

###############################################################################
class Universe:
    def __init__(self, title = "Big Bang!", width = 1200, height = 800, fps = 60, fgc = 0xFFFFFFFF, bgc = 0x000000FF):
        ''' 构造函数，在创建对象时自动调用，以设置帧频、窗口标题、前背景色和混色模式 '''
        game_initialize(sdl2.SDL_INIT_VIDEO | sdl2.SDL_INIT_TIMER)
        
        self.window = Call_For_Variable(sdl2.SDL_CreateWindow(title.encode('utf-8'),
            sdl2.SDL_WINDOWPOS_CENTERED, sdl2.SDL_WINDOWPOS_CENTERED, width, height, sdl2.SDL_WINDOW_SHOWN),
            None, "SDL 窗体创建失败：", sdl2.SDL_GetError())

        self.renderer = Call_For_Variable(sdl2.SDL_CreateRenderer(self.window, -1, sdl2.SDL_RENDERER_ACCELERATED),
            None, "SDL 渲染器创建失败：", sdl2.SDL_GetError())

        self.texture = Call_For_Variable(sdl2.SDL_CreateTexture(self.renderer,
            sdl2.SDL_PIXELFORMAT_RGBA8888, sdl2.SDL_TEXTUREACCESS_TARGET, width, height),
            None, "SDL 纹理创建失败：", sdl2.SDL_GetError())

        self.fps = fps
        self.fgc = fgc
        self.bgc = bgc
        game_world_reset(self.renderer, self.fgc, self.bgc, self.texture)

    def __del__(self):
        ''' 析构函数，在对象被销毁时自动调用 '''
        if self.texture:
            sdl2.SDL_DestroyTexture(self.texture)

        if self.renderer:
            sdl2.SDL_DestroyRenderer(self.renderer)

        if self.window:
            sdl2.SDL_DestroyWindow(self.window)


    def construct(self, argv):
        pass

    def big_bang(self):
        quit_time = 0
        width = ctypes.c_int()
        height = ctypes.c_int()
        handled = False

        sdl2.SDL_GetWindowSize(self.window, ctypes.byref(width), ctypes.byref(height))
        game_world_refresh(self.renderer, self.texture)
        
        while (quit_time == 0):
            for e in sdl2.ext.get_events():
                if e.type == sdl2.SDL_QUIT:
                    quit_time = e.quit.timestamp
                    handled = False
        
            if handled:
                game_world_refresh(self.renderer, self.texture)
                handled = False



###############################################################################
# __name__ 是一个特殊变量
# 可用于提示是否从这行代码启动应用程序
# 效果上相当于 C++ 程序的启动器，负责调用 main 函数
if __name__=="__main__":

    # 混沌初开，宇宙诞生
    universe = Universe("The Pong Game", 1200, 800, fgc = 0x00ff00ff, bgc = 0x00ff00ff)

    # 创建游戏世界
    universe.construct(sys.argv)

    # 宇宙大爆炸
    # 开启游戏主循环，直到玩家关闭游戏
    universe.big_bang()

    # Python 心满意足地退出
    # 顺便销毁游戏宇宙，回归虚无
    sys.exit(0)


