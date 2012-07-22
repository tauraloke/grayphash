require 'grayphash'

def test title, condition
  puts condition ? "[ Test `#{title}` is \033[32mcompleted!\033[0m ]" : "[ Test `#{title}` \033[31mfailed...\033[0m ]"  
end

a = Grayphash.new('./pics/1.jpg')
b = Grayphash.new('./pics/3.jpg')
c = Grayphash.new('./pics/4.jpg')
test "image_phash", a.phash==16162904659988308473
test "about", a.about!=nil
test "hamming", 6==c.hamming(c.phash,b.phash)

