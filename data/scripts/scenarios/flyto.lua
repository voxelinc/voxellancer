function main() 
	z = -120
	createLoopingTimer("spawnNextShip", 3.0)
end

function spawnNextShip()
	ship = createShip("basicship")
	task = createFlyToTask(ship)
	
	setTargetPoint(task, -20, -20, z)
	
	setPosition(ship, 0, 0, -40)
	spawn(ship)
	
	z = z - 30
end
