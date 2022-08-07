#include "game_of_life.hpp"

#include "text.hpp"
#include "random.hpp"
#include "image.hpp"

using namespace WarGrey::STEM;

/*************************************************************************************************/
static const int GRID_SIZE = 16;     // 方格边长

static inline int check_neighbor(int* world[], int nx, int ny, int x, int y) {
    return ((x >=0) && (x < nx)
            && (y >= 0) && (y < ny)
            && (world[x][y] > 0))
        ? 1 : 0;
}

static inline int count_neighbors(int *world[], int nx, int ny, int x, int y) {
    return check_neighbor(world, nx, ny, x - 1, y + 0)  // left
         + check_neighbor(world, nx, ny, x + 1, y + 0)  // right
         + check_neighbor(world, nx, ny, x + 0, y - 1)  // up
         + check_neighbor(world, nx, ny, x + 0, y + 1)  // down
         + check_neighbor(world, nx, ny, x - 1, y - 1)  // left-up
         + check_neighbor(world, nx, ny, x + 1, y + 1)  // right-down
         + check_neighbor(world, nx, ny, x + 1, y - 1)  // right-up
         + check_neighbor(world, nx, ny, x - 1, y + 1); // left-down
}

/*************************************************************************************************/
WarGrey::STEM::GameOfLife::GameOfLife(const char* title, int width, int height)
    : Universe(title, width, height, 8, 0x000000FFU, 0xFFFFFFFFU) {}

WarGrey::STEM::GameOfLife::~GameOfLife() {
    /* 销毁世界 */ {
        for (int i = 0; i < this->stage_height; i++) {
            delete [] this->world[i];
        }

        delete [] this->world;
    }

    delete [] this->shadow;
}

/*************************************************************************************************/
void WarGrey::STEM::GameOfLife::construct(int argc, char* argv[]) {
    int width, height;

    this->fill_window_size(&width, &height);

    this->screen_width = width;
    this->screen_height = height;
    this->stage_width = this->screen_height / GRID_SIZE - 1;
    this->stage_height = this->stage_width;

    // 确保舞台被绘制在屏幕中心
    this->stage_x = (this->screen_width - this->stage_width * GRID_SIZE) / 2;
    this->stage_y = (this->screen_height - this->stage_height * GRID_SIZE) / 2;

    /* 创建世界网格 */ {
        this->shadow = new int[this->stage_width * this->stage_height];
        this->world = new int*[this->stage_height];

        for (int i = 0; i < this->stage_height; i++) {
            this->world[i] = new int[this->stage_width];

            for (int j = 0; j < this->stage_width; j++) {
                this->world[i][j] = 0;
            }
        }
    }

    game_text_size(game_monospace_font, &this->chwidth, &this->lineheight, "x");
    
    this->generation = 0;
    this->switch_game_state(GameState::Run);
}

void WarGrey::STEM::GameOfLife::update(uint32_t interval, uint32_t count, uint32_t uptime) {
    switch (this->state) {
        case GameState::Run: { // 时间飞逝, 生命演化
            if (!this->forward_game_world(1, true)) {
                this->switch_game_state(GameState::Stop);
            }
        }; break;
        default: /* 什么都不做 */ ; break;
    }
}

void WarGrey::STEM::GameOfLife::draw(SDL_Renderer* renderer, int x, int y, int width, int height) {
    // 绘制舞台边界
    game_draw_frame(renderer, this->stage_x, this->stage_y, this->stage_width * GRID_SIZE, this->stage_height * GRID_SIZE);

    // 绘制舞台的网格
    if (!this->hide_grid) {
        game_draw_grid(renderer, this->stage_width, this->stage_height, GRID_SIZE, this->stage_x, this->stage_y);
    }

    // 绘制生命
    game_fill_grid(renderer, this->world, this->stage_width, this->stage_height, GRID_SIZE, this->stage_x, this->stage_y);

    /* 绘制提示信息 */ {
        uint32_t fgcolor = this->get_foreground_color();
        std::string desc_generation = game_create_string("Generation: %d", this->generation);
    
        game_draw_blended_text(game_monospace_font, renderer, fgcolor,
                this->screen_width - this->chwidth * int(desc_generation.size()), 0,
                "%s", desc_generation.c_str());

        this->display_instruction(renderer, "Play",    'p', 0);
        this->display_instruction(renderer, "Stop",    's', 1);
        this->display_instruction(renderer, "Edit",    'e', 2);
        this->display_instruction(renderer, "Random",  'r', 3);
        this->display_instruction(renderer, "Clear",   'c', 4);
        this->display_instruction(renderer, "Forward", 'f', 5);
    
        if (this->last_key_typed != '\0') {
            int rx = this->screen_width - this->chwidth * 2;
            int ry = this->screen_height - this->lineheight;

            game_draw_blended_text(game_monospace_font, renderer, fgcolor, rx, ry, "%c", this->last_key_typed);
        }

        this->display_user_message(renderer, this->user_message);
    }
}

void WarGrey::STEM::GameOfLife::display_game_state(SDL_Renderer* renderer, const std::string &desc_state, uint32_t color) {
    int x = this->screen_width - this->chwidth * (int(desc_state.size()) + 1);

    game_draw_blended_text(game_monospace_font, renderer, color, x, 0, "%s", desc_state.c_str());
}

void WarGrey::STEM::GameOfLife::display_instruction(SDL_Renderer* renderer, const std::string &desc_state, char key, int index) {
    uint32_t color = this->get_foreground_color();
    int y = index * this->lineheight;

    if (key == this->last_key_typed) {
        color = 0x00FF00FF;
    }

    game_draw_blended_text(game_monospace_font, renderer, color, 0, y, "[%c] %s", key, desc_state.c_str());
}

void WarGrey::STEM::GameOfLife::display_user_message(SDL_Renderer* renderer, const std::string &message) {
    if (message.size() > 0) {
        game_draw_shaded_text(game_monospace_font, renderer, 0xFF0000FF, this->get_background_color(),
            0, this->screen_height - this->lineheight,
            "[Error] %s", message.c_str());
    }
}

/*************************************************************************************************/
bool WarGrey::STEM::GameOfLife::on_char(char key, uint16_t modifiers, uint8_t repeats) {
    this->last_key_typed = key;

    switch(key) {
        case 's': this->switch_game_state(GameState::Stop); break;
        case 'p': this->switch_game_state(GameState::Run); break;
        case 'e': this->switch_game_state(GameState::Edit); break;
        case 'r': this->construct_random_game_world(); break;
        case 'c': this->reset_game_world(); break;
        case 'f': this->forward_game_world(repeats, false); break;
    }

    return true;
}

bool WarGrey::STEM::GameOfLife::on_click(int x, int y) {
    if (this->state == GameState::Edit) {
        int sx = x - this->stage_x;
        int sy = y - this->stage_y;
        int mx = this->stage_width * GRID_SIZE;
        int my = this->stage_height * GRID_SIZE;

        if ((sx > 0) && (sx < mx) && (sy > 0) && (sy < my)) {
            int gx = sx / GRID_SIZE;
            int gy = sy / GRID_SIZE;

            if ((gx < this->stage_width) && (gy < this->stage_height)) {
                this->world[gx][gy] = (this->world[gx][gy] == 0) ? 1 : 0;
            }
        }
    }

    return true;
}

/*************************************************************************************************/
void WarGrey::STEM::GameOfLife::construct_random_game_world() {
    if (this->state == GameState::Edit) {
        for (int i = 0; i < this->stage_height; i++) {
            for (int j = 0; j < this->stage_width; j++) {
                this->world[i][j] = ((random_raw() % 2 == 0) ? 1 : 0);
            }
        }

        this->last_key_typed = 'e';
    } else {
        this->user_message = "Please enter the 'Edit' mode first!";
        this->last_key_typed = '\0';
    }
}

void WarGrey::STEM::GameOfLife::reset_game_world() {
    if (this->state == GameState::Edit) {
        for (int i = 0; i < this->stage_height; i++) {
            for (int j = 0; j < this->stage_width; j++) {
                this->world[i][j] = 0;
            }
        }

        this->generation = 0;
    } else {
        this->user_message = "Please enter the 'Edit' mode first!";
        this->last_key_typed = '\0';
    }
}

bool WarGrey::STEM::GameOfLife::forward_game_world(int repeats, bool force) {
    bool evolved = false;

    if (force || (this->state != GameState::Run)) {
        // 应用演化规则
        this->evolve(this->world, this->shadow, this->stage_width, this->stage_height);

        // 同步舞台状态
        for (int x = 0; x < this->stage_height; x++) {
            for (int y = 0; y < this->stage_width; y++) {
                int state = this->shadow[x * this->stage_width + y];

                if (this->world[x][y] != state) {
                    this->world[x][y] = state;
                    evolved = true;
                }
            }
        }
    }

    if (evolved) {
        this->generation ++;
    }

    return evolved;
}

void WarGrey::STEM::GameOfLife::switch_game_state(GameState new_state) {
    if (this->state != new_state) {
        switch (new_state) {
        case GameState::Run: {
            this->state = new_state;
            this->hide_grid = true;
            this->last_key_typed = 'p';
            this->user_message = "";
        }; break;
        case GameState::Stop: {
            if (this->state == GameState::Run) { 
                this->state = new_state;
                this->last_key_typed = 's';
            }
        }; break;
        case GameState::Edit: {
            if (this->state == GameState::Stop) {
                this->state = new_state;
                this->hide_grid = false;
                this->last_key_typed = 'e';
                this->user_message = "";
            } else {
                this->user_message = "Please stop the game first!";
            }
        }; break;
        default: /* 什么都不做 */; break;
        }
    }
}

/*************************************************************************************************/
WarGrey::STEM::ConwayLife::ConwayLife(int width, int height) : GameOfLife("Conway's Game of Life", width, height) {}

void WarGrey::STEM::ConwayLife::evolve(int** world, int* shadow, int stage_width, int stage_height) {
    for (int x = 0; x < stage_height; x++) {
        for (int y = 0; y < stage_width; y++) {
            int n = count_neighbors(world, stage_width, stage_height, x, y);
            int i = x * stage_width + y;

            if (n < 2) {            // 死亡(离群索居)
                shadow[i] = 0;
            } else if (n > 3) {     // 死亡(过度竞争)
                shadow[i] = 0;
            } else if (n == 3) {    // 无性繁殖
                shadow[i] = 1;
            } else {                // 安居乐业
                shadow[i] = world[x][y];
            }
        }
    }
}

/*************************************************************************************************/
WarGrey::STEM::HighLife::HighLife(int width, int height) : GameOfLife("High Life", width, height) {}

void WarGrey::STEM::HighLife::evolve(int** world, int* shadow, int stage_width, int stage_height) {
    for (int x = 0; x < stage_height; x++) {
        for (int y = 0; y < stage_width; y++) {
            int n = count_neighbors(world, stage_width, stage_height, x, y);
            int i = x * stage_width + y;

            switch (n) {
            case 3: case 6: shadow[i] = 1; break;
            case 2: shadow[i] = world[x][y]; break;
            default: shadow[i] = 0;
            }
        }
    }
}

