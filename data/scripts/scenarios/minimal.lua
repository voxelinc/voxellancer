function main() 	
	count = 0
	createLoopingTimer('newShip', 0.3)
end

function newShip() 
	width = 10
	distance = 20

	x = count % width
	z = math.floor(count / width)
	
	otherShip = createShip('eagle')
	setPosition(otherShip, x * distance - distance * width/2, -30 + z * 5, -100 - z * distance)
	spawnShip(otherShip)
	
	count = count + 1
end
