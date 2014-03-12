require('math')

function main() 	
	z = 0
	
	ship0 = createShip('eagle')
	ship1 = createShip('eagle')
	setPosition(ship0, vec3(0, 0, z))
	setPosition(ship1, vec3(0, 0, z))
		
	anotherZ = -25
	anotherTimer = createLoopingTimer("another", 2.0)
	
	while true do
		z = z - 1
		setPosition(ship0, vec3(0, 0, z))
		s = spawn(ship0)
		if s then
			break
		end		
	end
		
	z = 0;
	while true do
		z = z + 1
		setPosition(ship1, vec3(0, 0, z))
		s = spawn(ship1)
		if s then
			break
		end		
	end
end

function another() 
	if math.abs(position(playerShip()).x) > 0 then
		print("player moved ", anotherTimer)
		setActive(anotherTimer, false)
		return
	end

	print("Spawning another 2 ship")
	ship0 = createShip('eagle')
	setPosition(ship0, vec3(-10, 0, anotherZ))
	spawn(ship0)
	
	ship1 = createShip('eagle')
	setPosition(ship1, vec3(10, 0, anotherZ))
	spawn(ship1)
	
	anotherZ = anotherZ - 25
end
