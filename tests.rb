require 'test/unit'
require 'grayphash'

class TC_GrayphashTest < Test::Unit::TestCase
  def test_001_phash
    assert_equal phash('./pics/1.jpg'), 16162904659988308473
  end

  def test_002_about
    assert_equal Grayphash.about, 'pHash 0.9.4. Copyright 2008-2010 Aetilius, Inc. Included only some image functions (grayphash v-0.0.8).'
  end

  def test_003_phash
    assert_equal 6, Grayphash.hamming(phash('./pics/3.jpg'), phash('./pics/4.jpg'))
  end
end
