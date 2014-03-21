function main() 
	showTextFor("Welcome to a mission script", 2.0)

	ship = createShip("mox")
	setPosition(ship, vec3(-10, -10, -40))
	spawn(ship)
	
	createSingleShotTimer("timeWarning", 5)
	createSingleShotTimer("timeout", 10)
end

function missionTitle() return "Kill'em all" end
function missionCaption() return "Hell is empty, and all the devils are here" end
function missionBriefing() return "Kill the ship, that's really not that difficult" end

function update(deltaSec) 
	if not valid(ship) then
		missionSucceeded()
	end
end

function timeout() 
	missionFailed()
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

