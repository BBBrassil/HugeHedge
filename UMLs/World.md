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

| FileException             |
| ------------------------- |
|                           |
| - fileName : string       |
|                           |
| + FileException(string s) |
| + getFileName() : string  |

| BadDimensions             |
| ------------------------- |
|                           |
|                           |
| + BadDimensions(string s) |

| EndOfFile                |
| ------------------------ |
|                          |
|                          |
| + EndOfFile(string s)    |

| FileOpenFailure             |
| --------------------------- |
|                             |
|                             |
| + FileOpenFailure(string s) |