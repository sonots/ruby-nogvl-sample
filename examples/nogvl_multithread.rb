require 'nogvl'

Signal.trap("INT") {|signo| puts "Ctrl-C"; exit }
Nogvl.multithread
