Grayphash is unstable simple gem for some functions from pHash library.

# Requirements

* Ruby
* CImg library

# How to get

Ubuntu example:
```
sudo apt-get install cimg-dev
sudo gem install grayphash
```
Compiling can take some minutes (0.5 - 2 minutes): slow CImg is slow.

# How to use

Calculcate perceptive hash for image: 
```
require 'grayphash'
phash = Grayphash.new('./pics/1.jpg').phash   # => 16162904659988308473

```

Calculate similarity:
```
a = Grayphash.new(('./pics/3.jpg')
b = Grayphash.new(('./pics/4.jpg')
similarity = 1 - (Grayphash.new(('./pics/4.jpg'), 	
 	Grayphash.image_phash('./pics/3.jpg')).to_f)/64   # => 0.90625
```

# Stable alternatives

* [pHash gem](https://github.com/toy/pHash/)
* [Phashion gem](https://github.com/mperham/phashion/)

# Licences:

* GPL3 for this wrapper.
* GPL3 for pHash code: see more at [pHash site](http://phash.org/licensing/)
* GNU GPL, GNU LPGL for CImg library: see more  at [CIimg FAQ](http://cimg.sourceforge.net/reference/group__cimg__faq.html#ssf15)
