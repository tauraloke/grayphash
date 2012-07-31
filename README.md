Grayphash is unstable simple gem for some functions from pHash library.

# Requirements

* Ruby
* CImg library
* Imagemagick for more stability

# How to get

Ubuntu example:
```
sudo apt-get install cimg-dev
sudo gem install grayphash
```
Compiling can take some minutes (0.5 - 2 minutes): slow CImg is slow.


Windows example:
You can use MinGW (it's just in ruby kit for windows). You also need Imagemagick if you want to use this gem.
And you need big library file CImg.h (just find it and copy to `%mingwpath%/include/`).

# How to use

Calculcate perceptive hash for image: 
```
require 'grayphash'
phash = Grayphash.phash('./pics/1.jpg')   # => 16162904659988308473
phash = phash('./pics/1.jpg')   # => 16162904659988308473

```

Calculate similarity:
```
a = './pics/3.jpg'
b = './pics/4.jpg'
similarity = 1 - Grayphash.hamming(phash(a), phash(b)).to_f / 64   # => 0.90625
```

# How it works
Grayphash is small ruby module which contains some methods from pHash library.
* `about()`               # returns info string about version.
* `phash(image_path)`     # calculate 64-bits perceptive hash for image. 
* `hamming(hash1, hash2)` # returns hamming distance between two numbers.

# Stable alternatives

* [pHash gem](https://github.com/toy/pHash/)
* [Phashion gem](https://github.com/mperham/phashion/)

# Licences:

* GPL3 for this wrapper.
* GPL3 for pHash code: see more at [pHash site](http://phash.org/licensing/)
* GNU GPL, GNU LPGL for CImg library: see more  at [cimg FAQ](http://cimg.sourceforge.net/reference/group__cimg__faq.html#ssf15)
