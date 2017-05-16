# lengd
Generate Read Length Histrogram Data

## Install

#### Clone from GitHub

```
git clone --recursive https://github.com/dantaki/lengd.git
```

#### Compile with [CMake](https://cmake.org/)

```
cd lengd/
mkdir build && cd build/

cmake .. && make 
```

##### Binary executable found under `lengd/build/src/lengd`

## Usage 

lengd records the number of aligned base pairs for a read. 

`lengd --help`

```
lengd        generate read length histogram data
Version: 1.0    Author: Danny Antaki <dantaki@ucsd.edu>

Usage: lengd -i <in.bam> -q <INT> -o <output.txt>

Options:
    -i        Input: BAM filename
    -q        Mapping quality threshold [10]
    -o        Output: filename
```

## Output

| CONTIG | READ LENGTH | FREQUENCY |
| ------ | ----------- | --------  |
|   1    |     150     |    20     |
|   2    |     150     |    21     | 
| GENOME |     150     |    41     | 

## Acknowledgements

lengd uses [BamTools](https://github.com/pezmaster31/bamtools)

> *BamTools*
> Copyright (c) 2009-2010 Derek Barnett, Erik Garrison, Gabor Marth, Michael Stromberg

Notice: BamTools requires [zlib](http://zlib.net/).

## License

MIT License

Copyright (c) 2017 Danny Antaki

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Contact

dantaki@ucsd.edu
