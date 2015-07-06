#Indexer

## What ?
Given a large text file, indexer makes an index and stores it in binary. When a specific line is needed, it hits the index first, then the original file.

## Why ?
For huge files, loading up particular lines on demand is too time taking in the simple way. Indexer is one approach to load them faster.

## How to run  ?
> #### Compile
    $ gcc index.c -o index.o
> #### Make the index
    $ ./index.o -w source_file index_file
> #### Read a line
    $ ./index.o -r -l line_number source_file index_file
