function main()
	reset(0)
end

function startMission(player)
	local mission = missionStart("killemall")
	remove(missionStartArea)
	onMissionFailure(mission, "reset")
	onMissionSuccess(mission, "firstChallengeTaken")
end

function startFightingMission(player)
	local mission = missionStart("getkilledbyall")
	remove(dareyou)
	onMissionFailure(mission, "reset")
	onMissionSuccess(mission, "firework")
end

function reset(dummy) 
	missionStartArea = createWorldObject("missionstart")
	setPosition(missionStartArea, vec3(-40, 50, -100))
	spawn(missionStartArea)
	
	onAABBEntered(playerShip(), vec3(-60, 30, -120), vec3(-20, 70, -80), "startMission")
end

function firstChallengeTaken(dummy)
	print("lol, mission over")
	
	dareyou = createWorldObject("idareyou")
	setPosition(dareyou, vec3(-100, 50, -160))
	spawn(dareyou)
	
	onAABBEntered(playerShip(), vec3(-120, 30, -180), vec3(-80, 70, -140), "startFightingMission")
end

function firework(dummy) 
	print("there be firework")
end
