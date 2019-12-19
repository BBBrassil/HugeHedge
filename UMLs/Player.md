| Player                                              |
| --------------------------------------------------- |
|                                                     |
| - position : Position                               |
| - facing : int                                      |
| - inventory : LinkedList<Item>*                     |
|                                                     |
| + Player(Position p                                 |
| + getWorld() : World                                |
| + getX() : int                                      |
| + getY() : int                                      |
| + getFacing() : int                                 |
| + getTile(relative : int) : Tile*                   |
| + getCurrentTile() : Tile*                          |
| - face(relative : int                               |
| - move(relative : int                               |
| - actionText(relative : int ) :string               |
| + hasItem(item : Item) : bool                       |
| + collectItem(item : Item)                          |
| + collectAll(list : LinkedList<Item>)               |
| + mapFound(os : ostream)                            |
| + lookAt(tile : Tile*)                              |
| + mainMenu(os : ostream)                            |
| + optionsmenu(os : ostream)                         |
| + examineMenu(poi : PointOfInterest*, os : ostream) |
| + inventoryMenu(os : ostream)                       |
| + mapMenu(os : ostream)                             |