| UniqueTile : Tile                   |
| ----------------------------------- |
|                                     |
| - fileName : string                 |
| - objectName : string               |
| - token : char                      |
| - wall : bool                       |
|                                     |
| + UniqueTile(Position p, string fn) |
| + read(istream& ns)                 |
| + isWall() : bool                   |
| + toChar() : char                   |
| + toString() : string               |
| + operator>>                        |