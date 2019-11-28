| UniqueTile : Tile                   |
| ----------------------------------- |
|                                     |
| - fileName : string                 |
| - wall : bool                       |
| - token : char                      |
| - name : string                     |
|                                     |
| + UniqueTile(Position p, string fn) |
| + read(istream& ns)                 |
| + isWall() : bool                   |
| + toChar() : char                   |
| + toString() : string               |