Grayphash is unstable simple gem for retrieving some functions from libpHash.so.

# Requirements

* Ruby
* Linux
* libpHash.so (you can find package `libphash0` in repos)

# How to get

`sudo gem install grayphash`

# How to use

Calculcate perceptive hash for image: 
```
require 'grayphash'
phash = Grayphash.image_phash('./pics/1.jpg')   # => 16162904659988308473

```

Calculate similarity:
```
similarity = 1 - (Grayphash.hamming(Grayphash.image_phash('./pics/4.jpg'), 		Grayphash.image_phash('./pics/3.jpg')).to_f)/64   # => 0.90625
```

# Stable alternatives

* pHash gem[pHash gem](https://github.com/toy/pHash/)
* Phashion gem[Phashion gem](https://github.com/mperham/phashion/)

