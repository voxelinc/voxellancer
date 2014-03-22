function main()
	reset(0)
end

function startMission(player)
	mission = missionStart("killemall")
	remove(missionStartArea)
	onMissionFailure(mission, "reset")
	onMissionSuccess(mission, "yodawg")
end

function reset(dummy) 
	missionStartArea = createWorldObject("missionstart")
	setPosition(missionStartArea, vec3(-40, 50, -100))
	spawn(missionStartArea)
	
	i = onAABBEntered(playerShip(), vec3(-60, 30, -120), vec3(-20, 70, -80), "startMission")
end

function yodawg(dummy)
	print("lol, mission over")
end
