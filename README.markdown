Prepend
--------------

(c) John Mair (banisterfiend) 
MIT license

Enables modules to be prepended to classes (or other modules). Methods
will then be looked up in module before the class.

** This is BETA software and has not yet been thoroughly tested, use
   at own risk **

install the gem: **for testing purposes only**
`gem install prepend`

example: 

    module M
        def hello
            puts "hello!"
        end
    end

    class A
        def hello
            puts "I feel only hate and loathing"
        end
        prepend M
    end

    # invoke class method
    A.new.hello #=> hello!
