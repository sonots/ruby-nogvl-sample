require 'nogvl'

Signal.trap("INT") {|signo| puts "Ctrl-C"; exit }
Nogvl.infinite_loop
