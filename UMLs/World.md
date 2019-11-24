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
| + xyToIndex(const int& x, const int& y) : int    |
| + tile(const int& x, const int& y) : Tile&       |
| + getDefaultTile() : Tile&                       |
| + operator()(const int& index) : Tile&           |
| + operator()(const int& x, const int& y) : Tile& |