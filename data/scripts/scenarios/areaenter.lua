function main() 	
	h = onAABBEntered(playerShip(), -50,-50,-100, 50,50,-20, "action")
end

function action(object) 
	for i = 0, 10 do	
		s = createShip("basicship")
		setPosition(s, -50 + i * 10, 0, -50)
		spawn(s)
	end
end
