function main() 
	showMessage("Welcome to another mission script")
	
	ships = {}
	count = 5
	radius = 40
	
	playerPos = position(playerShip())
	
	for i = 1, count do
		local type = "basicship"
		local ship = createShip(type)
		local angle = (i/count) * (2 * math.pi)
		
		local position = vec3(playerPos.x - 10 + math.cos(angle) * radius, playerPos.y -10 + math.sin(angle) * radius, playerPos.z - 60)
		
		setPosition(ship, position)
		
		task = createFightTask(ship)
		addFightTaskTarget(task, playerShip())		
		
		spawn(ship)
		ships[i] = ship
				
		onWorldObjectDestroyed(ship, "destroyed")
	end
	
	missionMessage("...and go!")
end

function missionTitle() 
	return "Leave the turtle be" 
end

function missionCaption() 
	return "The turtle has down thou no harm" 
end

function destroyed(ship) 
	count = count - 1
	if count == 0 then
		missionSucceed()
	end
end



