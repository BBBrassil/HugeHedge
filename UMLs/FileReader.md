| FileReader                                      |
| ----------------------------------------------- |
|                                                 |
| - fileName : string                             |
| - file : ifstream                               |
|                                                 |
| + open(string s) : ifstream &                   |
| + close()                                       |
| + getline(string s) : string                    |
| - isComment(string s) : bool                    |
| - findDelimiter(string s, char delimiter) : int |
| + key(string s) : string                        |
| + value(string s) : string                      |


| FileException             |
| ------------------------- |
|                           |
| - fileName : string       |
|                           |
| + FileException(string s) |
| + getFileName() : string  |

| BadFormat                  |
| -------------------------- |
|                            |
| - fileName : string        |
|                            |
| + BadFormat (string s)     |
| + getFileName() : string s |

| BadValue                                    |
| ------------------------------------------- |
| - fileName : string                         |
| - keyName : string                          |
| - valueName: string                         |
|                                             |
| + BadValue(string fn, string kn, string vn) |
| + getFileName() : string                    |
| + getKeyName() : string                     |

| EmptyFile                  |
| -------------------------- |
|                            |
|                            |
| + EmptyFile(string s)      |

| EndOfFile                  |
| -------------------------- |
|                            |
|                            |
| + EndOfFile(string s)      |

| FileOpenFail               |
| -------------------------- |
|                            |
|                            |
| + FileOpenFail(string s)   |

| MissingValue                        |
| ----------------------------------- |
| - fileName : string                 |
| - keyName : string                  |
|                                     |
| + MissingData(string fn, string kn) |
| + getFileName() : string            |
| + getKeyName() : string             |