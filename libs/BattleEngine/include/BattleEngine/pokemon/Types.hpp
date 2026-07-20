#pragma once

#include <cstdint>
#include <nlohmann/json.hpp>

namespace pokegym::engine::pokemon {

enum class Type : uint8_t {
    Fire,
    Water,
    Grass,
    Normal,

    Count
};

NLOHMANN_JSON_SERIALIZE_ENUM(Type, {
                                       {Type::Fire, "Fire"},
                                       {Type::Water, "Water"},
                                       {Type::Grass, "Grass"},
                                       {Type::Normal, "Normal"},
                                   })

}  // namespace pokegym::engine::pokemon
