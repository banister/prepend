
$LOAD_PATH.unshift File.join(File.expand_path(__FILE__), '..')

require 'rake/clean'
require 'rake/gempackagetask'

# get the texplay version
require 'lib/prepend/version'

$dlext = Config::CONFIG['DLEXT']

CLEAN.include("ext/**/*.#{$dlext}", "ext/**/*.log", "ext/**/*.o", "ext/**/*~", "ext/**/*#*", "ext/**/*.obj", "ext/**/*.def", "ext/**/*.pdb")
CLOBBER.include("**/*.#{$dlext}", "**/*~", "**/*#*", "**/*.log", "**/*.o")

specification = Gem::Specification.new do |s|
  s.name = "prepend"
  s.summary = "Prepend modules in front of a class"
  s.version = Prepend::VERSION
  s.date = Time.now.strftime '%Y-%m-%d'
  s.author = "John Mair (banisterfiend)"
  s.email = 'jrmair@gmail.com'
  s.description = s.summary
  s.require_path = 'lib'
  s.platform = Gem::Platform::RUBY
  #s.platform = 'i386-mingw32'
  s.homepage = "http://banisterfiend.wordpress.com"
  s.has_rdoc = false

  s.extensions = ["ext/prepend/extconf.rb"]
  s.files =  ["Rakefile", "README.markdown", "CHANGELOG", 
              "lib/prepend.rb", "lib/prepend/version.rb"] +
  #  ["lib/1.9/prepend.so", "lib/1.8/prepend.so"] +
  FileList["ext/**/extconf.rb", "ext/**/*.h", "ext/**/*.c", "test/*.rb"].to_a 
end

Rake::GemPackageTask.new(specification) do |package|
  package.need_zip = false
  package.need_tar = false
end
