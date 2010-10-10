direc = File.dirname(__FILE__)
require 'rubygems'
require "#{direc}/../lib/prepend"
require 'bacon'

describe 'prepend' do
  before do
    @m1 = Module.new {
      def hello
        :hello
      end
    }
  end

  it 'should make prepend a method on Module' do
    Module.method_defined?(:prepend).should.equal true
  end

  it 'should make module methods have precedence over class instance methods' do
    c = Class.new {
      def hello
        :bye
      end
    }
    c.new.hello.should.equal :bye
    c.send(:prepend, @m1)
    c.new.hello.should.equal :hello
  end

  it 'should make module 1 instance methods have precedence over module 2 instance methods' do
    m2 = Module.new {
      def hello
        :evil
      end
    }
    m2.send(:prepend, @m1)

    c = Class.new
    c.send(:prepend, m2)

    c.new.hello.should.equal :hello
  end
end


