#pragma once

class Tile;
class WallTile;
class FloorTile;
typedef std::shared_ptr<Tile> TilePtr;
typedef std::shared_ptr<WallTile> WallTilePtr;
typedef std::shared_ptr<FloorTile> FloorTilePtr;

enum class TileType {
    Wall,
    Floor
};


