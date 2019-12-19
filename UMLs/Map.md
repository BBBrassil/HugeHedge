| MapItem        |
| -------------- |
|                |
|                |
| + tile : Tile* |
| + key : char   |

| Map                                 |
| ----------------------------------- |
|                                     |
| - mapContents : stringstream        |
| - world : World*                    |
| - count : int                       |
|                                     |
| + Map(w : World*)                   |
| - isOrdered(tile : Tile*)           |
| - getKey(tile : Tile*)              |
| - tocLine(key : char, tile : Tile*) |
| - read()                            |
| - print(os : ostream)               |