#include <plteen/game.hpp>

namespace Linguisteen {
    class TheCosmos : public Plteen::Cosmos {
    public:
        TheCosmos(int fps) : Plteen::Cosmos(fps) {}
        virtual ~TheCosmos();

    public:  // 覆盖游戏基本方法
        void construct(int argc, char* argv[]) override;
        bool can_exit() override;

    protected:
        void update(uint64_t count, uint32_t interval, uint64_t uptime) override;

    protected:
        virtual void parse_cmdline_options(int argc, char* argv[]) {}

    private:
        Plteen::IPlane* splash;
    };
}
