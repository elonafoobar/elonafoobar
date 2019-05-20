"""
Elona Foobar map importer/exporter.
"""

from pprint import pprint
import sys
import re
import tiled as T
import os
from os.path import dirname, splitext, basename, exists, join, realpath
from lib import cpystruct
from struct import pack, unpack
from collections import namedtuple
from math import floor
import gzip


def represents_int(s):
    try:
        int(s)
        return True
    except ValueError:
        return False


def represents_bool(s):
    try:
        bool(s)
        return True
    except ValueError:
        return False


def read_typed_value(fh):
    ty = unpack("b", fh.read(1))[0]
    if ty == 0:
        val = unpack("I", fh.read(4))[0]
    elif ty == 1:
        val = unpack("b", fh.read(1))[0] == 1
    elif ty == 2:
        val = read_string(fh)
    else:
        raise Exception("unknown typed value " + str(ty))
    return val


def write_typed_value(out, prop, prop_type):
    if prop_type == "int":
        out.write(pack("b", 0))
        out.write(pack("I", int(prop)))
    elif prop_type == "bool":
        out.write(pack("b", 1))
        out.write(pack("b", bool(prop)))
    else:
        out.write(pack("b", 2))
        write_string(out, prop)


def read_string(fh):
    return "".join(iter(lambda: fh.read(1).decode("ascii"), "\x00"))


def write_string(out, s):
    out.write(str.encode(s))
    out.write(b"\0")


def load_tileset(m, filename):
    print("load " + filename)
    if not exists(filename):
        raise Exception("cannot find tileset file " + filename)
    tileset = T.loadTileset(filename)
    if tileset == None:
        raise Exception("failed to load " + filename)
    m.addTileset(tileset)


def load_tilesets(m, atlas, directory):
    tileset_directory = join(directory, "Elona_foobar")

    tile_atlas = join(tileset_directory, "map%01i.tsx" % atlas)
    load_tileset(m, tile_atlas)

    for filename in os.listdir(tileset_directory):
        if filename == "map0.tsx" or filename == "map1.tsx" or filename == "map2.tsx":
            continue
        if filename.endswith(".tsx"):
            print("load " + filename)
            atlas = join(tileset_directory, filename)
            load_tileset(m, atlas)


class ElonaFoobar(T.Plugin):
    @classmethod
    def shortName(cls):
        return "fmp"

    @classmethod
    def nameFilter(cls):
        return "Elona Foobar (*.fmp)"

    @classmethod
    def supportsFile(cls, f):
        with gzip.open(f, "rb") as fh:
            return fh.read(4) == b"FMP "

    @classmethod
    def init_map(cls, foo, m):
        for k, v in foo.mdata.items():
            m.setProperty(k, v)

        base_directory = dirname(realpath(__file__))
        load_tilesets(m, foo.mdata["atlas"], base_directory)

        tile_layer = T.Tiled.TileLayer(
            "Tiles", 0, 0, foo.width, foo.height)

        load_tiles(m, tile_layer, foo.tiles)
        m.addLayer(tile_layer)

        for layer in foo.layers:
            if layer["kind"] == 0:  # tile layer
                pass
            elif layer["kind"] == 1:  # object group
                new_layer = T.Tiled.ObjectGroup(layer["name"], 0, 0)
                load_objects(m, new_layer, layer["objs"])
                m.addLayer(new_layer)
            elif layer["kind"] == 2:  # group layer
                new_layer = T.Tiled.GroupLayer(layer["name"], 0, 0)
                m.addLayer(new_layer)
            elif layer["kind"] == 3:  # image layer
                pass

    @classmethod
    def read(cls, f):
        # Read map binary data.
        foo = ElonaFoobar(f)

        # Instantiate Tiled map from binary data.
        m = T.Tiled.Map(T.Tiled.Map.Orthogonal, foo.width, foo.height, 48, 48)

        # Load layers and properties into Tiled.
        ElonaFoobar.init_map(foo, m)

        return m

    def __init__(self, f):
        if isinstance(f, dict):
            self.version = 1

            self.mods = set()

            self.mdata = f

            self.width = self.mdata["width"]
            self.height = self.mdata["height"]

            self.tiles = [
                "core." + str(self.mdata["atlas"]) + "_0"] * self.width * self.height

            self.layers = list()

            return

        self.mdata = dict()
        with gzip.open(f, "rb") as fh:
            fh.read(4)

            self.version = unpack("I", fh.read(4))[0]

            mod_count = unpack("I", fh.read(4))[0]
            print("mod count " + str(mod_count))
            self.mods = set()
            for i in range(mod_count):
                self.mods.add(read_string(fh))

            ids_to_names = read_dict(fh)

            self.mdata = read_properties(fh, ids_to_names)

            self.width, self.height = unpack("II", fh.read(2 * 4))

            self.tiles = read_tiles(fh, self.width, self.height, ids_to_names)

            self.layers = list()
            layer_count = unpack("I", fh.read(4))[0]

            for i in range(layer_count):
                self.layers.append(read_layer(fh, ids_to_names))

    @classmethod
    def tile_layer_is_used(cls, tiles):
        for y in range(tiles.height()):
            for x in range(tiles.width()):
                tile = tiles.cellAt(x, y).tile()
                if tile != None:
                    return True
        return False

    @classmethod
    def validate(cls, m):
        map_atlas = m.propertyAsString("atlas")

        tile_layer_count = 0
        for i in range(m.layerCount()):
            l = m.layerAt(i)

            if l.isTileLayer():
                tiles = l.asTileLayer()
                if ElonaFoobar.tile_layer_is_used(tiles):
                    tile_layer_count += 1

        if tile_layer_count != 1:
            raise Exception(
                "There must be exactly 1 non-empty tile layer used, but there were '{}' found.".format(tile_layer_count))

        for i in range(m.layerCount()):
            l = m.layerAt(i)

            if l.isTileLayer():
                tiles = l.asTileLayer()
                for y in range(tiles.height()):
                    for x in range(tiles.width()):
                        tile = tiles.cellAt(x, y).tile()

                        if tile == None:
                            continue
                        if tile.type() != "core.map_chip":
                            raise Exception(
                                "The tile at ({},{}) does not come from the core.map_chip atlas, but is from '{}'. (Did you insert a character/item tile by accident?".format(x / 48, y / 48, tile.type()))
                        tile_atlas = tile.propertyAsString("atlas")
                        if tile_atlas != map_atlas:
                            raise Exception(
                                "The tile at ({},{}) is from atlas '{}', but this map's atlas is '{}'.".format(
                                    x / 48, y / 48, tile_atlas, map_atlas))
            elif l.isObjectGroup():
                objs = l.asObjectGroup()

                for i in range(objs.objectCount()):
                    obj = objs.objectAt(i)

                    if obj.effectiveType() == "core.map_chip":
                        raise Exception(
                            "The object at ({},{}) is of type core.map_chip. (Did you insert a map tile as an object by accident?".format(obj.x() / 48, obj.y() / 48))
        return True

    @classmethod
    def write(cls, m, filename):
        m.setInfinite(False)
        m.setOrientation(T.Tiled.Map.Orthogonal)
        m.setRenderOrder(T.Tiled.Map.RightDown)

        is_new_map = m.tilesetCount() == 0
        if is_new_map:
            mdata = {
                "width": m.width(),
                "height": m.height(),
                "atlas": 1,
                "next_regenerate_date": 0,
                "stair_up_pos": 0,
                "stair_down_pos": 0,
                "bgm": "",
                "max_item_count": 0,
                "should_regenerate": True,
                "max_crowd_density": m.width() * m.height() / 100
            }
            foo = ElonaFoobar(mdata)
            ElonaFoobar.init_map(foo, m)

        if not ElonaFoobar.validate(m):
            return False

        with gzip.open(splitext(filename)[0] + ".fmp", "wb") as out:
            out.write(pack("4s", b"FMP "))

            # Map version.
            version = 1
            out.write(pack("I", version))

            # Mod name/version.
            mods = collect_mods_used(m)
            out.write(pack("I", len(mods)))
            for mod in mods:
                write_string(out, mod)

            # Int -> String.
            property_names = collect_property_names(m)
            write_dict(out, property_names)

            write_properties(out, m, property_names)

            out.write(pack("II", m.width(), m.height()))

            write_tiles(out, m, property_names)

            out.write(pack("I", m.layerCount()))

            for i in range(m.layerCount()):
                l = m.layerAt(i)
                write_layer(out, m, l, i, property_names)

        return True


def collect_mods_used(m):
    mods = set()

    base_directory = dirname(realpath(__file__))
    mods_file = join(base_directory, "Elona_foobar/mods.txt")
    with open(mods_file, "r") as fh:
        for mod in fh:
            mods.add(mod)

    return mods


class Mapping():
    def __init__(self):
        self.i = 0
        self.names_to_ids = dict()

    def add(self, key):
        if not key in self.names_to_ids:
            self.names_to_ids[key] = self.i
            self.i += 1


def collect_property_names(m):
    mapping = Mapping()
    default_tile = get_default_tile(m)

    # map
    for key in m.properties().keys():
        mapping.add(key)

    # layers
    for i in range(m.layerCount()):
        l = m.layerAt(i)

        # tiles
        if l.isTileLayer():
            mdata = l.asTileLayer()
            for y in range(mdata.height()):
                for x in range(mdata.width()):
                    # tile property names
                    cell = mdata.cellAt(x, y)
                    tile = cell.tile()
                    if tile == None:
                        continue
                    mapping.add(tile.propertyAsString("data_id"))
                    for key in tile.properties().keys():
                        mapping.add(key)

        # objects
        elif l.isObjectGroup():
            objs = l.asObjectGroup()
            for i in range(objs.objectCount()):
                o = objs.objectAt(i)

                mapping.add(o.name())
                mapping.add(o.effectiveType())

                for key in o.properties().keys():
                    mapping.add(key)

                mapping.add(o.cell().tile().propertyAsString("data_id"))

                for key in o.cell().tile().properties().keys():
                    mapping.add(key)

        for key in l.properties().keys():
            mapping.add(key)

    return mapping.names_to_ids


def read_dict(fh):
    ids_to_names = dict()
    key_count = unpack("I", fh.read(4))[0]
    for i in range(key_count):
        key = read_string(fh)
        value = unpack("I", fh.read(4))[0]
        ids_to_names[value] = key

    return ids_to_names


def write_dict(out, d):
    out.write(pack("I", len(d.keys())))
    for key in d.keys():
        write_string(out, key)
        assert(isinstance(d[key], int))
        out.write(pack("I", d[key]))


def read_properties(fh, ids_to_names):
    props = dict()
    key_count = unpack("I", fh.read(4))[0]

    for i in range(key_count):
        key_id = unpack("I", fh.read(4))[0]
        key = ids_to_names[key_id]
        val = read_typed_value(fh)
        props[key] = val

    return props


def write_properties(out, m, names_to_ids):
    out.write(pack("I", len(list(m.properties().keys()))))
    for key in m.properties().keys():
        out.write(pack("I", names_to_ids[key]))

        prop = m.propertyAsString(key)
        prop_type = m.propertyType(key)
        write_typed_value(out, prop, prop_type)


def get_default_tile(m):
    default_id = "core." + m.propertyAsString("atlas") + "_0"
    default_tile = find_map_tile_across_all_tilesets(
        m, default_id)
    if default_tile == None:
        raise Exception("Could not find default tile '{}'".format(default_id))
    return default_tile


def read_tiles(fh, width, height, ids_to_names):
    raw_tiles = list(
        unpack("I" * (width * height), fh.read(width * height * 4)))
    return list(map(lambda tile_id: ids_to_names[tile_id], raw_tiles))


def write_tiles(out, m, names_to_ids):
    for i in range(m.layerCount()):
        if T.isTileLayerAt(m, i):
            mdata = T.tileLayerAt(m, i)

            for y in range(mdata.height()):
                for x in range(mdata.width()):
                    cell = mdata.cellAt(x, y)
                    tile = cell.tile()
                    if tile == None:
                        data_id = "core." + m.propertyAsString("atlas") + "_0"
                    else:
                        data_id = tile.propertyAsString("data_id")
                    out.write(pack("I", names_to_ids[data_id]))

            # Only write the first tile layer found. The format
            # assumes that only (width * height) tiles are written,
            # and having more than one layer will cause an error on
            # load.
            break


def write_layer(out, m, layer, layer_id, names_to_ids):
    if layer.isTileLayer():
        kind = 0
    elif layer.isObjectGroup():
        kind = 1
    elif layer.isGroupLayer():
        kind = 2
    elif layer.isImageLayer():
        kind = 3

    out.write(pack("II", layer_id, kind))
    write_string(out, layer.name())
    write_properties(out, layer, names_to_ids)

    if layer.isTileLayer():
        pass
    elif layer.isObjectGroup():
        objs = layer.asObjectGroup()
        out.write(pack("I", objs.objectCount()))
        for i in range(objs.objectCount()):
            o = objs.objectAt(i)
            write_object(out, o, names_to_ids)
    elif layer.isGroupLayer():
        group = layer.asGroupLayer()
        out.write(pack("I", group.layerCount()))
        for i in range(group.layerCount()):
            found = False
            for j in range(m.layerCount()):
                if m.layerAt(j) == group.layerAt(i):
                    out.write(pack("I", j))
                    found = True
                    break
            assert(found)
    elif layer.isImageLayer():
        pass
    else:
        raise Exception("unknown layer kind")


def read_layer(fh, ids_to_names):
    layer_id, kind = unpack("II", fh.read(2 * 4))
    name = read_string(fh)
    props = read_properties(fh, ids_to_names)
    objs = list()
    group = list()

    if kind == 0:
        # tile layer
        pass
    elif kind == 1:
        # object group
        obj_count = unpack("I", fh.read(4))[0]
        for i in range(obj_count):
            o = read_object(fh, ids_to_names)
            objs.append(o)
    elif kind == 2:
        # group layer
        layer_count = unpack("I", fh.read(4))[0]
        for i in range(layer_count):
            group.add(unpack("I", fh.read(4))[0])
    elif kind == 3:
        # image layer
        pass
    else:
        raise Exception("unknown layer kind " + str(kind))

    return {
        "id": layer_id,
        "kind": kind,
        "name": name,
        "props": props,
        "objs": objs,
        "group": group,
    }


def read_object(fh, ids_to_names):
    data_id_id, data_type_id, name_id, x, y = unpack("IIIII", fh.read(4 * 5))
    data_id = ids_to_names[data_id_id]
    data_type = ids_to_names[data_type_id]
    name = ids_to_names[name_id]
    props = read_properties(fh, ids_to_names)
    tile_props = read_properties(fh, ids_to_names)

    return {
        "data_id": data_id,
        "data_type": data_type,
        "name": name,
        "x": x,
        "y": y,
        "props": props,
        "tile_props": tile_props,
    }


def write_object(out, obj, names_to_ids):
    tile = obj.cell().tile()
    data_id = tile.propertyAsString("data_id")
    data_type = obj.effectiveType()
    name = obj.name()
    x = floor(obj.x() / 48.0)
    y = floor(obj.y() / 48.0) - 1
    # if obj.height() == 96:
    #     y += 1

    out.write(pack("IIIII", names_to_ids[data_id],
                   names_to_ids[data_type], names_to_ids[name], x, y))

    write_properties(out, obj, names_to_ids)

    # The properties of the object need to be combined with the
    # implicit properties of the tile.
    write_properties(out, obj.cell().tile(), names_to_ids)


def find_tileset(m, data_type):
    for i in range(m.tilesetCount()):
        ts = m.tilesetAt(i).data()
        if ts.name() == data_type:
            return ts
    return None


def find_object_tile(tileset, data_id, cache, tile_prop=""):
    if data_id in cache:
        return tileset.tileAt(cache[data_id])
    for i in range(tileset.tileCount()):
        tile = tileset.tileAt(i)
        found_data = tile.propertyAsString("data_id") == data_id
        found_tile = True
        if tile_prop != "" and tile.propertyAsString("tile") != tile_prop:
            found_tile = False
        if found_data and found_tile:
            if tile_prop == "":
                cache[data_id] = tile.id()
            return tile
    return None


def find_map_tile_across_all_tilesets(m, data_id):
    cache = dict()
    for i in range(m.tilesetCount()):
        ts = m.tilesetAt(i).data()
        if ts.name() == "core.map_chip":
            tile = find_object_tile(ts, data_id, cache)
            if tile != None:
                return tile
    return None


def load_tiles(m, tile_layer, tiles):
    cache = dict()
    tileset = find_tileset(m, "core.map_chip")
    if tileset == None:
        raise Exception("No tileset loaded that has core.map_chip")

    for y in range(m.height()):
        for x in range(m.width()):
            data_id = tiles[y * m.width() + x]
            tile = find_object_tile(tileset, data_id, cache)
            if tile == None:
                raise Exception("Could not find tile " + data_id)
            tile_layer.setCell(x, y, T.Tiled.Cell(tile))


def load_objects(m, object_group, d):
    cache = dict()
    tileset_cache = dict()

    for obj in d:
        data_type = obj["data_type"]
        if data_type in tileset_cache:
            tileset = tileset_cache[data_type]
        else:
            tileset = find_tileset(m, data_type)
            tileset_cache[data_type] = tileset
        if tileset == None:
            raise Exception("No tileset loaded that has " + data_type)
        data_id = obj["data_id"]
        name = obj["name"]
        tile_prop = ""
        if "tile" in obj["props"]:
            tile_prop = obj["props"]["tile"]
        elif "tile" in obj["tile_props"]:
            tile_prop = obj["tile_props"]["tile"]
        tile = find_object_tile(tileset, data_id, cache, tile_prop)
        if tile == None:
            raise Exception("No tileset loaded that has " +
                            data_type + "#" + data_id)

        x = obj["x"]
        y = obj["y"] + 1
        width = tile.width()
        height = tile.height()
        # if height == 96:
        #     y -= 1

        map_object = T.Tiled.MapObject(name, data_type, T.qt.QPointF(
            x * 48, y * 48), T.qt.QSizeF(width, height))
        for k, v in obj["props"].items():
            map_object.setProperty(k, v)
        # TODO
        # map_object.setProperty("id", obj.id)
        map_object.setType(data_type)
        map_object.setCell(T.Tiled.Cell(tile))
        object_group.addObject(map_object)
