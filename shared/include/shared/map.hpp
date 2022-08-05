#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>

namespace hp
{
    class world;
    class tileset;
    struct tile_data;

    struct tile
    {
        std::size_t gid;
        bool h_flip;
        bool v_flip;
        bool d_flip;
    };

    struct layer
    {
        std::size_t width;
        std::size_t height;
        std::vector<hp::tile> tiles;

        const hp::tile *get_tile(std::size_t x, std::size_t y) const;
    };

    struct map_tileset
    {
        std::size_t index;

        std::size_t first_gid;
        hp::tileset *tileset;

        const hp::tile_data &get_tile_data(std::size_t gid) const;
    };

    class map
    {
    public:
        std::string filename;

        std::size_t width;
        std::size_t height;
        std::size_t tile_width;
        std::size_t tile_height;
        std::vector<hp::layer> layers;
        std::vector<hp::map_tileset> map_tilesets;

        map(const std::string &filename, hp::world &world);

        void update(float delta_time);

        const hp::map_tileset &get_map_tileset(std::size_t gid) const;

        bool is_solid(std::size_t x, std::size_t y) const;
    };
};

#endif
