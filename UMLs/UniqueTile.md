| UniqueTile : Tile                   |
| ----------------------------------- |
|                                     |
| - fileName : string                 |
| - name : string                     |
| - token : char                      |
| - wall : bool                       |
|                                     |
| + UniqueTile(Position p, string fn) |
| + read(istream& ns)                 |
| + isWall() : bool                   |
| + toChar() : char                   |
| + toString() : string               |