function main() 	
	z = 0;
	
	ship0 = createShip('eagle')
	ship1 = createShip('eagle')
	setPosition(ship0, 0, 0, z)
	setPosition(ship1, 0, 0, z)
	
	while true do
		z = z - 1
		setPosition(ship0, 0, 0, z)
		s = spawn(ship0)
		if s then
			break
		end		
	end
		
	z = 0;
	while true do
		z = z + 1
		setPosition(ship1, 0, 0, z)
		s = spawn(ship1)
		if s then
			break
		end		
	end
end


