puts "start"

puts "disabled GC"
puts ""

c = Collapse.new
puts "collapse_new"
puts "c: #{c}"
puts "c.balance: #{c.balance}"
puts "c.balance.class: #{c.balance.class}"
puts "c.balance.get_value: #{c.balance.get_value}"
puts "c.object_id: #{c.object_id}"
puts "c.balance.object_id: #{c.balance.object_id}"
puts ""

b = Balance.new(3)
puts "balance_new"
puts "b.get_value: #{b.get_value}"
puts ""

1.times do
  ary = []
  100000.times do |i|
    if i == 2
      ary << Balance.new(5)
    else
      ary << 100
    end
  end
end

puts "GCstart\n"
GC.start
puts "GCend\n\n"

1.times do
  ary = []
  100000.times do |i|
    if i == 2
      ary << Balance.new(5)
    else
      ary << 100
    end
  end
end

puts "GCstart\n"
GC.start
puts "GCend\n\n"


puts "c: #{c}"
puts "c.balance: #{c.balance}"
puts "c.balance.class: #{c.balance.class}"
puts "##DANGER## c.balance.get_value: #{c.balance.get_value}"
puts "c.object_id: #{c.object_id}"
puts "c.balance.object_id: #{c.balance.object_id}"
puts ""
puts "end"
