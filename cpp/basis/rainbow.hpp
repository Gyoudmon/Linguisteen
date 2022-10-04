#ifndef _RAINBOW_H // 确保只被 include 一次
#define _RAINBOW_H

#include "game.hpp"

namespace WarGrey::STEM {
    class ColorWheel : public WarGrey::STEM::DrawingBoard {
        public:
            ColorWheel(float r = 256.0f, int blength = 32);
        
        public:
            void draw(SDL_Renderer* renderer, int x, int y, int width, int height);

        private:
            float radius;
            int block_length;
    };
    
    class Rainbow : public WarGrey::STEM::DrawingBoard {
        public:
            Rainbow(float r = 128.0f, float dh = 1.0f, float ds = 0.1f);
        
        public:
            void draw(SDL_Renderer* renderer, int x, int y, int width, int height);

        private:
            float radius;
        
        private:
            float hue_delta;
            float sample_delta;
    };
}

#endif
