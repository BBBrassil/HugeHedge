| World                              |
| ---------------------------------- |
|                                    |
| - fileName : string                |
| - tiles : Tile**                   |
| - defaultTile : Tile*              |
| - rowCount : int                   |
| - colCount : int                   |
| - tileCount : int                  |
|                                    |
| + World(string s)                  |
| + ~World()                         |
| - setDimensions()                  |
| + readTileData()                   |
| + makeTileMap()                    |
| - clear()                          |
| + height() : int                   |
| + width() : int                    |
| + size() : int                     |
| + xyToIndex(int x, int y) : int    |
| + indexToX(int index) : int        |
| + getDefaultTile() : Tile&         |
| + tile(int index) : Tile&          |
| + tile(int x, int y) : Tile&       |
| + operator[](int index) : Tile&    |
| + operator()(int index) : Tile&    |
| + operator()(int x, int y) : Tile& |

| BadDimensions             |
| ------------------------- |
|                           |
| - fileName : string       |
|                           |
| + BadDimensions(string s) |
| + getFileName : string    |

| OutOfWorld               |
| ------------------------ |
|                          |
| - position : Position    |
|                          |
| + getPosition : Position |