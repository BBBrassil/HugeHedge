| PointOfInterest : UniqueTile                |
| ------------------------------------------- |
|                                             |
| - inventory : LinkedList<Item>*             |
| - key : Item*                               |
| - reward : Item*                            |
| - unsolvedMessage : string                  |
| - solvedMessage : string                    |
| - requiresKey : bool                        |
| - solved : bool                             |
|                                             |
| + PointOfInterest(p : Position, fn : string |
| # hasReward() : bool                        |
| # seeUnsolvedMessage() : string             |
| # seeSolvedMessage() : string               |
| + addItem(item : Item)                      |
| + onEnter(player : Player, os : ostream)    |
| + onSolved(player : Player, os : ostream)   |
| + setSolved(s : bool)                       |
| + getKey() : Item                           |
| f operator<<                                |