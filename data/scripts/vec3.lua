
-- vec3 utilities - available to all scripts

function vec3(x,y,z)
	v = { x = x, y = y, z = z }
	return v
end

function vadd(vec_a, vec_b)
	return vec3(vec_a.x + vec_b.x, vec_a.y + vec_b.y, vec_a.z + vec_b.z)
end

function vmul(vec, scalar)
    return vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar)
end

function vlength(vec) 
	return math.sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z)
end

function vnormalize(vec)
    return vmul(vec, 1.0/vlength(vec))
end

function vstring(vec)
    return "vec3(" .. vec.x .. ", " .. vec.y .. ", " .. vec.z .. ")"
end

function vprint(vec)
    print(vstring(vec))
end

function table_to_string(table)
	s = ""
	for key,value in pairs(table) do s = s .. tostring(key) .. ":" .. tostring(value) .. ", " end
	return s
end
