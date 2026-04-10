# Run-length encoding

Implementation of Run-Length Encoding (RLE), a simple lossless compression algorithm that reduces consecutive repeated characters by storing a single character along with its count.

Depending on the input data, it can achieve very high compression ratios (up to ~100× in highly repetitive data), but may offer little to no compression on random or already compressed files.

Because C string handling can be a bit fragile, this implementation uses a slightly modified format:

### Original Format:

```
AAAAABBCCCCDDDD
```

### Encoded:

```
A:5:B:2:c:4:D:4
```

### Each sequence is stored as:

```
<count>:<character>
```

### To run:

```bash
gcc -o main main.c
./main <compress/decompress> <filepath>
```

### Output:

```
<filename><.compressed/.decompressed>
```