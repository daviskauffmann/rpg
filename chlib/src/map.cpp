#include <ch/map.hpp>

#include <algorithm>
#include <ch/tileset.hpp>
#include <ch/world.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

ch::map::map(const std::string &filename, ch::world &world)
    : filename(filename)
{
    spdlog::info("Loading map {}", filename);

    const auto map_json = nlohmann::json::parse(std::ifstream(filename));

    width = map_json.at("width");
    height = map_json.at("height");
    tile_width = map_json.at("tilewidth");
    tile_height = map_json.at("tileheight");

    for (const auto &layer_json : map_json.at("layers"))
    {
        layers.push_back({layer_json});
    }

    std::size_t index = 0;
    for (const auto &tileset_json : map_json.at("tilesets"))
    {
        tilesets.push_back({tileset_json, index++, world});
    }

    b2_world = std::make_unique<b2World>(b2Vec2(0.0f, 0.0f));

    for (std::size_t y = 0; y < height; ++y)
    {
        for (std::size_t x = 0; x < width; ++x)
        {
            if (is_solid(x, y))
            {
                b2BodyDef body_def;
                body_def.type = b2_staticBody;
                body_def.position.Set(
                    static_cast<float>(x * tile_width),
                    static_cast<float>(y * tile_height));

                b2PolygonShape shape;
                shape.SetAsBox(tile_width / 2.0f, tile_height / 2.0f);

                auto body = b2_world->CreateBody(&body_def);
                body->CreateFixture(&shape, 0.0f);
            }
        }
    }
}

const ch::map_tileset &ch::map::get_tileset(const size_t gid) const
{
    return *std::max_element(
        tilesets.begin(),
        tilesets.end(),
        [gid](const auto &a, const auto &b)
        {
            return a.first_gid < b.first_gid && b.first_gid <= gid;
        });
}

bool ch::map::is_solid(const std::size_t x, const std::size_t y) const
{
    const auto layer = std::find_if(
        layers.begin(),
        layers.end(),
        [this, x, y](const auto &layer)
        {
            const auto tile = layer.get_tile(x, y);
            return tile && get_tileset(tile->gid).get_tile(tile->gid).solid;
        });
    return layer != layers.end();
}

void ch::map::update(const float delta_time)
{
    b2_world->Step(delta_time, 8, 3);
}
