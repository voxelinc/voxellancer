function main()
	reset(0)
end

function startMission(player)
	local mission = missionStart("killemall")
	remove(missionStartBanner)
	onMissionFailure(mission, "reset")
	onMissionSuccess(mission, "firstChallengeTaken")
end

function startFightingMission(player)
	local mission = missionStart("getkilledbyall")
	remove(dareyouBanner)
	onMissionFailure(mission, "reset")
	onMissionSuccess(mission, "firework")
end

function reset(dummy) 
	missionStartBanner = createWorldObject("missionstart")
	setShowOnHud(missionStartBanner, true)
	setCanLockOn(missionStartBanner, false)

	setPosition(missionStartBanner, vec3(-40, 50, -100))
	spawn(missionStartBanner)
	
	onAABBEntered(playerShip(), vec3(-60, 30, -120), vec3(-20, 70, -80), "startMission")
end

function firstChallengeTaken(dummy)
	createSingleShotTimer("startSecondChallenge", 3)
end

function startSecondChallenge()
	print("lol, mission over")
	
	dareyouBanner = createWorldObject("idareyou")
	setShowOnHud(dareyouBanner, true)
	setCanLockOn(dareyouBanner, false)

	setPosition(dareyouBanner, vec3(-100, 50, -360))
	spawn(dareyouBanner)
	
	onAABBEntered(playerShip(), vec3(-120, 30, -380), vec3(-80, 70, -340), "startFightingMission")
end

function secondChallengeTaken(dummy) 
	createSingleShotTimer("firework", 3)
end

function firework()
	showMessage("Unbelievable, you survived! I got something for you!")
	playVoice("data/sound/mission/got_something.ogg")

	cake = createWorldObject("cake")
	setPosition(cake, vec3(0,0,-1000))
	setShowOnHud(cake, true)
	setCanLockOn(cake, false)
	spawn(cake)
end