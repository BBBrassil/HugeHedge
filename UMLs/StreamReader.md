| StreamReader                                    |
| ----------------------------------------------- |
|                                                 |
| - fileName : string                             |
| - fileStream : ifstream                         |
|                                                 |
| + StreamReader()                                |
| + open(string s)                                |
| + close()                                       |
| + `getline(istream& ns, string& s)`             |
| - `isComment(string s) : bool`                  |
| + `keyFrom(string s) : string`                  |
| + `valueFrom(string s) : string`                |

| BadString                         |
| --------------------------------- |
|                                   |
| - badString : string              |
| - fileName : string               |
|                                   |
| + BadString (string s)            |
| + BadString (string s, string fn) |
| + getString() : string            |
| + getFileName() : string)         |

| EmptyStream                |
| -------------------------- |
|                            |
| - fileName : string        |
|                            |
| + EmptyStream()            |
| + EmptyStream(string fn)   |
| + getFileName() : string   |

| EndOfFile                  |
| -------------------------- |
|                            |
| - fileName : string        |
|                            |
| + EndOffile()              |
| + EndOfFile(string fn)     |
| + getFileName() : string   |

| FileOpenFail                |
| --------------------------- |
|                             |
| - fileName : string         |
|                             |
| + FileOpenFail(string fn)   |
| + getFileName() : string    |

| MissingValue : BadString            |
| ----------------------------------- |
|                                     |
|                                     |
| + MissingValue(string s)            |
| + MissingValue(string s, string fn) |