| Tile                                          |
| ----------------------------------------------|
|                                               |
| - position : Position                         |
|                                               |
| + Tile(Position p)                            |
| + _read(istream& ns)_                         |
| + _toString() : string_                       |
| + _toChar() : char_                           |
| + _isWall() : bool_                           |
| + getWorld() : World&                         |
| + getX() : int                                |
| + getY() : int                                |
| + north() : Tile&                             |
| + east() : Tile&                              |
| + south() : Tile&                             |
| + west() : Tile&                              |
| + operator()(int x, int y) : Tile&            |
| + operator()(int cardinal) : Tile&            |
| + operator<<(ostream& os, Tile& t) : ostream& |
| + operator>>(istream& ns, Tile& t) : istream& |