#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include "../scene.hpp"
#include <SDL2/SDL_ttf.h>

namespace ch
{
    class menu_scene : public ch::scene
    {
    public:
        menu_scene(SDL_Renderer *renderer);
        ~menu_scene() override;

        ch::scene *handle_event(const SDL_Event &event) override;
        ch::scene *update(
            const std::uint8_t *keys,
            std::uint32_t mouse,
            int mouse_x,
            int mouse_y,
            float delta_time) override;

    private:
        TTF_Font *font;
    };
}

#endif