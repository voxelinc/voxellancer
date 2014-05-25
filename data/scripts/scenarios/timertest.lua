function main() 	
	count = 0
	createLoopingTimer('newShip', 5.0)
end

function newShip() 
	width = 10
	distance = 20

	x = count % width
	z = math.floor(count / width)
	
	otherShip = createShip('eagle')
	setPosition(otherShip, vec3(x * distance - distance * width/2, -30 + z * 5, -100 - z * distance))
	spawn(otherShip, "backen")
    
    task = createFlyToTask(otherShip)	
	setTargetPoint(task, vec3(-20 + distance*5000, -20, -100 - z*distance*13))
	
	count = count + 1
end
