| IOManager                                        |
| ------------------------------------------------ |
|                                                  |
| - fileName : string                              |
| - fileStream : fstream                           |
|                                                  |
| + IOManager()                                    |
| + open(fn : string)                              |
| + openOut(fn : string)                           |
| + close()                                        |
| + file() : fstream                               |
| + getline(ns : istream, s : string) : istream    |
| + getlineEOF(ns : istream, s : string) : istream |
| + isComment(s : string) : bool                   |
| + keyFrom(s : string) : string)                  |
| + valueFrom(s : string) : string)                |