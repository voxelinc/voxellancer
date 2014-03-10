function main() 
	z = -120
	createLoopingTimer("spawnNextShip", 3.0)
	createSingleShotTimer("welcome", 0.5)
end

function welcome()
    showText("Welcome to the Flyto Scenario")
end

function spawnNextShip()
	ship = createShip("basicship")
	task = createFlyToTask(ship)
	
	setTargetPoint(task, -20, -20, z)
	
	setPosition(ship, 0, 0, -40)
	spawn(ship)
	
	z = z - 30
end
