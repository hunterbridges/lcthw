class GhettoStack:
  def __init__(self):
      self.contents = []

  def push(self, val):
      self.contents = self.contents + [val]

  def pop(self):
      return self.contents.pop(len(self.contents) - 1)

stack = GhettoStack()
stack.push(1)
stack.push(2)
stack.push(3)

print stack.pop()
print stack.pop()
print stack.pop()
