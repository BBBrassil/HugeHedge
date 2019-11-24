# HugeHedge
A text-based adventure game in which the player is trapped in a maze.

## Requirements

>Your final project should demonstrate: 
>* Header files
>* Abstract Class
>* Subclasses 
>* Virtual function (in addition to the pure virtual function)
>* Inheritance
>* Polymorphism
>* Pointers
>* Static variables 
>* Static functions
>* Exceptions
>* Templates
>* File I/O 
>* Overloaded << or >> operator
>* Overloaded operators (at least one additional)
>
>Extra points for:
>* Recursion
>* Linked lists / Stacks / Queues
>* Binary search trees
>* Binary File with random access
>* A friend function not related to the << and >> operator
>Don’t forget: analysis, design, testing, pseudocode & documentation!!!

## Proposal
**Concept**:
A text-based adventure game in which the player is trapped in a maze. To escape, the player will have to locate the tile with the exit and find the key to unlock it.

The player will navigate the maze through the console, without visual cues. At each stage, their options will be to inspect any objects occupying the tile at their current location, or move to a neighboring tile. They will move in a relative direction (right, left, forward, or back) and their options will depend on which tiles are walls or traversable paths.

Items will be hidden in the maze, some required to solve puzzles and others to help with navigation. For example, the player can find a map that will print the maze layout to a file, and they will need to find a key to unlock the exit.

The program is divided into three general aspects: the **World**, **Item** objects, and the **Player**.
The **World** will utilize:
* An abstract Tile class implemented by different types of tiles, such as walls, traversable paths, and tiles containing other objects for the player to interact with
* Static variables and functions, such as the description of a tile type and whether it is a wall.
* File I/O, reading from a file to initialize the maze layout, and writing to a file when the player finds a Map item to help them navigate the maze.
* Overloaded >> and << operators to help with the above.
* Overloaded ++ and — operators to make iterating through tiles easier and avoid out of bounds issues.

**Items** will utilize:
* An Item class with different subclasses of items like a Key or a Map.
* Virtual functions, such as with item description. A generic item might have a simple toString() function, while a Weapon could list its stats.
* Pointers—e.g. a door will need to know which key unlocks it.

The **Player** will interact with the World and Items by:
* Looking at objects to see how they can interact with them, possibly handled with friend functions.
* Collecting Item objects. The inventory system might utilize a linked list.
* Solving puzzles that will lead them to find the Key that unlocks the Door on the exit Tile to escape the maze.
