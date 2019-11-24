| World                                            |
| -------------------------------------------------|
|                                                  |
| - fileName : string                              |
| - tiles : Tile**                                 |
| - defaultTile : Tile*                            |
| - rowCount : int                                 |
| - colCount : int                                 |
| - tileCount : int                                |
|                                                  |
| + World(string s)                                |
| + ~World()                                       |
| - clear()                                        |
| - setSize()                                      |
| - setupTiles()                                   |
| + height() : int                                 |
| + width() : int                                  |
| + size() : int                                   |
| + getDefaultTile() : Tile&                       |
| + xyToIndex(const int& x, const int& y) : int    |
| + tile(const int& x, const int& y) : Tile&       |
| + operator()(const int& index) : Tile&           |
| + operator()(const int& x, const int& y) : Tile& |

| BadDimensions             |
| ------------------------- |
|                           |
| - fileName : string       |
|                           |
| + BadDimensions(string s) |
| + getFileName() : string  |

| EndOfFile                |
| ------------------------ |
|                          |
| - fileName : string      |
|                          |
| + EndOfFile(string s)    |
| + getFileName() : string |

| FileOpenFailure             |
| --------------------------- |
|                             |
| - fileName : string         |
|                             |
| + FileOpenFailure(string s) |
| + getFileName() : string    |