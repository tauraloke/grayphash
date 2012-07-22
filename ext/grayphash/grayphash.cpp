    #include <ruby.h>
    #include <CImg.h>
    using namespace cimg_library;


    // Use this typedef to make the compiler happy when
    // calling rb_define_method()
    typedef VALUE (ruby_method)(...);
    typedef unsigned long long ulong64;

    extern "C" VALUE t_init(VALUE self, VALUE file)
    {
		Check_Type(file, T_STRING);
        rb_iv_set(self, "@file", file);

        return self;
    }

    extern "C" VALUE t_about(VALUE self)
    {
        return rb_str_new_cstr("pHash 0.9.4. Copyright 2008-2010 Aetilius, Inc. Included only some image functions (grayphash v-0.0.7).");
    }


    CImg<float>* ph_dct_matrix(const int N){
        CImg<float> *ptr_matrix = new CImg<float>(N,N,1,1,1/sqrt((float)N));
        const float c1 = sqrt(2.0/N); 
        for (int x=0;x<N;x++){
        for (int y=1;y<N;y++){
            *ptr_matrix->data(x,y) = c1*cos((cimg::PI/2/N)*y*(2*x+1));
        }
        }
        return ptr_matrix;
    }

    int ph_dct_imagehash(const char* file,ulong64 &hash){

        if (!file){
        return -1;
        }
        CImg<uint8_t> src;
        try {
        src.load(file);
        } catch (CImgIOException ex){
        return -1;
        }
        CImg<float> meanfilter(7,7,1,1,1);
        CImg<float> img;
        if (src.spectrum() == 3){
            img = src.RGBtoYCbCr().channel(0).get_convolve(meanfilter);
        } else if (src.spectrum() == 4){
        int width = img.width();
            int height = img.height();
            int depth = img.depth();
        img = src.crop(0,0,0,0,width-1,height-1,depth-1,2).RGBtoYCbCr().channel(0).get_convolve(meanfilter);
        } else {
        img = src.channel(0).get_convolve(meanfilter);
        }

        img.resize(32,32);
        CImg<float> *C  = ph_dct_matrix(32);
        CImg<float> Ctransp = C->get_transpose();

        CImg<float> dctImage = (*C)*img*Ctransp;

        CImg<float> subsec = dctImage.crop(1,1,8,8).unroll('x');;
       
        float median = subsec.median();
        ulong64 one = 0x0000000000000001;
        hash = 0x0000000000000000;
        for (int i=0;i< 64;i++){
        float current = subsec(i);
            if (current > median)
            hash |= one;
        one = one << 1;
        }
      
        delete C;

        return 0;
    }

    extern "C" VALUE t_phash(VALUE self) {
        VALUE lfile = rb_iv_get(self, "@file");
        char* file = RSTRING_PTR(lfile);
        ulong64 phash = 0;
        ph_dct_imagehash(file, phash);

        if(phash==0)
            rb_raise(rb_eFatal, "PHash cannot be 0 but it calcutaled as it. Probably you load PNG file with transparency.");
        
        rb_iv_set(self, "@phash", ULL2NUM(phash));

        return ULL2NUM(phash);
    }



    extern "C" VALUE t_hamming(VALUE self, VALUE phash1, VALUE phash2) {
        //Check_Type(phash1, T_BIGNUM);
        //Check_Type(phash2, T_BIGNUM);

        ulong64 hash1 = rb_num2ull(phash1);
        ulong64 hash2 = rb_num2ull(phash2);

        ulong64  x = hash1^hash2;
        const ulong64  m1  = 0x5555555555555555ULL;
        const ulong64  m2  = 0x3333333333333333ULL;
        const ulong64  h01 = 0x0101010101010101ULL;
        const ulong64  m4  = 0x0f0f0f0f0f0f0f0fULL;
        x -= (x >> 1) & m1;
        x = (x & m2) + ((x >> 2) & m2);
        x = (x + (x >> 4)) & m4;
        return INT2NUM((x * h01)>>56);
    }


    VALUE Grayphash;

    extern "C" void Init_grayphash() 
    {
        Grayphash = rb_define_class("Grayphash", rb_cObject);
        rb_define_method(Grayphash, "initialize", (ruby_method*) &t_init, 1);
        rb_define_method(Grayphash, "about", (ruby_method*) &t_about, 0);
        rb_define_method(Grayphash, "phash", (ruby_method*) &t_phash, 0);
        rb_define_method(Grayphash, "hamming", (ruby_method*) &t_hamming, 2);
    }

