| Tile                                           |
| -----------------------------------------------|
|                                                |
| - position : Position                          |
|                                                |
| + _isWall() : bool_                            |
| + _toChar() : char_                            |
| + _toString() : string_                        |
| + getWorld() : World&                          |
| + getX() : int                                 |
| + getY() : int                                 |
| + north() : Tile&                              |
| + east() : Tile&                               |
| + south() : Tile&                              |
| + west() : Tile&                               |
| operator()(const int& x, const int& y) : Tile& |
| operator()(const int& cardinal) : Tile&        |
| operator<<(ostream& os, Tile& t) : ostream     |
