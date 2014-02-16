function init() 	
	playerShip = createShip('specialbasicship')
	setPosition(playerShip, 0, 0, -20)	
	playerSetShip(playerShip)
	spawn(playerShip)
	
	otherShip = createShip('basicship')
	setPosition(playerShip, 0, 0, -20)	
	spawn(otherShip)
end
