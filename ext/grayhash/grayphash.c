// Include the Ruby headers and goodies
#include "ruby.h"
#include <dlfcn.h>

// Defining a space for information and references about the module to be stored internally
VALUE Grayphash = Qnil;

// Prototype for the initialization method - Ruby calls this, not you
void Init_grayphash();

VALUE method_about(VALUE self);
VALUE method_close(VALUE self);
VALUE method_image_phash(int argc, VALUE * argv, VALUE self);
VALUE method_hamming(int argc, VALUE * argv, VALUE self);
void* sdl_library = NULL;

// The initialization method for this module
void Init_grayphash() {
	Grayphash = rb_define_module("Grayphash");
	rb_define_method(Grayphash, "about", method_about, 0);
	rb_define_method(Grayphash, "close", method_close, 0);
    rb_define_method(Grayphash, "image_phash", &method_image_phash, -1);
    rb_define_method(Grayphash, "hamming", &method_hamming, -1);
  	sdl_library = dlopen("/usr/lib/libpHash.so", RTLD_LAZY);
}

VALUE method_hamming(int argc, VALUE * argv, VALUE self) {
	if (argc !=2) {  // there should only be 1 or 2 arguments
        rb_raise(rb_eArgError, "wrong number of arguments");
    }
	unsigned long long hash1 = rb_num2ull(argv[0]);
	unsigned long long hash2 = rb_num2ull(argv[1]);
	int* (*phash_func)();
	phash_func = dlsym(sdl_library, "ph_hamming_distance");

	return INT2FIX(
	  ((*phash_func)(hash1, hash2))
	  );
}


VALUE method_image_phash(int argc, VALUE * argv, VALUE self) {
	if(argc==0) return Qnil;
	char* file = StringValuePtr(*argv);
	unsigned long long hash = 0;
	int* (*phash_func)();
	phash_func = dlsym(sdl_library, "ph_dct_imagehash");
	((*phash_func)(file, &hash));

	return ULL2NUM(hash);
}

VALUE method_close(VALUE self) {
	if(dlclose(sdl_library)==0) {
		return Qtrue;
	}
	else {
		return Qfalse;
	}
}

VALUE method_about(VALUE self) {
	char* (*about)();
	about = dlsym(sdl_library, "ph_about");
	return rb_str_new_cstr((*about)());
}
