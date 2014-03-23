function main() 
	showTextFor("Welcome to a mission script", 2.0)
	
	ships = {}
	count = 6
	radius = 40
	
	playerPos = position(playerShip())
	
	for i = 1, count do
		local ship = createShip("basicship")
		print("Created ship with key", ship)
		local angle = (i/count) * (2 * math.pi)
		
		local position = vec3(playerPos.x - 10 + math.cos(angle) * radius, playerPos.y -10 + math.sin(angle) * radius, playerPos.z - 60)
		
		setPosition(ship, position)
		
		flyAnywhere(ship)		
		
		spawn(ship)
		ships[i] = ship
				
		onWorldObjectDestroyed(ship, "destroyed")
	end

	missionMessage("...and go!")
	
	playVoice("data/sound/mission/hell_is_empty.ogg")

	createSingleShotTimer("playGreetingVoice", 2)
	createSingleShotTimer("timeWarning1", 15)
	createSingleShotTimer("timeWarning2", 20)
	createSingleShotTimer("timeout", 40)
end

function missionTitle() 
	return "Kill'em all" 
end

function missionCaption() 
	return "Hell is empty, and all the devils are here" 
end

function missionBriefing() 
	return "Kill the ships, that's really not that difficult" 
end

function flyAnywhere(ship) 
	local task = createFlyToTask(ship)
	local position = position(ship)
	
	onAiTaskFinished(task, "nextTask")
	
	setTargetPoint(task, vec3(position.x + math.random(-100, 100), position.y + math.random(-100, 100), position.z + math.random(-100, 100)))			
end

function nextTask(task) 
	ship = taskExecutor(task)
	flyAnywhere(ship)
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

function timeWarning1() 
	missionMessage("Time is ticking, dude.")
	playVoice("data/sound/mission/time_is_ticking.ogg")
end

function timeWarning2() 
	missionMessage("Get your stuff done")
	playVoice("data/sound/mission/get_your_stuff_done.ogg")
end

function onFailure() 
	missionFailureMessage("That really took too long. You failed!")
	playVoice("data/sound/mission/that_took_too_long.ogg")

	for k, v in pairs(ships) do
		if valid(v) then
			remove(v)
		end
	end
end

function onSuccess()
	missionSuccessMessage("Yeah, you're so awsome, dude!")
	playVoice("data/sound/mission/youre_awesome.ogg")
end

