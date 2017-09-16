require 'bundler/gem_tasks'
require 'rake/extensiontask'
require 'rake/testtask'

Rake::ExtensionTask.new(:tuby) do |ext|
  ext.lib_dir = 'lib/tuby'
  ext.gem_spec = Gem::Specification.load('tuby.gemspec')
end

Rake::TestTask.new(:test) do |t|
  t.libs << 'test'
  t.libs << 'lib'
  t.test_files = FileList['test/**/*_test.rb']
end

Rake::Task[:test].prerequisites << :compile
task default: :test
