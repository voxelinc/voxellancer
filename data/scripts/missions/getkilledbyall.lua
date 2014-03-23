function main() 
	showTextFor("Welcome to another mission script", 2.0)
	
	ships = {}
	count = 5
	radius = 40
	
	playerPos = position(playerShip())
	
	for i = 1, count do
		local type
		if i > 3 then
			type = "eagle"
		else
			type = "mox"
		end
	
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
	
	createLoopingTimer("timeWarning", 7)
end

function missionTitle() 
	return "They will kill you" 
end

function missionCaption() 
	return "Now you have woken the dragon" 
end

function missionBriefing() 
	return "Kill the ships, and yep, that's difficult" 
end

function destroyed(ship) 
	count = count - 1
	if count == 0 then
		missionSucceed()
	end
end

function timeout() 
	missionFail()
end

function timeWarning() 
	missionMessage("You're not supposed to merely survive. Kill or be killed!")
end


