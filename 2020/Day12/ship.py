class Ship:
  def __init__(self, instructions):
    self.direction = 'E'
    self.positionShip = {'x': 0, 'y': 0}
    self.positionWaypoint = {'x': -10, 'y': 1}
    self.instructions = instructions
  
  def resetShip(self):
    self.direction = 'E'
    self.positionShip = {'x': 0, 'y': 0}
    self.positionWaypoint = {'x': -10, 'y': 1}

  def moveShip(self, item):
    if item['command'] == 'N' or item['command'] == 'F' and self.direction == 'N':
      self.positionShip['y'] += item['value']
    elif item['command'] == 'W' or item['command'] == 'F' and self.direction == 'W':
      self.positionShip['x'] += item['value']
    elif item['command'] == 'S' or item['command'] == 'F' and self.direction == 'S':
      self.positionShip['y'] -= item['value']
    elif item['command'] == 'E' or item['command'] == 'F' and self.direction == 'E':
      self.positionShip['x'] -= item['value']

  def rotateShip(self, item):
    dirs = ['E', 'S', 'W', 'N']
    value = round(item['value']/90)
    if item['command'] == 'R':
      self.direction = dirs[(dirs.index(self.direction) + value) % len(dirs)]
    else:
      self.direction = dirs[dirs.index(self.direction) - value]

  def executeInstructions(self):
    for item in self.instructions:
      if item['command'] in ['E', 'N', 'W', 'S', 'F']:
        self.moveShip(item)
      elif item['command'] in ['L', 'R']:
        self.rotateShip(item)

  def moveWaypoint(self, item):
    if item['command'] == 'N':
      self.positionWaypoint['y'] += item['value']
    elif item['command'] == 'W':
      self.positionWaypoint['x'] += item['value']
    elif item['command'] == 'S':
      self.positionWaypoint['y'] -= item['value']
    elif item['command'] == 'E':
      self.positionWaypoint['x'] -= item['value']
  
  def moveTowardsWaypoint(self, item):
    value = item['value']

    self.positionShip['x'] += value*self.positionWaypoint['x']
    self.positionShip['y'] += value*self.positionWaypoint['y']

  def rotateWaypoint(self, item):
    angle = item['value']
    if item['command'] == 'L':
      angle = 360 - angle
    if angle == 90:
      rotMat = [0, -1, 1, 0]
    elif angle == 180:
      rotMat = [-1, 0, 0, -1]
    else:
      rotMat = [0, 1, -1, 0]
    
    wayx = rotMat[0]*self.positionWaypoint['x'] + rotMat[1]*self.positionWaypoint['y']
    wayy = rotMat[2]*self.positionWaypoint['x'] + rotMat[3]*self.positionWaypoint['y']
    self.positionWaypoint['x'] = wayx
    self.positionWaypoint['y'] = wayy

  def executeInstructionsToWaypoint(self):
    for item in self.instructions:
      if item['command'] in ['E', 'N', 'W', 'S']:
        self.moveWaypoint(item)
      elif item['command'] in ['L', 'R']:
        self.rotateWaypoint(item)
      else:
        self.moveTowardsWaypoint(item)

  def getCurrentDistance(self):
    return abs(self.positionShip['x']) + abs(self.positionShip['y'])

  def printStatus(self):
    print("Current ship position ({}, {}), facing {}".format(self.positionShip['x'], self.positionShip['y'], self.direction))
    print("Current waypoint position ({}, {})".format(self.positionWaypoint['x'], self.positionWaypoint['y']))
