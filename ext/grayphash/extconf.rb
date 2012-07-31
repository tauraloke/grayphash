# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'
    
# Give it a name
extension_name = 'grayphash'

# The destination
#dir_config(extension_name)

if RUBY_PLATFORM =~ /mingw/
  paths = ["/usr/local/lib", "/usr/pkg/lib", "/usr/lib"]
  find_library("gdi32", "SetDIBitsToDevice", *paths)
end

# Do the work
create_makefile("#{extension_name}/#{extension_name}")
