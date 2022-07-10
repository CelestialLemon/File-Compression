# Lemon Archive
A CLI file archiver

## How to use
To Archive a file use command
```sh
LemonArchive encode huffman <input_filepath> <output_filepath>
```

To Extract a file use command
```sh
LemonArchive decode huffman <input_filepath> <output_filepath>
```

## Working
  The archiver uses Huffman Coding as a compression algorithm.
  > Huffman code is a particular type of optimal prefix code that is commonly used for lossless data compression. The output from Huffman's algorithm can be viewed as a variable-length code table for encoding a source symbol (such as a character in a file). The algorithm derives this table from the estimated probability or frequency of occurrence (weight) for each possible value of the source symbol. As in other entropy encoding methods, more common symbols are generally represented using fewer bits than less common symbols.

### Encoding
  We read the file in binary as a **string of bytes** i.e a char array. Then we count the frequncy of occurance of each character. The we need to assign variable length codes to each unique char to encode the string.
  To generate the codes we generate a heap for the symbols called a **Huffman Tree**. After we generate this tree we traverse it and generate the code for each symbol which is a leaf node in this tree.
  In huffman coding all codes have different prefixes so we can distinguish them during decoding.
  To arhive the file we now encode the original string of bytes by using these codes and save the symbol-code table and the encoded string in a ouput file.
  
### Decoding
  We read the file that has saved the symbol-code table and the encoded string from the encoding process. Decoding the string is simple. Convert the encoded string into
  a binary string of 0s and 1s. Then start reading from the beginning and compare it to the symbol table. If a match is found add the symbol-char to output string. If 
  the string doesn't match add the next char. Since all strings have unique prefixes we can be sure there is only one match to every string we read. Keep reading and 
  adding all the chars to get the complete decdoed string. Then convert this to an array of chars (bytes) and write it to an output file.
  
  ## Performance
  The app performs well and supports all file extensions. It performs best on files that don't have varied bytes. So text-files, log files etc. have higher compression ratio than images and videos.
  
  Some benchmarks for the compression ratio are provided below
  
  - Text File (.txt) ```15.6 MB -> 8.22 MB```
  - Image File (.bmp) ```1.67 MB -> 1.42 MB```
  - Image File (.jpg) ```1.82 MB -> 1.83 MB```
  - Document (.pdf) ```762 KB -> 760 KB```
  - Document (.docx) ```3.42 MB -> 3.41 MB```
  - Wonderdraft save file (.wdm) ```5.15 MB -> 4.02 MB```
  
