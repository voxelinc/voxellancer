function main() 
	createLoopingTimer("spawnNextShip", 3.0)
end

function spawnNextShip()
	ship = createShip("basicship")
	task = createFlyToTask(ship)
	
	setTargetPoint(task, -20, -20, -100)
	
	setPosition(ship, 0, 0, -40)
end
