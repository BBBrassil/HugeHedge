| World                               |
| ----------------------------------- |
|                                     |
| - fileName : string                 |
| - tiles : Tile**                    |
| - defaultTile : Tile*               |
| - exit : Tile*                      |
| - keyLocations : vector<int>        |
| - spareLocations : vector<int>      |
| - worldMap : Map*                   |
| - mapItem : Item*                   |
| - rowCount : int                    |
| - colCount : int                    |
| - tileCount : int                   |
| - gameOver : bool                   |
|                                     |
| + World(s : string)                 |
| + ~World()                          |
| - setDimensions()                   |
| + makeTileMap()                     |
| + readTileData()                    |
| + placeItems()                      |
| - clear()                           |
| + height() : int                    |
| + width() : int                     |
| + size() : int                      |
| + xyToIndex(x : int, y : int) : int |
| + indexToX(index : int) : int       |
| + indexToY(index : int) : int       |
| + getGameOver() : bool              |
| + setGameOver(b : bool)             |
| + getDefaultTile() : Tile*          |
| + tile(index : int) : Tile*         |
| + tile(x : int, y : int) : Tile*    |
| + getWorldMap() : Map*              |
| + getMapItem() : Item               |