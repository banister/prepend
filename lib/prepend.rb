direc = File.dirname(__FILE__)

begin
  if RUBY_VERSION && RUBY_VERSION =~ /1.9/
    require "#{direc}/1.9/prepend"
  else
    require "#{direc}/1.8/prepend"
  end
rescue LoadError => e
  require 'rbconfig'
  dlext = Config::CONFIG['DLEXT']
  require "#{direc}/prepend.#{dlext}"
end

require "#{direc}/prepend/version"
