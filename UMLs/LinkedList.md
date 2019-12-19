| ListNode<T>           |
| --------------------- |
|                       |
|                       |
| + T data              |
| + next : ListNode<T>* |
| + ListNode(d : T)     |

| LinkedList<T>                |
| ---------------------------- |
|                              |
| - head : ListNode<T>*        |
| - listSize : int             |
|                              |
| + LinkedList()               |
| + ~LinkedList()              |
| + empty() : bool             |
| + size() : int               |
| + contains() : bool          |
| + insert(data: T)            |
| + remove(data : T)           |
| + move(list : LinkedList<T>) |
| - clear()                    |
| + print(os : ostream)        |
| + operator bool              |