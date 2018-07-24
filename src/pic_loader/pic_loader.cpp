#include "pic_loader.hpp"
#include "../snail/application.hpp"
#include "../snail/image.hpp"
#include "../elona.hpp"
#include "../hcl.hpp"

namespace elona
{

namespace
{

std::unordered_map<std::string, pic_loader::page_index> page_index_table = {
    {"character.bmp", 0},
};

} // namespace

void pic_loader::clear()
{
    for (const auto& pair : buffers)
    {
        page_index index = pair.first;
        size_t buffer_count = pair.second.size();
        size_t start_buffer = 10 + index * 2;

        for (size_t i = start_buffer; i < start_buffer + buffer_count; i++)
        {
            buffer(i, 1, 1);
        }
    }

    buffers.clear();
    storage.clear();
}

void pic_loader::load(const fs::path& image_file,
                      const id_type& id,
                      page_index page)
{
    snail::basic_image img{image_file};
    extent ext{0, 0, 0, 0};

    auto& infos = buffers.at(page);

    size_t i = 0;
    while (true)
    {
        buffer_info& info = infos.at(i);
        if (auto pair = info.find(img.width(), img.height()))
        {
            size_t skyline_index = pair->first;
            ext = pair->second;
            ext.buffer = 10 + page * 2 + i;

            info.split(skyline_index, ext);
            info.merge_all();

            break;
        }
        i += 1;
        assert(i < 5);

        if (i == buffers.size())
        {
            add_buffer(page);
        }
    }

    gsel(ext.buffer);
    pos(ext.x, ext.y);
    const auto save = snail::application::instance().get_renderer().blend_mode();
    snail::application::instance().get_renderer().set_blend_mode(snail::blend_mode_t::none);
    snail::application::instance().get_renderer().render_image_crop(
        img, 0, 0, ext.x, ext.y);
    snail::application::instance().get_renderer().set_blend_mode(save);

    storage[id] = ext;
}

// void pic_loader::load_predefined_extents(const fs::path& hcl_file)
// {
//     const auto& value = hclutil::load(hcl_file);
//     if (!value.is<hcl::Object>() || !value.has("images"))
//     {
//         throw std::runtime_error{"\"images\" object not found"};
//     }

//     std::unordered_map<fs::path, map_type> extents;

//     for (const auto& pair : value.get<hcl::Object>("images"))
//     {
//         const auto& source = pair.second.get<std::string>("source");
//         auto& images = extents[source];

//         images[pair.first] = {
//             pair.second.get<int>("x"),
//             pair.second.get<int>("y"),
//             pair.second.get<int>("width"),
//             pair.second.get<int>("height"),
//         };
//     }

//     for (const auto& pair : extents)
//     {
//         add_predefined_extents(pair.first, pair.second, page_index_table(pair));
//     }
// }

void pic_loader::add_predefined_extents(const fs::path& atlas_file,
                                        const map_type& extents,
                                        page_index index)
{
    snail::basic_image img{atlas_file};
    int buffer = 10 + index * 2 + buffers.at(index).size();

    add_buffer(index, img.width(), img.height());
    gsel(buffer);

    buffer_info& info = buffers.at(index)[buffer];
    const auto save = snail::application::instance().get_renderer().blend_mode();
    snail::application::instance().get_renderer().set_blend_mode(snail::blend_mode_t::none);

    for (auto& pair : extents)
    {
        const extent& source = pair.second;

        assert(source.right() < img.width());
        assert(source.bottom() < img.height());

        auto found = info.find(img.width(), img.height());
        assert(found);

        size_t skyline_index = found->first;
        extent& ext = found->second;
        ext.buffer = buffer;

        info.split(skyline_index, ext);
        info.merge_all();

        snail::application::instance().get_renderer().render_image_crop(
            img, source.x, source.y, ext.x, ext.y);

        storage[pair.first] = ext;
    }

    snail::application::instance().get_renderer().set_blend_mode(save);
}

void pic_loader::add_buffer(page_index index, int w, int h)
{
    int new_buffer_index;
    size_t current_buffer_count = 0;

    const auto itr = buffers.find(index);

    if (itr == buffers.end())
    {
        buffers.emplace(index, std::vector<buffer_info>());
    }
    else
    {
        current_buffer_count = itr->second.size();
    }

    assert(current_buffer_count < 2);

    new_buffer_index = 10 + index * 2 + current_buffer_count;
    buffers[index].emplace_back(w, h);

    buffer(new_buffer_index, w, h);
}

} // namespace elona
