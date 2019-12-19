| _Tile_                                      |
| --------------------------------------------|
|                                             |
| - position : Position                       |
|                                             |
| + Tile(Position p)                          |
| + _getName() : string_                      |
| + _toString() : string_                     |
| + _toChar() : char_                         |
| + _isWall() : bool_                         |
| + onEnter(player : Player, os : ostream)    |
| + onExamined(player : Player, os : ostream) |
| + getWorld() : World*                       |
| + getX() : int                              |
| + getY() : int                              |
| + neighbor() : Tile*                        |
| + operator++                                |
| + operator--                                |
| f operator<<                                |