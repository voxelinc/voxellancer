function main() 
	showTextFor("Welcome to a mission script", 2.0)
	
	count = 10
	radius = 40
	
	for i = 1, count do
		local ship = createShip("basicship")
		local angle = (i/count) * (2 * math.pi)
		
		local position = vec3(-10 + math.cos(angle) * radius, -10 + math.sin(angle) * radius, -60)
		
		setPosition(ship, position)
		
		flyAnywhere(ship)		
		
		spawn(ship)
				
		onWorldObjectDestroyed(ship, "destroyed")
	end
	
	missionMessage("...and go!")
	
	createLoopingTimer("timeWarning", 10)
	createSingleShotTimer("timeout", 60)
end

function missionTitle() return "Kill'em all" end
function missionCaption() return "Hell is empty, and all the devils are here" end
function missionBriefing() return "Kill the ships, that's really not that difficult" end

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

function timeWarning() 
	missionMessage("Time is ticking, dude. Get your stuff done")
end

function onFailure() 
	missionFailureMessage("That really took too long.")
end

function onSuccess()
	missionSuccessMessage("Yeah, you're so awsome, dude!")
end

