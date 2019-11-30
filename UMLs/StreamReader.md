| StreamReader                                    |
| ----------------------------------------------- |
|                                                 |
| - fileName : string                             |
| - fileStream : ifstream                         |
|                                                 |
| + StreamReader()                                |
| + open(string s)                                |
| + close()                                       |
| + file() : ifstream&                            |
| + `getline(istream& ns, string& s)`             |
| + `getlineEOF(istream& ns, string& s)`          |
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