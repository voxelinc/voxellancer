function main() 	
	h = onAABBEntered(playerShip(), -50,-50,-100, 50,50,-20, "action")
	
end

function action(object) 
	p = position(playerShip())
	for i = 0, 10 do	
		s = createShip("basicship")
		setPosition(s, p.x - 50 + i * 10, p.y, p.z - 50)
		spawn(s)
	end
end
