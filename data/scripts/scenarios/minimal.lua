function main() 	
	otherShip = createShip('basicship')
	setPosition(playerShip, 0, 0, -20)	
	spawn(otherShip)
end
