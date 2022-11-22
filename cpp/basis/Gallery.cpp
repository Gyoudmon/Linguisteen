#include "digitama/world.hpp"

#include "digitama/graphlet/shapelet.hpp"
#include "digitama/graphlet/ui/textlet.hpp"

using namespace WarGrey::STEM;

/*************************************************************************************************/
namespace {
    class Gallery : public World {
        public:
            Gallery() : World("The Gallery of Sprites and Graphlets") {}

        public:
            void load(float width, float height) override {
                this->label = this->insert(new Labellet(game_font::unicode, 0U, "精灵和图元陈列馆"));

                // 三角形的三条边
                this->lines[0] = this->insert(new Linelet(-200, +200, RED));
                this->lines[1] = this->insert(new Linelet(+400, +000, GREEN));
                this->lines[2] = this->insert(new Linelet(+200, +200, BLUE));

                this->rectangle = this->insert(new Rectanglet(200, 100, YELLOWGREEN, ORANGE));  // 橘边黄绿色长方形
                this->circle = this->insert(new Circlet(50, PINK, PURPLE));                     // 紫边粉红色圆
                this->ellipse = this->insert(new Ellipselet(64, 32, KHAKI, SKYBLUE));           // 天蓝色边卡其色椭圆
    
                for (int n = 1; n <= sizeof(this->regular_polygons) / sizeof(IShapelet*); n++) {
                    this->regular_polygons[n - 1] = this->insert(new RegularPolygonlet(n, 32, -90.0, ROYALBLUE, FIREBRICK));
                }
            }

            void reflow(float width, float height) override {
                // 排列线段以组成三角形
                this->move_to(this->lines[0], 200, 400, MatterAnchor::LB); // 左下角对齐
                this->move_to(this->lines[1], 200, 400, MatterAnchor::LT); // 左上角对齐
                this->move_to(this->lines[2], 600, 400, MatterAnchor::RB); // 右下角对齐

                // 排列长方形和椭圆
                this->move_to(this->rectangle, 800, 100, MatterAnchor::LT);
                this->move_to(this->circle, 900, 400, MatterAnchor::CC);
                this->move_to(this->ellipse, 900, 600, MatterAnchor::CC);

                // 排列正多边形
                for (int i = 0; i < sizeof(this->regular_polygons) / sizeof(IShapelet*); i++) {
                    this->move_to(this->regular_polygons[i], 100 * i, 750, MatterAnchor::CC);
                }
            }

        public:
            bool can_select(WarGrey::STEM::IMatter* g) override {
                return true;
            }

        private: // 本游戏世界中的有以下物体
            WarGrey::STEM::Labellet* label;
            WarGrey::STEM::IShapelet* lines[3];
            WarGrey::STEM::IShapelet* rectangle;
            WarGrey::STEM::IShapelet* circle;
            WarGrey::STEM::IShapelet* ellipse;
            WarGrey::STEM::IShapelet* regular_polygons[10];
    };
}

/*************************************************************************************************/
int main(int argc, char* args[]) {
    Gallery universe;

    universe.construct(argc, args);
    universe.big_bang();

    return 0;
}

