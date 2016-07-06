GC.disable

assert('create balance') do
  b = Balance.new(50)
  assert_equal(b.number, 50)
end

assert('create collapse') do
  c = Collapse.new
  assert_equal(c.balance.number, 100)
end
