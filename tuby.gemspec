lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'tuby/version'

Gem::Specification.new do |spec|
  spec.name          = 'tuby'
  spec.version       = Tuby::VERSION
  spec.authors       = ['Kevin Deisz']
  spec.email         = ['kevin.deisz@gmail.com']

  spec.summary       = 'Tiny Ruby'
  spec.description   = 'A small language that compiles down to YARV.'
  spec.homepage      = 'https://github.com/kddeisz/tuby'
  spec.license       = 'MIT'

  spec.files         = `git ls-files -z`.split("\x0").reject do |f|
    f.match(%r{^(test|spec|features)/})
  end
  spec.bindir        = 'exe'
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']

  spec.add_development_dependency 'bundler', '~> 1.16.a'
  spec.add_development_dependency 'minitest', '~> 5.0'
  spec.add_development_dependency 'racc', '~> 1.4'
  spec.add_development_dependency 'rake', '~> 10.0'
  spec.add_development_dependency 'rake-compiler', '~> 1.0'
end
