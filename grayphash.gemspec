# encoding: UTF-8

Gem::Specification.new do |s|
  s.name = 'grayphash'
  s.version = '0.0.1'
  s.description = %q{pHash image wrapper}
  s.email = %q{tauraloke@gmail.com}
  s.summary = %q{Simple wrapper for some pHash image functions}
  s.homepage = "http://github.com/tauraloke/#{s.name}"
  s.authors = ['Tauraloke']
  s.license = 'MIT'

  s.rubyforge_project = s.name

  s.files = Dir.glob('lib/**/*.rb') +
            Dir.glob('ext/**/*.{c,h,rb}')
  s.extensions = ['ext/grayhash/extconf.rb']
#  s.executables = ['grayhash']

  s.require_paths = %w[lib]

  s.add_development_dependency 'rspec'
  s.add_development_dependency 'fspath'
end
