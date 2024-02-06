//p = position (relative to world space)
//lp = local position (relative to object center)
//sp = screen position (relative to screen space)
//s = scale
//c = custom (4 custom floats set by a programmer)
vec4 EmptyTexture(vec3 p, vec3 lp, vec3 sp, vec4 c)
{
	vec4 result = vec4(1, 1, 1, 1);
	return result;
}