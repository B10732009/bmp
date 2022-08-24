# Reading and Saving BMP File in C #

Reading BMP file in pure c without external library.

---

#### BMP File Format ####

*Header (14 bytes)*
|  Name | Size (Byte)  | Index |  Description |
|  ----  | ----  | ---- | ---- |
| Signature | 2 | 0-1 | should be "BM" | 
| FileSize | 4 | 2-5 | total file size |
| Reserved | 4 | 6-9 | not used |
| DataOffset| 4 | 10-13 | where the pixel data start |

*Info Header (40 bytes)*
|  Name | Size (Byte)  | Index |  Description |
|  ----  | ----  | ---- | ---- |
| Size | 4 | 0-3 | info header size |
| Width| 4 | 4-7 | image width |
| Height| 4 | 8-11 | image height |
| Planes | 2 | 12-13 | number of plane = 1 |
| BitCount | 2 | 14-15 | bits per pixel |
| Compression | 4 | 16-19 | compression type |
| ImageSize | 4 | 20-23 | (compressed) image size |
| XpixelsPerM | 4 | 24-27 | horizontal resolution (pixel/meter) |
| YpixelsPerM | 4 | 28-31 | vertical resolution (pixel/meter) |
| ColorsUsed | 4 | 32-35 | number of actually used colors |
| ColorsImportant | 4 | 36-39 | number of important colors |

*Color Table*
present only when *BitCount* < 8

*Pixels Data*
pixels data

---

#### Padding in BMP file ####
To make the number of bytes in each row become 4's multiple, BMP file will append some blank bytes at the end of row.

For example:
    
    width = 3
    R G B R G B R G B P P P
    bytes per row = 9 -> padding = 3

    width = 2
    R G B R G B P P
    bytes per row = 6 -> padding = 2

The formula will be:

    padding = (4 - ((*width) * 3) % 4) % 4

* when reading a BMP file, we need to jump over the *padding* to get the data at next line.
* when saving BMP file, we need to append *padding* at the end of each line, or the created image will be *"damaged"* due to wrong format. 

---